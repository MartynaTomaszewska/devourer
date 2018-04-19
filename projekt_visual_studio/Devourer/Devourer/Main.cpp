// Devourer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cstdlib>
#include <GL/glut.h>

#include "Game.h"

int _tmain(int argc, char* argv[])
{
	Game& game = Game::getInstance();

	glutInit(&argc, argv);      // inicjalizuj GLUT
	glutInitWindowSize(game.getWindowWidth(), game.getWindowHeight());
	glutCreateWindow("Devourer");  // stworz okno

	glutDisplayFunc(Game::draw);   // zarejestruj funkcje obslugi wyswietlania
	glutKeyboardFunc(Game::processKeyboard); // zarejestruj funkcje obslugi klawiatury
	glutIdleFunc(Game::loopCycle); //funkcja wywowywana w czasie spoczynku 
	glutMainLoop();             // glowna petla zdarzen

	return (EXIT_SUCCESS);
}