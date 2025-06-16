#include "raylib.h"
#include "../headers/core.h"
#include "../headers/map.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define height 860
#define width 1200

int main() {

    InitWindow(width, height, "The Legend Of Adventure Time");
    SetTargetFPS(60);


    PLAYER p1 = {600, 400, false, {600, 400, 'N'}, {0}};
    p1.hitbox = (Rectangle){p1.x_y.position_x, p1.x_y.position_y, 50, 50};
    MAP environment = {1, "../maps/mapa00.txt"};

    RenameMap(&environment);
    ReadMap(&environment);

    IntroductionMenu();

    while(!WindowShouldClose()) {

        BeginDrawing();
        DrawMap(&environment);
        PlayerControl(&p1, &environment);
        DrawRectangle(p1.x_y.position_x, p1.x_y.position_y, 50, 50, BLUE);
        RandomMovementGeneratorForMonsters(&environment);
        MousePositionForPlayerAttack(&p1);
        DrawGameBar();

        ClearBackground(BLACK);
        EndDrawing();

    }


    return 0;
}
