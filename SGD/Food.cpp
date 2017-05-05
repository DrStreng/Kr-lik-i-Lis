#include "Food.h"
#include "Player.h"
#include <SDL\SDL_image.h>
#include "LoadTexture.h"
#include <iostream>


Food::Food(SDL_Renderer * renderTarget, std::string filePath, int x, int y, int frameX, int frameY)
{

	_texture = LoadBG(filePath, renderTarget);
	SDL_QueryTexture(_texture, NULL, NULL, &_playerRect.w, &_playerRect.h);

	position.x = x;
	position.y = y;
	_textureWidth = _playerRect.w;
	_playerRect.w /= frameX;
	_playerRect.h /= frameY;

	_frameWidth = position.w = _playerRect.w;
	_frameHeight = position.h = _playerRect.h;

}

Food::~Food()
{
	SDL_DestroyTexture(_texture);
}

void Food::Draw(SDL_Renderer * render, SDL_Rect camera)
{
	SDL_Rect draw = { position.x - camera.x, position.y - camera.y, position.w,position.h };
	SDL_RenderCopy(render, _texture, &_playerRect, &draw);
}

void Food::Update(int mapX, int mapY)
{
	foodX = rand() % (mapX);
	foodY = rand() % (mapY);
	if (foodX < mapX- _playerRect.w && foodX > 0 + _playerRect.w) {
		position.x = foodX;
	} else {
		Update(mapX, mapY);
	}
	if (foodY < mapY- _playerRect.h && foodY > 90 + _playerRect.h) {
		position.y = foodY;
	} else {
		Update(mapX, mapY);
	}
	std::cout <<"Mapa: "<< mapX << " " << mapY << std::endl;
	std::cout<<"Marchew: " << foodX <<" " << foodY << std::endl;

}




