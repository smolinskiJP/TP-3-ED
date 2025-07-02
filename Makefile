all: bin/tp3.out

all_windows: bin/tp3.exe

bin/tp3.exe: obj/main.o obj/LogicSystem.o | bin
	g++ -Wall -Iinclude obj/main.o obj/LogicSystem.o -o bin/tp3.exe

bin/tp3.out: obj/main.o obj/LogicSystem.o | bin
	g++ -Wall -Iinclude obj/main.o obj/LogicSystem.o -o bin/tp3.out

obj/main.o: src/main.cpp | obj
	g++ -Wall -Iinclude -c src/main.cpp -o obj/main.o

obj/LogicSystem.o: src/LogicSystem.cpp include/LogicSystem.hpp | obj
	g++ -Wall -Iinclude -c src/LogicSystem.cpp -o obj/LogicSystem.o

bin:
	mkdir bin

obj:
	mkdir obj