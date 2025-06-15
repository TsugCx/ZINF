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

    PLAYER p1 = {600, 400, false, {600, 400, 'N'}, {0}};
    p1.hitbox = (Rectangle){p1.x_y.position_x, p1.x_y.position_y, 50, 50};
    GLOBAL environment = {1, "../maps/mapa00.txt"};

    IntroductionMenu();

    while(!WindowShouldClose()) {

        PlayerControl(&p1, &environment);
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
