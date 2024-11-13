bin/game: Entity.o Obstacle.o handle_next_event.o x\ utilities.o Polybolo.o Soldier.o\
	game.o
		g++-14 game.o handle_next_event.o  x\ utilities.o Obstacle.o Entity.o Polybolo.o Soldier.o\
			-o bin/game -lX11 -std=c++20
run: bin/game
	./bin/game

Entity.o: src/Entity.c++
	g++-14 -std=c++20 -c $<

x\ utilities.o: src/x\ utilities.c++
	g++-14 -std=c++20 -fmodules-ts -c "src/x utilities.c++"

%.o: src/%.c++
	g++-14 -std=c++20 -fmodules-ts -c $<