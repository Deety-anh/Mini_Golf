#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

#include "Core.h"
#include "Data.h"
bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0) { std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl; }
	if (!(IMG_Init(IMG_INIT_PNG))){ std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;}
	if (!(TTF_Init())) { std::cout << "TTF_init has failed. Error: " << SDL_GetError() << std::endl; }
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	return true;
}

bool SDLinit = init();
Core window("Mini-Golf", WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT);

SDL_Texture* ballTexture = window.loadTexture("res/gfx/ball.png");
SDL_Texture* holeTexture = window.loadTexture("res/gfx/hole.png");
SDL_Texture* pointTexture = window.loadTexture("res/gfx/point.png");
SDL_Texture* tileDarkTexture48 = window.loadTexture("res/gfx/tile32_dark.png");
SDL_Texture* tileDarkTexture64 = window.loadTexture("res/gfx/tile64_dark.png");
SDL_Texture* tileLightTexture48 = window.loadTexture("res/gfx/tile32_light.png");
SDL_Texture* tileLightTexture64 = window.loadTexture("res/gfx/tile64_light.png");
SDL_Texture* ballShadowTexture = window.loadTexture("res/gfx/ball_shadow.png");
SDL_Texture* bgTexture = window.loadTexture("res/gfx/bg.png");
SDL_Texture* uiBgTexture = window.loadTexture("res/gfx/UI_bg.png");
SDL_Texture* levelTextBgTexture = window.loadTexture("res/gfx/levelText_bg.png");
SDL_Texture* powerMeterTexture_FG = window.loadTexture("res/gfx/powermeter_fg.png");
SDL_Texture* powerMeterTexture_BG = window.loadTexture("res/gfx/powermeter_bg.png");
SDL_Texture* powerMeterTexture_overlay = window.loadTexture("res/gfx/powermeter_overlay.png");
SDL_Texture* logoTexture = window.loadTexture("res/gfx/logo.png");
SDL_Texture* click2start = window.loadTexture("res/gfx/click2start.png");
SDL_Texture* endscreenOverlayTexture = window.loadTexture("res/gfx/endscreen_overlay.png");
SDL_Texture* endTexture = window.loadTexture("res/gfx/end.png");
SDL_Texture* splashBgTexture = window.loadTexture("res/gfx/splashbg.png");

Mix_Chunk* chargeSfx = Mix_LoadWAV("res/sfx/charge.wav");
Mix_Chunk* swingSfx = Mix_LoadWAV("res/sfx/swing.wav");
Mix_Chunk* holeSfx = Mix_LoadWAV("res/sfx/hole.wav");

SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };
TTF_Font* font32 = TTF_OpenFont("res/font/font.ttf", 32);
TTF_Font* font48 = TTF_OpenFont("res/font/font.ttf", 48);
TTF_Font* font24 = TTF_OpenFont("res/font/font.ttf", 24);


std::vector<Tile> LoadData(short level, Ball* ball, Hole* hole, short* state) {
	std::vector<Tile> ret;
	ball->setVelocity(0, 0);
	ball->setScale(1, 1);
	ball->setWin(false);
	switch (level) {
	case 1:
		ball->setPos(240, 576);
		hole->setPos(240, 144);
		ret.push_back(Tile(Vector2f(192, 240), tileLightTexture64));
		ret.push_back(Tile(Vector2f(192, 336), tileLightTexture64));

		break;
	case 2:
		ball->setPos(240, 0);
		hole->setPos(240, 480);
		ret.push_back(Tile(Vector2f(0, 96), tileLightTexture64));
		ret.push_back(Tile(Vector2f(96, 96), tileLightTexture64));
		ret.push_back(Tile(Vector2f(384, 96), tileLightTexture64));
		ret.push_back(Tile(Vector2f(288, 96), tileLightTexture64));
		ret.push_back(Tile(Vector2f(192, 240), tileLightTexture48));
		ret.push_back(Tile(Vector2f(240, 240), tileLightTexture48));
		break;
	case 3:
		ball->setPos(213, 360);
		hole->setPos(69, 552);
		ret.push_back(Tile(Vector2f(144, 288), tileLightTexture48));
		ret.push_back(Tile(Vector2f(144, 384), tileLightTexture48));
		ret.push_back(Tile(Vector2f(240, 288), tileLightTexture48));
		ret.push_back(Tile(Vector2f(240, 384), tileLightTexture48));
		break;
	default:
		*state = 2;
		break;
	}
	for (short i = 0; i < ret.size(); i++) { ret[i].setAngle(0); }
	return ret;
}