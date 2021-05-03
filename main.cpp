#include <iostream>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "Pacman.h"
#include "ghost.h"
#include "map.h"
#include "point.h"
#include "menu_game.h"

BaseObject g_background;

bool loadBackground();
bool init();
void close();
void close();
void waitUntilKeyPressed();

int main(int argc, char *args[])
{
	if (init() == false)
		return -1;

	if (loadBackground() == false)
		return -1;

	bool quit = false;
	bool start = true;

	int score_overall = 0;

	while (!quit)
	{
		MenuGame menu_game;
		if (start)
		{
			menu_game.Menu_game(g_screen, g_window);
		}

		std::cerr << "dangh";

		Pacman *pacman = NULL;
		pacman = new Pacman;
		pacman->_LoadImg("pic/PacMan.bmp", g_screen);
		pacman->setClips();

		Ghost *ghost = NULL;
		ghost = new Ghost;
		ghost->_LoadImg("pic/Blinky.bmp", g_screen);
		ghost->setClips();

		std::vector<bool> flag_ghost(4);
		std::vector<Ghost *> ghost_list(4);
		for (int i = 0; i < 4; i++)
		{
			ghost_list[i] = new Ghost;
			flag_ghost[i] = new bool;
			flag_ghost[i] = false;
		}
		bool *g_flag_ghost = new bool;
		*g_flag_ghost = false;

		ghost_list[0]->_LoadImg("pic/Blinky.bmp", g_screen);
		ghost_list[1]->_LoadImg("pic/Inkey.bmp", g_screen);
		ghost_list[2]->_LoadImg("pic/Pinky.bmp", g_screen);
		ghost_list[3]->_LoadImg("pic/Clyde.bmp", g_screen);

		for (int i = 0; i < 4; i++)
			ghost_list[i]->setClips();

		std::vector<SDL_Rect> rect_ghost_list(4);
		for (int i = 0; i < 4; i++)
		{
			rect_ghost_list[i] = ghost_list[i]->getRect();
		}

		GameMap *game_map;
		game_map = new GameMap;
		game_map->setClipTile();

		Point *point;
		point = new Point;
		point->_LoadImg("pic/point.bmp", g_screen);
		point->setPosMap();
		point->setClipTile();

		std::cerr << "dao trong dang";

		//while()

		int frame_dead = 0;
		int score_eat_point = 0;
		int count_time = 0;

		bool after_eat_big = false;

		while (!pacman->IsGameOver(score_eat_point))
		{

			//menu game
			if (pacman->getHealth() == 0)
				break;

			if (pacman->getHealth() <= 3 && pacman->getFlagDead() == false && after_eat_big == false)
			{
				//pacman->setPos(TILE_SIZE * 9, TILE_SIZE * 15);
				// pacman->setSatus();
			}

			while (pacman->getFlagDead() == false && quit == false)
			{

				SDL_RenderClear(g_screen);
				pacman->ShowHealth(g_screen);

				while (SDL_PollEvent(&g_event) != 0)
				{
					if (g_event.type == SDL_QUIT)
					{
						quit = true;
					};
					//if (g_event.type == SDL_KEYDOWN || SDL_WaitEvent(&g_event) != 0){
					if (g_event.key.keysym.sym == SDLK_p)
					{
						//if (SDL_WaitEvent(&g_event) != 0)
						{
							menu_game.Menu_game(g_screen, g_window);
						}
					}
					//pacman->IsGameOver(score_eat_point);
					pacman->HandleInputAction(g_event, g_screen);
				}

				g_background.Render(g_screen, NULL);
				point->Show(g_screen);
				pacman->move(game_map->getColliders());
				pacman->Show(g_screen);
				SDL_RenderPresent(g_screen);

				for (int i = 0; i < 4; i++)
				{
					ghost_list[i]->Action();
					ghost_list[i]->move(game_map->getColliders());
					rect_ghost_list[i] = ghost_list[i]->getRect();
					ghost_list[i]->Show(g_screen);
				}

				SDL_RenderPresent(g_screen);
				SDL_Delay(120);

				//Check eat big point??
				if (point->checkBigPoint(pacman->getX() + 1, pacman->getY() + 1))
				{
					for (int i = 0; i < 4; i++)
					{
						ghost_list[i]->setFlagWhenPacEatBig(true);
						ghost_list[i]->setSTEPWhenDead();
					}
					ghost->setFlagWhenPacEatBig(true);

					pacman->setFlagEatBigPoint(true);
					count_time = 0;
				}

				// Pacman eat small point
				point->deletePoint(pacman->getX() + 1, pacman->getY() + 1);
				//sound
				//get score_eat_point
				score_eat_point = point->setClipTile();

				count_time++;
				cerr << score_eat_point << endl;

				// Pacman eat ghost and die
				if (pacman->checkCollisionWith(rect_ghost_list) == true && pacman->getFlagEatBigPoint() == false && ghost->getFlagWhenPacEatBig() == false && *g_flag_ghost == false && ghost->getFlagEatWeakGhost() == false) // co va cham voi ghost
				{
					pacman->setFlagDead(true);
					break;
				}

				// Check pacman eat weak ghost ??yes
				for (int i = 0; i < 4; i++)
				{
					if (pacman->checkCollisionWithEachGhost(ghost_list[i]->getRect()) == true && pacman->getFlagEatBigPoint() == true && ghost->getFlagWhenPacEatBig() == true && count_time < 50)
					{
						flag_ghost[i] = true;
						*g_flag_ghost = true;
						ghost_list[i]->setFlagEatWeakGhost(true);
						ghost->setFlagEatWeakGhost(true);
					}
				}
				if (*g_flag_ghost == true)
				{
					break;
				}

				// Check pacman eat weak ghost ??no
				if (pacman->getFlagDead() == false && pacman->getFlagEatBigPoint() == true && ghost->getFlagEatWeakGhost() == false && count_time == 50)
				{
					// Time of weakghost
					for (int i = 0; i < 4; i++)
					{
						if (flag_ghost[i] == true)
						{
							flag_ghost[i] = false;
						}
						*g_flag_ghost = false;
						ghost_list[i]->setFlagWhenPacEatBig(false);
						ghost_list[i]->setFlagEatWeakGhost(false);
					}

					ghost->setFlagEatWeakGhost(false);
					ghost->setFlagWhenPacEatBig(false);
					pacman->setFlagEatBigPoint(false);
					after_eat_big = true;
				}
				if (pacman->IsGameOver(score_eat_point) == true)
				{
					break;
				}
			} // end of while pacman alive

			// Status of pacman after die
			if (pacman->getFlagDead() == true && pacman->getFlagEatBigPoint() == false && frame_dead < 8 && ghost->getFlagWhenPacEatBig() == false)
			{
				SDL_RenderClear(g_screen);
				g_background.Render(g_screen, NULL);
				pacman->ShowHealth(g_screen);
				point->Show(g_screen);

				for (int i = 0; i < 4; i++)
				{
					ghost_list[i]->setPos(TILE_SIZE * 9, TILE_SIZE * 7);
					ghost_list[i]->Show(g_screen);
				}

				pacman->Show(g_screen, frame_dead);
				frame_dead++;

				SDL_RenderPresent(g_screen);
				SDL_Delay(250);
				cerr << "deading" << endl;
			}
			else if (pacman->getFlagDead() == true && pacman->getFlagEatBigPoint() == false && frame_dead == 8 && ghost->getFlagWhenPacEatBig() == false)
			{
				frame_dead = 0;
				pacman->setHealth((pacman->getHealth()) - 1);
				pacman->setPos(TILE_SIZE * 9, TILE_SIZE * 15);

				pacman->setFlagDead(false);
				after_eat_big == false;
			}

			// do: Pacman eat weakGhost
			if (pacman->getFlagDead() == false && pacman->getFlagEatBigPoint() == true && ghost->getFlagEatWeakGhost() == true && count_time < 50)
			{ // quit == false

				score_eat_point += 4;
				SDL_RenderClear(g_screen);
				g_background.Render(g_screen, NULL);
				pacman->ShowHealth(g_screen);
				point->Show(g_screen);
				pacman->Show(g_screen);

				// dung while tai day de render shost ve chinh giua
				for (int i = 0; i < 4; i++)
				{
					if (flag_ghost[i] == true)
					{
						ghost_list[i]->Action();
						ghost_list[i]->setPos(TILE_SIZE * 9, TILE_SIZE * 7);
						ghost_list[i]->setFlagWhenPacEatBig(false);
						ghost_list[i]->setFlagEatWeakGhost(false);
						// tim duonng ve chinh giua, viet ham khac
					}
					ghost_list[i]->Show(g_screen);
				}
				//

				// chuyen rendere vao trong while
				SDL_RenderPresent(g_screen);
				//SDL_Delay(120);

				// for (int i = 0; i < 4; i++)
				// {
				// 	if (flag_ghost[i] == true)
				// 	{
				// 		flag_ghost[i] = false;
				// 	}
				// 	*g_flag_ghost = false;
				// 	ghost_list[i]->setFlagWhenPacEatBig(false);
				// 	ghost_list[i]->setFlagEatWeakGhost(false);
				// }

				// ghost->setFlagEatWeakGhost(false);
				// ghost->setFlagWhenPacEatBig(false);
				// pacman->setFlagEatBigPoint(false);
				// after_eat_big = true;
			}
			else
				// Check pacman eat weak ghost ??no
				if (pacman->getFlagDead() == false && pacman->getFlagEatBigPoint() == true && ghost->getFlagEatWeakGhost() == true && count_time == 50)
			{
				// Time of weakghost
				for (int i = 0; i < 4; i++)
				{
					if (flag_ghost[i] == true)
					{
						flag_ghost[i] = false;
					}
					*g_flag_ghost = false;
					ghost_list[i]->setFlagWhenPacEatBig(false);
					ghost_list[i]->setFlagEatWeakGhost(false);
				}

				ghost->setFlagEatWeakGhost(false);
				ghost->setFlagWhenPacEatBig(false);
				pacman->setFlagEatBigPoint(false);
				after_eat_big = true;
			}
		}

		if (pacman->IsGameOver(score_eat_point) == true)
		{
			start = true;
			delete pacman;
			delete ghost;
			for (int i = 0; i < 4; i++)
			{
				delete ghost_list[i];
			}
			delete g_flag_ghost;
			delete game_map;
			delete point;
		}
		else
		{
			//start = false;
		}
	}

	std::cerr << "end game";

	close();
	SDL_Delay(1);

	return 0;
}

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
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
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
void waitUntilKeyPressed() // ok
{
	SDL_Event e;
	while (true)
	{
		if (SDL_WaitEvent(&e) != 0 &&
			(e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
			return;
		//SDL_Delay(100);
	}
}
