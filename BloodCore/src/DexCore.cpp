#include "DexCore.h"
#include "DexConfigFile.h"
#include "DexDynamicLibrary.h"
#include "DexResourceManager.h"
#include "DexScene.h"
#include "DexSceneObject.h"
#include "DexFileSystem.h"

namespace Dex
{
	Core::Core(const string& cLog, const string& cConfig)
		: CoreObject("CORE", new ofstream(cLog), WorkPriority::WP_MAIN)
	{
		mLogger = mOutFileStream;
		m_pRenderSystem = nullptr;
		m_pInputSystem = nullptr;
		m_pFileSystem = nullptr;

		AddSystem(new FileSystem(mLogger), true);

		ConfigFile* config = new ConfigFile(cConfig, mLogger);
		for (auto it : config->Get())
		{
			if (it.first == "load_module")
			{
				LoadModule(it.second);
			}
			else if (it.first == "set_render_system")
			{
				if (it.second == "DirectX_11" || it.second == "directX_11" || it.second == "Directx_11" || it.second == "directx_11"
					|| it.second == "DirectX 11" || it.second == "directX 11" || it.second == "Directx 11" || it.second == "directx 11"
					|| it.second == "DirectX11" || it.second == "directX11" || it.second == "Directx11" || it.second == "directx11"
					|| it.second == "11")
				{
					ChangeSystem(SystemsType::SYSTEM_RENDER_DIRECTX_11);
				}
				else if (it.second == "DirectX_9" || it.second == "directX_9" || it.second == "Directx_9" || it.second == "directx_9"
					|| it.second == "DirectX 9" || it.second == "directX 9" || it.second == "Directx 9" || it.second == "directx 9"
					|| it.second == "DirectX9" || it.second == "directX9" || it.second == "Directx9" || it.second == "directx9"
					|| it.second == "9")
				{
					ChangeSystem(SystemsType::SYSTEM_RENDER_DIRECTX_9);
				}
				else
				{
					DrawLine("Core: �������� ���������! set_render_system");
				}
			}
			else if (it.first == "set_input_system")
			{
				ChangeSystem(SystemsType::SYSTEM_INPUT_DX);
			}
			else if (it.first == "load_resource_folder")
			{
				m_pFileSystem->AddResourceFolder(it.second);
			}
			else if (it.first == "load_resource_archive")
			{
				//m_pFileSystem->AddResourceFolder(lConfig[i].cValue);
			}
		}

		DrawLine("Core: �������� ���������!");
	}

	Core::~Core(void)
	{
		_lDynamicLibrary::iterator it_DynamicLibrary;
		for (it_DynamicLibrary = m_lDynamicLibrary.begin(); it_DynamicLibrary != m_lDynamicLibrary.end(); ++it_DynamicLibrary)
		{
			UnLoadModule(it_DynamicLibrary->first);
		}
		m_lDynamicLibrary.clear();

		_lSystemsByType::iterator it_Systems = m_lSystems.begin();
		while (it_Systems != m_lSystems.end()) {
			ISystem* sys_ptr = it_Systems->second;

			RemoveSystem(sys_ptr);
			delete sys_ptr;
			it_Systems = m_lSystems.begin();
		}

		DrawLine("Core: ���������� ������!");

		mLogger->close();
	}

	// Dynamic Library
	typedef void (*START_DLL_MODULE)(Core*);
	typedef void (*STOP_DLL_MODULE)(Core*);

	bool Core::LoadModule(const string& cModule)
	{
		_lDynamicLibrary::iterator it_DynamicLibrary = m_lDynamicLibrary.find(cModule);

		if (it_DynamicLibrary == m_lDynamicLibrary.end())
		{
			DynamicLibrary* pModule = new DynamicLibrary(cModule, mLogger);

			if (pModule->CheckWork())
			{
				START_DLL_MODULE pFunc = (START_DLL_MODULE)pModule->GetAddress("Start_DexDynamicLibrary");
				pFunc(this);

				m_lDynamicLibrary[cModule] = pModule;

				return true;
			}
			else
			{
				DrawLine("Core: ������ " + cModule + " �� ��������!", MessageTypes::MT_ERROR);
			}
		}
		else
		{
			DrawLine("Core: ������ " + cModule + " ��� ��������", MT_WARNING);
		}

		return false;
	}

