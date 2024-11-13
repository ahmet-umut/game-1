bin/game: src/game.c++
	g++-14 -std=c++17 src/game.c++ -o bin/game
run: bin/game
	./bin/game