#include "raylib.h"
#include "Game.h"
#include <iostream>
#include <stdlib.h>



//------------------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------------------
#define BGCOLOR1 CLITERAL(Color) { 20, 23, 28, 255 }
#define BGCOLOR2 CLITERAL(Color) { 32, 35, 40, 255 }
#define BTCOLOR1 CLITERAL(Color) { 118, 107, 91, 255 }
#define BTCOLOR2 CLITERAL(Color) { 223, 208, 184, 255 }


//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen {TITLE = 0, GAME, PAUSE, AI } GameScreen;
Rectangle pause_btnBoundsResume = { 300,360,150,50 };
Rectangle pause_btnBoundsMenu = { 300,430,150,50 };

Rectangle title_btnBoundsPlay = { 300,280,150,50 };
Rectangle title_btnBoundsAI = { 300,350,150,50 };
Rectangle title_btnBoundsExit = { 300,420,150,50 };

//------------------------------------------------------------------------------------------
// Initialization
//------------------------------------------------------------------------------------------
const int screenWidth = 740;
const int screenHeight = 740;
Cell* cell = cells;

bool windowShouldClose = false;

GameScreen currentScreen = TITLE;

int btnPause_StateResume = 1;
int btnPause_StateMenu = 1;

int btnTitle_StatePlay = 1;
int btnTitle_StateAI = 1;
int btnTitle_StateExit = 1;

Vector2 mousePoint = { 0.0f, 0.0f };

//------------------------------------------------------------------------------------------
// Draw and Tick functions called in the main loop
//------------------------------------------------------------------------------------------

void titleDraw() {
    ClearBackground(BGCOLOR2);
    DrawText("MENU", screenWidth / 2 - 80, 70, 60, ELEMENTS_COLOR);
    DrawRectangle(0, 150, 750, 2, WHITE);

    if (btnTitle_StatePlay == 1) {
        DrawRectangleRounded(title_btnBoundsPlay, 0.8, 5, BTCOLOR1);
        DrawText("PLAY", title_btnBoundsPlay.x + 35, title_btnBoundsPlay.y + 12, 30, LIGHTGRAY);
    }
    else {
        DrawRectangleRounded(title_btnBoundsPlay, 0.8, 5, BTCOLOR2);
        DrawText("PLAY", title_btnBoundsPlay.x + 35, title_btnBoundsPlay.y + 12, 30, DARKGRAY);
    }

    if (btnTitle_StateAI == 1) {
        DrawRectangleRounded(title_btnBoundsAI, 0.8, 5, BTCOLOR1);
        DrawText("vs AI", title_btnBoundsAI.x + 35, title_btnBoundsAI.y + 12, 30, LIGHTGRAY);
    }
    else {
        DrawRectangleRounded(title_btnBoundsAI, 0.8, 5, BTCOLOR2);
        DrawText("vs AI", title_btnBoundsAI.x + 35, title_btnBoundsAI.y + 12, 30, DARKGRAY);
    }

    if (btnTitle_StateExit == 1) {
        DrawRectangleRounded(title_btnBoundsExit, 0.8, 5, BTCOLOR1);
        DrawText("EXIT", title_btnBoundsExit.x + 35, title_btnBoundsExit.y + 12, 30, LIGHTGRAY);
    }
    else {
        DrawRectangleRounded(title_btnBoundsExit, 0.8, 5, BTCOLOR2);
        DrawText("EXIT", title_btnBoundsExit.x + 35, title_btnBoundsExit.y + 14, 30, DARKGRAY);
    }


}

void titleTick() {
   
    if (WindowShouldClose())
        windowShouldClose = true;

    mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, title_btnBoundsPlay)) {
        btnTitle_StatePlay = 2;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            currentScreen = GAME;
        }
    }
    else {
        btnTitle_StatePlay = 1;
    }

    if (CheckCollisionPointRec(mousePoint, title_btnBoundsAI)) {
        btnTitle_StateAI = 2;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            currentScreen = AI;
        }
    }
    else {
        btnTitle_StateAI = 1;
    }
    
    if (CheckCollisionPointRec(mousePoint, title_btnBoundsExit)) {
        btnTitle_StateExit = 2;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
           if (currentScreen == TITLE) windowShouldClose = true;
        }
    }
    else {
        btnTitle_StateExit = 1;
    }
}

void gameDraw() {
    ClearBackground(BGCOLOR1);
    drawCells();
    drawPoints();
    drawXO();
    renderUI();
}

void gameTick() {
    if (IsMouseButtonPressed(0)) {
        setCells(GetMousePosition().x, GetMousePosition().y);
        calculateScore();
        std::cout << lastMove << std::endl;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        currentScreen = PAUSE;
    }
    else if (WindowShouldClose()) {
        windowShouldClose = true;
    }
}

void AIDraw() {

}

void AITick() {
    AITurn();
    if (IsMouseButtonPressed(0)) {
        setCells(GetMousePosition().x, GetMousePosition().y);
        calculateScore();
    };
   if (IsKeyPressed(KEY_ESCAPE)) {
       currentScreen = PAUSE;
   }
   else if (WindowShouldClose()) {
       windowShouldClose = true;
   };
}


void pauseDraw() {
    DrawRectangle(0, 250, screenWidth, 300, BGCOLOR2);
    DrawText("PAUSE", screenWidth / 2 - 80, 300, 50, ELEMENTS_COLOR);

    if (btnPause_StateResume == 1) {
        DrawRectangleRounded(pause_btnBoundsResume, 0.8, 5, BTCOLOR1);
        DrawText("RESUME", 313, 372, 30, LIGHTGRAY);
    }
    else {
        DrawRectangleRounded(pause_btnBoundsResume, 0.8, 5, BTCOLOR2);
        DrawText("RESUME", 313, 372, 30, DARKGRAY);
    }

    if (btnPause_StateMenu == 1) {
        DrawRectangleRounded(pause_btnBoundsMenu, 0.8, 5, BTCOLOR1);
        DrawText("MENU", 333, 442, 30, LIGHTGRAY);
    }
    else {
        DrawRectangleRounded(pause_btnBoundsMenu, 0.8, 5, BTCOLOR2);
        DrawText("MENU", 333, 442, 30, DARKGRAY);
    }   
}

void pauseTick() {

    mousePoint = GetMousePosition();

    if (WindowShouldClose())
        windowShouldClose = true;

    if (CheckCollisionPointRec(mousePoint, pause_btnBoundsResume)) {
        btnPause_StateResume = 2;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            currentScreen = GAME;
        }
    }
    else {
        btnPause_StateResume = 1;
    }

    if (CheckCollisionPointRec(mousePoint, pause_btnBoundsMenu)) {
        btnPause_StateMenu = 2;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            currentScreen = TITLE;
        }
    }
    else {
        btnPause_StateMenu = 1;
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    InitWindow(screenWidth, screenHeight, "Dots and boxes");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!windowShouldClose)    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        switch (currentScreen) {
        case TITLE:
            titleTick();
            break;
        case GAME:
            gameTick();
            break;
        case AI:
            AITick();
            break;
        case PAUSE:
            pauseTick();
            break;
        }

        //----------------------------------------------------------------------------------
        BeginDrawing();
        switch (currentScreen) {
        case TITLE:
            titleDraw();
            break;
        case GAME:
            gameDraw();
            break;
        case AI:
            gameDraw();
            break;
        case PAUSE:
            pauseDraw();
            break;
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
      }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}