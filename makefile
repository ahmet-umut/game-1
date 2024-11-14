bin/game: Line\ Obstacle.o Point\ Obstacle.o modules/handle_next_event.o modules/x_utilities.o Polybolo.o Soldier.o Line\ Segment.o handle_collision.o\
	game.o
		g++-14 *.o modules/*.o -o bin/game -lX11 -std=c++20
run: bin/game
	./bin/game


Line\ Segment.o: src/Line\ Segment.c++
	g++-14 -std=c++20 -fmodules-ts -c "src/Line Segment.c++"
Point\ Obstacle.o: src/Point\ Obstacle.c++
	g++-14 -std=c++20 -fmodules-ts -c "src/Point Obstacle.c++"
Line\ Obstacle.o: src/Line\ Obstacle.c++
	g++-14 -std=c++20 -fmodules-ts -c "src/Line Obstacle.c++"

game.o: src/game.c++
	g++-14 -std=c++20 -fmodules-ts -c src/game.c++

%.o: src/%.c++
	g++-14 -std=c++20 -c $<

modules/%.o: src/modules/%.c++
	g++-14 -std=c++20 -fmodules-ts -c $< -o $@