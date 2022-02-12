#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <ostream>

namespace VoxelReader
{
	class Chunk
	{
	public:
		Chunk() = default;
		Chunk(const std::vector<uint8_t>& data);

		std::vector<uint8_t>& GetData() { return m_Data; }
		std::vector<uint8_t>& GetContent() { return m_Content; }
		std::vector<uint8_t>& GetChildren(){ return m_Children; }

	protected:
		std::string m_Id;

		std::vector<uint8_t> m_Data;
		std::vector<uint8_t> m_Content;
		std::vector<uint8_t> m_Children;
	};
}