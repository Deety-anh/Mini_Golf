#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

#include "Core.h";
#include "Data.h"
Core  window("Twini-Golf", WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT);

SDL_Texture* ballTexture = window.loadTexture("res/gfx/ball.png");
SDL_Texture* holeTexture = window.loadTexture("res/gfx/hole.png");
SDL_Texture* pointTexture = window.loadTexture("res/gfx/point.png");
SDL_Texture* tileDarkTexture32 = window.loadTexture("res/gfx/tile32_dark.png");
SDL_Texture* tileDarkTexture64 = window.loadTexture("res/gfx/tile64_dark.png");
SDL_Texture* tileLightTexture32 = window.loadTexture("res/gfx/tile32_light.png");
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
SDL_Texture* endscreenOverlayTexture = window.loadTexture("res/gfx/end.png");
SDL_Texture* splashBgTexture = window.loadTexture("res/gfx/splashbg.png");

Mix_Chunk* chargeSfx = Mix_LoadWAV("res/sfx/charge.mp3");
Mix_Chunk* swingSfx = Mix_LoadWAV("res/sfx/swing.mp3");
Mix_Chunk* holeSfx = Mix_LoadWAV("res/sfx/hole.mp3");


SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };
TTF_Font* font32 = TTF_OpenFont("res/font/font.ttf", 32);
TTF_Font* font48 = TTF_OpenFont("res/font/font.ttf", 48);
TTF_Font* font24 = TTF_OpenFont("res/font/font.ttf", 24);