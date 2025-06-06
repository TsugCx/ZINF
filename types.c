//
// Created by gutsa on 05/06/2025.
//

#include "types.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void GlobalInit(GLOBAL *environment);



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

/*
void MousePositionForPlayerAttack(PLAYER *p1) {

#define DELTAX 50
#define DELTAY 200

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

        int mx = GetMouseX();
        int my = GetMouseY();

        if(mx > (p1->xy.px - DELTAX)) && mx < (p1->xy.px + DELTAX * 2)) {

            if(my > p1->xy.py) {

            }
            if(my > p1->xy.py) {

            }

        }


    }


}
*/

