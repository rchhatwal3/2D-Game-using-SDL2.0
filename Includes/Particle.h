/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#ifndef PARTICLE_H
#define PARTICLE_H

#include "SDL2_Files.h"
#include "CONSTANTS.h"

const int MAX_PARTICLES = 25;

class Particle
{
private:
    float x_pos;
    float y_pos;
    float x_vel;
    float y_vel;

    int width;
    int height;

    bool alive;
    int lifetime;

    SDL_Rect particle_rect;
    SDL_Surface* particle_surface;
    SDL_Texture* particle_texture;
public:
    Particle();
    ~Particle();

    void particle_init(const char* name, SDL_Renderer* renderer, int startX, int startY, int startW, int startH);
    void particle_update();
    void particle_render(SDL_Renderer* ren);
    void particle_quit();

    int particle_get_x_vel();
    void particle_set_x_vel(float new_vel);
    int particle_get_y_vel();
    void particle_set_y_vel(float new_vel);

    int particle_get_x_pos();
    void particle_set_x_pos(float new_pos);
    int particle_get_y_pos();
    void particle_set_y_pos(float new_pos);
    int particle_get_width();
    void particle_set_width(float new_w);
    int particle_get_height();
    void particle_set_height(float new_h);

    bool get_living_status();
    void set_living_status(bool new_status);

    int get_particle_lifetime();
    void set_particle_lifetime(int new_lifetime);
};


class ParticleEmitter
{
private:
    Particle particles[MAX_PARTICLES];

public:
    ParticleEmitter();
    ~ParticleEmitter();

    void emitter_init(const char* name, SDL_Renderer* renderer, int startX, int startY, int width, int height);
    void emitter_update();
    void emitter_render(SDL_Renderer* ren);
    void emitter_quit();
};


#endif