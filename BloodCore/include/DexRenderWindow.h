#pragma once

#include "DexPreCompletion.h"
#include "DexCommon.h"
#include "DexCoreObject.h"

namespace Dex
{
	class D_EXPORT RenderWindow : public CoreObject
	{
	public:
		RenderWindow(const string& c_name, ofstream* logger, bool fw = false);
		virtual ~RenderWindow();

		bool IsFullScrean(void);
		bool IsActive(void);

		virtual bool Create(const _lParametor & config) = 0;

		void SetCamera(CameraComponent* camera);
		CameraComponent* GetCamera();

	protected:
		int					m_hWnd;

		bool				m_bFullScrean;
		bool				m_bVSync;
		bool				m_bActive;
		bool				m_bInit;

		// Display Mode
		_32un				m_nWidth;
		_32un				m_nHeight;
		_32un				m_nBit;

		CameraComponent*	m_pCamera;
		Scene*				m_pSceneToRender;
	};
}