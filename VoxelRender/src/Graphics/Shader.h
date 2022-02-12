#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLAD/glad.h>

namespace GraphicsSystem
{
	class Shader
	{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader() = default;

		void Compile(const std::string& vertexPath, const std::string& fragmentPath);
		void Use();

		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetBool(const std::string& name, bool value);

		void SetVec2(const std::string& name, const glm::vec2& value);
		void SetVec3(const std::string& name, const glm::vec3& value);
		void SetVec4(const std::string& name, const glm::vec4& value);

		void SetMat3(const std::string& name, const glm::mat3& mat);
		void SetMat4(const std::string& name, const glm::mat4& mat);

	private:
		GLuint m_RendererID;
	};
}
