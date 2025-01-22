#pragma once

#include <any>
#include <vector>
#include <fstream>
#include <sstream>
#include <bitset>

#include <types/Group.h>
#include <types/Text.h>

namespace fracky
{
	class Serialization
	{
	public:

		void Write(std::vector<std::any> file, const char* filePath);
		void WriteBinary(std::vector<std::any> file, const char* filePath);

	public:
		uint8_t space = 2;

	private:
		bool isInt(const std::string& text);
		bool isFloat(const std::string& text);
	};
}