#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
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

	Entity player(Vector2f(0, 0), window.loadTexture("res/gfx/KIDDO.png"));
	player.pos = Vector2f(
			window.getWidth()/2 - player.getWidth()/2, 
			window.getHeight()/2- player.getHeight()/2);
	float player_angular_speed = 0.0f;
	float drag = 0.005f;

	Entity cursor(Vector2f(), window.loadTexture("res/gfx/cursor.png"));

	// Flappies
	std::vector<Entity> flappies;
	for (int i = 1; i <= 5; i++)
	{
		Entity temp_e(Vector2f(-32, -32), window.loadTexture("res/gfx/FlappyBird.png"));
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
						if (player.pos.x > 0)
						{
							player.pos.x-=5;
							// Rotation
							if (player.getAngle() > -90)
								player_angular_speed -= 0.2;
						}
						break;
					// RIGHT
					case SDLK_RIGHT: 
						// Movement
						if (player.pos.x < window.getWidth()-player.getWidth())
						{
							player.pos.x+=5;
							// Rotation
							if (player.getAngle() < 90)
								player_angular_speed += 0.2;
						}
						break;
				}
			}
		}


		// setting the position of the cursor
		cursor.pos.x = (float)mousePos.x/SCALE - cursor.getWidth()/2;
		cursor.pos.y = (float)mousePos.y/SCALE - cursor.getHeight()/2;

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

			window.render(bird);
		}
		window.render(player);

		// Top-most
		window.render(cursor);

		window.display();

	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}