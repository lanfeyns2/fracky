#include <Deserialization.h>

namespace fracky
{
	std::unordered_map<std::string, std::any> Deserialization::Read(const char* path)
	{
		std::ifstream file(path,std::ios::in);

		typedef std::unordered_map<std::string, std::any> uGroup;

		uGroup frackFile;
		std::vector<std::string> alias;
		alias.reserve(4);

		if (file.is_open())
		{
			std::string line;

			std::string label = "";
			std::string value = "";
			std::string valueType = "";

			bool writingLabel = true;
			bool writingValue = false;
			bool writingType = false;

			while (std::getline(file, line))
			{
				for (int i = 0; i < line.size() + 1; i++)
				{
					switch (line.c_str()[i])
					{
					case '[':
						writingValue = false;
						writingType = true;
						break;
					case ' ':
						if (writingLabel == false)
						{
							writingValue = true;
						}
						break;
					case ':':
						writingLabel = false;
						break;
					case '\0':
						if (label == "" && value == "") /* Group End */
						{
							alias.erase(alias.end() - 1);
							break;
						}
						else if (writingLabel == false && writingValue == false && writingType == false && label != "\0") /* Group Start */
						{
							alias.emplace_back(label);
							break;
						}
						else if (label != "" && value != "") /* Values */
						{
							if (valueType == "f")
							{
								insertFile(frackFile, alias, std::stof(value), label.c_str());
							}
							else if (valueType == "i")
							{
								insertFile(frackFile, alias, std::stoi(value), label.c_str());
							}
							else if (valueType == "ui")
							{
								unsigned int t = std::stoi(value);
								insertFile(frackFile, alias, t, label.c_str());
							}
							
						}
						break;
					default:
						if (writingLabel == true)
						{
							label += line.c_str()[i];
						}
						else if (writingLabel == false && writingValue == true && writingType == false)
						{
							value += line.c_str()[i];
						}
						else if (writingType == true)
						{
							if (line.c_str()[i] == 'f')
							{
								valueType += 'f';
							}
							else if (line.c_str()[i] == 'u')
							{
								const char* temp = valueType.c_str();

								valueType.erase(valueType.begin(), valueType.end());
								valueType.append('u' + temp);
							}
							else if (line.c_str()[i] == 'i')
							{
								valueType += 'i';
							}
						}
						break;
					}
				}

				label = "";
				value = "";
				valueType = "";

				writingLabel = true;
				writingValue = false;
				writingType = false;
			}
		}

		file.close();

		return frackFile;
	}
	std::unordered_map<std::string, std::any> Deserialization::ReadBinary(const char* path)
	{
		std::ifstream file(path, std::ios::in | std::ios::binary);

		typedef std::unordered_map<std::string, std::any> uGroup;

		uGroup frackFile;
		std::vector<std::string> alias;
		alias.reserve(4);

		if (file.is_open())
		{
			std::string line;
			std::string tline;

			std::string label = "";
			std::string value = "";
			std::string valueType = "";

			bool writingLabel = true;
			bool writingValue = false;
			bool writingType = false;

			while (std::getline(file, tline))
			{
				
				for (size_t i = 0; i < tline.size(); i += 8)
				{
					std::bitset<8> bitset(tline.substr(i, 8));
					char c = static_cast<char>(bitset.to_ulong());
					line.push_back(c);
				}
				for (int i = 0; i < line.size() + 1; i++)
				{
					switch (line.c_str()[i])
					{
					case '[':
						writingValue = false;
						writingType = true;
						break;
					case ' ':
						if (writingLabel == false)
						{
							writingValue = true;
						}
						break;
					case ':':
						writingLabel = false;
						break;
					case '\0':
						if (label == "" && value == "") /* Group End */
						{
							alias.erase(alias.end() - 1);
							break;
						}
						else if (writingLabel == false && writingValue == false && writingType == false && label != "\0") /* Group Start */
						{
							alias.emplace_back(label);
							break;
						}
						else if (label != "" && value != "") /* Values */
						{
							if (valueType == "f")
							{
								insertFile(frackFile, alias, std::stof(value), label.c_str());
							}
							else if (valueType == "i")
							{
								insertFile(frackFile, alias, std::stoi(value), label.c_str());
							}
							else if (valueType == "ui")
							{
								unsigned int t = std::stoi(value);
								insertFile(frackFile, alias, t, label.c_str());
							}

						}
						break;
					default:
						if (writingLabel == true)
						{
							label += line.c_str()[i];
						}
						else if (writingLabel == false && writingValue == true && writingType == false)
						{
							value += line.c_str()[i];
						}
						else if (writingType == true)
						{
							if (line.c_str()[i] == 'f')
							{
								valueType += 'f';
							}
							else if (line.c_str()[i] == 'u')
							{
								const char* temp = valueType.c_str();

								valueType.erase(valueType.begin(), valueType.end());
								valueType.append('u' + temp);
							}
							else if (line.c_str()[i] == 'i')
							{
								valueType += 'i';
							}
						}
						break;
					}
				}

				label = "";
				value = "";
				valueType = "";
				line = "";

				writingLabel = true;
				writingValue = false;
				writingType = false;
			}
		}

		file.close();

		return frackFile;
	}
	template<typename T>
	void Deserialization::insertFile(std::unordered_map<std::string, std::any>& file, std::vector<std::string>& keys, T value, const char* label)
	{
		uint32_t maxSize = keys.size();

		
		std::unordered_map<std::string, std::any>* currentMap = &file;

		for (size_t i = 0; i < maxSize; ++i) {
			const std::string& key = keys[i];

			if (currentMap->find(key) == currentMap->end()) {
				(*currentMap)[key] = std::unordered_map<std::string, std::any>();
			}

			std::unordered_map<std::string, std::any>& nextMap = std::any_cast<std::unordered_map<std::string, std::any>&>((*currentMap)[key]);

			currentMap = &nextMap;
		}

		(*currentMap)[label] = value;
	}

}
