#pragma once

#include <string>

namespace fracky
{
	struct Line
	{
		Line(std::string la, std::string li, std::string tags = "")
		{
			label = std::string(la + ": ");
			line = li;
			addionalTags = tags;
		}
		std::string label;
		std::string line;

		std::string addionalTags;
	};
}