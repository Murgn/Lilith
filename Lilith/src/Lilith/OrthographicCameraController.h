#pragma once

#include "Lilith/Renderer/OrthographicCamera.h"
#include "Lilith/Core/DeltaTime.h"

#include "Lilith/Events/ApplicationEvent.h"
#include "Lilith/Events/MouseEvent.h"

namespace Lilith {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(DeltaTime deltaTime);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e); 
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;
		glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
		float m_CameraMoveSpeed = 2.0f;
		float m_CameraRotation = 0;
		float m_CameraRotationSpeed = 180.0f;
	};

}