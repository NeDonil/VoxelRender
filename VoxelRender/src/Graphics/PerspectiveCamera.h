#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GraphicsSystem
{
	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float fovy, float aspectRatio, float near, float far);
		~PerspectiveCamera() = default;

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::vec3& GetPosition() const { return m_Position; }

		const glm::vec3& GetFront() const { return m_Front; }
		const glm::vec3& GetRight() const { return m_Right; }
		const glm::vec3& GetUp() const { return m_Up; }

		void SetSensitivity(float sensitivity) { m_Sensitivity = sensitivity; }

		void SetYaw(float xoffset);
		void SetPitch(float yoffset);

		void SetPosition(const glm::vec3& position);
		void SetProjection(float fovy, float aspectRatio, float near, float far);
	private:
		void RecalculateCameraVectors();
	private:
		float m_Yaw;
		float m_Pitch;
		float m_Sensitivity;

		glm::vec3 m_Position;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;

		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;
	};
}