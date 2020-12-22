**Background**

You are controlling an astronaut that lives on the Moon, but goes around to different planets.  On one of the planets, you had a rough landing and your rocket ship broke into many pieces.  You're mission is to retrieve all of the rocket ship pieces without being struck by a flying asteroid in order to repair your ship and get off the planet.

**Clemson Class Objective**

I made this game as part of my Clemson class CPSC 4160 - 2-D Game Engine Design, taught by Dr. Zordan.  The focus of this class was to learn the basics of game development by using SDL2.0.  This game was an overall assessment of what I had learned throughout the class

**How to Play:**

Arrow keys to move sprite around.
Only cardinal movement - using Position Delta Movement Metaphor

  * UP - Sprite walks towards North Direction
  * LEFT - Sprite walks toward West Direction
  * RIGHT - Sprite walks toward East Direction
  * DOWN - Sprite walks toward South Direction  

**In Order to Run Game**
These SDL2.0 Library files must be downloaded to your path:
  * SDL2/SDL.h
  * SDL2/SDL_image.h
  * SDL2/SDL_timer.h
  * SDL2/SDL_ttf.h

**Helper Classes:**

  * Background.cpp
  * Asteroid.cpp
  * Astronaut.cpp
  * Particle.cpp
  * EndScreen.cpp
  * Rocket.cpp
  * StartScreen.cpp
  * TextManager.cpp

**Collision Handling Method:**
  * I am using the box collider method to check for collisions.

**Collision Response:**
  * When a collision happens between the astronaut (PC) and an asteroid, the astronaut gets vaporized and the asteroid breaks into pieces and disappears.

**TTF Elements:**
  * The current amount of rockets you have and need to receive to beat the game are showed in the top left of the screen.

**Start/End Screen:**
  * There is a start and end screen for the game that has the ability to take keyboard input to enter or exit the game.

**Deployment:**

  * make clean to get rid of the .o and executable files.
  * make to compile
  * ./Moontian_Escape_from_the_Planet to run the game


