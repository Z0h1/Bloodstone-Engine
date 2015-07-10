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

		bool IsFullScrean(void);
		bool IsActive(void);

		virtual bool Create(const _lParametor & config) = 0;
		
		void SetCamera(CameraComponent* camera);
		CameraComponent* GetCamera();

		void Render();
		virtual void IRender() = 0;

	protected:
		int					m_hWnd;

		bool				m_bFullScrean;
		bool				m_bVSync;
		bool				m_bActive;
		bool				m_bInit;

		// Display Mode
		UInt32				m_nWidth;
		UInt32				m_nHeight;
		UInt32				m_nBit;

		CameraComponent*	m_pCamera;
	};
}