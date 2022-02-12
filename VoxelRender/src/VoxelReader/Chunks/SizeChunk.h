#pragma once

#include <vector>
#include <VoxelReader/Chunks/Chunk.h>
#include <VoxelReader/Reader.h>

namespace VoxelReader
{
	class SizeChunk : public Chunk
	{
	public:
		SizeChunk(const std::vector<uint8_t>& data)
		{
			m_Data = data;

			x = Reader::ToInt32(m_Data, 12);
			y = Reader::ToInt32(m_Data, 16);
			z = Reader::ToInt32(m_Data, 20);
		}

		friend std::ostream& operator<<(std::ostream& stream, const SizeChunk& value)
		{
			stream << "Size Chunk: X = " << value.x << "; Y = " << value.y << "; Z = " << value.z << std::endl;
			return stream;
		}

	private:
		int x, y, z;
	};
}