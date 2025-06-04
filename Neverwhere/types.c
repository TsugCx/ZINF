#include "raylib.h"
#include "types.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>


void GlobalInit(GLOBAL *environment);



void PlayerControl(PLAYER *p1){

        #define MOVE 2

        if ((IsKeyPressed(KEY_D) || IsKeyDown(KEY_D)) && p1->px < 1200)//Move o player para a direita
            p1->px += MOVE;

        if ((IsKeyPressed(KEY_A) || IsKeyDown(KEY_A)) && p1->px >= 0)//Move o player para a esquerda
            p1->px -= MOVE;

        if ((IsKeyPressed(KEY_W) || IsKeyDown(KEY_W)) && p1->py >= 60)//Move o player para cima
            p1->py -= MOVE;

        if ((IsKeyPressed(KEY_S) || IsKeyDown(KEY_S)) && !(p1->py >= 860))//Move o player para baixo
            p1->py += MOVE;
}

void DrawGameBar() {

    DrawRectangle(0, 0, 1200, 60, BLUE);

}
