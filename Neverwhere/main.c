#include "raylib.h"
#include "core.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stdint.h>
#include <stdbool.h>

#define height 800
#define width 1200

int main() {

    InitWindow(width, height, "Neverwhere");
    SetTargetFPS(60);

    int x = 400, y = 600;

    introduction_menu();
    while(!WindowShouldClose()) {

        if (IsKeyPressed(KEY_RIGHT) || IsKeyDown(KEY_RIGHT)) {
            x += 4;
        }

        if (IsKeyPressed(KEY_LEFT) || IsKeyDown(KEY_LEFT)) {
            x -= 4;
        }

        if (IsKeyPressed(KEY_UP) || IsKeyDown(KEY_UP)) {
            y -= 4;
        }

        if (IsKeyPressed(KEY_DOWN) || IsKeyDown(KEY_DOWN)) {
            y += 4;
        }

        BeginDrawing();
        DrawRectangle(x, y, 20, 20, BLUE);
        ClearBackground(BLACK);
        EndDrawing();

        if (x < 0 || x > 1200 || y < 0 || y > 800) {
            CloseWindow();
        }
    }


    return 0;
}
