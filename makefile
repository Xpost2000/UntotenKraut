GCC=g++
LIBS=`pkg-config --libs --cflags sdl2` `pkg-config --libs --cflags glew` -Wl,-Bstatic -lfreetype -Wl,-Bdynamic -lSDL2_image -lSDL2_mixer
LLIBS=`pkg-config --libs --cflags sdl2` `pkg-config --libs --cflags glew` `pkg-config --libs --cflags freetype2` -lSDL2_image -lSDL2_mixer
CFLAGS=-std=gnu++11 -O2
#compile only needed parts.
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
      src/wall.cpp\
      src/world.cpp\
      src/gun.cpp\
      src/levelloader.cpp\
      src/level.cpp\
      src/zombie.cpp\
      src/spawner.cpp\
      src/texturemanager.cpp\
      src/gunmanager.cpp\
      src/gui_text.cpp\
      src/gui_button.cpp\
      src/fsm.cpp\
      src/state.cpp\
      src/gamestate.cpp\
      src/menustate.cpp\
      src/quitstate.cpp\
      src/deathstate.cpp\
      src/barricade.cpp\
      src/detail_ent.cpp\
      src/editorstate.cpp\
      src/mapselectionstate.cpp\
      src/font-renderer.cpp
OUTPUT=game.exe
LOUTPUT=game_linux

all:
	$(GCC) $(FILES) $(LIBS) $(CFLAGS) -o bin/$(OUTPUT) -lOpenGL32	
linux:
	$(GCC) $(FILES) $(LLIBS) -lGL $(CFLAGS) -o bin/$(LOUTPUT)	
clean:
	rm bin\\$(OUTPUT)
