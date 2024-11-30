CC= gcc 
#x86_64-w64-mingw32-gcc
#clang
#gcc
JAVA= -I/usr/lib/jvm/java-8-openjdk-amd64/include -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux
DBG= -g

all: lib lib-jni lib-jni-dll

init:
	mkdir obj/ -p
	mkdir lib/ -p
	rm -f ../libsmsg.so
	ln -s libsmsg/lib/libsmsg.so ../libsmsg.so

lib: clean obj/smsg.o
	$(CC) -shared -o lib/libsmsg.so obj/smsg.o

lib-jni: clean obj/smsg.o obj/jni_wrapper.o
	$(CC) $(JAVA) -shared -o lib/libjni-smsg.so obj/smsg.o obj/jni_wrapper.o

lib-jni-dll: clean
	x86_64-w64-mingw32-gcc $(JAVA) $(DBG) -c -fPIC src/jni_wrapper.c -o obj/win64_jni_wrapper.o
	x86_64-w64-mingw32-gcc $(DBG) -c -fPIC src/smsg.c -o obj/win64_smsg.o
	x86_64-w64-mingw32-gcc $(JAVA) -shared -o lib/jni-smsg.dll obj/win64_smsg.o obj/win64_jni_wrapper.o

obj/smsg.o: src/smsg.c
	$(CC) $(DBG) -c -fPIC src/smsg.c -o obj/smsg.o

obj/jni_wrapper.o: src/jni_wrapper.c
	$(CC) $(JAVA) $(DBG) -c -fPIC src/jni_wrapper.c -o obj/jni_wrapper.o

clean:
	rm -f obj/*.o