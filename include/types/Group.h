#pragma once

#include "Text.h"
#include <unordered_map>
#include <string>

namespace fracky
{
	struct Group
	{
		Group(std::string la)
		{
			label = std::string(la + ":");
		}
		std::string label;
	};

	struct GroupEnd
	{

	};
}