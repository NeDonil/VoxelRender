#pragma once

#include <vector>
#include <iostream>
#include <ostream>
#include "Chunk.h"


namespace VoxelReader
{
	struct Voxel
	{
		int x, y, z, colorIndex;
	};

	class VoxelChunk : public Chunk
	{
	public:

		VoxelChunk(const std::vector<uint8_t>& data)
		{
			m_Data = data;

			m_Voxels.resize(Reader::ToInt32(m_Data, 12));

			for (int i = 0; i < m_Voxels.size(); i++)
			{
				m_Voxels[i] = 
				{ 
					data[16 + i * 4],  // x
					data[17 + i * 4],  // y
					data[18 + i * 4],  // z
					data[19 + i * 4]   // colorIndex
				};
			}
		}

		std::vector<Voxel> GetVoxels() { return m_Voxels; }

		friend std::ostream& operator<<(std::ostream& stream, const VoxelChunk& value)
		{
			stream << "Voxel Chunk: " << std::endl;

			for (auto voxel : value.m_Voxels)
				stream << "(" << voxel.x << ", " << voxel.y << ", " << voxel.z << ", " << voxel.colorIndex << ")" << std::endl;

			return stream;
		}

	private:
		std::vector<Voxel> m_Voxels;
	};
}