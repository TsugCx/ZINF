//
// Created by gutsa on 05/06/2025.
//

#include "raylib.h"
#include "core.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
                draw_menu(select);

            if(IsKeyPressed(KEY_ENTER))
                continuos = false;

            break;

            case 1:
                draw_menu(select);
            break;

            case 2:
                draw_menu(select);
            break;

            case 3:
                draw_menu(select);

            if(IsKeyPressed(KEY_ENTER))
                CloseWindow();
            break;
        }


    } while(continuos);
}

void draw_menu(int select) {

    BeginDrawing();

    DrawText("The Legend Of",       60, 160, 60, BLUE);
    DrawText("Adventure Time",       160, 220, 120, BLUE);

    DrawText("Iniciar",       500, 500, 25, WHITE);
    DrawText("Placar",        500, 560, 25, WHITE);
    DrawText("Configurações", 500, 620, 25, WHITE);
    DrawText("Sair",          500, 680, 25, WHITE);

    switch(select) {

        case 0:
            DrawRectangle(500, 530, 76, 4, BLUE);
        break;

        case 1:
            DrawRectangle(500, 590, 68, 4, BLUE);
        break;

        case 2:
            DrawRectangle(500, 650, 180, 4, BLUE);
        break;

        case 3:
            DrawRectangle(500, 710, 50, 4, BLUE);
        break;
    }

    ClearBackground(BLACK);
    EndDrawing();

}


