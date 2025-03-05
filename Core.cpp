#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>


#include "Core.h"
#include "Data.h"

Core::Core(const char* title, int width, int height) :window(NULL), renderer(NULL) {
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL) { std::cout << "WINDOW FAILED TO INIT. ERROR: " << SDL_GetError() << std::endl; }
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) { std::cout << "RENDERER FAILED TO INIT. ERROR: " << SDL_GetError() << std::endl; }

}
SDL_Texture* Core::loadTexture(const char* filePath) {
	SDL_Texture* tex = NULL;
	tex = IMG_LoadTexture(renderer, filePath);
	if (tex == NULL) {std::cout << "FAILED TO LOAD TEXTURE. ERROR: " << SDL_GetError() << std::endl;}
	return tex;
}
void Core::cleanUp() { SDL_DestroyWindow(window); }
void Core::clear() { SDL_RenderClear(renderer); }
void Core::render(Entity& entity) {
	SDL_Rect src;
	src.x = entity.getCurrentFrame().x;
	src.y = entity.getCurrentFrame().y;
	src.w = entity.getCurrentFrame().w;
	src.h = entity.getCurrentFrame().h;
	SDL_Rect dst;
	dst.x = entity.getPos().x + (entity.getCurrentFrame().w * (1 - entity.getScale().x)) / 2;
	dst.y = entity.getPos().y + (entity.getCurrentFrame().h * (1 - entity.getScale().y)) / 2;
	dst.w = entity.getCurrentFrame().w * entity.getScale().x;
	dst.h = entity.getCurrentFrame().h * entity.getScale().y;

	SDL_RenderCopyEx(renderer, entity.getTex(), &src, &dst, entity.getAngle(), 0, SDL_FLIP_NONE);
}
void Core::render(int x, int y, SDL_Texture* Texture) {
	SDL_Rect src;
	src.x = 0; 
	src.y = 0;
	src.w;
	src.h;
	SDL_QueryTexture(Texture, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;
	SDL_RenderCopy(renderer, Texture, &src, &dst);
}
/*
* Void rendertext
*/
void Core::display() { SDL_RenderPresent(renderer); }
