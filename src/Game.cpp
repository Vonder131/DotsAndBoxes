#include "Game.h"
#include <vector>
#include <cstdlib> // Needed for rand() and srand()
#include <ctime>   // Needed for time()

void drawX(int X, int Y) {
    Vector2 v1 = { X - 18,Y - 18 };
    Vector2 v2 = { X + 18,Y + 18 };
    Vector2 v3 = { X - 18,Y + 18 };
    Vector2 v4 = { X + 18,Y - 18 };
    DrawLineEx(v1, v2, 5, GREEN);
    DrawLineEx(v3, v4, 5, GREEN);
}

int Cell::returnEdges() {
    int number = 0;
    for (int i = 0; i < 4; i++) {
        if (this->edges[i])
            number++;
    }
    return number;
}

Cell::Cell() {
    for (int i = 0; i < 4; i++) {
        this->edges[i] = 0;
    }
    value = 0;
}

bool Cell::checkValue() {
    if (edges[0] == true && edges[1] == true && edges[2] == true && edges[3] == true) {
        if (xTurn == true) {
            this->value = 1;
        }
        else {
            this->value = -1;
        }
        return true;
    }
    else
        return false;
}

bool Cell::updateEdge(int orientation) {
    switch(orientation) {
        case LEFT: 
            if (edges[LEFT] == 0)edges[LEFT] = 1;
            else
                return true;
            break;
        case TOP: 
            if (edges[TOP] == 0)edges[TOP] = 1;
            else return true;
            break;
        case RIGHT: 
            if (edges[RIGHT] == 0)edges[RIGHT] = 1;
            else return true;
            break;
        case DOWN: 
            if (edges[DOWN] == 0)edges[DOWN] = 1;
            else return true;
            break;
        default:
            break;
	}

    return checkValue();
}

void drawO(int X, int Y) {

    Vector2 v = { X,Y };
    DrawRing(v, 17, 22, 0, 360, 16, RED);
}


int checkInput(int X, int Y) {

    int input = 1;

    if ((X - 100) % 60 > 4 && ((X - 100) % 60 < 56)) {
        input = 2;
        if ((Y - 100) % 60 > 4 && (Y - 100) % 60 < 56)
            input = 0;
    }

    return input;
}


int getIndex(int number) {
    if (number % 60 >= 0 && number % 60 < 30) {
        return (number - 8) / 60;
    }
    else
        return (number / 60);

}

void setCells(int X, int Y) {
    if (checkInput(X, Y) == 0) {
        return;
    }

    if (checkInput(X, Y) == 1) {
        if (X - 100 < 5) {
            xTurn = (cells[9 * ((Y - 100) / 60)].updateEdge(LEFT)) ? xTurn : !xTurn;
            lastMove = 4 * (9 * ((Y - 100) / 60));
        }
        else if (X - 100 > 536) {
            xTurn = (cells[9 * ((Y - 100) / 60) + 8].updateEdge(RIGHT)) ? xTurn : !xTurn;
            lastMove = 4 * (9 * ((Y - 100) / 60) + 8) + 2;
        }
        else {

            if (cells[9 * ((Y - 100) / 60) + getIndex(X - 100)].updateEdge(RIGHT) + //the addition instead of "&&" is used for the second condition to execute
                cells[9 * ((Y - 100) / 60) + getIndex(X - 100) + 1].updateEdge(LEFT) == 0) { //checks if there is no scoring point for both boxes
                xTurn = !xTurn;
            }
            lastMove = 4 * (9 * ((Y - 100) / 60) + getIndex(X - 100)) + 2;
        }
    }
    else {
        if (Y - 100 < 5) {
            xTurn = (cells[(X - 100) / 60].updateEdge(TOP)) ? xTurn : !xTurn;
            lastMove = 4 * ((X - 100) / 60) + 1;
        }
        else if (Y - 100 > 536) {
            xTurn = (cells[((X - 100) / 60) + 72].updateEdge(DOWN)) ? xTurn : !xTurn;
            lastMove = 4 * (((X - 100) / 60) + 72) + 3;
        }
        else  {
            if (cells[((X - 100) / 60) + 9 * getIndex(Y - 100)].updateEdge(DOWN) +
                cells[((X - 100) / 60) + 9 * getIndex(Y - 100) + 9].updateEdge(TOP) == 0) {
                xTurn = !xTurn;
            };
            lastMove = 4 * (((X - 100) / 60) + 9 * getIndex(Y - 100)) + 3;
        }
    }
}

void drawCells() {

    for (int i = 0; i < 81; i++) {
        for (int j = 0; j < 4; j++) {
            if (cells[i].edges[0])
                DrawRectangle(98 + (60 * (i % 9)), 98 + (60 * std::floor(i / 9)), 4, 60, ELEMENTS_COLOR);
            if (cells[i].edges[1])
                DrawRectangle(98 + (60 * (i % 9)), 98 + (60 * std::floor(i / 9)), 60, 4, ELEMENTS_COLOR);
            if (cells[i].edges[2])
                DrawRectangle(158 + (60 * (i % 9)), 98 + (60 * std::floor(i / 9)), 4, 60, ELEMENTS_COLOR);
            if (cells[i].edges[3])
                DrawRectangle(98 + (60 * (i % 9)), 158 + (60 * std::floor(i / 9)), 60, 4, ELEMENTS_COLOR);
        }
    }

    if (lastMove != -1) {
        drawLastMove();
    }
}

