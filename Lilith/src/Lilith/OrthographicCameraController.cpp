#include "lipch.h"
#include "OrthographicCameraController.h"

#include "Lilith/Input.h"
#include "Lilith/KeyCodes.h"

namespace Lilith {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(DeltaTime deltaTime)
	{
		// Camera Movement ------------------------------------------------
		if (Input::IsKeyPressed(LI_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * deltaTime;
		if (Input::IsKeyPressed(LI_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * deltaTime;
		if (Input::IsKeyPressed(LI_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * deltaTime;
		if (Input::IsKeyPressed(LI_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * deltaTime;

		// Camera Rotation ------------------------------------------------
		if (m_Rotation)
		{
			if (Input::IsKeyPressed(LI_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * deltaTime;
			if (Input::IsKeyPressed(LI_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * deltaTime;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraMoveSpeed = m_ZoomLevel / 0.5;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(LI_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(LI_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio -= (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}