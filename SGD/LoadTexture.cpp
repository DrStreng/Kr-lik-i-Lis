#include "LoadTexture.h"

SDL_Texture *LoadBG(std::string path, SDL_Renderer * render)
{
	SDL_Texture *_texture = nullptr;
	SDL_Surface *_surface = IMG_Load(path.c_str());
	if (_surface == NULL) {
		blad("_surface = NULL");
	}
	else {
		_texture = SDL_CreateTextureFromSurface(render, _surface);
		if (_texture == NULL) {
			blad("_optimized = NULL");
		}
	}
	SDL_FreeSurface(_surface);
	return _texture;
}


