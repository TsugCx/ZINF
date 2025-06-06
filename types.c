#include "types.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void PlayerControl(PLAYER *p1){

#define MOVE 8.0

    if ((IsKeyPressed(KEY_D) || IsKeyDown(KEY_D)) && p1->xy.px < 1150)//Move o player para a direita
        p1->xy.px += MOVE;

    if ((IsKeyPressed(KEY_A) || IsKeyDown(KEY_A)) && p1->xy.px > 0)//Move o player para a esquerda
        p1->xy.px -= MOVE;

    if ((IsKeyPressed(KEY_W) || IsKeyDown(KEY_W)) && p1->xy.py > 60)//Move o player para cima
        p1->xy.py -= MOVE;

    if ((IsKeyPressed(KEY_S) || IsKeyDown(KEY_S)) && p1->xy.py < 810)//Move o player para baixo
        p1->xy.py += MOVE;
}

void DrawGameBar() {

    DrawRectangle(0, 0, 1200, 60, WHITE);

}


void MousePositionForPlayerAttack(PLAYER *p1) {

    const float DELTA_X = 100.0;
    const float DELTA_Y = 200.0;

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        int mx = GetMouseX();
        int my = GetMouseY();

        bool ch_y = my < p1->xy.py - DELTA_Y;
        bool dg_y = my > (p1->xy.py - DELTA_Y) && my < (p1->xy.py + DELTA_Y);
        bool eh_y = my > p1->xy.py + DELTA_Y;

    //Verifica A e B || SUL e NORTE
        if (mx > (p1->xy.px - DELTA_X) && mx < (p1->xy.px + DELTA_X * 2)) {

            if (my > p1->xy.py)
                DrawRectangle(mx, my, 50, 50, RED); //Lado A: SUL

            if (my < p1->xy.py)
                DrawRectangle(mx, my, 50, 50, RED); //Lado B: NORTE

            return;

        } else if (mx < p1->xy.px) {         //Verifica {C, D, E} || OESTE[inferior, medial e superior]

            if (ch_y)
                DrawRectangle(mx, my, 100, 100, PURPLE);
            if (dg_y)
                DrawRectangle(mx, my, 100, 100, SKYBLUE);
            if (eh_y)
                DrawRectangle(mx, my, 100, 100, PINK);

            return;

        } else if (mx > p1->xy.px) {        //Verifica {H, G, F} || LESTE[inferior, medial e superior]

            if (ch_y)
                DrawRectangle(mx, my, 100, 100, LIME);
            if (dg_y)
                DrawRectangle(mx, my, 100, 100, GOLD);
            if (eh_y)
                DrawRectangle(mx, my, 100, 100, BROWN);

            return;
        }
    }
}
