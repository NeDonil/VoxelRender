#include "PerspectiveCamera.h"

#include <iostream>

#include <unordered_map>

namespace GraphicsSystem
{

	PerspectiveCamera::PerspectiveCamera(float fovy, float aspectRatio, float near, float far)
	{
		m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Right = glm::vec3(1.0f, 0.0f, 0.0f);
		m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

		m_Position = glm::vec3(0.0f, 0.0f, 0.0f);

		m_Yaw = -90.0f; m_Pitch = 0.0f;

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		m_ProjectionMatrix = glm::perspective(fovy, aspectRatio, near, far);
	}

	void PerspectiveCamera::SetYaw(float xoffset)
	{
		m_Yaw += xoffset * m_Sensitivity;
		RecalculateCameraVectors();
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void PerspectiveCamera::SetPitch(float yoffset)
	{
		m_Pitch += yoffset * m_Sensitivity;

		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		RecalculateCameraVectors();
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void PerspectiveCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void PerspectiveCamera::SetProjection(float fovy, float aspectRatio, float near, float far)
	{
		m_ProjectionMatrix = glm::perspective(fovy, aspectRatio, near, far);
	}

	void PerspectiveCamera::RecalculateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);

		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}

}