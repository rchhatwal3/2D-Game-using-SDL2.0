**In Order to Run Game**
These SDL2.0 Library files must be downloaded to your path:
  * SDL2/SDL.h
  * SDL2/SDL_image.h
  * SDL2/SDL_timer.h

**Helper Classes:**

  * Background.cpp
  * Asteroid.cpp
  * Astronaut.cpp
  * Particle.cpp

**Collision Handling Method:**
  * I am using the box collider method to check for collisions.

**Collision Response:**
  * When a collision happens between the astronaut (PC) and an asteroid, the astronaut gets vaporized and the asteroid breaks into pieces and disappears.


**Deployment:**

  * make clean to get rid of the .o and executable files.
  * make to compile
  * ./Moontian_Escape_from_the_Planet to run the game

**How to Play:**

Arrow keys to move sprite around.
Only cardinal movement - using Position Delta Movement Metaphor

  * UP - Sprite walks towards North Direction
  * LEFT - Sprite walks toward West Direction
  * RIGHT - Sprite walks toward East Direction
  * DOWN - Sprite walks toward South Direction  