#include "DexRenderSystemD11_2.h"
#include "DexRenderComponentD11_2.h"
#include "DexRenderWindowD11_2.h"

using namespace DirectX;
using namespace Microsoft::WRL;

namespace Dex
{
	RenderSystemD11_2::RenderSystemD11_2(ofstream* logger, FileSystem* fileSystem)
		: RenderSystem("RENDER_SYSTEM_D11_2", logger, SystemsType::SYSTEM_RENDER_DIRECTX_11_2)
	{
		m_pFileSystem = fileSystem;
	}

	RenderSystemD11_2::~RenderSystemD11_2()
	{
		DrawLine("~RenderSystemD11_1: Модуль DirectX 11.1 выгружен");
	}

	string RenderSystemD11_2::GetErrorHR(HRESULT hr)
	{
		LPTSTR errorText = nullptr;
		string str;

		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&errorText, 0, nullptr);

		if (errorText)
		{
			str = errorText;
			str = str.substr(0, str.size() - 2);

			LocalFree(errorText);
			errorText = nullptr;
		}

		return str;
	}

	bool RenderSystemD11_2::Init(const _lParametor& config)
	{
		_lParametor::const_iterator parametor;
		HRESULT hr = S_FALSE;

		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;

		parametor = config.find("device_type");
		if (parametor != config.end())
		{
			if (parametor->second == "software")
			{
				driverType = D3D_DRIVER_TYPE_SOFTWARE;
			}
			else if (parametor->second == "warp") {
				driverType = D3D_DRIVER_TYPE_WARP;
			}
			else {
				driverType = D3D_DRIVER_TYPE_UNKNOWN;

				DrawLine("RenderWindow_D11: \"device_type\" параметр не указан set D3D_DRIVER_TYPE_UNKNOWN", MT_ERROR);
			}
		}

		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> context;

		// Create device
		hr = D3D11CreateDevice(
			nullptr,
			driverType,
			0,
			creationFlags,
			featureLevels,
			ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION,
			&device,
			&m_d3dFeatureLevel,
			&context
			);

		if (FAILED(hr))
		{
			DrawLine("RenderSystemD11_1: Ошибка D3D11CreateDevice " + GetErrorHR(hr), MT_ERROR);

			m_bInit = false;
		}
		else {
			device.As(&m_d3dDevice);
			context.As(&m_d3dContext);

			ComPtr<IDXGIDevice2> dxgiDevice;
			m_d3dDevice.As(&dxgiDevice);

			ComPtr<IDXGIAdapter> dxgiAdapter;
			dxgiDevice->GetAdapter(&dxgiAdapter);

			ComPtr<IDXGIFactory2> dxgiFactory;
			dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

			ComPtr<IDXGIAdapter> adapter;

			// Use the factory to create an adapter for the primary graphics interface (video card).
			hr = dxgiFactory->EnumAdapters(0, &adapter);
			if (FAILED(hr))
			{
				return false;
			}

			ComPtr<IDXGIOutput> adapterOutput;

			// Enumerate the primary adapter output (monitor).
			hr = adapter->EnumOutputs(0, &adapterOutput);
			if (FAILED(hr))
			{
				return false;
			}

			unsigned int numModes;

			// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
			hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
			if (FAILED(hr))
			{
				return false;
			}

			DXGI_MODE_DESC* displayModeList;

			// Create a list to hold all the possible display modes for this monitor/video card combination.
			displayModeList = new DXGI_MODE_DESC[numModes];
			if (!displayModeList)
			{
				return false;
			}

			// Now fill the display mode list structures.
			hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
			if (FAILED(hr))
			{
				return false;
			}

			// Now go through all the display modes and find the one that matches the screen width and height.
			// When a match is found store the numerator and denominator of the refresh rate for that monitor.
			for (int i = 0; i < numModes; i++)
			{
				stringstream sstr;
				sstr << displayModeList[i].Width << "x" << displayModeList[i].Height
					<< " Numerator = " << displayModeList[i].RefreshRate.Numerator << " Denominator = " << displayModeList[i].RefreshRate.Denominator;
				DrawLine(sstr.str());
				/*if (displayModeList[i].Width == (UINT)screenWidth)
				{
					if (displayModeList[i].Height == (UINT)screenHeight)
					{
						numerator = displayModeList[i].RefreshRate.Numerator;
						denominator = displayModeList[i].RefreshRate.Denominator;
					}
				}*/
			}

			// Release the display mode list.
			delete[] displayModeList;
			displayModeList = 0;

			m_bInit = true;
		}

		return m_bInit;
	}

	void RenderSystemD11_2::ISetAdapter()
	{
	}

	RenderComponent* RenderSystemD11_2::CreateRenderComponent(const string& c_name, SceneObject* parent)
	{
		RenderComponentD11_2* render_component = new RenderComponentD11_2(c_name, parent, this);
		m_lRenderComponentD11.push_back(render_component);

		return render_component;
	}

	void RenderSystemD11_2::GetAvailableDisplayMode(_lString& ls)
	{
	}

	void RenderSystemD11_2::GetAvailableAdpter(_lString& ls)
	{
	}

	RenderWindow* RenderSystemD11_2::CreateRenderWindow(const _lParametor& config)
	{
		_lParametor::const_iterator it;

		it = config.find("window_name");
		if (it != config.end())
		{
			_lWindow::iterator it_Window = m_lWindow.find(it->second);

			if (it_Window == m_lWindow.end())
			{
				RenderWindowD11_2* window = new RenderWindowD11_2(mOutFileStream, this);

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

	void RenderSystemD11_2::RenderOneWindow(RenderWindow* window)
	{
		RenderWindowD11_2* d3d_window = dynamic_cast<RenderWindowD11_2*>(window);

		if (d3d_window) {
			d3d_window->Render();
		}
	}

	void RenderSystemD11_2::ReloadWindow(RenderWindow* window)
	{
		RenderWindowD11_2* d3d_window = dynamic_cast<RenderWindowD11_2*>(window);

		if (d3d_window) {
			//d3d_window->RefreshResources();
		}
	}

	void RenderSystemD11_2::RefreshResources()
	{
		for (auto component : m_lRenderComponentD11)
		{
			component->RefreshResource();
		}
	}

	void RenderSystemD11_2::LoadResources()
	{
		for (auto component : m_lRenderComponentD11)
		{
			component->LoadResource();
		}
	}

	void RenderSystemD11_2::ReleaseResources()
	{
		for (auto component : m_lRenderComponentD11)
		{
			component->ReleaseResource();
		}
	}
}