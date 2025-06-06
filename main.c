#include "raylib.h"
#include "core.h"
#include "types.h"
#include <stdbool.h>

#define height 860
#define width 1200


int main() {

    InitWindow(width, height, "The Legend Of Adventure Time");
    SetTargetFPS(60);

    PLAYER p1 = {100, 100, false, {600.0f, 100.0f, 'N'}, {p1.xy.px, p1.xy.py, 50, 50}};

    IntroductionMenu();

    while(!WindowShouldClose()) {

        PlayerControl(&p1);

        BeginDrawing();

        DrawRectangle(p1.xy.px, p1.xy.py, 50, 50, BLUE);
        MousePositionForPlayerAttack(&p1);
        DrawGameBar();

        ClearBackground(BLACK);
        EndDrawing();

    }


    return 0;
}
