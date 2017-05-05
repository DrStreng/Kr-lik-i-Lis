#pragma once
#include <SDL\SDL.h>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include <SDL\SDL_mixer.h>
#include <SDL\SDL_ttf.h>


class GameSystem
{
public:
	GameSystem();
	~GameSystem();
	void start();
	bool _GameStop;


private:
	TTF_Font *font;
	SDL_Surface	*message;
	SDL_Surface	*messagePkt;
	SDL_Texture *textTexture;
	SDL_Texture *textTexturePkt;
	SDL_Rect textRect;
	SDL_Rect textRectPkt;

	SDL_Surface	*message2;
	SDL_Surface	*messagePkt2;
	SDL_Texture *textTexture2;
	SDL_Texture *textTexturePkt2;
	SDL_Rect textRect2;
	SDL_Rect textRectPkt2;
	SDL_Color color;

	SDL_Joystick* _joystick;
	void setup();
	void gameLoop();
	SDL_Window *window;
	SDL_Renderer *renderTarget;
	SDL_Texture *texture;
	int currentTime;
	int prevTime;
	float delta;
	const Uint8 *keyState;
	SDL_Rect camerRect;
	int mapX, mapY;
	int b;
	Mix_Music *general;

	void render(Player &player1, Player &player2, Food &food1, Enemy &enemy1, Enemy &enemy2, Enemy &enemy3);

	void RenderRabbit(Player &player);
	void RenderFox(Player &player);

	
};

