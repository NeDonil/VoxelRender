#pragma once

#include <vector>
#include <array>
#include "Chunk.h"
#include <VoxelReader/Reader.h>

namespace VoxelReader
{
	struct Color
	{
		uint8_t r, g, b, a;
	};

	class PalleteChunk : public Chunk
	{
	public:
		PalleteChunk(const std::vector<uint8_t> data)
		{
			m_Data = data;

			for (int i = 0; i < 256; i++)
				m_Colors[i] = 
				{   data[12 + i * 4], 
					data[13 + i * 4], 
					data[14 + i * 4], 
					data[15 + i * 4] 
				};
		}

		std::array<Color, 256> GetColors() { return m_Colors; }

		friend std::ostream& operator<<(std::ostream& stream, const PalleteChunk& value)
		{
			stream << "Pallete Chunk:" << std::endl;

			for (auto& color : value.m_Colors)
			{
				stream << "(" << (int)color.r << ", " << (int)color.g << ", " << (int)color.b << ", " << (int)color.a << ")" << std::endl;
			}

			return stream;
		}
	private:
		std::array<Color, 256> m_Colors;
	};

}