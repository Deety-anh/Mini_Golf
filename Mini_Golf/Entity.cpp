#include<iostream>
#include<vector>

#include "Data.h"	

Entity::Entity(Vector2f pos , SDL_Texture* tex) : En_Position(pos),En_Texture(tex) {
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
	SDL_QueryTexture(tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}
void Entity::setPos(double x, double y) {
	En_Position.x = x;
	En_Position.y = y;
}
void Entity::setScale(double x, double y) {
	En_Scale.x = x;
	En_Scale.y = y;
}
void Entity::setAngle(float angle) { En_Angle = angle; }