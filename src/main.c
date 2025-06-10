#include "raylib.h"
#include "../headers/core.h"
#include "../headers/types.h"
#include <stdbool.h>
#include <stdio.h>

#define height 860
#define width 1200

int main() {

    InitWindow(width, height, "The Legend Of Adventure Time");
    SetTargetFPS(60);

    PLAYER p1 = {100, 100, false, {600, 100, 'N'}, {p1.x_y.position_x = 550, p1.x_y.position_y = 350, 50, 50}};
    GLOBAL environment = {1, "../maps/mapa00.txt"};

    IntroductionMenu();

    while(!WindowShouldClose()) {

        PlayerControl(&p1);
        RenameMap(&environment);
        ReadMap(&environment);

        BeginDrawing();

        DrawMap(&environment);

        DrawRectangle(p1.x_y.position_x, p1.x_y.position_y, 50, 50, BLUE);
        MousePositionForPlayerAttack(&p1);
        DrawGameBar();

        ClearBackground(BLACK);
        EndDrawing();

    }


    return 0;
}
