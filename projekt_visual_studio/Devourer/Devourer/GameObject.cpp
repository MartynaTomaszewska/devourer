#include "stdafx.h"
#include "GameObject.h"
#include "Map.h"
#include <math.h>

#include <GL/glut.h>

GameObject::GameObject()
{
	position = Point(0,0);
	width = 0;
	height = 0;
}

const Point& GameObject::getPosition()
{
	return position;
}

void GameObject::setSize(float w, float h)
{
	width = w;
	height = h;
}

void GameObject::setWindowSize(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
}

void GameObject::draw()
{
	float leftBottomX = -1.0 + ((float)2/windowWidth * position.x * width);
	float leftBottomY = -1.0 + ((float)2/windowHeight * position.y * height); 

	float leftTopX = -1.0 + ((float)2/windowWidth * position.x * width);
	float leftTopY = -1.0 + ((float)2/windowHeight * (position.y + 1) * height); 

	float rightTopX = -1.0 + ((float)2/windowWidth * (position.x + 1) * width);
	float rightTopY = -1.0 + ((float)2/windowHeight * (position.y + 1) * height);

	float rightBottomX = -1.0 + ((float)2/windowWidth * (position.x + 1) * width);
	float rightBottomY = -1.0 + ((float)2/windowHeight * position.y * height);

	// ustawianie koloru rysowania
	glColor3f(color.red, color.green, color.blue);   

	// narysuj wielokat 
	glBegin(GL_POLYGON); {           
		glVertex2f(leftBottomX, leftBottomY);
		glVertex2f(leftTopX, leftTopY);
		glVertex2f(rightTopX, rightTopY);
		glVertex2f(rightBottomX, rightBottomY);
	} glEnd();
}

void GameObject::setColor(float r, float g, float b)
{
	color.red = r;
	color.green = g;
	color.blue = b;
}

void GameObject::setPosition(const Point& p)
{
	position = p;
}

bool MovingGameObject::move(MoveDirection direction)
{
	switch(direction)
	{
	case UP:
		if (map->canObjectMove(this, direction))
		{
			position.y++;
			return true;
		}
		break;
	case DOWN:
		if (map->canObjectMove(this, direction))
		{
			position.y--;
			return true;
		}
		break;
	case LEFT:
		if (map->canObjectMove(this, direction))
		{
			position.x--;
			return true;
		}
		break;
	case RIGHT:
		if (map->canObjectMove(this, direction))
		{
			position.x++;
			return true;
		}
		break;
	}
	return false;
}

void MovingGameObject::setMap(Map* m)
{
	map = m;
}

bool Devourer::eat()
{
	Ghost* ghostToEat = map->getGhostAtPosition(position);
	if (ghostToEat != NULL)
	{
		map->removeGhost(ghostToEat);
		return true;
	}
	
	return false;
}

Ghost::Ghost()
{
	lastMoveDirection = UP;
}

bool Ghost::isCloseToDevourer()
{
	if (((position.x - map->player->getPosition().x) > -10 && (position.x - map->player->getPosition().x) < 10)
		&& ((position.y - map->player->getPosition().y) > -10 && (position.y - map->player->getPosition().y) < 10))
	{
		return true;
	}

	return false;
}

void Ghost::runFromDevourer()
{
	int tryCount = 0;			// licznik, zeby zapobiec zablokowaniu sie ducha. 
	int tryCountLimit = 10;		// jesli osiagnie wartosc 10, to duch sie ruszy gdziekolwiek nawet jesli mialoby to oznaczac zblizenie sie do pozeracza.
	while(true)
	{
		MoveDirection randomDirection;
		bool takeTheSameDirection = (rand() % 100) < 80; // jest 80% szansy, ze duch wybierze ten sam kierunek co wczesniej
		bool goAwayFromDevourer = true ;(rand() % 100) < 70; // jest 70% szansy, ze duch wybierze kierunek oddalajcy go od pozeracza
		if (takeTheSameDirection)
		{	
			randomDirection = lastMoveDirection;
		}
		else
		{
			randomDirection = (MoveDirection)(rand() % 4);
		}

		if (map->canObjectMove(this, randomDirection) == false)
		{
			continue;
		}

		if (goAwayFromDevourer && isCloseToDevourer())
		{
			int currentDistance;
			int nextDistance;
			switch(randomDirection)
			{
			case UP:
				currentDistance = abs(position.y - map->player->getPosition().y);
				nextDistance = abs(position.y + 1 - map->player->getPosition().y);
				break;
			case DOWN:
				currentDistance = abs(position.y - map->player->getPosition().y);
				nextDistance = abs(position.y - 1 - map->player->getPosition().y);
				break;
			case LEFT:
				currentDistance = abs(position.x - map->player->getPosition().x);
				nextDistance = abs(position.x - 1 - map->player->getPosition().x);
				break;
			case RIGHT:
				currentDistance = abs(position.x - map->player->getPosition().x);
				nextDistance = abs(position.x + 1 - map->player->getPosition().x);
				break;
			}
			if (nextDistance < currentDistance)
			{
				// Nie chcemy, zeby duch sie zblizyl do pozeracza...
				if (tryCount < tryCountLimit)
				{
					tryCount++;
					continue;
				}
			}
		}
		if (move(randomDirection))
		{
			lastMoveDirection = randomDirection;
			break;
		}
		else
		{
			if (tryCount > tryCountLimit)
			{
				break;
			}
			tryCount++;
		}
	}
}

MapTile::MapTile()
{
	type = EMPTY;
}

void MapTile::setType(MapTileType t)
{
	type = t;
}