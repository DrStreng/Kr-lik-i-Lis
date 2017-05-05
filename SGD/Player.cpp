#include "Player.h"
#include <SDL\SDL_image.h>
#include "LoadTexture.h"
#include <iostream>
#include <SDL\SDL_mixer.h>



Player::Player(SDL_Renderer * renderTarget, std::string filePath, int x, int y, int frameX, int frameY,int pktIl)
{

	eat = Mix_LoadWAV("sounds/eat.wav");
	attack = Mix_LoadWAV("sounds/attack.wav");
	pkt = pktIl;
	_points  = 0.0f;
	_texture = LoadBG(filePath, renderTarget);
	SDL_QueryTexture(_texture, NULL, NULL, &_playerRect.w, &_playerRect.h);

	position.x = x;
	position.y = y;
	_textureWidth = _playerRect.w;
	_playerRect.w /= frameX;
	_playerRect.h /= frameY;
	
	_frameWidth = position.w = _playerRect.w;
	_frameHeight = position.h = _playerRect.h;

	oX = _frameWidth / 2;
	oY = _frameHeight / 2;

	_isActive = false;
	static int playerNumber = 0;
	playerNumber++;
	_moveSpeed = 150.0f;


	if (SDL_NumJoysticks() < 1) {
		
		if (playerNumber == 1) {

			keys[0] = SDL_SCANCODE_W;
			keys[1] = SDL_SCANCODE_S;
			keys[2] = SDL_SCANCODE_A;
			keys[3] = SDL_SCANCODE_D;

		} else {

			keys[0] = SDL_SCANCODE_UP;
			keys[1] = SDL_SCANCODE_DOWN;
			keys[2] = SDL_SCANCODE_LEFT;
			keys[3] = SDL_SCANCODE_RIGHT;
		}

	} else {

		if (playerNumber == 1) {

			keys[0] = SDL_SCANCODE_W;
			keys[1] = SDL_SCANCODE_S;
			keys[2] = SDL_SCANCODE_A;
			keys[3] = SDL_SCANCODE_D;

		} else {

		}
		
	}
	
}

Player::~Player()
{
	SDL_DestroyTexture(_texture);
	Mix_FreeChunk(eat);
	Mix_FreeChunk(attack);

}

void Player::Update(float delta, const Uint8 * keyState, int mapX, int mapY, int a)
{
	
	if (a != 5) {
		_isActive = true;
		if (keyState[keys[0]] || a == 2)//gora
		{
			if (0 + _playerRect.h > position.y + position.h) {
				std::cout << "y=0" << std::endl;
				position.y -= _moveSpeed * 0;
				_playerRect.y = _frameHeight * 3;
			}
			else {
				position.y -= _moveSpeed *delta;
				_playerRect.y = _frameHeight * 3;
			}
		}
		else if (keyState[keys[1]] || a == 3)//dol
		{
			if (mapY <= position.y + position.h) {
				std::cout << "y=600" << std::endl;
				position.y += _moveSpeed * 0;
				_playerRect.y = 3;
			}
			else {
				position.y += _moveSpeed *delta;
				_playerRect.y = 3;
			}
		}
		else if (keyState[keys[2]] || a == 0)//lewo
		{
			if (0 + _playerRect.w > position.x + position.w) {
				std::cout << "x=0" << std::endl;
				position.x -= _moveSpeed * 0;
				_playerRect.y = _frameHeight;
			}
			else {
				position.x -= _moveSpeed *delta;
				_playerRect.y = _frameHeight;
			}
		}
		else if (keyState[keys[3]] || a == 1)//prawo
		{
			if (mapX <= position.x + position.w) {
				std::cout << "x=800" << std::endl;
				position.x += _moveSpeed * 0;
				_playerRect.y = _frameHeight * 2;

			}
			else {
				position.x += _moveSpeed *delta;
				_playerRect.y = _frameHeight * 2;
			}
		}
		else
			_isActive = false;

		if (_isActive) {
			_frame += delta;
			if (_frame >= 0.1f)
			{
				_frame = 0;
				_playerRect.x += _frameWidth;
				if (_playerRect.x >= _textureWidth)
					_playerRect.x = 0;
			}
		} else {
			_frame = 0;
			_playerRect.x = 0;
		}

	} else {
		_frame = 0;
		_playerRect.x = 0;
	}
	
}
bool Player::Watter(Player &p)
{
	if (90 < p.position.y + p.position.h) {
		SDL_SetTextureColorMod(_texture, 255, 255, 255);
		return false;
	}
	else {
		p._points = p._points - 30;
		SDL_SetTextureColorMod(_texture, 255, 0, 0);
		return true;
	}
}

int Player::RabbitPoints()
{
	return _points;
}

void Player::Draw(SDL_Renderer * renderTarget, SDL_Rect camera)
{
	SDL_Rect draw = { position.x - camera.x, position.y - camera.y, position.w,position.h };
	SDL_RenderCopy(renderTarget, _texture, &_playerRect, &draw);

}
bool Player::Collision(Player &p, SDL_Renderer * renderTarget)
{
	if (position.x + position.w < p.position.x+9 || position.x+9 > p.position.x + p.position.w ||
		position.y + position.h < p.position.y+9 || position.y+9 > p.position.y + p.position.h) 
	{
		SDL_SetTextureColorMod(_texture, 255, 255, 255);
		return false;
	} else {
			Mix_PlayChannel(-1, attack, 0);
			p._points = p._points + (50 * pkt);
			_playerRect.x = _playerRect.y= _playerRect.w = _playerRect.h=0;
			_texture = LoadBG("img/dead.png", renderTarget);
			SDL_QueryTexture(_texture, NULL, NULL, &_playerRect.w, &_playerRect.h);
		return true;
	}
}

bool Player::CollisionFood(Food &f,int mapX, int mapY)
{
	if (position.x + position.w < f.position.x + 9 || position.x + 9 > f.position.x + f.position.w ||
		position.y + position.h < f.position.y + 9 || position.y + 9 > f.position.y + f.position.h)
	{
		SDL_SetTextureColorMod(_texture, 255, 255, 255);
		return false;
	} else {
		Mix_PlayChannel(-1, eat, 0);
		_points = _points +(1*pkt);
		f.Update(mapX, mapY);
		RabbitPoints();
		return true;
	}
}

int Player::getoX()
{
	return position.x + oX;
	
}

int Player::getoY()
{
	return position.y+ oY;
}



