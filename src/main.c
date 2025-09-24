#include <stdio.h>

#include "raylib.h"
#include "../headers/type.h"
#include "../headers/core.h"

#define SCREEN_HEIGHT 860
#define SCREE_WIDTH 1200


int main() {
    //Pré-boot
    InitWindow(SCREE_WIDTH, SCREEN_HEIGHT, "The Legend Of Adventure Time");
    SetWindowIcon(LoadImage("../assets/finn_icon.png"));


    Texture2D finn = LoadTexture("../assets/sprite_finn.png");
    Texture2D zombie = LoadTexture("../assets/sprite_zombie.png");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        //loop principal do jogo.
        IntroductionMenu();

        MAP environment = {0};
        CONTROL org = {0};
        PLAYER p1 = {0};

        RenameMap(&org);
        ReadMap(&environment, &org, &p1);
        SetupPlayer(&p1);

        bool game_running = false;

        while (!WindowShouldClose()) {

            if (IsKeyPressed(KEY_TAB)) {
                game_running = !game_running;
            }


            if (game_running) {
                BeginDrawing();
                ClearBackground(BLACK);
                PauseMenu(&game_running);
                EndDrawing();
            } else {
                LogicProcessingCore(&environment, &org, &p1);
                GraphicsProcessingCore(&environment, &org, &p1, finn, zombie);
            }

        }
    }

    return 0;
}

