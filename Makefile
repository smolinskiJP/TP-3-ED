all: bin/tp3.out

all_windows: bin/tp3.exe

bin/tp3.exe: obj/main.o obj/LogicSystem.o obj/Event.o | bin
	g++ -Wall -Iinclude obj/main.o obj/LogicSystem.o obj/Event.o -o bin/tp3.exe

bin/tp3.out: obj/main.o obj/LogicSystem.o obj/Event.o | bin
	g++ -Wall -Iinclude obj/main.o obj/LogicSystem.o obj/Event.o -o bin/tp3.out

obj/main.o: src/main.cpp include/LogicSystem.hpp | obj
	g++ -Wall -Iinclude -c src/main.cpp -o obj/main.o

obj/LogicSystem.o: src/LogicSystem.cpp include/LogicSystem.hpp include/AVL.hpp include/DynamicArray.hpp include/Event.hpp include/Node.hpp | obj
	g++ -Wall -Iinclude -c src/LogicSystem.cpp -o obj/LogicSystem.o

obj/Event.o: src/Event.cpp include/Event.hpp | obj
	g++ -Wall -Iinclude -c src/Event.cpp -o obj/Event.o

bin:
	mkdir bin

obj:
	mkdir obj