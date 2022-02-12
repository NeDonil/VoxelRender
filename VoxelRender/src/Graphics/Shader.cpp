#include "Shader.h"
#include <Utils\Utils.h>

namespace GraphicsSystem
{

	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		Compile(vertexPath, fragmentPath);
	}

	void Shader::Compile(const std::string& vertexPath, const std::string& fragmentPath)
	{
		m_RendererID = glCreateProgram();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertexString = Utils::read_file(vertexPath);
		std::string fragmentString = Utils::read_file(fragmentPath);

		const char* vertexShaderSrc = vertexString.c_str();
		const char* fragmentShaderSrc = fragmentString.c_str();

		glShaderSource(vertexShader, 1, &vertexShaderSrc, 0);
		glShaderSource(fragmentShader, 1, &fragmentShaderSrc, 0);

		glCompileShader(vertexShader);
		glCompileShader(fragmentShader);

		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		glLinkProgram(m_RendererID);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Shader::Use()
	{
		glUseProgram(m_RendererID);
	}

	void Shader::SetInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}

	void Shader::SetFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}

	void Shader::SetBool(const std::string& name, bool value)
	{
		glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}

	void Shader::SetVec2(const std::string& name, const glm::vec2& value)
	{
		glUniform2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, glm::value_ptr(value));
	}

	void Shader::SetVec3(const std::string& name, const glm::vec3& value)
	{
		glUniform3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, glm::value_ptr(value));
	}

	void Shader::SetVec4(const std::string& name, const glm::vec4& value)
	{
		glUniform4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, glm::value_ptr(value));
	}

	void Shader::SetMat3(const std::string& name, const glm::mat3& mat)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& mat)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

}