#include "Errors.h"
#include <iostream>
#include <SDL\SDL.h>

void blad(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Pres key to Exit" << std::endl;
	int key;
	std::cin >> key;
	SDL_Quit();
}