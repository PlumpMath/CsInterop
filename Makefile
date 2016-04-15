all: libfile res app

libfile:
	g++ -fPIC -c -Iinclude -o src/file.o src/file.c
	g++ -shared -o gtk/libfile.so src/file.o
	
res:
	glib-compile-resources gtk/res.xml --target=gtk/res.h --generate-source
	
app:
	g++ -fPIC -c -Iinclude -o gtk/main.o gtk/main.cpp `pkg-config --cflags gtk+-3.0`
	g++ -o gtk/main gtk/main.o `pkg-config --libs gtk+-3.0` -Lgtk -lfile
	cp gtk/main bin/main
	cp gtk/run.sh bin/run.sh
	cp gtk/libfile.so bin/libfile.so

test: all
	cd bin; \
	./run.sh

clean:
	if [ -e src/file.o ]; then rm src/file.o; fi
	if [ -e gtk/lib* ]; then rm gtk/lib*; fi
	if [ -e gtk/res.h ]; then rm gtk/res.h; fi
	if [ -e gtk/*.o ]; then rm gtk/*.o; fi
	if [ -e gtk/main ]; then rm gtk/main; fi
	if [ -e gtk/*.txt ]; then rm gtk/*.txt; fi
	if [ -e bin/*.txt ]; then rm bin/*.txt; fi
	if [ -e bin/lib* ]; then rm bin/lib*; fi
	if [ -e bin/*.sh ]; then rm bin/*.sh; fi
	if [ -e bin/main ]; then rm bin/main; fi
