all: libfile res app

libfile:
	g++ -fPIC -c -Iinclude -o src/file.o src/file.c
	g++ -shared -o gtk/libfile.so src/file.o
	
res:
	glib-compile-resources gtk/res.xml --target=gtk/res.c --generate-source
	g++ -fPIC -c -o gtk/res.o gtk/res.c `pkg-config --cflags gtk+-3.0`
	
app:
	g++ -fPIC -c -Iinclude -o gtk/main.o gtk/main.cpp `pkg-config --cflags gtksourceview-3.0`
	g++ -fPIC -c -o gtk/about.o gtk/about.c `pkg-config --cflags gtksourceview-3.0`
	g++ -o gtk/main gtk/about.o gtk/main.o gtk/res.o `pkg-config --libs gtksourceview-3.0` -Lgtk -lfile
	cp gtk/main bin/main
	cp gtk/run.sh bin/run.sh
	cp gtk/libfile.so bin/libfile.so

test:
	cd bin; \
	./run.sh

clean:
	if [ -e src/file.o ]; then rm src/file.o; fi
	if [ -e gtk/lib* ]; then rm gtk/lib*; fi
	if [ -e gtk/res.c ]; then rm gtk/res.c; fi
	if [ -e gtk/about.o ]; then rm gtk/*.o; fi
	if [ -e gtk/*.o ]; then rm gtk/*.o; fi
	if [ -e gtk/main ]; then rm gtk/main; fi
	if [ -e gtk/*.txt ]; then rm gtk/*.txt; fi
	if [ -e bin/*.txt ]; then rm bin/*.txt; fi
	if [ -e bin/lib* ]; then rm bin/lib*; fi
	if [ -e bin/*.sh ]; then rm bin/*.sh; fi
	if [ -e bin/main ]; then rm bin/main; fi
