#pragma once

#include "DexPreComplitionD11_2.h"
#include "DexRenderSystem.h"

namespace Dex
{
	typedef list<RenderComponentD11_2*>	_lRenderComponentD11;

	class D_EXPORT_D11_1 RenderSystemD11_2 : public RenderSystem
	{
	public:
		RenderSystemD11_2(ofstream* loggerm, FileSystem* fileSystem);
		~RenderSystemD11_2();

		static string GetErrorHR(HRESULT hr);

		virtual bool Init(const _lParametor& parametor);

		virtual RenderComponent* CreateRenderComponent(const string& c_name, SceneObject* parent);

		virtual void GetAvailableDisplayMode(_lString& ls);
		virtual void GetAvailableAdpter(_lString& ls);

		virtual RenderWindow* CreateRenderWindow(const _lParametor& config);

		virtual void RenderOneWindow(RenderWindow* window);
		virtual void ReloadWindow(RenderWindow* window);

		// D3D Accessors.
		ID3D11Device2*			GetD3DDevice() const { return m_d3dDevice.Get(); }
		ID3D11DeviceContext2*	GetD3DDeviceContext() const { return m_d3dContext.Get(); }
		D3D_FEATURE_LEVEL		GetDeviceFeatureLevel() const { return m_d3dFeatureLevel; }

		FileSystem* GetFileSystem() const { return m_pFileSystem; };

		void RefreshResources();
		void LoadResources();
		void ReleaseResources();

	private:
		virtual void ISetAdapter();

		FileSystem*										m_pFileSystem;
		_lRenderComponentD11							m_lRenderComponentD11;

		// D3D11.2 => win 8.1
		D3D_FEATURE_LEVEL								m_d3dFeatureLevel;
		Microsoft::WRL::ComPtr<ID3D11Device2>			m_d3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext2>	m_d3dContext;
	};
}