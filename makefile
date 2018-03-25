GCC=g++
LIBS=`pkg-config --libs --cflags sdl2` `pkg-config --libs --cflags glew` `pkg-config --libs --cflags freetype2` -lOpenGL32
CFLAGS=-std=gnu++11 -Wall -O2
FILES=src/main.cpp\
      src/window.cpp\
      src/input.cpp
OUTPUT=game.exe

all:
	$(GCC) $(FILES) $(LIBS) $(CFLAGS) -o bin/$(OUTPUT)	
clean:
	rm bin\\$(OUTPUT)
