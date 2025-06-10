#include "../headers/types.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void RenameMap(GLOBAL *environment) {//Subfunção de ReadMap();

    if (environment->count_map < 1)//Garante que nenhum mapa fora do escopo seja chamado [1 - 99]
        environment->count_map = 1;

    if (environment->count_map < 10 && environment->count_map > 0) {//Renomeia o arquivo para casos em que o contador esteja no intervalo de [1 - 9]
        sprintf(environment->map_name, "../maps/mapa0%d.txt", environment->count_map);

    } else if (environment->count_map > 9 && environment->count_map <= 99) {//Renomeia o arquivo para casos em que o contador esteja no intervalo de [10 - 99]
        sprintf(environment->map_name, "../maps/mapa%d.txt", environment->count_map);
    }

}


void ReadMap(GLOBAL *environment) {
    FILE *arq = fopen(environment->map_name, "r");

    if (arq != NULL) {

        char caractere;
        for(int8_t i = 0; i < 16; i++)
            for (int8_t j = 0; j < 24; j++) {

                caractere = getc(arq);

                if(caractere == '\n') {
                    continue;
                } else {
                    environment->phase_map[i][j] = caractere;
                }
            }

    }
    fclose(arq);
}

void DrawMap(GLOBAL *environment) {

    const int8_t lines = 16, columns = 24;

    for (int8_t i = 0; i <  columns; i++)
        for (int8_t j = 0; j < lines; j++) {

            switch (environment->phase_map[i][j]) {

                case ' ':
                    DrawRectangle(0 + 50 * i, 60 + 50 * j, 50, 50, DARKGREEN);
                break;

                case 'P':

                    if (j < columns && environment->phase_map[i][j + 1] == 'P') {
                        DrawRectangle(0 + 50 * i, 60 + 50 * j, 50, 50, GRAY);
                    } else {
                        DrawRectangle(0 + 50 * i, 60 + 50 * j, 50, 50, DARKGRAY);
                    }
                break;

                case 'M':
                    DrawRectangle(0 + 50 * i, 60 + 50 * j, 50, 50, RED);
                    break;
                case 'V':
                    DrawRectangle(0 + 50 * i, 60 + 50 * j, 50, 50, PINK);
                    break;
                default:
                    DrawRectangle(0 + 50 * i, 60 + 50 * j, 50, 50, DARKGREEN);
                break;
            }
        }

}



void PlayerControl(PLAYER *p1) {

    #define MOVE 6

    if ((IsKeyPressed(KEY_D) || IsKeyDown(KEY_D)) && p1->x_y.position_x < 1150)//Move o player para a direita
        p1->x_y.position_x += MOVE;

    if ((IsKeyPressed(KEY_A) || IsKeyDown(KEY_A)) && p1->x_y.position_x > 0)//Move o player para a esquerda
        p1->x_y.position_x -= MOVE;

    if ((IsKeyPressed(KEY_W) || IsKeyDown(KEY_W)) && p1->x_y.position_y > 60)//Move o player para cima
        p1->x_y.position_y -= MOVE;

    if ((IsKeyPressed(KEY_S) || IsKeyDown(KEY_S)) && p1->x_y.position_y < 810)//Move o player para baixo
        p1->x_y.position_y += MOVE;
}

void MousePositionForPlayerAttack(PLAYER *p1) {

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        int mouse_x = GetMouseX();
        int mouse_y = GetMouseY();

        const uint8_t DELTA_X = 100, DELTA_Y = 200;

        bool ch_y = mouse_y < p1->x_y.position_y - DELTA_Y;
        bool dg_y = mouse_y > (p1->x_y.position_y - DELTA_Y) && mouse_y < (p1->x_y.position_y + DELTA_Y);
        bool eh_y = mouse_y > p1->x_y.position_y + DELTA_Y;

        //Verifica A e B || SUL e NORTE
        if (mouse_x > (p1->x_y.position_x - DELTA_X) && mouse_x < (p1->x_y.position_x + DELTA_X * 2)) {
            if (mouse_y > p1->x_y.position_y)
                DrawRectangle(mouse_x, mouse_y, 50, 50, RED); //Lado A: SUL

            if (mouse_y < p1->x_y.position_y)
                DrawRectangle(mouse_x, mouse_y, 50, 50, RED); //Lado B: NORTE

            return;
        } else if (mouse_x < p1->x_y.position_x) {
            //Verifica {C, D, E} || OESTE[inferior, medial e superior]

            if (ch_y)
                DrawRectangle(mouse_x, mouse_y, 100, 100, PURPLE);
            if (dg_y)
                DrawRectangle(mouse_x, mouse_y, 100, 100, SKYBLUE);
            if (eh_y)
                DrawRectangle(mouse_x, mouse_y, 100, 100, PINK);

            return;
        } else if (mouse_x > p1->x_y.position_x) {
            //Verifica {H, G, F} || LESTE[inferior, medial e superior]

            if (ch_y)
                DrawRectangle(mouse_x, mouse_y, 100, 100, LIME);
            if (dg_y)
                DrawRectangle(mouse_x, mouse_y, 100, 100, GOLD);
            if (eh_y)
                DrawRectangle(mouse_x, mouse_y, 100, 100, BROWN);

            return;
        }
    }
}

void DrawGameBar(){

    DrawRectangle(0, 0, 1200, 60, BLACK);

}