#pragma once

class Devourer;
#include "GameObject.h"

class Map
{
public:
	int width;
	int height;

	MapTile** tiles;
	Devourer* player;
	Ghost* ghosts;
	int ghostsNumber;

	float tileWidth;
	float tileHeight;

	int windowWidth;
	int windowHeight;

	Map(int w, int h, int winW, int winH, int ghostsNum);

	bool canObjectMove(GameObject* object, MoveDirection direction);
	bool isPositionEmpty(const Point& position);
	void moveGhosts();

	Ghost* getGhostAtPosition(const Point& position);
	void removeGhost(Ghost* ghostToRemove);
	void createGhosts(int ghostsNum);
	void createWalls();

	~Map();

	void draw();
};