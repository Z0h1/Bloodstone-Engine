#pragma once

#include "DexPreCompletion.h"
#include "DexCommon.h"
#include "DexCoreObject.h"

namespace Dex
{
	class D_EXPORT IRenderWindow : public CoreObject
	{
	public:
		IRenderWindow(const string& c_name, ofstream* logger, bool fw = false);
		virtual ~IRenderWindow();

		bool IsFullScrean( void );
		bool IsActive( void );

	protected:
		HWND				m_hWnd;

		bool				m_FullScrean;
		bool				m_VSync;
		bool				m_Active;

		// Display Mode
		int					m_nWidth;
		int					m_nHeight;
		int					m_nBit;
	};
}