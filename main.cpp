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

int main(int argc, char *args[])
{
	if (init() == false)
		return -1;

	if (loadBackground() == false)
		return -1;

	bool quit = false;


	Pacman *pacman = NULL;
	pacman = new Pacman;
	//pacman -> LoadPNG("pic/PacMan.bmp", g_screen);
	pacman->_LoadImg("pic/PacMan.bmp", g_screen);
	pacman->setClips();

	Ghost *ghost = NULL;
	ghost = new Ghost;
	ghost->_LoadImg("pic/Blinky.bmp", g_screen);
	ghost->setClips();

	std::vector<bool> flag_ghost(4);
	std::vector<Ghost *> ghost_list(4);
	for (int i = 0; i < 4; i++){
		ghost_list[i] = new Ghost;
		flag_ghost[i] = new bool;
		flag_ghost[i] = false;
 	}
	ghost_list[0]->_LoadImg("pic/Blinky.bmp", g_screen);
	ghost_list[1]->_LoadImg("pic/Inkey.bmp", g_screen);
	ghost_list[2]->_LoadImg("pic/Pinky.bmp", g_screen);
	ghost_list[3]->_LoadImg("pic/Clyde.bmp", g_screen);

	for (int i = 0; i < 4; i++)
		ghost_list[i]->setClips();

	ghost_list[0]->setPos(168, 196);
	//setPos tiep

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

	int fram = 0;

	int score = 0;
	int mang = 2;
	int count = 0;

	bool after_eat_big = false;

	while (!quit)
	{	
		cerr << "con " << mang+1 << " mang" << endl;
		if (mang == -1) break;
		if (mang < 2 && pacman->getFlagDead() == false && after_eat_big == false){
			for (int i = 0; i < 4; i++){
				ghost_list[i]->setPos(TILE_SIZE * 9, TILE_SIZE * 7);
			}
			pacman->setPos(TILE_SIZE* 9, TILE_SIZE*15);
			pacman->setSatus();
		}

		while (pacman->getFlagDead() == false)
		{

			SDL_RenderClear(g_screen);
			while (SDL_PollEvent(&g_event) != 0)
			{
				if (g_event.type == SDL_QUIT)
				{
					quit = true;
				};
				pacman->HandleInputAction(g_event, g_screen);
			}
			g_background.Render(g_screen, NULL);
			point->Show(g_screen);
			pacman->move(game_map->getColliders());
			pacman->Show(g_screen);


			if (point->checkBigPoint(pacman->getX() + 1, pacman->getY() + 1)){
				pacman->setFlagEatBigPoint(true);
				for (int i = 0; i < 4; i++){
					ghost_list[i]->setFlagWhenPacEatBig(true);
					//ưset
				}

				cerr << "an duoc big point";
			}

			point->deletePoint(pacman->getX() + 1, pacman->getY() + 1);

			//sound
			//get score
			score = point->setClipTile();
			cout << score << endl;


			if (pacman->checkCollisionWith(rect_ghost_list)== true && pacman->getFlagEatBigPoint() == false)// co va cham voi ghost
			{
				pacman->setFlagDead(true);
				break;
				std::cerr << "co va cham";

			}
			if (pacman->checkCollisionWith(rect_ghost_list) == true && pacman->getFlagEatBigPoint() == true){
					for (int i = 0; i < 4; i ++){
						if (pacman->checkCollisionWithEachGhost(ghost_list[i] -> getRect())){
							flag_ghost[i] = true;
							ghost_list[i] -> setFlagEatWeakGhost(true);
							cerr << "cbi break"<< endl;
							break;
						}
					}
					break;
			}

			std::cerr << "dang";


			for (int i = 0; i < 4; i++)
			{
				ghost_list[i]->Action();
				ghost_list[i]->move(game_map->getColliders());
				rect_ghost_list[i] = ghost_list[i]->getRect();
				ghost_list[i]->Show(g_screen);
			}


			SDL_RenderPresent(g_screen);

			SDL_Delay(130);
		}


		// trang thai luc pacman chet co 9 animation
		if (fram != 8 && pacman->getFlagDead() == false && pacman-> getFlagEatBigPoint() == false)
		{
			SDL_RenderClear(g_screen);
			g_background.Render(g_screen, NULL);
			point->Show(g_screen);
			for (int i = 0; i < 4; i++)
			{
				ghost_list[i]->Show(g_screen);
			}
			pacman->Show(g_screen, fram);
			SDL_RenderPresent(g_screen);
			SDL_Delay(250);

			fram++;
		}
		else if (fram == 8 && pacman->getFlagDead() == false)
		{
			fram = 0;
			mang--;
			pacman->setFlagDead(false);
			after_eat_big == false;
		}


		if (pacman->getFlagEatBigPoint() == true){
			
			//if (count!=0) count++;
			SDL_RenderClear(g_screen);
			g_background.Render(g_screen, NULL);
			point->Show(g_screen);

			for (int i = 0; i < 4; i++)
			{
				if (flag_ghost[i] == true){
					ghost_list[i] -> Action();
					ghost_list[i] -> setPos(TILE_SIZE * 9, TILE_SIZE * 7);
					// tim duonng ve chinh giua, viet ham khac
					ghost_list[i]->Show(g_screen);
				}
			}

			for (int i = 0; i < 4; i++)
			{
				if (flag_ghost[i] == true){
					flag_ghost[i] = false;
				}
				ghost_list[i] -> setFlagWhenPacEatBig(false);
				ghost_list[i] -> setFlagEatWeakGhost(false);
			}

			pacman->Show(g_screen, fram);
			SDL_RenderPresent(g_screen);
			SDL_Delay(130);

			pacman->getFlagEatBigPoint() == false;
			after_eat_big = true;

		}else if (count == 1000){
			// thoi gian tat big point
			
		}

	};
	std::cerr << "end game";

	close();

	SDL_Delay(10000);

	return 0;
}
