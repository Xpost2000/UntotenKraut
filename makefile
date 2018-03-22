GCC=g++
LIBS=`pkg-config --libs --cflags sdl2` `pkg-config --libs --cflags glew` -lOpenGL32
CFLAGS=-std=gnu++11 -Wall -O2
FILES=src/main.cpp\
      src/window.cpp\
      src/input.cpp
OUTPUT=game.exe

all:
	$(GCC) $(FILES) $(LIBS) $(CFLAGS) -o bin/$(OUTPUT)	
clean:
	rm bin\\$(OUTPUT)
