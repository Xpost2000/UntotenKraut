GCC=g++
LIBS=`pkg-config --libs --cflags sdl2` `pkg-config --libs --cflags glew` -lfreetype -lOpenGL32 -lSDL2_image -lSDL2_mixer
CFLAGS=-std=gnu++11 -Wall -O2
FILES=src/main.cpp\
      src/window.cpp\
      src/input.cpp\
      src/shader.cpp\
      src/texture.cpp\
      src/renderer.cpp\
      src/sprite.cpp\
      src/entity.cpp\
      src/player.cpp\
      src/sound.cpp\
      src/bullet.cpp\
      src/font-renderer.cpp
OUTPUT=game.exe

all:
	$(GCC) $(FILES) $(LIBS) $(CFLAGS) -o bin/$(OUTPUT)	
clean:
	rm bin\\$(OUTPUT)
