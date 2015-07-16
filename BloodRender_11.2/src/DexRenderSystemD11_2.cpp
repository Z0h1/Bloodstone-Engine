#include "DexRenderSystemD11_2.h"
#include "DexRenderComponentD11_2.h"
#include "DexRenderWindowD11_2.h"

using namespace DirectX;
using namespace Microsoft::WRL;

namespace Dex
{
	RenderSystemD11_2::RenderSystemD11_2(ofstream* logger, FileSystem* fileSystem)
		: RenderSystem("RENDER_SYSTEM_D11_1", logger, SystemsType::SYSTEM_RENDER_DIRECTX_11_2)
	{
		m_pFileSystem = fileSystem;
	}

	RenderSystemD11_2::~RenderSystemD11_2()
	{
		DrawLine("~RenderSystemD11_1: ������ DirectX 11.1 ��������");
	}

	string RenderSystemD11_2::GetErrorHR(HRESULT hr)
	{
		LPTSTR errorText = nullptr;
		string str;

		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&errorText, 0, nullptr);

		if (nullptr != errorText)
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

				DrawLine("RenderWindow_D11: \"device_type\" �������� �� ������ set D3D_DRIVER_TYPE_UNKNOWN", MT_ERROR);
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
			DrawLine("RenderSystemD11_1: ������ D3D11CreateDevice " + GetErrorHR(hr), MT_ERROR);

			m_bInit = false;
		}
		else {
			device.As(&m_d3dDevice);
			context.As(&m_d3dContext);

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
				DrawLine("CreateRenderWindow: ���� " + it->second + " ��� ����������", MT_WARNING);
			}
		}
		else
		{
			DrawLine("CreateRenderWindow: window_name �� ������� ��� ������������ ����!", MT_WARNING);
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