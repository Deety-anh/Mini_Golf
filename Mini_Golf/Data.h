#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include<vector>

const double friction = 0.0015;
const double PI = 3.1415;
const int WINDOW_SCREEN_WIDTH = 486;
const int WINDOW_SCREEN_HEIGHT = 735;

struct Vector2f {
	Vector2f(): x(0.0f), y(0.0f) {}
	Vector2f(double p_x, double p_y) : x(p_x), y(p_y) {}
	double x, y;
};

class Entity {
public:
	Entity(Vector2f En_pos, SDL_Texture* En_tex);
	SDL_Texture* getTex() { return En_Texture; }
	Vector2f& getPos() { return En_Position; }
	float getAngle() { return En_Angle; }
	Vector2f getScale() { return En_Scale; }
	void setPos(double x, double y);
	void setScale(double x, double y);
	void setAngle(float angle);
	void update(double deltaTime);
	SDL_Rect getCurrentFrame() { return currentFrame; }
private:
	Vector2f En_Position;
	float En_Angle;
	Vector2f En_Scale = Vector2f(1, 1);
	SDL_Rect currentFrame;
	SDL_Texture* En_Texture;
};

class Hole : public Entity {
public:
	Hole(Vector2f Hole_Position, SDL_Texture* Hole_Texture);
private:
};

class Tile : public Entity {
public:
	Tile(Vector2f Tile_pos, SDL_Texture* Tile_Texture);
private:
};
class Ball : public Entity {
public:
	Ball(Vector2f Ball_Position, SDL_Texture* Ball_Texture, SDL_Texture* Ball_pointTexture, SDL_Texture* Ball_powerMTexFG, SDL_Texture* Ball_powerMTexBG);
	Vector2f& getVelocity() { return Ball_Velocity;}
	Vector2f& getInitialMousePos() { return initialMousePos; }
	std::vector<Entity> getPowerBar() { return powerBars; }
	std::vector<Entity> getPoints() { return points; }
	int getStorkes() { return strokes; }
	bool isWin() { return win; }
	void setWin(bool Win);
	void setInitialMousePos(float x, float y);
	void setVelocity(float x, float y);
	void setLaunchedVelocity(float x, float y);	
	void update(double deltaTime, bool mouseDown, bool mousePressed, Hole hole,std::vector<Tile> tiles,Mix_Chunk *holeSFx, Mix_Chunk* chargeSfx, Mix_Chunk* swingSfx);
private:
	Vector2f Ball_Velocity;
	Vector2f Target;
	Vector2f Ball_launchedVelocity;
	float velocity1D;
	float launchedVelocity1D;
	Vector2f initialMousePos;
	bool canMove = true;
	bool playedSwingFx = true;
	int strokes = 0;
	int dirX = 1;
	int dirY = 1;
	bool win = false;
	std::vector<Entity> points;
	std::vector<Entity> powerBars;
};
