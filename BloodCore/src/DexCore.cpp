#include <DexCore.h>
#include <DexConfigFile.h>
#include <DexDynamicLibrary.h>
#include <DexResourceManager.h>
#include <DexScene.h>
#include <DexSceneObject.h>

namespace Dex
{
	Core::Core(const String& cLog, const String& cConfig)
		: CoreObject("CORE", nullptr, WorkPriority::WP_MAIN)
	{
		m_pRenderSystem = nullptr;
		m_pInputSystem = nullptr;

		mLogger = new OFStream(cLog);
		SetOutFileStream(mLogger);

		//m_pResourceManager = new ResourceManager();

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
					ChangeSystem(SystemsType::RENDER_SYSTEM_DIRECTX_11);
				}
				else if (it.second == "DirectX_9" || it.second == "directX_9" || it.second == "Directx_9" || it.second == "directx_9"
					|| it.second == "DirectX 9" || it.second == "directX 9" || it.second == "Directx 9" || it.second == "directx 9"
					|| it.second == "DirectX9" || it.second == "directX9" || it.second == "Directx9" || it.second == "directx9"
					|| it.second == "9")
				{
					ChangeSystem(SystemsType::RENDER_SYSTEM_DIRECTX_9);
				}
				else
				{
					DrawLine("Core: Неверный параметор! set_render_system");
				}
			}
			else if (it.first == "set_input_system")
			{
				ChangeSystem(SystemsType::INPUT_SYSTEM_DX);
			}
			else if (it.first == "load_resource_file")
			{
				//m_pFileSystem->AddResourceFolder(lConfig[i].cValue);
			}
			else if (it.first == "load_resource_zip")
			{
				//m_pFileSystem->AddResourceFolder(lConfig[i].cValue);
			}
		}

		DrawLine("Core: Загрузка завершена!");
	}

	Core::~Core(void)
	{
		_lDynamicLibrary::iterator it_DynamicLibrary;
		for (it_DynamicLibrary = m_lDynamicLibrary.begin(); it_DynamicLibrary != m_lDynamicLibrary.end(); ++it_DynamicLibrary)
		{
			UnLoadModule(it_DynamicLibrary->first);
		}
		m_lDynamicLibrary.clear();

		_lSystemsByType::iterator it_Systems;
		for (it_Systems = m_lSystems.begin(); it_Systems != m_lSystems.end(); ++it_Systems)
		{
			RemoveSystem(it_Systems->second);
		}
		m_lSystems.clear();

		DrawLine("Core: Завершение работы!");

		delete mLogger;
	}

	// Dynamic Library
	typedef void (*START_DLL_MODULE)(Core*);
	typedef void (*STOP_DLL_MODULE)(Core*);

	bool Core::LoadModule(const String& cModule)
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
				DrawLine("Core: Модуль " + cModule + " не работает!", MessageTypes::MT_ERROR);
			}
		}
		else
		{
			DrawLine("Core: Модуль " + cModule + " уже загружен", MT_WARNING);
		}

		return false;
	}

	bool Core::UnLoadModule(const String& cModule)
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
			DrawLine("Core: Модуль " + cModule + " не загружен", MessageTypes::MT_WARNING);
		}

		return false;
	}

	void Core::AddSystem(ISystem* s_ptr)
	{
		DrawLine("Core: AddSystem(" + s_ptr->GetName() + ")");

		_lSystemsByType::iterator it = m_lSystems.find(s_ptr->GetType());
		if (it == m_lSystems.end()) {
			s_ptr->SetOutFileStream(mLogger);
			m_lSystems.insert(_lSystemsByType::value_type(s_ptr->GetType(), s_ptr));

			DrawLine("Core: System " + s_ptr->GetName() + " loading");
		}
		else {
			DrawLine("Core: System " + s_ptr->GetName() + " is loaded", MessageTypes::MT_WARNING);
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

			m_lSystems.erase(it);
		}
	}

	void Core::ChangeSystem(const SystemsType eType)
	{
		if (m_lSystems.find(eType) == m_lSystems.end()) {
			DrawLine("Core: Данная система не инициализирована!", MessageTypes::MT_ERROR);
		}
		else {
			switch (eType)
			{
			case Dex::RENDER_SYSTEM_DIRECTX_9:
			case Dex::RENDER_SYSTEM_DIRECTX_11:
				if (m_pRenderSystem && m_pRenderSystem->GetType() == eType)
				{
					DrawLine("Core: Данная система визуализации уже инициализирована!");
				}
				else
				{
					m_pRenderSystem = (IRenderSystem*)m_lSystems[eType];
					DrawLine("Core: Установлена системы визуализации " + m_pRenderSystem->GetName());
				}
				break;
			case Dex::INPUT_SYSTEM_DX:
				if (m_pInputSystem && m_pInputSystem->GetType() == eType)
				{
					DrawLine("Core: Данная система ввода уже инициализирована!");
				}
				else
				{
					m_pInputSystem = (IInputSystem*)m_lSystems[eType];
					DrawLine("Core: Установлена системы ввода " + m_pInputSystem->GetName());
				}
				break;
			default:
				DrawLine("Core: ChangeRenderSystem не верный пораметор!", MessageTypes::MT_WARNING);
				break;
			}
		}
	}

	// Scene System
	Scene* Core::CreateScene(const String& cName)
	{
		_lScene::iterator it_Scene = m_lScene.find(cName);

		if (it_Scene == m_lScene.end())
		{
			m_lScene[cName] = new Scene(cName);
		}
		else
		{
			DrawLine("Core:CreateScene: " + cName + " Уже сцществует", MessageTypes::MT_WARNING);
		}

		return m_lScene[cName];
	}

	Scene* Core::GetScene(const String& cName)
	{
		return m_lScene[cName];
	}

	OFStream* Core::GetLogger()
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