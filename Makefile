CC=gcc
DBG= -g

all: clean lib

init:
	rm -f ../libsmsg.so
	ln -s libsmsg/lib/libsmsg.so ../libsmsg.so

lib: obj/smsg.o
	$(CC) -shared -o lib/libsmsg.so obj/smsg.o

obj/smsg.o: src/smsg.c
	$(CC) $(DBG) -c -fPIC src/smsg.c -o obj/smsg.o

clean:
	rm -f obj/*.o