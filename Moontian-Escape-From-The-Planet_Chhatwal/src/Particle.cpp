/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#include "../Includes/Particle.h"
#include <iostream>

Particle::Particle(){}
Particle::~Particle(){}

void Particle::particle_init(const char* name, SDL_Renderer* renderer, int startX, int startY, int startW, int startH)
{
    x_pos = (float)startX;
    y_pos = (float)startY;
    width = (float)startW;
    height = (float)startH;

    alive = true;
    particle_surface = IMG_Load(name);
    particle_texture = SDL_CreateTextureFromSurface(renderer, particle_surface);
}

void Particle::particle_update()
{
    x_pos += x_vel;
    y_pos += y_vel;

    if (lifetime > 0)
    {
        particle_rect.x = (int)x_pos;
        particle_rect.y = (int)y_pos;
        particle_rect.w = (int)width / 2 + width * (int)(10 * lifetime / 100);
        particle_rect.h = (int)height / 2 + height * (int)(10 * lifetime / 100);
    }
    lifetime--;
}

void Particle::particle_render(SDL_Renderer* ren)
{
    if (lifetime > 0)
    {
        SDL_RenderCopy(ren, particle_texture, NULL, &particle_rect);
    }
}

void Particle::particle_quit()
{
    SDL_FreeSurface(particle_surface);
    SDL_DestroyTexture(particle_texture);
}

int Particle::particle_get_x_vel()
{
    return (int)x_vel;
}

void Particle::particle_set_x_vel(float new_vel)
{
    x_vel = new_vel;
}

int Particle::particle_get_y_vel()
{
    return (int)y_vel;
}

void Particle::particle_set_y_vel(float new_vel)
{
    y_vel = new_vel;
}

int Particle::particle_get_x_pos()
{
    return (int)x_pos;
}

void Particle::particle_set_x_pos(float new_pos)
{
    x_pos = new_pos;
}

int Particle::particle_get_y_pos()
{
    return (int)y_pos;
}

void Particle::particle_set_y_pos(float new_pos)
{
    y_pos = new_pos;
}

int Particle::particle_get_width()
{
    return (int)width;
}

void Particle::particle_set_width(float new_w)
{
    width = new_w;
}

int Particle::particle_get_height()
{
    return (int)height;
}

void Particle::particle_set_height(float new_h)
{
    height = new_h;
}

bool Particle::get_living_status()
{
    return alive;
}

void Particle::set_living_status(bool new_status)
{
    alive = new_status;
}

int Particle::get_particle_lifetime()
{
    return lifetime;
}

void Particle::set_particle_lifetime(int new_lifetime)
{
    lifetime = new_lifetime;
}

ParticleEmitter::ParticleEmitter(){}
ParticleEmitter::~ParticleEmitter(){}

void ParticleEmitter::emitter_init(const char* name, SDL_Renderer* renderer, int startX, int startY, int width, int height)
{
    srand(5);
    
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        particles[i].particle_init(name, renderer, startX, startY, width, height);
        particles[i].particle_set_x_vel(ASTEROID_VEL - ((rand() % 30) - 30)/ 2.0);
        particles[i].particle_set_y_vel(ASTEROID_VEL - ((rand() % 30) - 30) / 2.0);
        particles[i].set_particle_lifetime(10 + (rand() % 10));
    }
}

void ParticleEmitter::emitter_update()
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        particles[i].particle_update();
    }
}

void ParticleEmitter::emitter_render(SDL_Renderer* ren)
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        particles[i].particle_render(ren);
    }
}

void ParticleEmitter::emitter_quit()
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (particles[i].get_particle_lifetime() < 0)
        {
            particles[i].particle_quit();
        }
    }
    
}