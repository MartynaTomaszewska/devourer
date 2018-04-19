#pragma once

#include "Tools.h"

 class Map;

enum MoveDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class GameObject
{
protected:
	Point position;
	float width;
	float height;
	int windowWidth;
	int windowHeight;
	Color color;
public:

	GameObject();

	void setSize(float w, float h);
	void setWindowSize(int w, int h);
	void setPosition(const Point& p);
	void setColor(float r, float g, float b);
	const Point& getPosition();

	void draw();
};

class MovingGameObject : public GameObject
{
protected:
	Map* map;
public:
	virtual bool move(MoveDirection direction);
	void setMap(Map* m);
};

class Ghost : public MovingGameObject
{
private:
public:
	MoveDirection lastMoveDirection;

	Ghost();
	void runFromDevourer();
	bool isCloseToDevourer();
};

class Devourer : public MovingGameObject
{
private:
public:
	bool eat();
};

enum MapTileType
{
	EMPTY,
	WALL
};

class MapTile : public GameObject
{
private:

public:
	MapTileType type;

	MapTile();

	void setType(MapTileType t);
};