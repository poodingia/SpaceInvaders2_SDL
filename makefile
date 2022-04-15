all:
	g++ -Iinclude -Iinclude/sdl -Iinclude/headers -Llib -o Main src/*.cpp include/headers/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf 

	