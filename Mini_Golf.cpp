// Mini_Golf.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<string>
#include "Data.h"
#include "Core.h"
#include "Resource.h"


// level here
short level = 1;
bool gameRunning = true;
bool mouseDown = false;
bool mousePressed = false;

bool swingPlayed = false;
bool secondSwingPlayed = false;

SDL_Event event;

short state = 0; // 0 = title screen, 1 = game play, 2 = end screen

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

Ball ball(Vector2f(0,0),ballTexture,pointTexture,powerMeterTexture_FG,powerMeterTexture_BG);
Hole hole(Vector2f(0, 0), holeTexture);
std::vector<Tile>tiles = LoadData(level, &ball, &hole, &state);

std::string getStrokeText() {
	std::string s = std::to_string( ball.getStorkes()); s = "STROKES: " + s;
	return s;
}

std::string getLevelText() {
	char lv = '0' + level;
	std::string s = "HOLE: ";s += lv;
	return s;
}

void titleScreen() {
	if (SDL_GetTicks() < 2000) {
		if (!swingPlayed) {
			Mix_PlayChannel(-1, swingSfx, 0);
			swingPlayed = true;
		}
		while (SDL_PollEvent(&event)) {
			switch (event.type){
			case SDL_QUIT:
				gameRunning = false;
				break;
			}
		}
		window.clear();
		window.render(0, 0, bgTexture);
		window.render(0, 0, splashBgTexture);
		window.renderText(0, 0 + 3, "POLYMARS", font32, black, 1);
		window.renderText(0, 0, "POLYMARS", font32, white, 1);

	}
	else {
		if (!secondSwingPlayed) {
			Mix_PlayChannel(-1, swingSfx, 0);
			secondSwingPlayed = true;
		}
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());
		
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				gameRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					Mix_PlayChannel(-1, holeSfx, 0);
					state = 1;
				}
				break;
			}
		}
		window.clear();
		window.render(0, 0, bgTexture);
		window.render(320 - 160, 240 - 100 - 50 + 4 * sin(SDL_GetTicks() * (PI / 1500)), logoTexture);
		window.render(0, 0, click2start);
		window.renderText(0, 240 - 48 + 3 - 24 - 6, "LEFT CLICK TO START", font48, black, 1);
		window.renderText(0, 240 - 48 - 24 -6, "LEFT CLICK TO START", font48, white,1);
		window.display();
	}
}
void update() {
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = double((currentTick - lastTick)) / 10000;
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
		ball.update(deltaTime, mouseDown, mousePressed, hole,tiles, holeSfx, chargeSfx, swingSfx);
		if (ball.getScale().x < -1) {
			level++;
			tiles = LoadData(level, &ball, &hole, &state);
		}
		//Load level
	}
//	std::cout << "Ball velocity: " << "x = " << ball.getVelocity().x << ", y = " << ball.getVelocity().y << std::endl;
	std::cout << ball.getInitialMousePos().x << " " << ball.getInitialMousePos().y << std::endl;
}
void graphics() {
	window.clear();
	window.render(0, 0, bgTexture);
	window.render(hole);
	if (!ball.isWin()) {
		window.render(ball.getPos().x, ball.getPos().y, ballShadowTexture);
		if (mouseDown) {
			for (Entity& point : ball.getPoints()) { window.render(point); }
			for (Entity& pBar : ball.getPowerBar()) { pBar.setAngle(0); window.render(pBar); }
		}
		for (Tile& t : tiles) { window.render(t); }
		window.render(ball);
	}
	if (state != 2) {
		window.render(0, 703, levelTextBgTexture);
		window.renderText(-176, 352,   getLevelText().c_str(), font24, black, 1);
		window.renderText(-176, 352, getLevelText().c_str(), font24, white, 1);
	//	std::cout << getStrokeText() << std::endl;
		window.render(290, 0, uiBgTexture);
		window.renderText(160 , -352, getStrokeText().c_str(), font24, black, 1);
		window.renderText(160,-352, getStrokeText().c_str(), font24, white, 1);
	}
	else {
		window.render(0, 0, endscreenOverlayTexture);
		window.render(0, 296, endTexture);
		window.renderText(0, 3, "YOU COMPLETED THE COURSE", font32, black,1);
		window.renderText(0, 0, "YOU COMPLETED THE COURSE", font32, white, 1);
	}
	window.display();
}

void gameRun() {
	if (state == 0) {
		titleScreen();
	}
	else {
		update();
		graphics();
	}
}
int main(int argc, char* agrv[])
{
	while (gameRunning) { gameRun(); /*sleep_for(seconds(1)); */ }
	window.cleanUp();
	TTF_CloseFont(font32);
	TTF_CloseFont(font24);
	SDL_Quit();
	TTF_Quit();
	return 0;
}
