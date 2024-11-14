bin/game: Vector.o Entity.o Obstacle.o handle_next_event.o x\ utilities.o Polybolo.o Soldier.o Line\ Segment.o Point\ Obstacle.o Line\ Obstacle.o Point\ Obstacle.o Collisions.o\
	game.o
		g++-14 *.o -o bin/game -lX11 -std=c++20
run: bin/game
	./bin/game

Entity.o: src/Entity.c++
	g++-14 -std=c++20 -c $<
Obstacle.o: src/Obstacle.c++
	g++-14 -std=c++20 -c $<

x\ utilities.o: src/x\ utilities.c++
	g++-14 -std=c++20 -fmodules-ts -c "src/x utilities.c++"

%.o: src/%.c++
	g++-14 -std=c++20 -fmodules-ts -c $<

Line\ Segment.o: src/Line\ Segment.c++
	g++-14 -std=c++20 -fmodules-ts -c "src/Line Segment.c++"
Point\ Obstacle.o: src/Point\ Obstacle.c++
	g++-14 -std=c++20 -fmodules-ts -c "src/Point Obstacle.c++"
Line\ Obstacle.o: src/Line\ Obstacle.c++
	g++-14 -std=c++20 -fmodules-ts -c "src/Line Obstacle.c++"