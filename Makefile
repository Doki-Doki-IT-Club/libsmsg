CC= gcc
#x86_64-w64-mingw32-gcc-win32
#x86_64-w64-mingw32-gcc
#clang
#gcc
JAVA= -I/usr/lib/jvm/java-8-openjdk-amd64/include -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux
DBG= -g

all: clean lib

init:
	mkdir obj/ -p
	mkdir lib/ -p
	rm -f ../libsmsg.so
	ln -s libsmsg/lib/libsmsg.so ../libsmsg.so

lib: obj/smsg.o
	$(CC) -shared -o lib/libsmsg.so obj/smsg.o

lib-jni: obj/smsg.o obj/jni_wrapper.o
	$(CC) $(JAVA) -shared -o lib/libsmsg-jni.so obj/smsg.o obj/jni_wrapper.o

obj/smsg.o: src/smsg.c
	$(CC) $(DBG) -c -fPIC src/smsg.c -o obj/smsg.o

obj/jni_wrapper.o: src/jni_wrapper.c
	$(CC) $(JAVA) $(DBG) -c -fPIC src/jni_wrapper.c -o obj/jni_wrapper.o

dll: obj/smsg.o obj/jni_wrapper.o
	x86_64-w64-mingw32-gcc-win32 $(JAVA) -shared -o lib/libsmsg-jni.dll obj/smsg.o obj/jni_wrapper.o

clean:
	rm -f obj/*.o