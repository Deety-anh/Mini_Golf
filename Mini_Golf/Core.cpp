#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>


#include "Data.h"
#include "Core.h"

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
void Core::render(Entity& obj) {
	SDL_Rect src;
	src.x = obj.getCurrentFrame().x;
	src.y = obj.getCurrentFrame().y;
	src.w = obj.getCurrentFrame().w;
	src.h = obj.getCurrentFrame().h;
	SDL_Rect dst;
	dst.x = obj.getPos().x + (obj.getCurrentFrame().w * (1 - obj.getScale().x)) / 2;
	dst.y = obj.getPos().y + (obj.getCurrentFrame().h * (1 - obj.getScale().y)) / 2;
	dst.w = obj.getCurrentFrame().w * obj.getScale().x;
	dst.h = obj.getCurrentFrame().h * obj.getScale().y;

	SDL_RenderCopyEx(renderer, obj.getTex(), &src, &dst, obj.getAngle(), 0, SDL_FLIP_NONE);
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
void Core::renderText(float x, float y, const char* text, TTF_Font* font, SDL_Color color, bool isAlign) {
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, color);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surfaceMessage->w;
	src.h = surfaceMessage->h;

	SDL_Rect dst;
	dst.w = src.w;
	dst.h = src.h;
	if (isAlign) {
		dst.x = WINDOW_SCREEN_WIDTH / 2 - src.w / 2 + x;
		dst.y = WINDOW_SCREEN_HEIGHT / 2 - src.h / 2 + y;
	}
	else {
		dst.x = x;
		dst.y = y;
	}

	SDL_RenderCopy(renderer, message, &src, &dst);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}
void Core::display() { SDL_RenderPresent(renderer); }