	bool Core::UnLoadModule(const string& cModule)
	{
		_lDynamicLibrary::iterator it_DynamicLibrary = m_lDynamicLibrary.find(cModule);

		if (it_DynamicLibrary != m_lDynamicLibrary.end())
		{
			STOP_DLL_MODULE pFunc = (STOP_DLL_MODULE)m_lDynamicLibrary[cModule]->GetAddress("Stop_DexDynamicLibrary");
			pFunc(this);

			return true;
		}
		else
		{
			DrawLine("Core: ������ " + cModule + " �� ��������", MessageTypes::MT_WARNING);
		}

		return false;
	}

	void Core::AddSystem(ISystem* s_ptr, bool set_def)
	{
		DrawLine("Core: AddSystem(" + s_ptr->GetName() + ")");

		_lSystemsByType::iterator it = m_lSystems.find(s_ptr->GetType());
		if (it == m_lSystems.end()) {
			m_lSystems.insert(_lSystemsByType::value_type(s_ptr->GetType(), s_ptr));

			DrawLine("Core: System " + s_ptr->GetName() + " loading");
		}
		else {
			DrawLine("Core: System " + s_ptr->GetName() + " is loaded", MessageTypes::MT_WARNING);
		}

		if (set_def) {
			ChangeSystem(s_ptr->GetType());
		}
	}

	void Core::RemoveSystem(ISystem* s_ptr)
	{
		DrawLine("Core: RemoveSystem(" + s_ptr->GetName() + ")");

		_lSystemsByType::iterator it = m_lSystems.find(s_ptr->GetType());
		if (it != m_lSystems.end())
		{
			if (m_pRenderSystem == s_ptr)
			{
				m_pRenderSystem = nullptr;
			}

			if (m_pInputSystem == s_ptr)
			{
				m_pInputSystem = nullptr;
			}

			if (m_pFileSystem == s_ptr)
			{
				m_pFileSystem = nullptr;
			}

			m_lSystems.erase(it);
		}
	}

	void Core::ChangeSystem(const SystemsType eType)
	{
		if (m_lSystems.find(eType) == m_lSystems.end()) {
			DrawLine("Core: ������ ������� �� ����������������!", MessageTypes::MT_ERROR);
		}
		else {
			switch (eType)
			{
			case Dex::SYSTEM_RENDER_DIRECTX_9:
			case Dex::SYSTEM_RENDER_DIRECTX_11:
				if (m_pRenderSystem && m_pRenderSystem->GetType() == eType)
				{
					DrawLine("Core: ������ ������� ������������ ��� ����������������!");
				}
				else
				{
					m_pRenderSystem = (IRenderSystem*)m_lSystems[eType];
					DrawLine("Core: ����������� ������� ������������ " + m_pRenderSystem->GetName());
				}
				break;
			case Dex::SYSTEM_INPUT_DX:
				if (m_pInputSystem && m_pInputSystem->GetType() == eType)
				{
					DrawLine("Core: ������ ������� ����� ��� ����������������!");
				}
				else
				{
					m_pInputSystem = (IInputSystem*)m_lSystems[eType];
					DrawLine("Core: ����������� ������� ����� " + m_pInputSystem->GetName());
				}
				break;
			case Dex::SYSTEM_FILE_DEX:
				if (m_pFileSystem && m_pFileSystem->GetType() == eType)
				{
					DrawLine("Core: ������ �������� ������� ��� ����������������!");
				}
				else
				{
					m_pFileSystem = (FileSystem*)m_lSystems[eType];
					DrawLine("Core: ����������� �������� ������� " + m_pFileSystem->GetName());
				}
				break;
			default:
				DrawLine("Core: ChangeSystem �� ������ ���������!", MessageTypes::MT_WARNING);
				break;
			}
		}
	}

	// Scene System
	Scene* Core::CreateScene(const string& cName)
	{
		_lScene::iterator it_Scene = m_lScene.find(cName);

		if (it_Scene == m_lScene.end())
		{
			m_lScene[cName] = new Scene(cName);
		}
		else
		{
			DrawLine("Core:CreateScene: " + cName + " ��� ����������", MessageTypes::MT_WARNING);
		}

		return m_lScene[cName];
	}

	Scene* Core::GetScene(const string& cName)
	{
		return m_lScene[cName];
	}

	ofstream* Core::GetLogger()
	{
		return mLogger;
	}

	ISystem* Core::GetSystem(const SystemsType st)
	{
		if (m_lSystems.find(st) == m_lSystems.end()) {
			return nullptr;
		}

		return m_lSystems[st];
	}
}