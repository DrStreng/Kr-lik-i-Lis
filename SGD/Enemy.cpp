#include "Enemy.h"
#include <string>
#include <SDL\SDL_image.h>
#include "LoadTexture.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <SDL\SDL_mixer.h>

Enemy::Enemy(SDL_Renderer * renderTarget, std::string filePath, int x, int y, int frameX, int frameY)
{
	eat = Mix_LoadWAV("sounds/eat.wav");
	_texture = LoadBG(filePath, renderTarget);
	SDL_QueryTexture(_texture, NULL, NULL, &_playerRect.w, &_playerRect.h);

	position.x = x;
	position.y = y;
	_textureWidth = _playerRect.w;
	_playerRect.w /= frameX;
	_playerRect.h /= frameY;

	_frameWidth = position.w = _playerRect.w;
	_frameHeight = position.h = _playerRect.h;
	speed = 0;
	
}

Enemy::~Enemy()
{
	SDL_DestroyTexture(_texture);
}

void Enemy::Draw(SDL_Renderer * render, SDL_Rect camera)
{
	SDL_Rect draw = { position.x - camera.x, position.y - camera.y, position.w,position.h };
	SDL_RenderCopy(render, _texture, &_playerRect, &draw);
}

void Enemy::UpdateEnemy(float delta, Player &p1, Player &p2,bool kwiat)
{
	_moveSpeed = 150.0f;
	
	speed++;

	int x1 = abs(position.x - p1.position.x);
	int y1 = abs(position.y - p1.position.y);
	double fox = sqrt((x1*x1) + (y1*y1));
	int x2 = abs(position.x - p2.position.x);
	int y2 = abs(position.y - p2.position.y);
	double rabbit = sqrt((x2*x2) + (y2*y2));

	if (speed == 3) {

		if (fox < rabbit) {
			move(p1, delta, kwiat);
		} else {
			move(p2, delta, kwiat);
		}
		speed = 0;
	}
	
	 _frame += delta;
	 if (_frame >= 0.1f)
	 {
		 _frame = 0;
		 _playerRect.x += _frameWidth;
		 if (_playerRect.x >= _textureWidth)
			 _playerRect.x = 0;
	 }
}


void Enemy::move(Player & p, float delta,bool kwiat)
{
	if (p.position.x < position.x)
	{
		if (!kwiat) {
			position.x -= _moveSpeed *delta;
		}
		_playerRect.y = _frameHeight;//kk
	}
	if (p.position.x > position.x) {
		if (!kwiat) {
			position.x += _moveSpeed *delta;
		}
		_playerRect.y = _frameHeight * 2;
	}

	if (p.position.y < position.y)
	{
		if (!kwiat) {
			position.y -= _moveSpeed*delta;
		}
		
		_playerRect.y = _frameHeight * 3;//gora
	}
	if (p.position.y > position.y)
	{
		if (!kwiat) {
			position.y += _moveSpeed*delta;
		}
		_playerRect.y = 3;//dol
	}
}
bool Enemy::CollisionEnemy(Player & e, SDL_Renderer * renderTarget, bool animal)
{
	if (position.x + position.w < e.position.x +9  || position.x+9  > e.position.x + e.position.w ||
		position.y + position.h < e.position.y+9  || position.y+9  > e.position.y + e.position.h)
	{
		SDL_SetTextureColorMod(_texture, 255, 255, 255);
		return false;
	}
	else {
		if (animal) {
			e._texture = LoadBG("img/foxdead.png", renderTarget);
			e._points = e._points - 15;
		} else {
			e._texture = LoadBG("img/dead.png", renderTarget);
			e._points = e._points - 20;
		}
		e._playerRect.x = e._playerRect.y = e._playerRect.w = e._playerRect.h = 0;
		SDL_QueryTexture(e._texture, NULL, NULL, &e._playerRect.w, &e._playerRect.h);
		Mix_PlayChannel(-1, eat, 0);
		return true;
	}
}
