MSFW=C:\Windows\Microsoft.NET\Framework\v4.0.30319
MSBUILD=${MSFW}\MSBuild.exe

CFLAGS=/p:Configuration=Release;AllowUnsafeBlocks=true /p:CLSCompliant=False
LDFLAGS=/tv:4.0 /p:TargetFrameworkVersion=v4.5 /p:Platform="Any Cpu" /p:OutputPath="${CWD}bin"

all: libfile csapp
	
libfile:
	g++ -c -DEXPORT_DLL src/file.c -o bin/file.o -Iinclude
	g++ -O2 -shared -o bin/file.dll bin/file.o

csapp:
	${MSBUILD} win/CsInterop.sln ${CFLAGS} ${LDFLAGS}

test: all
	g++ -c test.c -Iinclude
	g++ -O2 -o test.exe test.o -Lbin -lfile
	copy /Y bin\file.dll file.dll

clean:
	rmdir /S /Q bin
	mkdir bin
	if exist *.o del *.o
	if exist *.dll del *.dll
	if exist *.exe del *.exe
	if exist *.txt del *.txt
	if exist ${CWD}win\CsInterop\bin rmdir /S /Q ${CWD}win\CsInterop\bin
	if exist ${CWD}win\CsInterop\obj rmdir /S /Q ${CWD}win\CsInterop\obj