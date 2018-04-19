#pragma once

class Map;

class Game
{
private:
	int windowWidth;
	int windowHeight;
	Map* map;
	unsigned long currentTickCount;
	unsigned long lastGhostsMovedTime;
	int ghostsSpeed;
	int level;
public:
	Game(int w, int h);

	~Game();

	int getWindowHeight();

	int getWindowWidth();

	void nextLevel();

	static Game& getInstance();

	static void draw();

	static void loopCycle();

	void drawText(float x, float y, const unsigned char* string);

	void drawUI();

	static void processKeyboard(unsigned char key, int x, int y);
};