# A simple Makefile for SDL projects

# set the compiler
CC = g++

# set the compiler flags
CFLAGS = `sdl2-config --libs --cflags` -ggdb3 -O0 -lSDL2_image -lSDL2_ttf -lm

# add header files here
HDRS = game_engine.h gameObject.h playerSpriteManager.h backgroundManager.h tileManager.h textureLoader.h particle.h collision_detection.h collision_handler.h obj_node.h particle_generator.h fontManager.h UI.h enemy_generator.h

# add source files here
SRCS = main.cpp game_engine.cpp gameObject.cpp playerSpriteManager.cpp backgroundManager.cpp tileManager.cpp textureLoader.cpp particle.cpp collision_detection.cpp collision_handler.cpp obj_node.cpp particle_generator.cpp fontManager.cpp UI.cpp enemy_generator.cpp

# generate names of object files
OBJS = $(SRCS:.cpp=.o)

# name of executable
EXEC = my_game

# default recipe
all: $(EXEC)

#showfont: showfont.c Makefile
#    $(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

#glfont: glfont.c Makefile
#    $(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files
$(OBJS): $(@:.o=.cpp) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.cpp) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC)
	rm -f $(OBJS)


run:
	./my_game
