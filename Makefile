all:
	g++ -I src/include -L src/lib -o zombie *.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf