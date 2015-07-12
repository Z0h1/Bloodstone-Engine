#include "DexRenderWindow.h"
#include "DexSceneObject.h"
#include "DexCameraComponent.h"

namespace Dex
{
	IRenderWindow::IRenderWindow(const string& c_name, ofstream* logger, bool fw)
		: CoreObject(c_name, logger, WorkPriority::WP_STEP_1, fw)
	{
		m_pCamera = nullptr;
		m_bActive = true;
		m_bFullScrean = false;
		m_bVSync = false;
		m_nWidth = 800;
		m_nHeight = 600;
		m_nBit = 32;
		m_hWnd = 0;
		m_bInit = false;
	}

	IRenderWindow::~IRenderWindow()
	{
	}

	bool IRenderWindow::IsFullScrean( void )
	{
		return m_bFullScrean;
	}

	bool IRenderWindow::IsActive( void )
	{
		return m_bActive;
	}

	void IRenderWindow::SetCamera(CameraComponent* camera)
	{
		if (m_pCamera) {
			DrawLine("SetCamera: смена камеры c " + m_pCamera->GetName() + " на " + camera->GetName());
		}
		else {
			if (camera) {
				DrawLine("SetCamera: установка камеры " + camera->GetName());
			}
			else {
				DrawLine("SetCamera: входной параметр пуст camera");
			}
		}

		m_pCamera = camera;
	}

	CameraComponent* IRenderWindow::GetCamera()
	{
		return m_pCamera;
	}

	void IRenderWindow::Render()
	{
		if (m_bActive && m_pCamera != nullptr) {
			IRender();
		}
	}
}