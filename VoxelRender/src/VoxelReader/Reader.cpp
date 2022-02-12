#include "Reader.h"

#include "Chunks/SizeChunk.h"
#include "Chunks/PaletteChunk.h"
#include "Chunks/VoxelChunk.h"

namespace VoxelReader
{
	std::vector<uint8_t> Reader::ReadBytes(const std::string& file)
	{
		std::ifstream input(file, std::ios::binary);
		std::vector<char> chars((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
		input.close();

		std::vector<uint8_t> bytes;
		for (auto c : chars)
			bytes.push_back(static_cast<uint8_t>(c));

		return bytes;
	}

	int Reader::ToInt32(const std::vector<uint8_t>& data, int offset)
	{
		return (data[offset + 3] << 24) + (data[offset + 2] << 16) + (data[offset + 1] << 8) + data[offset + 0];
	}

	glm::vec3 Reader::BytesToVec3(int x, int y, int z)
	{
		return glm::vec3(x / 255.0f, y / 255.0f, z / 255.0f);
	}

	glm::vec4 Reader::BytesToVec4(int x, int y, int z, int w)
	{
		return glm::vec4(x / 255.0f, y / 255.0f, z / 255.0f, w / 255.0f);
	}

	std::vector<uint8_t> Reader::GetRange(const std::vector<uint8_t>& data, int startIndex, int length)
	{
		std::vector<uint8_t> output(length);
		memcpy(&output[0], &data[startIndex], length);
		return output;
	}

	std::vector<Chunk> Reader::GetChunks(const std::vector<uint8_t>& data)
	{
		std::vector<Chunk> chunks;

		int mainChunkContentSize = ToInt32(data, 12);
		int mainChunkChildrenSize = ToInt32(data, 16);

		std::vector<uint8_t> mainChunkChildren = GetRange(data, 20 + mainChunkContentSize, mainChunkChildrenSize);

		for(int i = 0; i < mainChunkChildren.size(); i++)
		{
			int chunkContentSize = ToInt32(mainChunkChildren, i + 4);
			int chunkChildrenSize = ToInt32(mainChunkChildren, i + 8);
		
			int chunkSize = 12 + chunkContentSize + chunkChildrenSize;
			std::vector<uint8_t> chunkData = GetRange(mainChunkChildren, i, chunkSize);

			std::string id = GetString(chunkData, 0, 4);
			
			Chunk chunk;

			if (id == "PACK")
				std::cout << "File with more than one model is not supported now" << std::endl;
			else if (id == "SIZE")
				chunk = SizeChunk(chunkData);
			else if (id == "XYZI")
				chunk = VoxelChunk(chunkData);
			else if (id == "RGBA")
				chunk = PalleteChunk(chunkData);

			if (!chunk.GetData().empty())
				chunks.push_back(chunk);

			i += chunkSize - 1;
		}

		return chunks;
	
	}

	std::string Reader::GetString(const std::vector<uint8_t>& data, int startIndex, int lenght)
	{
		std::string output;

		for (int i = 0; i < lenght; i++)
			output += (char)data[startIndex + i];

		return output;
	}

	uint32_t Reader::GetChunkSize(const std::vector<uint8_t>& data)
	{
		return 12 + ToInt32(data, 4) + ToInt32(data, 8);
	}

}
