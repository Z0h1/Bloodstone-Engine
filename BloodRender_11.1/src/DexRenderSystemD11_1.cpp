#include "DexRenderSystemD11_1.h"
#include "DexRenderComponentD11_1.h"
#include "DexRenderWindowD11_1.h"

namespace Dex
{
	RenderSystemD11_1::RenderSystemD11_1(ofstream* logger)
		: IRenderSystem("RENDER_SYSTEM_D11_1", logger, SystemsType::SYSTEM_RENDER_DIRECTX_11_1)
	{
		HRESULT eResult = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&m_pFactory);

		if (SUCCEEDED(eResult))
		{
			// Enumerate All Render Driver
			IDXGIAdapter* pAdapter = nullptr;
			UINT nAdapter = 0;

			while (m_pFactory->EnumAdapters(nAdapter, &pAdapter) != DXGI_ERROR_NOT_FOUND)
			{
				DXGI_ADAPTER_DESC eAdapterDesc;

				pAdapter->GetDesc(&eAdapterDesc);

				wchar_t* cBuff_WCAHR = eAdapterDesc.Description;
				char cBuff_CHAR[128];

				WideCharToMultiByte(CP_UTF8, NULL, cBuff_WCAHR, 128, cBuff_CHAR, 128, NULL, NULL);

				string cAdapterName(cBuff_CHAR);
				DrawLine("RenderSystemD11_1: Обноруженно устройство " + cAdapterName);

				m_lDXGIAdapter.insert(_lDXGIAdapter::value_type(cAdapterName, pAdapter));

				nAdapter++;
			}

			DrawLine("RenderSystemD11_1: Модуль DirectX 11.1 инициализирован");

			// Выбор стандартного адаптера.. 0?
			//ID3D11Device* pDevice = NULL;
			//D3D_FEATURE_LEVEL eFeatureLevel;
			//D3D_FEATURE_LEVEL eFeatureLevels[] =
			//{
			//	D3D_FEATURE_LEVEL_11_1,
			//	D3D_FEATURE_LEVEL_11_0,
			//	D3D_FEATURE_LEVEL_10_1,
			//	D3D_FEATURE_LEVEL_10_0,
			//	D3D_FEATURE_LEVEL_9_3,
			//	D3D_FEATURE_LEVEL_9_2,
			//	D3D_FEATURE_LEVEL_9_1,
			//};

			//D3D11CreateDevice(m_lDXGIAdapter[0], D3D_DRIVER_TYPE_HARDWARE, NULL, 0, eFeatureLevels, 6, D3D11_SDK_VERSION, &pDevice, &eFeatureLevel, NULL);

			//IDXGIDevice* pDXGIDevice;
			//eResult = pDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);
			//if (FAILED(eResult))
			//{
			//	/*cError = DXGetErrorDescription(eResult);
			//	DrawLine("RenderSystem_D11:RenderSystem_D11 Ошибка - " + cError);*/
			//}

			//pDXGIDevice->GetAdapter(&pAdapter);

			//DXGI_ADAPTER_DESC eAdapterDesc;

			//pAdapter->GetDesc(&eAdapterDesc);
			//wchar_t* cBuff_WCAHR = eAdapterDesc.Description;
			//char cBuff_CHAR[128];

			//WideCharToMultiByte(CP_UTF8, NULL, cBuff_WCAHR, 128, cBuff_CHAR, 128, NULL, NULL);

			//string cAdapterName(cBuff_CHAR);

			//pAdapter->Release();
			//pDXGIDevice->Release();
			//pDevice->Release();

			//m_cActiveAdapter = cAdapterName;
		}
		else {
			wchar_t cBuff_WCAHR[256];
			char cBuff_CHAR[256];
			DXGetErrorDescription(eResult, cBuff_WCAHR, 256);
			WideCharToMultiByte(CP_ACP, NULL, cBuff_WCAHR, 256, cBuff_CHAR, 256, NULL, NULL);

			string str(cBuff_CHAR);
			str = str.substr(0, str.length() - 2);

			DrawLine("~RenderSystemD11_1: Ошибка - " + str);
		}
	}

	RenderSystemD11_1::~RenderSystemD11_1()
	{
		m_pFactory->Release();

		DrawLine("~RenderSystemD11_1: Модуль DirectX 11.1 выгружен");
	}

	RenderComponent* RenderSystemD11_1::CreateRenderComponent(const string& c_name, SceneObject* parent)
	{
		return new RenderComponentD11_1(c_name, parent);
	}

	void RenderSystemD11_1::GetAvailableDisplayMode(_lString& ls)
	{
	}

	void RenderSystemD11_1::GetAvailableAdpter(_lString& ls)
	{
		for (auto n : m_lDXGIAdapter)
		{
			ls.push_back(n.first);
		}
	}

	IRenderWindow* RenderSystemD11_1::CreateRenderWindow(const _lParametor& config)
	{
		_lParametor::const_iterator it;

		it = config.find("window_name");
		if (it != config.end())
		{
			_lWindow::iterator it_Window = m_lWindow.find(it->second);

			if (it_Window == m_lWindow.end())
			{
				RenderWindowD11_1* window = new RenderWindowD11_1(mOutFileStream, m_lDXGIAdapter[m_nAdapter]);

				if (window->Create(config))
				{
					m_lWindow[it->second] = window;

					return window;
				}
			}
			else
			{
				DrawLine("CreateRenderWindow: Окно " + it->second + " уже существует", MT_WARNING);
			}
		}
		else
		{
			DrawLine("CreateRenderWindow: window_name Не указано имя создаваемого окна!", MT_WARNING);
		}

		return nullptr;
	}

	void RenderSystemD11_1::RenderAllWindow(void)
	{
		for (auto n : m_lWindow)
		{
			RenderWindowD11_1* window = (RenderWindowD11_1*)n.second;

			if (window && window->IsActive()) {
				CameraComponent* camera = window->GetCamera();

				window->Render();
			}
		}
	}
}