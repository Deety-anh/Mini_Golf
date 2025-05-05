#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

#include "Data.h"
class Core {
public:
	Core(const char* title, int width, int height);
	SDL_Texture* loadTexture(const char* filePath);
	void cleanUp();
	void clear();
	void display();
	void render(Entity& entity);
	void render(int x, int y, SDL_Texture* texture);
	void renderText(float x, float y, const char* text, TTF_Font* font, SDL_Color color, bool isAlign);
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};