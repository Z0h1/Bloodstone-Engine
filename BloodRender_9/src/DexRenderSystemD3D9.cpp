#include "DexRenderSystemD3D9.h"
#include "DexRenderWindowD3D9.h"
#include "DexRenderAdapterD3D9.h"
#include "DexScene.h"
#include "DexSceneObject.h"
#include "DexRenderConnect.h"
#include "DexRenderComponent.h"
#include "DexLightComponent.h"
#include "DexCameraComponent.h"
#include "DexCore.h"

namespace Dex
{
	RenderSystemD3D9::RenderSystemD3D9(ofstream* logger)
		: IRenderSystem("RENDER_SYSTEM_D9", logger, SystemsType::SYSTEM_RENDER_DIRECTX_9)
	{
		m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
		m_Adapter = D3DADAPTER_DEFAULT;

		InitSystem();
		EnumerationAdapter();

		DrawLine("RenderSystemD3D9: Модуль DirectX 9 инициализирован");
	}

	RenderSystemD3D9::~RenderSystemD3D9(void)
	{
		D_RELEASE(m_pD3D9);

		DrawLine("RenderSystemD3D9: Модуль DirectX 9 выгружен");
	}

	void RenderSystemD3D9::InitSystem(void)
	{
	}

	void RenderSystemD3D9::EnumerationAdapter(void)
	{
		for (UINT i = 0; i < m_pD3D9->GetAdapterCount(); i++)
		{
			m_lDriver.push_back(new RenderAdapterD3D9(mOutFileStream, i, m_pD3D9));

			m_lAdapter.push_back(m_lDriver[i]->GetName());
		}
	}

	void RenderSystemD3D9::GetAvailableDisplayMode(_lString& ls)
	{
		for (auto n : m_lDriver[m_Adapter]->GetDisplayMode()) {
			ls.push_back(n);
		}
	}

	void RenderSystemD3D9::GetAvailableAdpter(_lString& ls)
	{
		for (auto n : m_lAdapter) {
			ls.push_back(n);
		}
	}

	IRenderWindow* RenderSystemD3D9::CreateRenderWindow(const _lParametor& config)
	{
		_lParametor::const_iterator it;

		D3DDEVTYPE type = D3DDEVTYPE_HAL;

		it = config.find("device_type");
		if (it != config.end())
		{
			if (it->second == "Software")
			{
				type = D3DDEVTYPE_REF;
			}
		}

		it = config.find("window_name");
		if (it != config.end())
		{
			_lWindow::iterator it_Window = m_lWindow.find(it->second);

			if (it_Window == m_lWindow.end())
			{
				RenderWindowD3D9* window = new RenderWindowD3D9(mOutFileStream, m_Adapter, type, m_pD3D9);

				if (window->Create(config))
				{
					m_lWindow[it->second] = window;

					return window;
				}
			}
			else
			{
				DrawLine("RenderSystemD3D9: Окно " + it->second + " уже существует", MT_WARNING);
			}
		}
		else
		{
			DrawLine("RenderSystemD3D9: Не указано имя создаваемого окна!", MT_WARNING);
		}

		return nullptr;
	}

	void RenderSystemD3D9::RenderWindow(const string& cName)
	{
		IRenderConnect* pConnect = GetConnect(cName);

		g_sFocusRenderConnect* pFocus = pConnect->GetFocus();

		if (!pFocus)
		{
			return;
		}

		pConnect->Clear();
		pConnect->PreRender();

		pConnect->SetViewMatrix(pFocus->m_pFocusCameraComponent);

		_lSceneObject lSceneObject;
		pFocus->m_pFocusScene->GetSceneObjects(lSceneObject);
		for (auto i : lSceneObject)
		{
			_lObjectComponent lObjectComponent;
			i->GetObjectComponents(lObjectComponent);
			for (auto n : lObjectComponent)
			{
				switch (n->GetType())
				{
				case OCT_RENDER:
				{
					RenderComponent* pRenderComponent = (RenderComponent*)n;

					pConnect->RenderObject(pRenderComponent);
				}
				break;
				case OCT_LIGHT:
				{
					pConnect->SetLight(static_cast<LightComponent*>(n));
				}
				break;
				}
			}
		}

		pConnect->PostRender();
		pConnect->Present();
	}

	void RenderSystemD3D9::RenderAllWindow(void)
	{
		_lWindow::iterator it_Window;
		for (it_Window = m_lWindow.begin(); it_Window != m_lWindow.end(); ++it_Window)
		{
			RenderWindow(it_Window->first);
		}
	}

	IRenderWindow* RenderSystemD3D9::GetWindow(const string& cNameWindow)
	{
		return static_cast<IRenderWindow*>(m_lWindow[cNameWindow]);
	}

	IRenderConnect* RenderSystemD3D9::GetConnect(const string& cNameWindow)
	{
		return static_cast<IRenderConnect*>(m_lWindow[cNameWindow]);
	}
}