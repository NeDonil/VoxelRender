#pragma once

#include "Chunks/Chunk.h"

#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>

namespace VoxelReader
{
	enum ChunkType { PACK, SIZE, XYZI, RGBA};

	class Reader
	{
	public:
		static std::vector<uint8_t> ReadBytes(const std::string& file);

		static int ToInt32(const std::vector<uint8_t>& data, int offset);
		static glm::vec3 BytesToVec3(int x, int y, int z);
		static glm::vec4 BytesToVec4(int x, int y, int z, int w);

		static std::vector<uint8_t> GetRange(const std::vector<uint8_t>& data, int startIndex, int lenght);
		static std::string GetString(const std::vector<uint8_t>& data, int startIndex, int lenght);

		static std::vector<Chunk> GetChunks(const std::vector<uint8_t>& data);
		static uint32_t GetChunkSize(const std::vector<uint8_t>& data);
	};
}