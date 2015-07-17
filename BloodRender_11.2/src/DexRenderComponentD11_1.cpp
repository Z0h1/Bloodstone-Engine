#include "DexRenderComponentD11_2.h"
#include "DexRenderSystemD11_2.h"
#include "DexCoreFile.h"
#include "DexFile.h"
#include "DexFileSystem.h"
#include "DexMath.h"

namespace Dex
{
	RenderComponentD11_2::RenderComponentD11_2(const string& c_name, SceneObject* parent, RenderSystemD11_2* system)
		: RenderComponent(c_name, parent)
	{
		m_pRSystem = system;

		m_vertexOffset = 0;
		m_indexCount = 0;
	}

	RenderComponentD11_2::~RenderComponentD11_2()
	{
		ReleaseResource();
	}

	void RenderComponentD11_2::RefreshResource()
	{
		ReleaseResource();
		LoadResource();
	}

	void RenderComponentD11_2::LoadResource()
	{

		if (!m_bGeometryLoaded) {
			LoadGeometry();
		}
	}

	void RenderComponentD11_2::ReleaseResource()
	{
		m_bGeometryLoaded = false;
		m_vertexOffset = 0;
		m_indexCount = 0;

		m_vertexShader.Reset();
		m_inputLayout.Reset();
		m_pixelShader.Reset();
		m_constantBuffer.Reset();
		m_vertexBuffer.Reset();
		m_indexBuffer.Reset();
	}

	void RenderComponentD11_2::LoadVertexShader(void* shader_code_ptr, _32un count_byte)
	{
		HRESULT hr = S_FALSE;

		hr = m_pRSystem->GetD3DDevice()->CreateVertexShader(
			shader_code_ptr,
			count_byte - 1,
			nullptr,
			&m_vertexShader
			);

		if (FAILED(hr))
		{
			DrawLine("LoadVertexShader: Ошибка CreateVertexShader " + RenderSystemD11_2::GetErrorHR(hr), MT_ERROR);

			m_bActive = false;
		}
	}

	void RenderComponentD11_2::LoadVertexLayout(_vertexLayouts& vertexLayouts, void* shader_code_ptr, _32un count_byte)
	{
		vector<D3D11_INPUT_ELEMENT_DESC> lD3D11Layout;
		_32un offset = 0;

		for (auto layout : vertexLayouts)
		{
			D3D11_INPUT_ELEMENT_DESC eIE;

			switch (layout)
			{
			case VertexLayout::VL_POSITION:
			{
				eIE.SemanticName = "POSITION";
				VL_OFFSET_POSITION(offset);
			}
			break;

			case VertexLayout::VL_TEXTURE:
			{
				eIE.SemanticName = "TEXCOORD";
				VL_OFFSET_TEXTURE(offset);
			}
			break;

			case VertexLayout::VL_NORMAL:
			{
				eIE.SemanticName = "NORMAL";
				VL_OFFSET_NORMAL(offset);
			}
			break;
			}

			eIE.SemanticIndex = 0;
			eIE.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			eIE.InputSlot = 0;
			eIE.AlignedByteOffset = offset;
			eIE.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			eIE.InstanceDataStepRate = 0;

			lD3D11Layout.push_back(eIE);
		}

		HRESULT hr = m_pRSystem->GetD3DDevice()->CreateInputLayout(
			lD3D11Layout.data(),
			lD3D11Layout.size(),
			shader_code_ptr,
			count_byte - 1,
			&m_inputLayout
			);

		if (FAILED(hr))
		{
			DrawLine("LoadShaderVertexShader: Ошибка CreateInputLayout " + RenderSystemD11_2::GetErrorHR(hr), MT_ERROR);

			m_bActive = false;
		}
	}

	void RenderComponentD11_2::LoadVertexBuffer(void* buffer, _32un offset, _32un size)
	{
		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = buffer;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		m_vertexOffset = offset;

		CD3D11_BUFFER_DESC vertexBufferDesc(size * offset, D3D11_BIND_VERTEX_BUFFER);
		HRESULT hr = m_pRSystem->GetD3DDevice()->CreateBuffer(
			&vertexBufferDesc,
			&vertexBufferData,
			&m_vertexBuffer
			);

		if (FAILED(hr))
		{
			DrawLine("LoadShaderVertexShader: Ошибка CreateBuffer " + RenderSystemD11_2::GetErrorHR(hr), MT_ERROR);

			m_bActive = false;
		}
	}

	void RenderComponentD11_2::LoadIndexBuffer(void* buffer, _32un offset, _32un size)
	{
		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = buffer;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC indexBufferDesc(size * offset, D3D11_BIND_INDEX_BUFFER);

		m_indexCount = size;

		HRESULT hr = m_pRSystem->GetD3DDevice()->CreateBuffer(
			&indexBufferDesc,
			&indexBufferData,
			&m_indexBuffer
			);

		m_IndexFormat = DXGI_FORMAT_R32_UINT;

		if (offset == sizeof(unsigned short)) {
			m_IndexFormat = DXGI_FORMAT_R16_UINT;
		}

		if (FAILED(hr))
		{
			DrawLine("LoadShaderVertexShader: Ошибка CreateBuffer " + RenderSystemD11_2::GetErrorHR(hr), MT_ERROR);

			m_bActive = false;
		}
	}

	void RenderComponentD11_2::LoadPixelShader(void* shader_code_ptr, _32un count_byte)
	{
		auto divace = m_pRSystem->GetD3DDevice();

		HRESULT hr;

		hr = divace->CreatePixelShader(
			shader_code_ptr,
			count_byte - 1,
			nullptr,
			&m_pixelShader
			);

		if (FAILED(hr))
		{
			DrawLine("LoadVertexShader: Ошибка CreatePixelShader " + RenderSystemD11_2::GetErrorHR(hr), MT_ERROR);

			m_bActive = false;
		}

		CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ConstantBuffer_ModelViewProjection), D3D11_BIND_CONSTANT_BUFFER);
		hr = divace->CreateBuffer(
			&constantBufferDesc,
			nullptr,
			&m_constantBuffer
			);

		if (FAILED(hr))
		{
			DrawLine("LoadVertexShader: Ошибка CreateBuffer " + RenderSystemD11_2::GetErrorHR(hr), MT_ERROR);

			m_bActive = false;
		}
	}

	void RenderComponentD11_2::Render(ID3D11DeviceContext2* context)
	{
		if (!context) {
			return;
		}

		if (!m_bActive) {
			return;
		}

		context->UpdateSubresource(
			m_constantBuffer.Get(),
			0,
			nullptr,
			&m_constantBufferData,
			0,
			0
		);

		UINT stride = m_vertexOffset;
		UINT offset = 0;
		context->IASetVertexBuffers(
			0,
			1,
			m_vertexBuffer.GetAddressOf(),
			&stride,
			&offset
		);

		context->IASetIndexBuffer(
			m_indexBuffer.Get(),
			m_IndexFormat,
			0
		);

		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		context->IASetInputLayout(m_inputLayout.Get());

		context->VSSetShader(
			m_vertexShader.Get(),
			nullptr,
			0
		);

		context->VSSetConstantBuffers(
			0,
			1,
			m_constantBuffer.GetAddressOf()
		);

		context->PSSetShader(
			m_pixelShader.Get(),
			nullptr,
			0
		);

		context->DrawIndexed(
			m_indexCount,
			0,
			0
		);
	}
}