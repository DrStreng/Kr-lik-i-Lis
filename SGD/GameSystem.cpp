#include "GameSystem.h"
#include <iostream>
#include "Errors.h"
#include <SDL\SDL_image.h>
#include "Player.h"
#include "LoadTexture.h"
#include <SDL\SDL_mixer.h>
#include "Food.h"
#include <SDL\SDL_ttf.h>
#include "Enemy.h"

GameSystem::GameSystem()
{
	_GameStop = true;
	window = nullptr;
	renderTarget = nullptr;
	currentTime = 0;
	prevTime = 0;
	color = { 6, 47, 50, 1 };
	delta = 0.0f;
	camerRect = { 0 ,0 ,800, 600 };
	_joystick = nullptr;

	font= NULL;
	message = NULL;
	message2 = NULL;

	textRect.x = 120;
	textRect.y = 30;
	textRect2.x = 100;
	textRect2.y = 0;
	textRectPkt.x = 0;
	textRectPkt.y = 30;
	textRectPkt2.x = 0; 
	textRectPkt2.y = 0;

	
}

GameSystem::~GameSystem()
{
	SDL_FreeSurface(message);
	SDL_FreeSurface(message2);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyTexture(texture);
	Mix_FreeMusic(general);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(textTexture2);
	textTexture = nullptr;
	textTexture2 = nullptr;
	message = nullptr;
	message2 = nullptr;
	general = nullptr;
	renderTarget = nullptr;
	window = nullptr;
	texture = nullptr;
	if (_joystick != NULL) {
		SDL_JoystickClose(_joystick);
	}
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

}

void GameSystem::start()
{
	setup();
	gameLoop();
}

void GameSystem::setup()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO);

	window = SDL_CreateWindow("SDL SGD Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024) < 0) {
		blad("cos z muzyka jest nie tak");
	}
	general = Mix_LoadMUS("sounds/generalmp3cut.mp3");

	texture = LoadBG("img/grassland11.png", renderTarget);
	SDL_QueryTexture(texture, NULL, NULL, &mapX, &mapY);

	if (TTF_Init() < 0) {
		blad("cos z ttf jest nie tak");
	}


	font = TTF_OpenFont("TTF/Capture_it.ttf", 30);


	messagePkt = TTF_RenderText_Solid(font, "Rabbit:", color);
	textTexturePkt = SDL_CreateTextureFromSurface(renderTarget, messagePkt);
	SDL_QueryTexture(textTexturePkt, NULL, NULL, &textRectPkt.w, &textRectPkt.h);
	messagePkt2 = TTF_RenderText_Solid(font, "Fox:", color);
	textTexturePkt2 = SDL_CreateTextureFromSurface(renderTarget, messagePkt2);
	SDL_QueryTexture(textTexturePkt2, NULL, NULL, &textRectPkt2.w, &textRectPkt2.h);

	if (SDL_NumJoysticks() < 1) {
		std::cout << "Brak pada " << std::endl;
		b = 4;
	} else {
		b = 5;
		_joystick = SDL_JoystickOpen(0);
		std::cout << "Controler: " << SDL_JoystickName(_joystick) << std::endl;
		std::cout << "Num Axes: " << SDL_JoystickNumAxes(_joystick) << std::endl;
		std::cout << "Num Buttons: " << SDL_JoystickNumButtons(_joystick) << std::endl;
	}
		
}


