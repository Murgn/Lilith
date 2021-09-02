#include "lipch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>


namespace Lilith {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float zNear /*= 1.0*/, float zFar /*= -1.0*/)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, zNear, zFar)), m_ViewMatrix(1.0f), m_zNear(zNear), m_zFar(zFar)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, GetzNear(), GetzFar());
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}