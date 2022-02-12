#pragma once

#include <VoxelReader/Chunks/SizeChunk.h>
#include <VoxelReader/Chunks/VoxelChunk.h>
#include <VoxelReader/Chunks/PaletteChunk.h>
#include <VoxelReader/Reader.h>

#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace GraphicsSystem
{
	class Scene
	{
	public:
		Scene() = default;
		Scene(const std::string& path);

		void AddLightSource(const glm::vec3& lightSource);
		void Draw();

		~Scene() = default;

	private:
		std::vector<glm::vec3> m_LightSources;

		std::shared_ptr<VoxelReader::SizeChunk> m_SizeChunk;
		std::shared_ptr<VoxelReader::VoxelChunk> m_VoxelChunk;
		std::shared_ptr<VoxelReader::PalleteChunk> m_PalleteChunk;
	};
}