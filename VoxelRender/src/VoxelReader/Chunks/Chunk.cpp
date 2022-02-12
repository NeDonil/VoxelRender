#include "Chunk.h"
#include "VoxelReader/Reader.h"

#include <assert.h>

namespace VoxelReader
{
	Chunk::Chunk(const std::vector<uint8_t>& data)
	{
		assert(data.empty()); // data is empty

		m_Id = Reader::GetString(data, 0, 4);
		m_Content = Reader::GetRange(data, 12, Reader::ToInt32(data, 4));
		m_Children = Reader::GetRange(data, 12 + m_Content.size(), Reader::ToInt32(data, 8));
	}
}
