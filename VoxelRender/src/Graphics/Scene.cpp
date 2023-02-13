#include "Scene.h"

#include "Renderer.h"

#include <GLFW/glfw3.h>

namespace GraphicsSystem
{
	Scene::Scene(const std::string& path)
	{
		auto chunks = VoxelReader::Reader::GetChunks(VoxelReader::Reader::ReadBytes(path));

		m_SizeChunk = std::make_shared<VoxelReader::SizeChunk>(chunks[0].GetData());
		m_VoxelChunk = std::make_shared<VoxelReader::VoxelChunk>(chunks[1].GetData());
		m_PalleteChunk = std::make_shared<VoxelReader::PalleteChunk>(chunks[2].GetData());
	}

	void Scene::AddLightSource(const glm::vec3& lightSource)
	{
		m_LightSources.push_back(lightSource);
	}

	void Scene::Draw()
	{
		Renderer::SetActualLightSource(m_LightSources[(int)(glfwGetTime()) % 4]);

		for (auto voxel : m_VoxelChunk->GetVoxels())
		{
			VoxelReader::Color voxColor = m_PalleteChunk->GetColors()[voxel.colorIndex];
			glm::vec4 color = VoxelReader::Reader::BytesToVec4(voxColor.r, voxColor.g, voxColor.b, voxColor.a);

			Renderer::DrawCube(voxel.y, voxel.z, voxel.x, glm::vec3(color.r, color.g, color.b));
		}
	}

}