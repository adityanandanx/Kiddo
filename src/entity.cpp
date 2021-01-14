#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex)
:pos(p_pos), tex(p_tex)
{
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);

	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = w;
	currentFrame.h = h;
}

SDL_Texture* Entity::getTexture()
{
	return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

void Entity::rotateC(float p_deg, Vector2f point)
{
    rotCenter.x = point.x;
    rotCenter.y = point.y;
    angle += p_deg;
    if (angle < 0)
    {
    	angle = 360 + angle;
    }
    else if (angle > 360)
    {
    	angle = angle - 360;
    }
    // SDL_RendererFlip flip = SDL_FLIP_NONE; // the flip of the texture.
}
