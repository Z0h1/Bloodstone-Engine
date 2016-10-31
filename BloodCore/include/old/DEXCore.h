#pragma once

#include "DEXPreCompletion.h"

class DEX_EXPORT DEXCore
{
public:
	DEXCore();

	DEX_PVOID NewMemory(DEX_UINT size_one_block);
	DEX_PVOID NewMemory(DEX_UINT size_one_block, DEX_UINT count_block);

	// Debug
	void FreeAllMemory();
	void PrintMemory(bool show = false);

	DEX_PClass InitSystem();

private:
	DEX_PMemory		pMemory;
	DEX_UINT		nMemoryCount;
	DEX_UINT		nMemoryMaxCount;
	DEX_UINT		nMemoryStep;
};

#include "DexCoreObject.h"

namespace DEX
{
	typedef map< string, Scene* >					_lScene;
	typedef map< string, DynamicLibrary* >			_lDynamicLibrary;
	typedef map< const SystemsType, ISystem* >		_lSystemsByType;

	class D_EXPORT Core : public CoreObject
	{
	public:
		Core(const string& cLog = "DexLog.log", const string& cConfig = "DexConfig.cfg");
		~Core(void);

		// Dynamic Library
		bool LoadModule(const string& cModule);
		bool UnLoadModule(const string& cModule);

		void AddSystem(ISystem* s_ptr, bool set_def = false);
		void RemoveSystem(ISystem* s_ptr);
		void ChangeSystem(const SystemsType eType);

		// Scene System
		Scene* CreateScene(const string& cName);
		Scene* GetScene(const string& cName);

		ofstream* GetLogger();
		ISystem* GetSystem(const SystemsType st);

		RenderSystem* GetRenderSystem();
		InputSystem* GetInputSystem();
		FileSystem* GetFileSystem();

	private:
		RenderSystem*			m_pRenderSystem;
		InputSystem*			m_pInputSystem;
		FileSystem*				m_pFileSystem;

		_lDynamicLibrary		m_lDynamicLibrary;
		_lSystemsByType			m_lSystems;
		_lScene					m_lScene;

		ofstream*				mLogger;
		ofstream*				mStateDump;
	};
}