#pragma once

#include "DexPreCompletion.h"
#include "DexCoreObject.h"

#include <DexResourceManager.h>
#include <DexRenderSystem.h>
#include <DexInputSystem.h>

namespace Dex
{
	typedef std::map< String, Scene* >					_lScene;
	typedef std::map< String, DynamicLibrary* >			_lDynamicLibrary;
	typedef std::map< const SystemsType, ISystem* >		_lSystemsByType;

	class D_EXPORT Core : public CoreObject
	{
	public:
		Core(const String& cLog = "DexLog.html", const String& cConfig = "DexConfig.cfg");
		~Core(void);

		// Dynamic Library
		bool LoadModule(const String& cModule);
		bool UnLoadModule(const String& cModule);

		void AddSystem(const SystemsType st, void* s_ptr);
		void RemoveSystem(void* s_ptr);
		//const _lString& GetListAvailableSystem(const SystemsType st);
		void ChangeSystem(const SystemsType eType);

		// Scene System
		Scene* CreateScene(const String& cName);
		Scene* GetScene(const String& cName);

	private:
		IRenderSystem*				m_pRenderSystem;
		IInputSystem*				m_pInputSystem;

		_lDynamicLibrary			m_lDynamicLibrary;
		_lSystemsByType				m_lSystems;
		_lScene						m_lScene;

		OFStream*					mLogger;
		OFStream*					mStateDump;
	};
}