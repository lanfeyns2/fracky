#include <Serialization.h>

namespace fracky
{
	void Serialization::Write(std::vector<std::any> file, const char* filePath)
	{
		uint16_t depth = 0;

		std::string text;

		for (std::any line : file)
		{
			text.append(std::string(depth * space,' '));
			if (line.type() == typeid(fracky::Group))
			{
				depth += 1;
				text.append(std::any_cast<fracky::Group>(line).label + "\n");
				continue;
			}
			if (line.type() == typeid(fracky::GroupEnd))
			{
				depth -= 1;
				text.erase(std::remove(text.end() - 2, text.end(), ' '), text.end());
				text.append("\n");
				continue;
			}
			if (line.type() == typeid(fracky::Line))
			{
				text.append(std::any_cast<fracky::Line>(line).label);

				const std::string& l = std::any_cast<fracky::Line>(line).line;
				const std::string& tags = std::any_cast<fracky::Line>(line).addionalTags;

				if (isInt(l))
				{
					text.append(l + "[i]" + tags + "\n");
					continue;
				}
				else if (isFloat(l))
				{
					text.append(l + "[f]" + tags + "\n");
					continue;
				}
				else
				{
					text.append(l + tags + "\n");
					continue;
				}
			}
		}

		std::ofstream outFile(filePath, std::ios::out);

		if (outFile.is_open())
		{
			outFile << text;
		}

		outFile.close();
	}
	void Serialization::WriteBinary(std::vector<std::any> file, const char* filePath)
	{
		uint16_t depth = 0;

		std::string text;

		for (std::any line : file)
		{
			text.append(std::string(depth * space, ' '));
			if (line.type() == typeid(fracky::Group))
			{
				depth += 1;
				text.append(std::any_cast<fracky::Group>(line).label + "\n");
				continue;
			}
			if (line.type() == typeid(fracky::GroupEnd))
			{
				depth -= 1;
				text.append("[end]\n");
				continue;
			}
			if (line.type() == typeid(fracky::Line))
			{
				text.append(std::any_cast<fracky::Line>(line).label);

				const std::string& l = std::any_cast<fracky::Line>(line).line;
				const std::string& tags = std::any_cast<fracky::Line>(line).addionalTags;

				if (isInt(l))
				{
					text.append(l + "[i]" + tags + "\n");
					continue;
				}
				else if (isFloat(l))
				{
					text.append(l + "[f]" + tags + "\n");
					continue;
				}
				else
				{
					text.append(l + tags + "\n");
					continue;
				}
			}
		}

		std::ofstream outFile(filePath, std::ios::out | std::ios::binary);

		std::string binary;
		std::string binaryLine;
		std::stringstream ss(text);
		
		while (std::getline(ss, binaryLine))
		{
			for (char c : binaryLine)
			{
				binary.append(std::bitset<8>(c).to_string());
			}
			binary.append("\n");
		}

		if (outFile.is_open())
		{
			outFile << binary;
		}

		outFile.close();
	}


	bool Serialization::isInt(const std::string& text)
	{
		std::istringstream iss(text); 
		int x; 
		return (iss >> x) && (iss.eof());
	}
	bool Serialization::isFloat(const std::string& text)
	{
		std::istringstream iss(text); 
		float x; 
		return (iss >> x) && (iss.eof());
	}
}