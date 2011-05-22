#ifndef SDL_LOGGER_H_INCLUDED
#define SDL_LOGGER_H_INCLUDED 1

#include <SDL.h>
#include "logger.h"

#define SDL_ERROR(func_name) LOG_ERROR(#func_name "() failed: %s", SDL_GetError())

#endif SDL_LOGGER_H_INCLUDED
