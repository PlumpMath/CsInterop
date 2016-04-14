all: libfile res app

libfile:
	g++ -fPIC -c -Iinclude src/file.c -o bin/file.o
	g++ -shared -Iinclude -o bin/libfile.so bin/file.o

res:
	glib-compile-resources gtk/res.xml --target=gtk/res.h --generate-source

app:
	g++ -c -Iinclude `pkg-config --cflags gtk+-3.0` gtk/main.cpp -o bin/main.o
	g++ -o bin/main bin/main.o `pkg-config --libs gtk+-3.0` -Lbin -lfile
	cp gtk/run.sh bin/run.sh
	
clean:
	rm bin/*.o
	rm bin/*.so
	rm gtk/res.h
	rm bin/main
	rm bin/*.sh
