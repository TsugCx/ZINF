#include "raylib.h"
#include "core.h"
#include "types.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#define height 860
#define width 1200


int main() {

    InitWindow(width, height, "Neverwhere");
    SetTargetFPS(60);

    PLAYER p1 = {100, 100, 600, 100, 0, false, 'N'};  // life, px, py, score, weapon


    int x = 460, y = 600;

    introduction_menu();

    while(!WindowShouldClose()) {

        PlayerControl(&p1);

        BeginDrawing();

        DrawRectangle(p1.px, p1.py, 50, 50, WHITE);
        DrawGameBar();

        ClearBackground(BLACK);
        EndDrawing();

    }


    return 0;
}
