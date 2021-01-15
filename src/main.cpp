#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

void init ()
{
	// INITIALIZIING 
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL_INIT FAILED! \n" << SDL_GetError() << std::endl;
	}

	if ( !(IMG_Init(IMG_INIT_PNG)) )
	{
		std::cout << "IMG_Init FAILED! \n" << SDL_GetError() << std::endl;
	}

}

int main (int argc, char* args[])
{
	// WINDOW
	RenderWindow window("Kiddo v1.0", 400, 600);

	// Loading Images
	// SDL_Texture* tile0 = window.loadTexture("res/gfx/Tile001.png");

	Entity back(Vector2f(0, 0), window.loadTexture("res/gfx/back.png"));

	Entity cursor(Vector2f(), window.loadTexture("res/gfx/cursor.png"));

	// <OPEN> ---------- PLAYER PROPERTIES ----------
	Entity player(Vector2f(0, 0), window.loadTexture("res/gfx/KIDDO.png"));
	// actual
	player.pos = Vector2f(
			window.getWidth()/2/SCALE - player.getWidth()/2, 
			window.getHeight()/2/SCALE - player.getHeight()/2);
	float player_angular_speed = 0.0f;
	float drag = 0.001f;
	// apparent
	Vector2f p_apparent_pos = player.pos;
	Vector2f p_apparent_vel(0.0f, -1.0f);
	// <CLOSE> ---------- PLAYER PROPERTIES ----------

	// Flappies
	std::vector<Entity> flappies;
	for (int i = 1; i <= 50; i++)
	{
		Vector2f range(-int(window.getWidth()/SCALE) + 3*(rand() % int(window.getWidth()/SCALE)), -(rand() % int(window.getHeight()/SCALE)));

		Entity temp_e(range, window.loadTexture("res/gfx/FlappyBird.png"));
		
		flappies.push_back(temp_e);
	}

	bool gameRunning = true;

	SDL_Event event;
	Vector2i mousePos(0, 0);
	SDL_ShowCursor(SDL_DISABLE);

	while (gameRunning)
	{
		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			// X(ing)
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
			
			// MOUSE
			if (event.type == SDL_MOUSEMOTION)
			{
				SDL_GetMouseState(&mousePos.x, &mousePos.y);
			}

			if (event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					// LEFT
					case SDLK_LEFT:
						// Movement
						p_apparent_vel.x = -5;
						// Rotation
						if (player.getAngle() > -90)
							player_angular_speed -= 0.2;
						break;
					// RIGHT
					case SDLK_RIGHT: 
						// Movement
						p_apparent_vel.x = 5;
						// Rotation
						if (player.getAngle() < 90)
							player_angular_speed += 0.2;
						break;
				}
			}

			// KEY UP
			if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)
					p_apparent_vel.x = 0;
			}
		}


		// setting the position of the cursor
		cursor.pos.x = (float)mousePos.x/SCALE - cursor.getWidth()/2;
		cursor.pos.y = (float)mousePos.y/SCALE - cursor.getHeight()/2;

		// moving the player (well, apparently)
		p_apparent_pos.add_to(p_apparent_vel);

		// warping the player (apparently)
		if (p_apparent_pos.x < -window.getWidth()/SCALE)
			p_apparent_pos.x = 2*window.getWidth()/SCALE;
		if (p_apparent_pos.x > 2*window.getWidth()/SCALE)
			p_apparent_pos.x = -window.getWidth()/SCALE;

		// rotating the player
		if (player.getAngle() > 360-90 && player.getAngle() < 360)
		{player_angular_speed += 0.15;}
		else if (player.getAngle() < 90 && player.getAngle() > 0)
		{player_angular_speed -= 0.15;}

		// Limiting player_angular_speed
		if (player_angular_speed < 0)
			player_angular_speed += drag;
		if (player_angular_speed > 0)
			player_angular_speed -= drag;
		{
			float max = 5.0f;
			if (player_angular_speed > max)
				player_angular_speed = max;
			if (player_angular_speed < -max)
				player_angular_speed = -max;
		}
		// Actually Rotating the player
		player.rotateC(player_angular_speed, Vector2f(player.getWidth()/2, 50));

		window.clear();
		// Bottom-most
		window.render(back);

		// Mid
		for (Entity& bird : flappies)
		{
			bird.pos.subtract_from(p_apparent_vel);
			if (bird.pos.y > window.getHeight()/SCALE)
			{

				Vector2f range(-int(window.getWidth()/SCALE) + 3*(rand() % int(window.getWidth()/SCALE)), -(rand() % int(window.getHeight()/SCALE)));
				bird.pos.x = range.x;
				bird.pos.y = range.y;
			}
			bird.pos.y += -1.0f + rand() % 5;
			// warping the bird
			if (bird.pos.x < -window.getWidth()/SCALE)
				bird.pos.x = 2*window.getWidth()/SCALE;
			if (bird.pos.x > 2*window.getWidth()/SCALE)
				bird.pos.x = -window.getWidth()/SCALE;
			window.render(bird);
		}
		window.render(player);

		// Top-most
		window.render(cursor);

		window.display();

		// DEBUG MSGS
		p_apparent_pos.print();

	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}