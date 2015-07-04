#pragma once

#include <DexSerializer.h>

namespace Dex
{
	#define MESH_VERSION_SERIALIZER 1

	class D_EXPORT MeshSerializer : public Serializer
	{
	public:
		MeshSerializer(const String& c_name, bool fw = true);
		virtual ~MeshSerializer();

		void ImportMesh( void );

	private:
		void ReadGeometry( void );
		void ReadVertex( void );

	protected:
		HardwareBufferData*			m_pBufferData;

	private:
		MeshStruct					m_sMeshStruct;
	};
}

