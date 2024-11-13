bin/game: Obstacle.o handle_next_event.o x\ utilities.o game.o
	g++-14 game.o handle_next_event.o  x\ utilities.o Obstacle.o \
		-o bin/game -lX11 -std=c++17
run: bin/game
	./bin/game

handle_next_event.o: src/handle_next_event.c++
	g++-14 -std=c++17 -fmodules-ts -c src/handle_next_event.c++
game.o: src/game.c++
	g++-14 -std=c++17 -fmodules-ts -c src/game.c++
x\ utilities.o: src/x\ utilities.c++
	g++-14 -std=c++17 -fmodules-ts -c src/x\ utilities.c++
Obstacle.o: src/Obstacle.c++
	g++-14 -std=c++17 -fmodules-ts -c src/Obstacle.c++