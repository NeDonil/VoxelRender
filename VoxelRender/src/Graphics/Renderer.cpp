#include "Renderer.h"

#include <cassert>
#include <cstdint>

#include <glm/gtc/matrix_transform.hpp>

namespace GraphicsSystem
{
	void Renderer::Init()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_BLEND);
		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

		s_VAO = VoxelArray(MAX_VOXEL_PER_DRAW * 6 * 4);

		s_VoxelShader = std::make_shared<Shader>("assets/shaders/VoxelShader.vert.glsl", "assets/shaders/VoxelShader.frag.glsl");
		s_ActualLightSource = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Renderer::SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	void Renderer::SetActualLightSource(const glm::vec3& lightSource)
	{
		s_ActualLightSource = lightSource;
	}

	void Renderer::BeginVoxelScene(PerspectiveCamera& camera)
	{
		s_VoxelShader->Use();

		s_VoxelShader->SetVec3("u_ViewPos", camera.GetPosition());
		s_VoxelShader->SetVec3("u_LightPos", s_ActualLightSource);

		s_VoxelShader->SetMat4("u_View", camera.GetViewMatrix());
		s_VoxelShader->SetMat4("u_Projection", camera.GetProjectionMatrix());
	}

	void Renderer::EndVoxelScene()
	{
		Flush();
	}

	void Renderer::Flush()
	{
		s_VAO.Use();
		s_VAO.SetInstanceData(s_Data.Data, s_Data.DataSize);

		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, s_Data.TotalVoxelCount);

		s_Data.DataPtr = s_Data.DataBasePtr;
		s_Data.TotalVoxelCount = 0;
		s_Data.AvailableMemory = MAX_VOXEL_PER_DRAW * 6 * 4;
		s_Data.DataSize = 0;
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::DrawCube(int x, int y, int z, const glm::vec3& color)
	{
		if (s_Data.AvailableMemory <= 6 * 4)
			Flush();

		(*s_Data.DataPtr++) = x;
		(*s_Data.DataPtr++) = y;
		(*s_Data.DataPtr++) = z;

		(*s_Data.DataPtr++) = color.r;
		(*s_Data.DataPtr++) = color.g;
		(*s_Data.DataPtr++) = color.b;

		s_Data.TotalVoxelCount++;
		s_Data.AvailableMemory -= 6 * 4;
		s_Data.DataSize += 6 * 4;
	}

	VoxelArray Renderer::s_VAO;
	RenderData Renderer::s_Data;

	std::shared_ptr<Shader> Renderer::s_VoxelShader;
	glm::vec3 Renderer::s_ActualLightSource;
}