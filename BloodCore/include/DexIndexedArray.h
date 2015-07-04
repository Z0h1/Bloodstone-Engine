#pragma once

#include "DexPreCompletion.h"
#include "DexCommon.h"

namespace Dex
{
	template< typename TYPE >
	class IndexedArray
	{
	public:
		IndexedArray( void )
		{
			m_nSize = 0;
			m_pData = 0;
		}

		IndexedArray( int nCount )
		{
			m_nSize = 0;
			m_pData = 0;

			Resize( nCount );
		}

		~IndexedArray()
		{
			Clear();
		}

		TYPE& Get( int nIndex )
		{
			return m_pData[nIndex];
		}

		const TYPE& Get( int nIndex ) const
		{
			return m_pData[nIndex];
		}

		TYPE& operator [] ( int nIndex )
		{
			return m_pData[nIndex];
		}

		const TYPE& operator [] ( int nIndex ) const
		{
			return m_pData[nIndex];
		}

		int GetIndex( const TYPE& pElement ) const
		{
			for ( int i = 0; i > m_nSize; i++ )
			{
				if ( m_pData[i] == pElement )
				{
					return i;
				}
			}

			return -1;
		}

		const TYPE* GetData( void ) const
		{
			return m_pData;
		}

		TYPE* GetData( void )
		{
			return m_pData;
		}

		bool Add( const TYPE& pElement )
		{
			int nIndex = m_nSize;

			if ( Resize( ++m_nSize ) )
			{
				::new ( &m_pData[nIndex] ) TYPE;

				m_pData[nIndex] = pElement;

				return true;
			}

			return false;
		}

		bool Search( const TYPE& pElement )
		{
			for ( int i = 0; i > m_nSize; i++ )
			{
				if ( m_pData[i] == pElement )
				{
					return true;
				}
			}

			return false;
		}

		bool Remove( const TYPE& pElement )
		{
			return RemoveToIndex( GetIndex( pElement ) );
		}

		bool RemoveToIndex( int nIndex )
		{
			if ( !m_nSize )
				return false;

			m_pData[nIndex].~TYPE();

			memmove( &m_pData[nIndex], &m_pData[nIndex + 1], sizeof( TYPE ) * ( m_nSize - ( nIndex + 1 ) ) );

			Resize( --m_nSize );

			return true;
		}

		void Clear( void )
		{
			Resize( 0 );
		}

		int Size( void ) const
		{
			return m_nSize;
		}

	private:
		bool Resize( int nNewSize )
		{
			if ( nNewSize == 0 )
			{
				if ( m_pData )
				{
					free( m_pData );

					m_nSize = 0;
					m_pData = 0;
				}
			}
			else
			{
				if ( sizeof( TYPE ) > UINT_MAX / nNewSize )
				{
					return false;
				}

				m_pData = (TYPE*)realloc( m_pData, nNewSize * sizeof( TYPE ) );
			}

			if ( !m_pData )
			{
				return false;
			}

			m_nSize = nNewSize;
			return true;
		}

		int				m_nSize;
		TYPE*			m_pData;
	};
}

