#include "raylib.h"
#include "../headers/core.h"
#include <stdint.h>
#include <stdbool.h>

void IntroductionMenu(){

    int8_t select = 0;
    bool continuos = true;

    do{
        if(IsKeyPressed(KEY_W)){
            select--;
            if(select < 0){
                select = 3;
            }
        }

        if(IsKeyPressed(KEY_S)){
            select++;
            if(select > 4){
                select = 0;
            }
        }


        switch(select) {

            case 0:
                DrawMenu(select);

            if(IsKeyPressed(KEY_ENTER))
                continuos = false;

            break;

            case 1:
                DrawMenu(select);
            break;

            case 2:
                DrawMenu(select);
            break;

            case 3:
                DrawMenu(select);

            if(IsKeyPressed(KEY_ENTER))
                CloseWindow();
            break;
        }


    } while(continuos);
}

void DrawMenu(int select) {

    BeginDrawing();

    DrawText("The Legend Of",       140, 180, 60, WHITE);
    DrawText("Adventure Time",       140, 240, 120, RED);

    DrawText("Iniciar",       140, 500, 25, WHITE);
    DrawText("Placar",        140, 560, 25, WHITE);
    DrawText("Configurações", 140, 620, 25, WHITE);
    DrawText("Sair",          140, 680, 25, WHITE);

    switch(select) {

        case 0:
            DrawRectangle(140, 530, 76, 4, RED);
        break;

        case 1:
            DrawRectangle(140, 590, 68, 4, RED);
        break;

        case 2:
            DrawRectangle(140, 650, 180, 4, RED);
        break;

        case 3:
            DrawRectangle(140, 710, 50, 4, RED);
        break;
    }

    ClearBackground(BLACK);
    EndDrawing();

}

void ErrorWarning() {

    do {
        Rectangle rec = {100, 60, 1000, 720};

        BeginDrawing();
        ClearBackground(BLACK);


        DrawRectangleRounded(rec, 2, 10, WHITE);
        EndDrawing();
    } while (!WindowShouldClose());
}
