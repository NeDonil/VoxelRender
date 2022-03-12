#include "Scene.h"

#include "Renderer.h"

#include <GLFW/glfw3.h>

namespace GraphicsSystem
{
	Scene::Scene(const std::string& path)
		: m_MainCamera(Camera(90.0f, 1280.0f / 720.0f, 0.1f, 100.f))
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
		Renderer::SetActualLightSource(m_LightSources[0]);

		for (auto voxel : m_VoxelChunk->GetVoxels())
		{
			VoxelReader::Color voxColor = m_PalleteChunk->GetColors()[voxel.colorIndex];
			glm::vec4 color = VoxelReader::Reader::BytesToVec4(voxColor.r, voxColor.g, voxColor.b, voxColor.a);

			Renderer::DrawCube(voxel.y, voxel.z, voxel.x, glm::vec3(color.r, color.g, color.b));
		}
	}

	void Scene::Update()
	{
		m_MainCamera.Update();
	}

}