#ifndef SDL_LOGGER_HPP_INCLUDED
#define SDL_LOGGER_HPP_INCLUDED

#include <SDL.h>
#include "logger.hpp"

#define SDL_ERROR(func_name) ERROR(#func_name "() failed: %s", SDL_GetError())

#endif // !defined(SDL_LOGGER_HPP_INCLUDED)
