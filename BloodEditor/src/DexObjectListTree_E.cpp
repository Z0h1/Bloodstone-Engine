#include "DexObjectListTree_E.h"
#include "DexSceneObject.h"

namespace Dex
{
	EObjectListTreeData::EObjectListTreeData(CoreObject* obj)
	{
		m_pObject = obj;
	}

	EObjectListTreeData::~EObjectListTreeData()
	{

	}

	CoreObject* EObjectListTreeData::GetObject()
	{
		return m_pObject;
	}

	EObjectListTree::EObjectListTree(ofstream* logger,
		wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
		long style, const wxValidator& validator, const wxString& name)
		: wxTreeCtrl(parent, id, pos, size, style, validator, name), CoreObject(name.ToStdString(), logger, WorkPriority::WP_STEP_1)
	{
	}

	EObjectListTree::~EObjectListTree()
	{

	}

	void EObjectListTree::SetEngine(Scene* s, IRenderSystem* r)
	{
		m_pScene = s;
		m_pRenderSystem = r;

		AddRoot(m_pScene->GetName());
		ExpandAll();
	}

	SceneObject* EObjectListTree::CreateSceneObject(const string& name)
	{
		if (m_pScene) {
			EObjectListTreeData* e_obj = new EObjectListTreeData(m_pScene->CreateObject(name));

			wxTreeItemId item = AppendItem(GetRootItem(), wxString(name.c_str()), -1, -1, e_obj);
			Expand(item);

			return (SceneObject*)e_obj->GetObject();
		}
		else {
			DrawLine("CreateSceneObject: Cцена не создана");
		}

		return nullptr;
	}

	CoreComponent* EObjectListTree::CreateObjectComponent(SceneObject* obj, const _lParametor& parametors)
	{
		CoreComponent* component = nullptr;
		string name = "";

		if (m_pScene && m_pRenderSystem) {
			_lParametor::const_iterator _p;

			_p = parametors.find("name");
			if (_p != parametors.end()) {
				name = _p->second;

				_p = parametors.find("type");
				if (_p != parametors.end()) {
					if (_p->second == "rander") {
						_p = parametors.find("primitive_type");
						if (_p != parametors.end()) {
							PrimitiveType p_type = PrimitiveType::PT_NULL;
							StringConverter::ParsePrimitiveType(_p->second, p_type);

							component = m_pRenderSystem->CreateRenderComponent(name, obj, p_type);
						}
						else {
							DrawLine("CreateObjectComponent: параметр primitive_type не указан");
						}
					}
					else if (_p->second == "camera") {
						_p = parametors.find("camera_focus");
						if (_p != parametors.end()) {
							component = new CameraComponent(name, obj, StringConverter::Parse_Point(_p->second));
						}
						else {
							DrawLine("CreateObjectComponent: параметр camera_focus не указан");
						}
					}
					else if (_p->second == "light") {
						_p = parametors.find("light_color");
						if (_p != parametors.end()) {
							Point4 color(0, 0, 0, 0);
							color = StringConverter::Parse_Point4(_p->second);

							_p = parametors.find("light_range");
							if (_p != parametors.end()) {
								component = new LightComponent(name, obj, color, StringConverter::Parse_Point(_p->second));
							}
							else {
								DrawLine("CreateObjectComponent: параметр light_range не указан");
							}
						}
						else {
							DrawLine("CreateObjectComponent: параметр light_color не указан");
						}
					}
					else {
						DrawLine("CreateObjectComponent: значение type неверное = rander/camera/light");
					}
				}
				else {
					DrawLine("CreateObjectComponent: параметр type не указан");
				}
			}
			else {
				DrawLine("CreateObjectComponent: параметр name не указан");
			}
		}
		else {
			DrawLine("CreateObjectComponent: Cцена не создана или системя визуализации не инициализирована");
		}

		if (component) {
			wxTreeItemId root = GetRootItem();

			wxTreeItemIdValue cookie;
			wxTreeItemId item = GetFirstChild(root, cookie);
			while (item.IsOk())
			{
				EObjectListTreeData* data = (EObjectListTreeData*)GetItemData(item);

				if (data->GetObject() == obj) {
					AppendItem(item, wxString(name.c_str()), -1, -1, new EObjectListTreeData(component));

					break;
				}

				item = GetNextChild(root, cookie);
			}
		}

		return component;
	}

	/*void EObjectListTree::FindAndAddObjectList(CoreObject* obj, CoreObject* add)
	{
		if (m_pObjectList) {
			wxTreeItemId root = m_pObjectList->GetRootItem();
			wxTreeItemIdValue cookie;
			wxTreeItemId item = m_pObjectList->GetFirstChild(root, cookie);

			while (item.IsOk())
			{
				EObjectListTreeData* data = (EObjectListTreeData*)m_pObjectList->GetItemData(item);

				if (data->GetObject() == obj) {
					m_pObjectList->AppendItem(item, DEX_TO_WX_NAME(add), -1, -1, new EObjectListTreeData(add));

					break;
				}

				item = m_pObjectList->GetNextChild(root, cookie);
			}
		}
	}*/
}