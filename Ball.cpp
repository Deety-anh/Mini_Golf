#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<math.h>

#include "Data.h"

void Entity::update(double deltaTime){}
Ball::Ball(Vector2f Ball_Pos, SDL_Texture* Ball_Tex, SDL_Texture* Ball_pointTexture, SDL_Texture* Ball_powerMTexFG, SDL_Texture* Ball_powerMtexBG)
:Entity(Ball_Pos,Ball_Tex){
	points.push_back(Entity(Vector2f(-64, -64), Ball_pointTexture));
	powerBars.push_back(Entity(Vector2f(-64, -64), Ball_powerMtexBG));
	powerBars.push_back(Entity(Vector2f(-64, -64), Ball_powerMTexFG));
}

void Ball::setVelocity(float x, float y) { Ball_Velocity.x = x; Ball_Velocity.y = y; }
void Ball::setLaunchedVelocity(float x, float y) { Ball_launchedVelocity.x = x, Ball_launchedVelocity.y = y; }
void Ball::setInitialMousePos(float x, float y) { initialMousePos.x = x, initialMousePos.y = y; }
void Ball::setWin(bool Win) { win = Win; }
void Ball::update(double deltaTime, bool mouseDown, bool mousePressed,Hole hole) {
	if (win) {
		if (getPos().x < Target.x) { setPos(getPos().x + 0.1 * deltaTime, getPos().y); }
		else if (getPos().x > Target.x) { setPos(getPos().x - 0.1 * deltaTime, getPos().y); }
		if (getPos().y < Target.y) { setPos(getPos().x, getPos().y + 0.1 * deltaTime); }
		else if (getPos().y > Target.y) { setPos(getPos().x, getPos().y - 0.1 * deltaTime); }
		setScale(getScale().x - 0.1 * deltaTime, getScale().y - 0.1 * deltaTime); 
		return;
	}
	if (getPos().x + 4 > hole.getPos().x && getPos().x < hole.getPos().x + 4 && getPos().y + 4 > hole.getPos().y && getPos().y < hole.getPos().y + 4) {
		//play holeSfx
		setWin(true);
		//Some code here
	}
	if (mousePressed && canMove) {
		// play chargeSfx
		playedSwingFx = false;
		int mouse_X_Position = 0;
		int mouse_Y_Position = 0;
		SDL_GetMouseState(&mouse_X_Position, &mouse_Y_Position);
		setInitialMousePos(mouse_X_Position, mouse_Y_Position);
	//	std::cout << "Mouse Position: " << "x = " << getInitialMousePos().x << "   " << "y = " << getInitialMousePos().y << std::endl;
	}
	if (mouseDown && canMove) {
		int mouse_X_Position = 0;
		int mouse_Y_Position = 0;
		SDL_GetMouseState(&mouse_X_Position, &mouse_Y_Position);
		setVelocity((mouse_X_Position - getInitialMousePos().x) / -150, (mouse_Y_Position - getInitialMousePos().y) / -150);
		setLaunchedVelocity(getVelocity().x, getVelocity().y);
		velocity1D = sqrt(pow(getVelocity().x, 2) + pow(getVelocity().y, 2));
	//	std::cout << velocity1D <<"x = "<<getVelocity().x<<"   "<<"y = "<<getVelocity().y<<std::endl;
		launchedVelocity1D = velocity1D;
		/*
		* Setting point here;
		*/
		dirX = Ball_Velocity.x / abs(Ball_Velocity.x);
		dirY = Ball_Velocity.y / abs(Ball_Velocity.y);
		//Setting powerbar here
	}
	else {
		if (!playedSwingFx) {
			//play swingSfx here
			playedSwingFx = true;
			strokes++;
		}
		/*
		Setting points and powerbar here
		*/
		canMove = false;
		setPos(getPos().x + getVelocity().x * deltaTime, getPos().y + getVelocity().y * deltaTime);
		if (abs(getVelocity().x) > 0.0001 || abs(getVelocity().y) > 0.0001) {
			if(velocity1D > 0){velocity1D -= friction*deltaTime;}
			else{velocity1D = 0;}
			Ball_Velocity.x = (velocity1D / launchedVelocity1D) * abs(Ball_launchedVelocity.x) * dirX;
			Ball_Velocity.y = (velocity1D / launchedVelocity1D) * abs(Ball_launchedVelocity.y) * dirY;
			
		}
		else {
			setVelocity(0,0);
			int mouse_X_Position = 0;
			int mouse_Y_Position = 0;
			SDL_GetMouseState(&mouse_X_Position, &mouse_Y_Position);
			setInitialMousePos(mouse_X_Position, mouse_Y_Position);
			canMove = true;
		}
		if (getPos().x + getCurrentFrame().w > WINDOW_SCREEN_WIDTH) {
			Ball_Velocity.x = -abs(Ball_Velocity.x);
			dirX = -1;
		}
		else if (getPos().x < 0) {
			Ball_Velocity.x = abs(Ball_Velocity.x);
			dirX = 1;
		}
		if (getPos().y + getCurrentFrame().h > WINDOW_SCREEN_HEIGHT) {
			Ball_Velocity.y = -abs(Ball_Velocity.y);
			dirY = -1;
		}
		else if (getPos().y < 0) {
			Ball_Velocity.y = abs(Ball_Velocity.y);
			dirY = 1;
		}
		/*
		Setting tiles here
		*/
	}
}