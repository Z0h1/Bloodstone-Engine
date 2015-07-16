#include "DexRenderWindow.h"
#include "DexSceneObject.h"
#include "DexCameraComponent.h"

namespace Dex
{
	RenderWindow::RenderWindow(const string& c_name, ofstream* logger, bool fw)
		: CoreObject(c_name, logger, WorkPriority::WP_STEP_1, fw)
	{
		m_pCamera = nullptr;
		m_pSceneToRender = nullptr;

		m_bActive = true;

		m_bFullScrean = false;
		m_bVSync = false;
		m_nWidth = 800;
		m_nHeight = 600;
		m_nBit = 32;
		m_hWnd = 0;

		m_bInit = false;
	}

	RenderWindow::~RenderWindow()
	{
	}

	bool RenderWindow::IsFullScrean(void)
	{
		return m_bFullScrean;
	}

	bool RenderWindow::IsActive(void)
	{
		return m_bActive;
	}

	void RenderWindow::SetCamera(CameraComponent* camera)
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

		if (m_pCamera) {
			m_pSceneToRender = m_pCamera->GetSceneObject()->GetScene();
		}
	}

	CameraComponent* RenderWindow::GetCamera()
	{
		return m_pCamera;
	}
}