#pragma once
#include <SDL\SDL.h>
#include <string>
#include "Errors.h"
#include <iostream>

class Food
{

public:
	Food(SDL_Renderer * renderTarget, std::string filePath, int x, int y, int frameX, int frameY);
	~Food();
	SDL_Rect position;
	void Draw(SDL_Renderer *render, SDL_Rect camera);
	void Update(int mapX, int mapY);
	
private:
	int foodX, foodY;
	SDL_Texture *_texture;
	SDL_Rect _playerRect;
	int _frameWidth, _frameHeight;
	int oX, oY;
	int _textureWidth;
	

};

