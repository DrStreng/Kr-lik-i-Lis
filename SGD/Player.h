#pragma once
#include <SDL\SDL.h>
#include <string>
#include "Errors.h"
#include "Food.h"
#include <iostream>
#include <SDL\SDL_mixer.h>


class Player
{
public:
	Player(SDL_Renderer *renderTarget,std::string filePath,int x, int y,int frameX,int frameY, int pktIl);
	~Player();
	void Update(float delta,const Uint8 *keyState, int mapX, int mapY,int a);
	void Draw(SDL_Renderer *render,SDL_Rect camera);
	SDL_Rect position;
	bool Collision(Player &p, SDL_Renderer * renderTarget);
	//bool CollisionEnemy(Enemy & p, SDL_Renderer * renderTarget);
	bool CollisionFood(Food &f, int mapX, int mapY);
	int getoX();
	int getoY();
	bool Watter(Player &p);
	int RabbitPoints();
	int _points;
	SDL_Texture *_texture;
	SDL_Rect _playerRect;

private:

	float _moveSpeed;
	float _frame;
	int _frameWidth, _frameHeight;
	int _textureWidth;
	bool _isActive;
	SDL_Scancode keys[4];
	int oX, oY;
	int a;
	
	int pkt;
	Mix_Chunk *attack;
	Mix_Chunk *eat;
	
};

