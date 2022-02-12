#pragma once

#include <string>
#include <fstream>
#include <iostream>

namespace Utils
{
	inline std::string read_file(const std::string& filePath)
	{
		std::ifstream ifs((filePath).c_str());
		std::string content(std::istreambuf_iterator<char>(ifs.rdbuf()), std::istreambuf_iterator<char>());
		return content;
	}
}