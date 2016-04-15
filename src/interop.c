#include <file.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef EXPORT_DLL
#define INTEROP __declspec(dllexport)
#else
#define INTEROP __declspec(dllimport)
#endif

void INTEROP writeToFile(const char*, const char*);
const char* INTEROP readFromFile(const char*);

#ifdef __cplusplus
}
#endif

void writeToFile(const char* filename, const char* content)
{
	File file;
	file.writeToFile(filename, content);
}

const char* readFromFile(const char* filename)
{
	File file;
	file.readFromFile(filename);
}