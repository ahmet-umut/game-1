bin/game: Line\ Obstacle.o Point\ Obstacle.o handle_next_event.o modules/x_utilities.o Polybolos.o Soldier.o Line\ Segment.o handle_collision.o Entity.o Projectile.o\
	game.o
		g++-14 *.o modules/*.o -o bin/game -lX11 -std=c++20
run: bin/game
	./bin/game


Line\ Segment.o: src/Line\ Segment.c++
	g++-14 -std=c++20 -c "src/Line Segment.c++"
Point\ Obstacle.o: src/Point\ Obstacle.c++
	g++-14 -std=c++20 -c "src/Point Obstacle.c++"
Line\ Obstacle.o: src/Line\ Obstacle.c++
	g++-14 -std=c++20 -c "src/Line Obstacle.c++"

game.o: src/game.c++
	g++-14 -std=c++20 -fmodules-ts -c src/game.c++

handle_next_event.o: src/handle_next_event.c++
	g++-14 -std=c++20 -c src/handle_next_event.c++

%.o: src/%.c++ include/%.hh
	g++-14 -std=c++20 -c $<

modules/%.o: src/modules/%.c++
	g++-14 -std=c++20 -fmodules-ts -c $< -o $@