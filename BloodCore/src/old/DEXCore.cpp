#include "DEXCore.h"

DEXCore::DEXCore()
{
	nMemoryStep = 16;
}

DEX_PVOID DEXCore::NewMemory(DEX_UINT size_one_block)
{
	return NewMemory(size_one_block, 1);
}

DEX_PVOID DEXCore::NewMemory(DEX_UINT size_one_block, DEX_UINT count_block)
{
	if (!pMemory)
	{
		nMemoryMaxCount = nMemoryStep;

		pMemory = static_cast<DEX_PMemory>(malloc(nMemoryMaxCount * sizeof(DEXMemory)));
		nMemoryCount = 0;
	}

	if ((nMemoryCount + 1) > nMemoryMaxCount)
	{
		nMemoryMaxCount += nMemoryStep;
		pMemory = static_cast<DEX_PMemory>(realloc(pMemory, nMemoryMaxCount * sizeof(DEXMemory)));
	}

	DEX_PVOID m = malloc(count_block * size_one_block);

	if (!m)
	{
		//std::cout << "error memory allocation" << std::endl;
		return nullptr;
	}

	DEXMemory info_m;
	info_m.nCountBlock = count_block;
	info_m.nSizeOneBlock = size_one_block;
	info_m.pFirstAddres = m;

	pMemory[nMemoryCount] = info_m;
	nMemoryCount++;

	return m;
}

// Debug
void DEXCore::FreeAllMemory()
{
	if (!pMemory)
	{
		return;
	}

	for (int a = 0; a < nMemoryCount; a++)
	{
		DEXMemory m = pMemory[a];

		free(m.pFirstAddres);
	}

	free(pMemory);
	pMemory = nullptr;
	nMemoryCount = 0;
}

void DEXCore::PrintMemory(bool show)
{
	if (!pMemory)
	{
		//std::cout << "error memory" << std::endl;
		return;
	}

	float AllMemorySize = 0;

	for (int a = 0; a < nMemoryCount; a++)
	{
		DEXMemory m = pMemory[a];

		if (show)
		{
			//std::cout << m.pFirstAddres << " = " << m.nCountBlock << " * " << m.nSizeOneBlock << std::endl;
		}

		AllMemorySize += m.nCountBlock * m.nSizeOneBlock;
	}

	//std::cout << "Memory = " << (AllMemorySize / 1024) / 1024 << " mb, Count block = " << nMemoryCount << std::endl;
}

DEX_PClass DEXCore::InitSystem()
{
	return nullptr;
}

#include "DexConfigFile.h"
#include "DexDynamicLibrary.h"
#include "DexRenderSystem.h"
#include "DexInputSystem.h"
#include "DexScene.h"
#include "DexSceneObject.h"
#include "DexFileSystem.h"

namespace DEX
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
				if (it.second == "11.2")
				{
					ChangeSystem(SystemsType::SYSTEM_RENDER_DIRECTX_11_2);
				}
				else
				{
					DrawLine("Core: Неверный параметор! set_render_system");
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

		_lSystemsByType::iterator it_Systems = m_lSystems.begin();
		while (it_Systems != m_lSystems.end()) {
			ISystem* sys_ptr = it_Systems->second;

			RemoveSystem(sys_ptr);
			delete sys_ptr;
			it_Systems = m_lSystems.begin();
		}

		DrawLine("~Core: Завершение работы!");

		mLogger->close();
	}

	// Dynamic Library
	typedef void(*START_DLL_MODULE)(Core*);
	typedef void(*STOP_DLL_MODULE)(Core*);

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
				DrawLine("LoadModule: Модуль " + cModule + " не работает!", MessageTypes::MT_ERROR);
			}
		}
		else
		{
			DrawLine("LoadModule: Модуль " + cModule + " уже загружен", MT_WARNING);
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
			DrawLine("UnLoadModule: Модуль " + cModule + " не загружен", MessageTypes::MT_WARNING);
		}

		return false;
	}

	void Core::AddSystem(ISystem* s_ptr, bool set_def)
	{
		DrawLine("AddSystem(" + s_ptr->GetName() + ")");

		_lSystemsByType::iterator it = m_lSystems.find(s_ptr->GetType());
		if (it == m_lSystems.end()) {
			m_lSystems.insert(_lSystemsByType::value_type(s_ptr->GetType(), s_ptr));

			DrawLine("AddSystem: System " + s_ptr->GetName() + " loading");
		}
		else {
			DrawLine("AddSystem: System " + s_ptr->GetName() + " is loaded", MessageTypes::MT_WARNING);
		}

		if (set_def) {
			ChangeSystem(s_ptr->GetType());
		}
	}

	void Core::RemoveSystem(ISystem* s_ptr)
	{
		DrawLine("RemoveSystem(" + s_ptr->GetName() + ")");

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
			DrawLine("ChangeSystem: Данная система не инициализирована!", MessageTypes::MT_ERROR);
		}
		else {
			switch (eType)
			{
			case DEX::SYSTEM_RENDER_DIRECTX_9:
			case DEX::SYSTEM_RENDER_DIRECTX_11:
			case DEX::SYSTEM_RENDER_DIRECTX_11_1:
			case DEX::SYSTEM_RENDER_DIRECTX_11_2:
				if (m_pRenderSystem && m_pRenderSystem->GetType() == eType)
				{
					DrawLine("ChangeSystem: Данная система визуализации уже инициализирована!");
				}
				else
				{
					m_pRenderSystem = (RenderSystem*)m_lSystems[eType];
					DrawLine("ChangeSystem: Установлена системы визуализации " + m_pRenderSystem->GetName());
				}
				break;
			case DEX::SYSTEM_INPUT_DX:
				if (m_pInputSystem && m_pInputSystem->GetType() == eType)
				{
					DrawLine("ChangeSystem: Данная система ввода уже инициализирована!");
				}
				else
				{
					m_pInputSystem = (InputSystem*)m_lSystems[eType];
					DrawLine("ChangeSystem: Установлена системы ввода " + m_pInputSystem->GetName());
				}
				break;
			case DEX::SYSTEM_FILE_DEX:
				if (m_pFileSystem && m_pFileSystem->GetType() == eType)
				{
					DrawLine("ChangeSystem: Данная файловая система уже инициализирована!");
				}
				else
				{
					m_pFileSystem = (FileSystem*)m_lSystems[eType];
					DrawLine("ChangeSystem: Установлена файловая система " + m_pFileSystem->GetName());
				}
				break;
			default:
				DrawLine("ChangeSystem: не верный пораметор!", MessageTypes::MT_WARNING);
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
			m_lScene[cName] = new Scene(cName, mOutFileStream);
		}
		else
		{
			DrawLine("CreateScene: " + cName + " Уже сцществует", MessageTypes::MT_WARNING);
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

	RenderSystem* Core::GetRenderSystem()
	{
		return m_pRenderSystem;
	}

	InputSystem* Core::GetInputSystem()
	{
		return m_pInputSystem;
	}

	FileSystem* Core::GetFileSystem()
	{
		return m_pFileSystem;
	}
}