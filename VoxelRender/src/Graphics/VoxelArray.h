#pragma once

#include <GLAD/glad.h>
#include <glm/glm.hpp>

namespace GraphicsSystem
{
	class VoxelArray
	{
	public:
		VoxelArray() = default;
		VoxelArray(size_t dataSize);

		void SetInstanceData(const float* data, size_t dataSize);
		void Use() { glBindVertexArray(m_VAO); }

		GLuint& GetVAO() { return m_VAO; }
		GLuint& GetVBO() { return m_DynamicVBO; }

		~VoxelArray();
	private:
		GLuint m_VAO;
		GLuint m_StaticVBO;
		GLuint m_DynamicVBO;
	};
}