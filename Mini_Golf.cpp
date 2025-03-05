// Mini_Golf.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<thread>
#include<chrono>

#include "Data.h"
#include "Core.h"
#include "Resource.h"

// level here
bool gameRunning = true;
bool mouseDown = false;
bool mousePressed = false;

bool swingPlayed = false;
bool secondSwingPlayed = false;

SDL_Event event;

int state = 1; // 0 = title screen, 1 = game play, 2 = end screen

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;
//load level here
Ball ball(Vector2f(0,0),ballTexture,pointTexture,powerMeterTexture_FG,powerMeterTexture_BG);
Hole hole(Vector2f(100, 100), holeTexture);

void update() {
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = double((currentTick - lastTick)) / 10000;
	std::cout << deltaTime << std::endl;
	mousePressed = false;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				mouseDown = true;
				mousePressed = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				mouseDown = false;
			}
			break;
		}
	}
	if (state == 1) {
		ball.update(deltaTime, mouseDown, mousePressed,hole);
		//Load level
	}
//	std::cout << "Ball velocity: " << "x = " << ball.getVelocity().x << ", y = " << ball.getVelocity().y << std::endl;
//	std::cout << ball.getInitialMousePos().x << " " << ball.getInitialMousePos().y << std::endl;
}
void graphics() {
	window.clear();
	window.render(0, 0, bgTexture);
	window.render(hole);
	if (!ball.isWin()) { window.render(ball.getPos().x, ball.getPos().y, ballShadowTexture); }

	window.render(ball);
	window.display();
}

void gameRun() {
	if (state == 0) {
		//titleScreen();
	}
	else {
		update();
		graphics();
	}
}
int main(int argc, char* agrv[])
{
	using namespace std::this_thread;
	using namespace std::chrono;
	while (gameRunning) { gameRun(); /*sleep_for(seconds(1)); */ }
	window.cleanUp();
	TTF_CloseFont(font32);
	TTF_CloseFont(font24);
	SDL_Quit();
	TTF_Quit();
	return 0;
}
