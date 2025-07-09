#pragma once
#include "raylib.h"
#include <iostream>


#define ELEMENTS_COLOR  CLITERAL(Color) { 129, 176, 181, 255 }
#define LAST_MOVE_COLOR CLITERAL(Color) { 210, 98, 199, 255 }

typedef enum orientation {
	LEFT = 0,
	TOP,
	RIGHT,
	DOWN,
	MIDDLE, // for the center cell
} orientation;

static bool xTurn = true;

static int scoreX = 0;
static int scoreO = 0;
static int lastMove = -1;

void drawX(int X, int Y);

class Cell {
public:

	bool edges[4];
	int value; //-1,0,1

	Cell();
	bool checkValue();
	bool updateEdge(int orientation);
	int returnEdges();
};


int checkInput(int X, int Y);
int getIndex(int number);


static Cell cells[81];
void setCells(int X, int Y);
void calculateScore();
int getTypeOfMove(int move);
int getTypeOfEdge(int move);


void drawO(int X, int Y);
void renderUI();
void drawCells();
void drawLastMove();
void drawPoints();
void drawXO();



void AITurn();
bool makeAMove();
int chooseTheMove();
int randomMove();
bool checkBadMove(int move);
int getRandomNumber(int size);