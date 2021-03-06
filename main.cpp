#include <iostream>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "Pacman.h"
#include "ghost.h"
#include "map.h"
#include "point.h"
#include "menu_game.h"
#include "TextObject.h"

BaseObject g_background;
TTF_Font *g_font = NULL;

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

	long score_overall = -1;

	while (!quit)
	//do
	{
		MenuGame menu_game;
		if (start)
		{
			menu_game.Menu_game(g_screen, g_window);
		}

		Pacman *pacman = NULL;
		pacman = new Pacman;
		pacman->_LoadImg("image/PacMan.bmp", g_screen);
		pacman->setClips();

		Ghost *ghost = NULL;
		ghost = new Ghost;
		ghost->_LoadImg("image/Blinky.bmp", g_screen);
		ghost->setClips();

		std::vector<bool> flag_ghost_was_eaten(4);
		std::vector<Ghost *> ghost_list(4);
		for (int i = 0; i < 4; i++)
		{
			ghost_list[i] = new Ghost;
			flag_ghost_was_eaten[i] = new bool;
			flag_ghost_was_eaten[i] = false;
		}

		ghost_list[0]->_LoadImg("image/Blinky.bmp", g_screen);
		ghost_list[1]->_LoadImg("image/Inkey.bmp", g_screen);
		ghost_list[2]->_LoadImg("image/Pinky.bmp", g_screen);
		ghost_list[3]->_LoadImg("image/Clyde.bmp", g_screen);

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
		point->_LoadImg("image/point.bmp", g_screen);
		point->setPosMap();
		point->setClipTile();

		int frame_dead = 0;
		int score_eat_point = 0;
		int score_eat_ghost = 0;
		int count_time = 0;

		bool after_eat_big = false;

		while (!pacman->IsGameOver(score_eat_point) && !quit)
		{

			//menu game
			if (pacman->getHealth() == 0)
				break;

			while (pacman->getFlagDead() == false && quit == false)
			{

				SDL_RenderClear(g_screen);
				
				while (SDL_PollEvent(&g_event) != 0)
				{
					if (g_event.type == SDL_QUIT)
					{
						quit = true;
					};
					if (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_ESCAPE)
					{
						menu_game.Pause_game(g_screen, g_window);
					}
					pacman->HandleInputAction(g_event, g_screen);
				}

				g_background.Render(g_screen, NULL);
				pacman->ShowHealth(g_screen);
				point->Show(g_screen);
				pacman->move(game_map->getColliders());
				pacman->Show(g_screen);

				TextObject text_score("SCORE: \n");
				TextObject high_score("HIGHT SCORE: ");
				text_score.str_ += std::to_string(score_overall * 10);
				high_score.str_ += std::to_string(menu_game.get_high_score());
				high_score.renderTexture(high_score.GetText(22, g_screen), g_screen, TILE_SIZE * 4 - TILE_SIZE / 2, TILE_SIZE * 21 + TILE_SIZE / 4);
				text_score.renderTexture(text_score.GetText(22, g_screen), g_screen, TILE_SIZE * 7 - TILE_SIZE / 2, TILE_SIZE * 19 + TILE_SIZE / 4);
				text_score.DestroyText();
				high_score.DestroyText();

				for (int i = 0; i < 4; i++)
				{
					ghost_list[i]->Action();
					ghost_list[i]->move(game_map->getCollidersGHO());
					rect_ghost_list[i] = ghost_list[i]->getRect();
					ghost_list[i]->Show(g_screen);
				}

				SDL_RenderPresent(g_screen);
				SDL_Delay(125);

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

				point->deletePoint(pacman->getX() + 1, pacman->getY() + 1);
				score_eat_point = point->setClipTile();
				score_overall = score_eat_point + score_eat_ghost;
				count_time++;

				if (pacman->checkCollisionWith(rect_ghost_list) == true && pacman->getFlagEatBigPoint() == false /*&& ghost->getFlagWhenPacEatBig() == false /*&& *g_flag_ghost_was_eaten == false*/ && ghost->getFlagEatWeakGhost() == false) // co va cham voi ghost
				{
					pacman->setFlagDead(true);
					break;
				}

				// Check pacman eat weak ghost ??yes
				for (int i = 0; i < 4; i++)
				{
					if (pacman->checkCollisionWithEachGhost(ghost_list[i]->getRect()) == true && pacman->getFlagEatBigPoint() == true && ghost->getFlagWhenPacEatBig() == true && count_time < 50)
					{
						flag_ghost_was_eaten[i] = true;
						//*g_flag_ghost_was_eaten = true;
						ghost_list[i]->setFlagEatWeakGhost(true);
						ghost->setFlagEatWeakGhost(true);
					}
				}

				if (ghost->getFlagEatWeakGhost() == true)
				{
					break;
				}

				// Check pacman eat weak ghost ??no
				if (pacman->getFlagDead() == false && pacman->getFlagEatBigPoint() == true && ghost->getFlagEatWeakGhost() == false && count_time == 50)
				{
					// Time of weakghost
					for (int i = 0; i < 4; i++)
					{
						if (flag_ghost_was_eaten[i] == true)
						{
							flag_ghost_was_eaten[i] = false;
						}
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

			// Pacman death
			if (pacman->getFlagDead() == true && pacman->getFlagEatBigPoint() == false && frame_dead < 8 && ghost->getFlagWhenPacEatBig() == false)
			{
				SDL_RenderClear(g_screen);
				g_background.Render(g_screen, NULL);
				pacman->ShowHealth(g_screen);
				point->Show(g_screen);

				TextObject text_score("SCORE: \n");
				TextObject high_score("HIGHT SCORE: ");
				text_score.str_ += std::to_string(score_overall * 10);
				high_score.str_ += std::to_string(menu_game.get_high_score());
				high_score.renderTexture(high_score.GetText(22, g_screen), g_screen, TILE_SIZE * 4 - TILE_SIZE / 2, TILE_SIZE * 21 + TILE_SIZE / 4);
				text_score.renderTexture(text_score.GetText(22, g_screen), g_screen, TILE_SIZE * 7 - TILE_SIZE / 2, TILE_SIZE * 19 + TILE_SIZE / 4);
				text_score.DestroyText();
				high_score.DestroyText();

				for (int i = 0; i < 4; i++)
				{
					ghost_list[i]->setPos(TILE_SIZE * 9, TILE_SIZE * 9);
					ghost_list[i]->Show(g_screen);
				}

				pacman->Show(g_screen, frame_dead);
				frame_dead++;

				SDL_RenderPresent(g_screen);
				SDL_Delay(250);
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
			{ 
				// quit == false
				score_eat_point += 4;

				for (int i = 0; i < 4; i++)
				{
					if (flag_ghost_was_eaten[i] == true)
					{
						score_eat_ghost += 4;
						
						ghost_list[i]->Action();
						ghost_list[i]->setPos(TILE_SIZE * 9, TILE_SIZE * 9);
						ghost_list[i]->setFlagWhenPacEatBig(false);
						ghost_list[i]->setFlagEatWeakGhost(false);

						flag_ghost_was_eaten[i] = false;
					}
				}
			}
			else
				// Check pacman eat weak ghost ??no
				if (pacman->getFlagDead() == false && pacman->getFlagEatBigPoint() == true && ghost->getFlagEatWeakGhost() == true && count_time == 50)
			{
				// Time of weakghost
				for (int i = 0; i < 4; i++)
				{
					if (flag_ghost_was_eaten[i] == true)
					{
						flag_ghost_was_eaten[i] = false;
					}
					ghost_list[i]->setFlagWhenPacEatBig(false);
					ghost_list[i]->setFlagEatWeakGhost(false);
				}

				ghost->setFlagEatWeakGhost(false);
				ghost->setFlagWhenPacEatBig(false);
				pacman->setFlagEatBigPoint(false);
				after_eat_big = true;
			}
		}

		if (pacman->IsGameOver(score_eat_point) == true || quit == true)
		{
			start = true;
			pacman = NULL;
			ghost = NULL;
			for (int i = 0; i < 4; i++)
			{
				ghost_list[i] = NULL;
			}
			game_map = NULL;
			point = NULL;
		}
		else
		{
			start = false;
		}
	}
	std::cerr << "end game";

	close();
	return 0;
}

bool loadBackground()
{
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

			if (TTF_Init() == -1)
			{
				success = false;
			}
			g_font = TTF_OpenFont("font/emulogic.ttf", 13);
			if (g_font == NULL)
			{
				success = true;
			}
			if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2,  2048) == -1)
			{
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

	TTF_CloseFont(g_font);
	g_font = NULL;

	Mix_Quit();
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
	}
}
