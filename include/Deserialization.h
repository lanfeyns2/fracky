#pragma once

#include <types/Group.h>
#include <types/Text.h>

#include <unordered_map>
#include <vector>
#include <any>
#include <fstream>
#include <bitset>
#include <string>
#include <iostream>

namespace fracky
{
	class Deserialization
	{
	public:
		std::unordered_map<std::string,std::any> Read(const char* path);
		std::unordered_map<std::string, std::any> ReadBinary(const char* path);

	private:
		template<typename T>
		void insertFile(std::unordered_map<std::string, std::any>& file,std::vector<std::string>& keys,T value,const char* label);
	};
}
