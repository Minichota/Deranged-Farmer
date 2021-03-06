#ifndef UTIL_HPP
#define UTIL_HPP

#include <SDL2/SDL.h>

#include "vectors.hpp"

void clear_render_settings(SDL_Renderer* const renderer);
Ivec map_world(Ivec pos);
extern unsigned char* keys;
extern Ivec camera;
#endif
