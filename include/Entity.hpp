#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// #include <vector>

#include "Math.hpp"

class Entity
{
	
public:
	Vector2f pos;
	Entity(Vector2f p_pos, SDL_Texture* p_tex);

	// Get(ters) make the class variables READ-ONLY 
	Vector2f getPos()
	{
		return pos;
	}

	// getters
	float getWidth()
	{return currentFrame.w;}

	float getHeight()
	{return currentFrame.h;}

	float getAngle()
	{return angle;}

	Vector2f getCenter()
	{
		return Vector2f(pos.x + currentFrame.w/2, pos.y + currentFrame.h/2);
	}

	// setters
	void setAngle(float p_angle)
	{angle = p_angle;}

	SDL_Point getRotCenter()
	{return rotCenter;}

	SDL_Texture* getTexture();
	SDL_Rect getCurrentFrame();

	void rotateC(float p_deg, Vector2f point);

private:
	SDL_Rect currentFrame;
	SDL_Texture* tex;
	float angle = 0.0f;
    SDL_Point rotCenter; // the center where the texture will be rotated.
};
