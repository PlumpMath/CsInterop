#include <file.h>

File::File() {}

void File::writeToFile(const char* filename, const char* content)
{
	std::ofstream file;
	file.open(filename);
	file << content << "\n";
	file.close();
}

const char* File::readFromFile(const char* filename)
{
	std::ifstream file(filename);
	std::string line;
	std::string content;
	if(file.is_open())
	{
		while(getline(file, line))
		{
			content += std::string(line);
			content += std::string("\n");
		}
		file.close();
	}

	return content.c_str();
}
