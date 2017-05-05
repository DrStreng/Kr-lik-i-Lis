#pragma once

#include <SDL\SDL_image.h>
#include <iostream>
#include "Errors.h"

extern SDL_Texture *LoadBG(std::string path, SDL_Renderer * render);