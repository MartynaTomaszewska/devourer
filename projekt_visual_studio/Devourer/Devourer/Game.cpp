#include "stdafx.h"
#include "Game.h"
#include "Tools.h"
#include "Map.h"
#include <Windows.h>

#include <GL/glut.h>
#include < GL/freeglut.h>

Game::Game(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	map = new Map(40, 40, windowWidth, windowHeight, 5);
	currentTickCount = GetTickCount();
	lastGhostsMovedTime = GetTickCount();
	ghostsSpeed = 1;
	level = 1;
}

Game::~Game()
{
	delete map;
}

int Game::getWindowHeight()
{
	return windowHeight;
}

int Game::getWindowWidth()
{
	return windowWidth;
}

Game& Game::getInstance()
{
	static Game game(1024, 1024);
	return game;
}

void Game::loopCycle()
{
	Game::getInstance().draw();
	Game::getInstance().map->player->eat();

	if (Game::getInstance().map->ghostsNumber < 1)
	{
		Game::getInstance().nextLevel();
	}
	
	DWORD currentTickCount = GetTickCount();
	if (currentTickCount - Game::getInstance().lastGhostsMovedTime > (1000/Game::getInstance().ghostsSpeed))
	{
		Game::getInstance().lastGhostsMovedTime = currentTickCount;
		Game::getInstance().map->moveGhosts();
	}
}

void Game::draw()
{
	// czyszczenie buforu
	glClear(GL_COLOR_BUFFER_BIT);   

	Game::getInstance().map->draw();

	Game::getInstance().drawUI();

	//wyrzuc na ekran stan buforu. 
	glFlush();	
}

void Game::drawText(float x, float y, const unsigned char* string)
{  
	glColor3f(1.0f, 1.0f, 1.0f); 
	glRasterPos2f(x, y);

	glutBitmapString(GLUT_BITMAP_HELVETICA_18, string);
}

void Game::drawUI()
{
	char buffer[10];

	float levelTextX = -1.0 + ((float)2/windowWidth * 5);
	float levelTextY = -1.0 + ((float)2/windowHeight * (windowHeight - 20)); 
	float levelValueX = -1.0 + ((float)2/windowWidth * 60);
	float levelValueY = levelTextY;
	drawText(levelTextX, levelTextY, reinterpret_cast<const unsigned char *>("level: "));
	drawText(levelValueX, levelValueY, reinterpret_cast<const unsigned char *>(itoa(level, buffer, 10)));
}

void Game::processKeyboard(unsigned char key, int x, int y)
{
	bool playerMoved = false;

	if (key == 'q' || key == 'Q')
	{
		exit(EXIT_SUCCESS);
	}
	else if (key == 'w' || key == 'W')
	{
		playerMoved = Game::getInstance().map->player->move(UP);
	}
	else if (key == 's' || key == 'S')
	{
		playerMoved = Game::getInstance().map->player->move(DOWN);
	}
	else if (key == 'a' || key == 'A')
	{
		playerMoved = Game::getInstance().map->player->move(LEFT);
	}
	else if (key == 'd' || key == 'D')
	{
		playerMoved = Game::getInstance().map->player->move(RIGHT);
	}
}

void Game::nextLevel()
{
	level++;

	ghostsSpeed = level;

	map->createGhosts(5);
}