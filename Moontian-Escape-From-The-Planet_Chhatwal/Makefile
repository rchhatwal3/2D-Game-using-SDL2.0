# A simple Makefile for SDL projects

# set the compiler
CC = g++

# set the compiler flags
CFLAGS = `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2_image -lSDL2_ttf -lm -v -std=c++14

# add header files here
HDRS = Includes/GameEngine.h Includes/CONSTANTS.h Includes/SDL2_Files.h Includes/Astronaut.h Includes/Asteroid.h Includes/Background.h Includes/Particle.h Includes/TextManager.h Includes/Rocket.h Includes/StartScreen.h Includes/EndScreen.h

# add source files here
SRCS = src/main.cpp  src/GameEngine.cpp src/Astronaut.cpp src/Asteroid.cpp src/Background.cpp src/Particle.cpp src/TextManager.cpp src/Rocket.cpp src/StartScreen.cpp src/EndScreen.cpp

# generate names of object files
OBJS = $(SRCS:.cpp=.o)

# name of executable
EXEC = Moontian_Escape_from_the_Planet

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

