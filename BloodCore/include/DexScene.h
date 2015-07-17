#pragma once

#include "DexPreCompletion.h"
#include "DexCoreObject.h"
#include "DexRenderConnect.h"

namespace Dex
{
	typedef vector< SceneObject* >		_lSceneObject;
	typedef	vector< IRenderConnect* >	_lRenderConnect;

	class D_EXPORT Scene : public CoreObject
	{
	public:
		Scene(const string& cName, ofstream* logger);
		~Scene(void);

		SceneObject* CreateObject(const string& c_name, SceneObject* parent = nullptr);
		SceneObject* GetSceneObject(_32un id);
		void GetSceneObject(const string& c_name, _lSceneObject& so);
		void RemoveObject(const string& c_name);
		void RemoveObject(SceneObject* obj);
		void RemoveObject(_32un id);

		void GetSceneObjects(_lSceneObject& so);

		void AddRenderConnect(IRenderConnect* pConnect);
		void RemoveRenderConnect(IRenderConnect* pConnect);
		void GetRenderConnects(_lRenderConnect& rc);

	private:
		_lSceneObject		m_lSceneObject;
		_lRenderConnect		m_lRenderConnect;
	};
}