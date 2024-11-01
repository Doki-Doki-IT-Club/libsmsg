CC=clang
DBG= -g

all: clean lib

lib: smsg.o
	$(CC) -shared -o libsmsg.so smsg.o

smsg.o: src/smsg.c
	$(CC) $(DBG) -c -fPIC src/smsg.c

clean:
	rm -rf *.o