#include <iostream>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "Pacman.h"
#include "ghost.h"
#include "map.h"
#include "point.h"


BaseObject g_background;

bool loadBackground()
{
	//bool ret = g_background.BGLoadImg("image_py/level.png", g_screen);
	bool ret = g_background.BGLoadImg("image/newmap_1.png", g_screen);
	if (ret == false)
		return false;

	return true;
}
bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		//printf("Warning: Linear texture filtering not enabled!");
	}

	g_window = SDL_CreateWindow("pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL)
	{
		//printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create renderer for window
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL)
		{
			//printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				//printf("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError());
				success = false;
			}
		}
	}

	return success;
}
void close()
{
	g_background.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char *args[])
{
	if (init() == false)
		return -1;

	if (loadBackground() == false)
		return -1;

	bool quit = false;
	//SDL_Event e;

	Pacman *pacman = NULL;
	pacman = new Pacman;
	//pacman -> LoadPNG("pic/PacMan.bmp", g_screen);
	pacman->_LoadImg("pic/PacMan.bmp", g_screen);
	pacman->setClips();

	Ghost *ghost = NULL;
	ghost = new Ghost;
	ghost->_LoadImg("pic/Blinky.bmp", g_screen);
	ghost->setClips();

	std::vector<Ghost *> ghost_list(4);
	for (int i = 0; i < 4; i++)
		ghost_list[i] = new Ghost;
	ghost_list[0]->_LoadImg("pic/Blinky.bmp", g_screen);
	ghost_list[1]->_LoadImg("pic/Inkey.bmp", g_screen);
	ghost_list[2]->_LoadImg("pic/Pinky.bmp", g_screen);
	ghost_list[3]->_LoadImg("pic/Clyde.bmp", g_screen);

	for (int i = 0; i < 4; i++)
		ghost_list[i]->setClips();

	ghost_list[0]->setPos(168, 196);
	//setPos tiep

	GameMap *game_map;
	game_map = new GameMap;
	//game_map->LoadMap("map.txt");
	game_map->setClipTile();

	Point *point;
	point = new Point;
	point->_LoadImg("pic/point.bmp", g_screen);
	point->setPosMap();
	point->setClipTile();

	std::cerr << "dao trong dang";

	int score = 0;
	while (!quit)
	{
		SDL_RenderClear(g_screen);
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				quit = true;
			};
			pacman->HandleInputAction(g_event, g_screen);
		
		};
		g_background.Render(g_screen, NULL);

		point->deletePoint(pacman->getX() + 1, pacman->getY() + 1); 
		//sound
		//get score
		score = point->setClipTile();
		cout << score << endl;
		
		point -> Show(g_screen);

		for (int i = 0; i < 4; i++)
		{
			ghost_list[i]->Action();
			ghost_list[i]->move(game_map->getColliders());
			ghost_list[i]->Show(g_screen);
		}


		pacman->move(game_map->getColliders());
		pacman->Show(g_screen);
		//Clear screen
		//SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		

		SDL_RenderPresent(g_screen);

		SDL_Delay(130);
	};
	//g_background.waitUntilKeyPressed();
	g_background.Destroy(NULL, g_window, g_screen);

	return 0;
}
