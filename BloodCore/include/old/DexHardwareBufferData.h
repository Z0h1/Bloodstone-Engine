//#pragma once
//
//#include "DexPreCompletion.h"
//#include "DexCommon.h"
//
//namespace Dex
//{
//	typedef IndexedArray< HardwareVertexBuffer* >	g_lVertexBuffer;
//
//	class D_EXPORT HardwareBufferData
//	{
//	public:
//		HardwareBufferData(void);
//		~HardwareBufferData(void);
//
//		HardwareVertexBuffer* CreateVertexBuffer(unsigned int nVertexCount);
//		HardwareIndexBuffer* CreateIndexBuffer(unsigned int nIndexCount, const IndexType& eType);
//
//		const g_lVertexBuffer& GetListVertexBuffer(void) const;
//		int GetVertexBufferCount(void) const;
//		HardwareIndexBuffer* GetIndexBuffer(void) const;
//
//	protected:
//		g_lVertexBuffer				m_lVertexBuffer;
//		HardwareIndexBuffer*		m_pIndexBuffer;
//	};
//}