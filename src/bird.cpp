#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Bird.hpp"

Bird::Bird(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_vel):Entity(p_pos, p_tex)
// :vel(p_vel)
{
	vel = p_vel;
}

void Bird::fly(RenderWindow window, Vector2f player_vel)
{
	// moving the bird
	pos.subtract_from(player_vel);
	pos.add_to(vel);
	pos.y += -1 + rand() % 2;

	// warping the bird along y
	if (pos.y > window.getHeight()/SCALE)
	{
		Vector2f range(-int(window.getWidth()/SCALE) + 3*(rand() % int(window.getWidth()/SCALE)), -(rand() % int(window.getHeight()/SCALE)));
		pos.x = range.x;
		pos.y = range.y;
	}

	// warping the bird along x
	if (pos.x < -window.getWidth()/SCALE)
		pos.x = 2*window.getWidth()/SCALE;
	if (pos.x > 2*window.getWidth()/SCALE)
		pos.x = -window.getWidth()/SCALE;

}