all: bin/tp3.out

all_windows: bin/tp3.exe

bin/tp3.exe: obj/main.o | bin
	g++ -Wall -Iinclude obj/main.o -o bin/tp3.exe

bin/tp3.out: obj/main.o | bin
	g++ -Wall -Iinclude obj/main.o -o bin/tp3.out

obj/main.o: src/main.cpp | obj
	g++ -Wall -Iinclude -c src/main.cpp -o obj/main.o

bin:
	mkdir bin

obj:
	mkdir obj