#pragma once
#include <SDL\SDL.h>
#include <string>
#include "Errors.h"
#include "Player.h"
#include <iostream>

class Enemy
{
public:
	Enemy(SDL_Renderer * renderTarget, std::string filePath, int x, int y, int frameX, int frameY);
	~Enemy();
	SDL_Rect position;
	void Draw(SDL_Renderer *render, SDL_Rect camera);
	void UpdateEnemy(float delta,  Player & p1, Player & p2, bool kwiat);
	bool CollisionEnemy(Player & e, SDL_Renderer * renderTarget,bool animal);

private:
	SDL_Texture *_texture;
	SDL_Rect _playerRect;
	int _frameWidth, _frameHeight;
	int _textureWidth;
	float _moveSpeed;
	float _frame;
	int speed = 0;
	void move(Player & pp, float delta, bool kwiat);
	Mix_Chunk *eat;
};



