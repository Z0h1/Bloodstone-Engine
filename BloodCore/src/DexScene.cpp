#include "DexScene.h"
#include "DexSceneObject.h"
#include "DexStringConverter.h"

namespace Dex
{
	Scene::Scene(const string& cName, ofstream* logger)
		: CoreObject(cName, logger, WorkPriority::WP_SYSTEM)
	{
		DrawLine("Scene " + cName + " инициализирована");
	}

	Scene::~Scene(void)
	{
		_lSceneObject::iterator it = m_lSceneObject.begin();
		while (it != m_lSceneObject.end()) {
			SceneObject* obj = *it;

			it = m_lSceneObject.erase(it);
			delete obj;
		}
	}

	SceneObject* Scene::CreateObject(const string& c_name, SceneObject* parent)
	{
		SceneObject* pObject = new SceneObject(c_name, this, m_lSceneObject.size(), GetOutFileStream(), parent);
		m_lSceneObject.push_back(pObject);

		return pObject;
	}
	SceneObject* Scene::GetSceneObject(_32un id)
	{
		for (auto n : m_lSceneObject)
		{
			if (n->GetId() == id) {
				return n;
			}
		}

		DrawLine("GetObjectById(" + StringConverter::toString(id) + ") обьект не найден", MessageTypes::MT_ERROR);
		return nullptr;
	}

	void Scene::GetSceneObject(const string& c_name, _lSceneObject& so)
	{
		for (auto n : m_lSceneObject)
		{
			if (n->GetName() == c_name) {
				so.push_back(n);
			}
		}
	}

	void Scene::GetSceneObjects(_lSceneObject& so)
	{
		so = m_lSceneObject;
	}

	void Scene::RemoveObject(const string& c_name)
	{
		_lSceneObject::iterator it = m_lSceneObject.begin();
		while (it != m_lSceneObject.end()) {
			SceneObject* obj = *it;

			if (obj->GetName() == c_name) {
				it = m_lSceneObject.erase(it);
				delete obj;
			}
		}
	}

	void Scene::RemoveObject(SceneObject* obj)
	{
		for (_lSceneObject::iterator i = m_lSceneObject.begin(); i != m_lSceneObject.end(); i++)
		{
			if (*i == obj) {
				m_lSceneObject.erase(i);
				break;
			}
		}
	}

	void Scene::RemoveObject(_32un id)
	{
		for (_lSceneObject::iterator i = m_lSceneObject.begin(); i != m_lSceneObject.end(); i++)
		{
			if ((*i)->GetId() == id) {
				m_lSceneObject.erase(i);
				break;
			}
		}
	}

	void Scene::AddRenderConnect(IRenderConnect* pConnect)
	{
		m_lRenderConnect.push_back(pConnect);
	}
	void Scene::RemoveRenderConnect(IRenderConnect* pConnect)
	{
		for (_lRenderConnect::iterator i = m_lRenderConnect.begin(); i != m_lRenderConnect.end(); i++)
		{
			if (*i == pConnect) {
				m_lRenderConnect.erase(i);
				break;
			}
		}
	}
	void Scene::GetRenderConnects(_lRenderConnect& rc)
	{
		for (auto n : m_lRenderConnect)
		{
			rc.push_back(n);
		}
	}
}