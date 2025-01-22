#pragma once

/*------------------CORE FILES---------------------*/
#include <Serialization.h>
#include <Deserialization.h>
/*--------------------TYPES------------------------*/
#include <types/Group.h>
#include <types/Text.h>
/*------------------FUNCTIONS----------------------*/
namespace fracky
{
	inline std::unordered_map<std::string, std::any> GetDepth(std::unordered_map<std::string, std::any>& file, const char* group)
	{
		return std::any_cast<std::unordered_map<std::string, std::any>>(file[group]);
	}
}
/*-------------------DEFINES-----------------------*/
#ifdef FRACKY_USE_FRACKY_FILE
typedef std::unordered_map<std::string, std::any> frackyFile;
#endif // FRACKY_USE_FRACKY_FILE
/*-------------------------------------------------*/