void drawLastMove() {

    int i = lastMove / 4;

    for (int j = 0; j < 4; j++) {
        if (lastMove % 4 == 0)
            DrawRectangle(98 + (60 * (i % 9)), 98 + (60 * std::floor(i / 9)), 4, 60, LAST_MOVE_COLOR);
        if (lastMove % 4 == 1)
            DrawRectangle(98 + (60 * (i % 9)), 98 + (60 * std::floor(i / 9)), 60, 4, LAST_MOVE_COLOR);
        if (lastMove % 4 == 2)
            DrawRectangle(158 + (60 * (i % 9)), 98 + (60 * std::floor(i / 9)), 4, 60, LAST_MOVE_COLOR);
        if (lastMove % 4 == 3)
            DrawRectangle(98 + (60 * (i % 9)), 158 + (60 * std::floor(i / 9)), 60, 4, LAST_MOVE_COLOR);
    }
}

void drawPoints() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            DrawCircle(100 + i * 60, 100 + j * 60, 4, ELEMENTS_COLOR);
        }
    }
}

void drawXO() {
    for (int i = 0; i < 81; i++) {
        if (cells[i].value == 1) {
            drawX(130 + 60 * (i % 9), 130 + 60 * (i / 9));
        }
        else if (cells[i].value == -1) {
            drawO(130 + 60 * (i % 9), 130 + 60 * (i / 9));
        }
    }
}

void calculateScore() {
    scoreX = 0;
    scoreO = 0;
    for (int i = 0; i < 81; i++) {
        if (cells[i].value == 1)
            scoreX++;
        else if (cells[i].value == -1)
            scoreO++;
    }
}

void renderUI() {

    DrawRectangle(300, 10, 60, 4, ELEMENTS_COLOR);//Drawing the box that shows turn
    DrawRectangle(300, 10, 4, 60, ELEMENTS_COLOR);
    DrawRectangle(300, 70, 60, 4, ELEMENTS_COLOR);
    DrawRectangle(360, 10, 4, 64, ELEMENTS_COLOR);

    DrawRectangle(0, 78, 750, 2, WHITE);//Draws the white line between the UI and rest of screen
    if (xTurn)
        drawX(333, 40);
    else
        drawO(333, 40);

    DrawText(TextFormat("X: %d", scoreX), 440, 15, 30, GREEN); //Drawing the score
    DrawText(TextFormat("O: %d", scoreO), 440, 45, 30, RED);
}

void AITurn() {
    if (!xTurn) {
        if (!makeAMove())
            xTurn = !xTurn;
        else
            AITurn();
    }
}

bool AIUpdateCell(int i, int j) {

    bool pointCheck1 = false;//boolean value to check if the update resulted in a scoring point
    bool pointCheck2 = false;//second boolean used when the edge is between two boxes

    if (i < 9 && j == 1) {
        pointCheck1 = cells[i].updateEdge(TOP);
        lastMove = i * 4 + 1;
    }
    else if (i > 72 && j == 3) {
        pointCheck1 = cells[i].updateEdge(DOWN);
        lastMove = i * 4 + 3;
    }
    else {
        if (j == 0) {
            pointCheck1 = cells[i].updateEdge(LEFT);
            lastMove = i * 4;
            if (i % 9 > 0) {
                pointCheck2 = cells[i - 1].updateEdge(RIGHT);
            }
        }
        else if (j == 1) {
            pointCheck1 = cells[i].updateEdge(TOP);
            pointCheck2 = cells[i - 9].updateEdge(DOWN);
            lastMove = i * 4 + 1;
        }
        else if (j == 2) {
            pointCheck1 = cells[i].updateEdge(RIGHT);
            lastMove = i * 4 + 2;
            if (i % 9 < 8) {
                pointCheck2 = cells[i + 1].updateEdge(LEFT);
            }
        }
        else if (j == 3) {

            pointCheck1 = cells[i].updateEdge(DOWN);
            pointCheck2 = cells[i + 9].updateEdge(TOP);
            lastMove = i * 4 + 3;
        }
    }
    if (pointCheck1 || pointCheck2) {
        return true;
    }
    else return false;
}

bool makeAMove() {
    int move = chooseTheMove();
    return AIUpdateCell(int(move / 4), move % 4);
}

int chooseTheMove() {

    int move = randomMove();

    if (move == -1) {
        for (int i = 0; i < 81; i++) {
            if (cells[i].value == 0) {
                for (int j = 0; j < 4; j++) {
                    if (cells[i].edges[j] == false) {
                        move = i * 4 + j;
                        break;//finds the first unchecked edge in an empty cell
                    }
                }
                break;
            }
        } // initialize the edge values with the first valid move
    }

    for (int i = 0; i < 81; i++) {
        if (cells[i].returnEdges() == 3) {
            for (int j = 0; j < 4; j++) {
                if (cells[i].edges[j] == false) {
                    move = i * 4 + j;
                }
            }
        }
    }

    return move;
}

