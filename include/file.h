#ifndef FILE_H
#define FILE_H

#include <fstream>

class File
{
public:
	File();
	
	void writeToFile(const char*, const char*);
	const char* readFromFile(const char*);
};

#endif // FILE_H
