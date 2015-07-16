#pragma once

#include "DexPreComplitionD11_2.h"
#include "DexRenderComponent.h"
#include "DexShaderStructures.h"

namespace Dex
{
	class D_EXPORT_D11_1 RenderComponentD11_2 : public RenderComponent
	{
	public:
		RenderComponentD11_2(const string& c_name, SceneObject* parent, RenderSystemD11_2* system);
		~RenderComponentD11_2();

		virtual void LoadVertexShader(void* shader_code_ptr, _intun count_byte);
		virtual void LoadVertexLayout(_vertexLayouts& vertexLayouts, void* shader_code_ptr, _intun count_byte);
		virtual void LoadVertexBuffer(void* buffer, _intun _stride);
		virtual void LoadPixelShader(void* shader_code_ptr, _intun count_byte);
		virtual void LoadIndexBuffer(void* buffer, _intun size, IndexType type);

		ID3D11Buffer* const* GetVertexBuffer() const { return m_vertexBuffer.GetAddressOf(); }
		UINT GetStrideVertex() { return m_strideVertex; }
		UINT GetIndexCount() { return m_indexCount; }
		ID3D11Buffer* GetIndexBuffer() const { return m_indexBuffer.Get(); }
		ID3D11InputLayout* GetInputLayout() const { return m_inputLayout.Get(); }
		ID3D11VertexShader* GetVertexShader() const { return m_vertexShader.Get(); }
		ID3D11PixelShader* GetPixelShader() const { return m_pixelShader.Get(); }
		auto GetConstantBuffer() const { return m_constantBuffer; }
		ConstantBuffer_ModelViewProjection GetConstantBufferStruct() const { return m_constantBufferData; }
		void RefreshResource();
		void LoadResource();
		void ReleaseResource();

	private:
		UINT										m_indexCount;
		UINT										m_strideVertex;

		Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inputLayout;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_indexBuffer;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_vertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pixelShader;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_constantBuffer;

		ID3DBlob *pShaderCode;
		ID3DBlob *pShaderCodePS;

		ConstantBuffer_ModelViewProjection			m_constantBufferData;

		RenderSystemD11_2*							m_pRSystem;
	};
}