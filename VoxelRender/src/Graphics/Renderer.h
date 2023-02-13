#pragma once

#include <GLAD/glad.h>
#include "Shader.h"
#include "PerspectiveCamera.h"
#include "VoxelArray.h"

#include <unordered_map>

#define MAX_VOXEL_PER_DRAW 30000

namespace GraphicsSystem
{
	struct RenderData
	{
		float Data[MAX_VOXEL_PER_DRAW * 6];

		uint32_t AvailableMemory = MAX_VOXEL_PER_DRAW * 6 * 4;
		uint32_t TotalVoxelCount = 0;
		uint32_t DataSize = 0;

		float* DataBasePtr = &Data[0];
		float* DataPtr = DataBasePtr;
	};

	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		static void Init();

		static void SetClearColor(float r, float g, float b, float a);
		static void SetViewport(int x, int y, int width, int height);
		static void SetActualLightSource(const glm::vec3& lightSource);

		static void BeginVoxelScene(PerspectiveCamera& camera);
		static void EndVoxelScene();
		static void Flush();

		static void DrawCube(int x, int y, int z, const glm::vec3& color);

		static void Clear();

	private:
		static std::shared_ptr<Shader> s_VoxelShader;

		static glm::vec3 s_ActualLightSource;

		static VoxelArray s_VAO;
		static RenderData s_Data;
	};
}