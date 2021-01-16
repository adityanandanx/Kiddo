#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

#include "Entity.hpp"
#include "Math.hpp"
#include "RenderWindow.hpp"

class Bird : public Entity
{
public:
	Bird(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_vel);

	void fly(RenderWindow window, Vector2f player_vel);

	Vector2f vel;

private:

};
