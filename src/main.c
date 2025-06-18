#include "raylib.h"
#include "../headers/core.h"
#include "../headers/map.h"

#include <stdbool.h>


#define height 860
#define width 1200

int main() {

    InitWindow(width, height, "The Legend Of Adventure Time");
    SetTargetFPS(60);


    PLAYER p1 = {600, 400, 0,false, {600, 400, 'N'}, {0}, {0},{0}};
    p1.hitbox = (Rectangle){p1.position.x, p1.position.y, 50, 50};
    MAP environment = {1, "../maps/mapa00.txt"};

    RenameMap(&environment);
    ReadMap(&environment);

    IntroductionMenu();

    while(!WindowShouldClose()) {

        Knockback(&p1, &environment);

        BeginDrawing();
        DrawMap(&p1, &environment);
        PlayerControl(&p1, &environment);
        DrawRectangle(p1.position.x, p1.position.y, 50, 50, BLUE);
        RandomMovementGeneratorForMonsters(&environment);
        MousePositionForPlayerAttack( &p1,  &environment);        DrawGameBar();

        ClearBackground(BLACK);
        EndDrawing();

    }


    return 0;
}