int randomMove() {
    int edge = -1;

    int chosenCell;
    int chosenEdge;
    std::vector<int> v1;

    for (int i = 0; i < 81; i++) {
        if (cells[i].returnEdges() != 2 && cells[i].returnEdges() != 4) {
            for (int j = 0; j < 4; j++) {
                if (cells[i].edges[j] == false) {
                    v1.push_back(i * 4 + j);
                }
            }
        }
    }
    std::vector<int> v2(v1);
    if (!v1.empty()) {
        int randomNumber = getRandomNumber(v1.size());// get a random valid index
        bool checked = checkBadMove(v1[randomNumber]);//check if the index generates a bad move
        std::cout << "Bad moves: {";
        while (checked && !v1.empty()) {
            std::cout << "[" << v1[randomNumber] / 4 << ", " << v1[randomNumber] % 4 << "]," << std::endl;
            v1.erase(v1.begin() + randomNumber);
            if (v1.empty()) break;
            randomNumber = getRandomNumber(v1.size());//get a new valid index
            checked = checkBadMove(v1[randomNumber]);

        };

        std::cout << "}" << std::endl;
        if (!v1.empty()) {
            edge = v1[randomNumber];
        }
        else {
            int newRandomNumber = getRandomNumber(v2.size());// if all moves are bad, choose a random one from the original vector
            edge = v2[newRandomNumber];// this will be a bad move, but at least it will be a valid one
        }
    }

    return edge;

}

bool checkBadMove(int move) {
    if (cells[move / 4].returnEdges() == 2) {
        return true;
    }

    switch (getTypeOfMove(move)) {
    case MIDDLE:
        switch (getTypeOfEdge(move)) {
        case LEFT:
            if (cells[(move / 4 - 1)].returnEdges() == 2) return true;
            break;
        case TOP:
            if (cells[(move / 4 - 9)].returnEdges() == 2) return true;
            break;
        case RIGHT:
            if (cells[(move / 4 + 1)].returnEdges() == 2) return true;
            break;
        case DOWN:
            if (cells[(move / 4 + 9)].returnEdges() == 2) return true;
        }
        break;
    case LEFT:
        switch (getTypeOfEdge(move)) {
        case TOP:
            if (cells[move / 4 - 9].returnEdges() == 2) return true;
            break;
        case RIGHT:
            if (cells[move / 4 + 1].returnEdges() == 2) return true;
            break;
        case DOWN:
            if (cells[move / 4 + 9].returnEdges() == 2) return true;
            break;
        }
        break;
    case TOP:
        switch (getTypeOfEdge(move)) {
        case LEFT:
            if (cells[move / 4 - 1].returnEdges() == 2) return true;
            break;
        case RIGHT:
            if (cells[move / 4 + 1].returnEdges() == 2) return true;
            break;
        case DOWN:
            if (cells[move / 4 + 9].returnEdges() == 2) return true;
            break;
        }
        break;
    case RIGHT:
        switch (getTypeOfEdge(move)) {
        case LEFT:
            if (cells[move / 4 - 1].returnEdges() == 2) return true;
            break;
        case TOP:
            if (cells[move / 4 - 9].returnEdges() == 2) return true;
            break;
        case DOWN:
            if (cells[move / 4 + 9].returnEdges() == 2) return true;
            break;
        }
        break;
    case DOWN:
        switch (getTypeOfEdge(move)) {
        case LEFT:
            if (cells[move / 4 - 1].returnEdges() == 2) return true;
            break;
        case TOP:
            if (cells[move / 4 - 9].returnEdges() == 2) return true;
            break;
        case RIGHT:
            if (cells[move / 4 + 1].returnEdges() == 2) return true;
            break;
        }
        break;
    default:
        std::cout << "Invalid move type!" << std::endl;
        break;
    }

    std::cout << "Good move: cell: " << int(move / 4) << ", edge: " << move % 4 << std::endl;
    return false; // if no bad move is found, return false
}

int getRandomNumber(int size) {
    std::srand(time(0));
    int random = 0;
    if (size != 0) {
        random = rand() % size;
    }
    return random;
}

int getTypeOfMove(int move) {
    if (move / 4 < 9) {
        return TOP; // Top row
    }
    else if (move / 4 > 72) {
        return DOWN; // Bottom row
    }
    else if (move / 4 % 9 == 0) {
        return LEFT; // Left column
    }
    else if (move / 4 % 9 == 8) {
        return RIGHT; // Right column
    }
    else {
        return MIDDLE; // Middle cells
    }
}

int getTypeOfEdge(int move) {
    if (move % 4 == 0) {
        return LEFT; // Left edge
    }
    else if (move % 4 == 1) {
        return TOP; // Top edge
    }
    else if (move % 4 == 2) {
        return RIGHT; // Right edge
    }
    else if (move % 4 == 3) {
        return DOWN; // Bottom edge
    }
    else {
        return -1; // Invalid edge
    }
}