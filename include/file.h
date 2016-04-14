#ifndef FILE_H
#define FILE_H

#include <fstream>

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef EXPORT_DLL
#define INTEROP __declspec(dllexport)
#else
#define INTEROP
#endif

void INTEROP writeToFile(const char*, const char*);
const char* INTEROP readFromFile(const char*);

#ifdef __cplusplus
}
#endif

#endif // FILE_H
