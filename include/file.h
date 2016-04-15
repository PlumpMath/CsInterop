#ifndef FILE_H
#define FILE_H

#include <fstream>

// #ifdef __cplusplus
// extern "C"
// {
// #endif

// #ifdef EXPORT_DLL
// #define CSDLL __declspec(dllexport)

// void CSDLL writeToFile(const char*, const char*);
// const char* CSDLL readFromFile(const char*);

// #endif

// #ifdef __cplusplus
// }
// #endif

class File
{
public:
	File();
	
	void writeToFile(const char*, const char*);
	const char* readFromFile(const char*);
};

#endif // FILE_H