void GameSystem::gameLoop()
{

	Player player1(renderTarget, "img/monster018-fox.png", 100, 100, 4, 4, 2);
	Player player2(renderTarget, "img/rabbit.png", 200, 300, 3, 4, 1);
	Food  food1(renderTarget, "img/marchew.png", 200, 200, 1, 1);
	Enemy enemy1(renderTarget, "img/Anaconda.png", 300, 300, 3, 4);
	Enemy enemy2(renderTarget, "img/kwiat1.png", 400, 400, 3, 4);
	Enemy enemy3(renderTarget, "img/kwiat2.png", 500, 300, 3, 4);

	bool isRuning = true;
	
	SDL_Event event;
	if (!Mix_PlayingMusic()) {
		Mix_PlayMusic(general, -1);
	}
	RenderFox(player1);
	RenderRabbit(player2);
	int pp1 = player1.RabbitPoints();
	int pp2 = player2.RabbitPoints();


	while (isRuning) {

			while (SDL_PollEvent(&event) != 0) {
				switch (event.type) {
				case SDL_QUIT:
					isRuning = false;
					break;
				}
			}

			while (_GameStop) {

				prevTime = currentTime;
				currentTime = SDL_GetTicks();
				delta = (currentTime - prevTime) / 1000.0f;

				while (SDL_PollEvent(&event) != 0) {
					switch (event.type) {
					case SDL_QUIT:
						_GameStop = false;
						isRuning = false;
						break;
					case SDL_JOYAXISMOTION:
						if (event.jaxis.which == 0) {
							if (event.jaxis.axis == 0) {
								if (event.jaxis.value < -8000) {
									std::cout << "Lewo" << std::endl;
									b = 0;
								}
								else if (event.jaxis.value == 0) {
									std::cout << "STOP" << std::endl;
									b = 5;
								}
								else if (event.jaxis.value > 8000) {
									std::cout << "Prawo" << std::endl;
									b = 1;
								}
							}
							if (event.jaxis.axis == 1) {
								if (event.jaxis.value < -8000) {
									std::cout << "Gora" << std::endl;
									b = 2;
								}
								else if (event.jaxis.value > 8000) {
									std::cout << "Dol" << std::endl;
									b = 3;
								}
								else if (event.jaxis.value == 0) {
									std::cout << "STOP" << std::endl;
									b = 5;
								}
							}
						}
					}
				}

				keyState = SDL_GetKeyboardState(NULL);
				int d = 4;
				player1.Update(delta, keyState, mapX, mapY, d);
				player2.Update(delta + delta*0.3f, keyState, mapX, mapY, b);
				enemy1.UpdateEnemy(delta - delta*0.6f, player1, player2, false);
				enemy2.UpdateEnemy(delta - delta*0.6f, player1, player2, true);
				enemy3.UpdateEnemy(delta - delta*0.6f, player1, player2, true);

				camerRect.x = player2.getoX() - 400;
				camerRect.y = player2.getoY() - 400;

				if (camerRect.x < 0) { camerRect.x = 0; }
				if (camerRect.y < 0) { camerRect.y = 0; }
				if (camerRect.x + camerRect.w >= mapX) { camerRect.x = mapX - 800; }
				if (camerRect.y + camerRect.h >= mapY) { camerRect.y = mapY - 600; }

				player1.CollisionFood(food1, mapX, mapY);
				player2.CollisionFood(food1, mapX, mapY);
				enemy1.CollisionEnemy(player1, renderTarget, true);
				enemy1.CollisionEnemy(player2, renderTarget, false);
				player2.Collision(player1, renderTarget);
				player1.Watter(player1);
				player2.Watter(player2);

				bool watter2 = player2.Watter(player2);
				bool watter = player1.Watter(player1);
				bool a = player2.Collision(player1, renderTarget);
				bool enem1 = enemy1.CollisionEnemy(player1, renderTarget, true);
				bool enem2 = enemy1.CollisionEnemy(player2, renderTarget, false);
				bool enem3 = enemy2.CollisionEnemy(player1, renderTarget, true);
				bool enem4 = enemy2.CollisionEnemy(player2, renderTarget, false);
				bool enem5 = enemy3.CollisionEnemy(player1, renderTarget, true);
				bool enem6 = enemy3.CollisionEnemy(player2, renderTarget, false);

				if (enem2 || enem1 || enem3 || enem4 || enem5 || enem6 || a || watter || watter2) {
					_GameStop = false;
				}

				if (pp1 != player1.RabbitPoints()) {
					RenderFox(player1);
					pp1 = player1.RabbitPoints();
				}
				if (pp2 != player2.RabbitPoints()) {
					RenderRabbit(player2);
					pp2 = player2.RabbitPoints();
				}

				render(player1, player2, food1, enemy1, enemy2, enemy3);
			}
	}
}

void GameSystem::RenderRabbit(Player &player)
{
	std::string s = std::to_string(player.RabbitPoints());
	char const *pchar = s.c_str();
	message = TTF_RenderText_Solid(font, pchar, color);
	textTexture = SDL_CreateTextureFromSurface(renderTarget, message);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
}

void GameSystem::RenderFox(Player &player)
{
	std::string s = std::to_string(player.RabbitPoints());
	char const *pchar = s.c_str();
	message2 = TTF_RenderText_Solid(font, pchar, color);
	textTexture2 = SDL_CreateTextureFromSurface(renderTarget, message2);
	SDL_QueryTexture(textTexture2, NULL, NULL, &textRect2.w, &textRect2.h);
}

void GameSystem::render(Player &player1, Player &player2, Food &food1,Enemy &enemy1,Enemy &enemy2, Enemy &enemy3)
{

	SDL_RenderClear(renderTarget);
	SDL_RenderCopy(renderTarget, texture, &camerRect, NULL);
	food1.Draw(renderTarget, camerRect);
	player1.Draw(renderTarget, camerRect);
	player2.Draw(renderTarget, camerRect);
	enemy1.Draw(renderTarget, camerRect);
	enemy2.Draw(renderTarget, camerRect);
	enemy3.Draw(renderTarget, camerRect);
	SDL_RenderCopy(renderTarget, textTexturePkt, NULL, &textRectPkt);
	SDL_RenderCopy(renderTarget, textTexture, NULL, &textRect);
	SDL_RenderCopy(renderTarget, textTexturePkt2, NULL, &textRectPkt2);
	SDL_RenderCopy(renderTarget, textTexture2, NULL, &textRect2);
	SDL_RenderPresent(renderTarget);


}








