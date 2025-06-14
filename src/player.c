#include "../headers/map.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


//INICIO: Grupo de funções que definem as colisões, o deslocamento e seus limites pelo mapa para o jogador.
bool PlayerWallCollision(PLAYER *p1, MAP *environment) {//Verifica se a posição atual da hitbox coincide com uma hitbox de parede interando no array que armazena as paredes para colisão.

    for (int16_t i = 0; i < environment->count_obstacle; i++) {
        if (CheckCollisionRecs(p1->hitbox, environment->collision_map[i])) {
            return true;
        }
    }
    return false;
}

void Position_Modifier_And_Hitbox_In_X(PLAYER *p1, MAP *environment, int8_t MOVE) {//Recebe um valor positvo ou negativo e atualiza a posição do jogador e de sua hitbox em X.

    p1->x_y.position_x += MOVE;
    p1->hitbox.x = p1->x_y.position_x;

    if (PlayerWallCollision(p1, environment)) {
        p1->x_y.position_x -= MOVE;
        p1->hitbox.x = p1->x_y.position_x;
    }
}

void Position_Modifier_And_Hitbox_In_Y(PLAYER *p1, MAP *environment, int8_t MOVE) {//Recebe um valor positvo ou negativo e atualiza a posição do jogador e de sua hitbox em Y.

    p1->x_y.position_y -= MOVE;
    p1->hitbox.y = p1->x_y.position_y;

    if (PlayerWallCollision(p1, environment)) {
        p1->x_y.position_y += MOVE;
        p1->hitbox.y = p1->x_y.position_y;
    }
}

void PlayerControl(PLAYER *p1, MAP *environment) {

    const int8_t MOVE_POSITIVE = 3, MOVE_NEGATIVE = -3;

    if ((IsKeyPressed(KEY_D) || IsKeyDown(KEY_D)) && p1->x_y.position_x < 1150)//Move o player para a direita
        Position_Modifier_And_Hitbox_In_X(p1, environment, MOVE_POSITIVE);

    if ((IsKeyPressed(KEY_A) || IsKeyDown(KEY_A)) && p1->x_y.position_x > 0)//Move o player para a esquerda
        Position_Modifier_And_Hitbox_In_X(p1, environment, MOVE_NEGATIVE);

    if ((IsKeyPressed(KEY_W) || IsKeyDown(KEY_W)) && p1->x_y.position_y > 60)//Move o player para cima
        Position_Modifier_And_Hitbox_In_Y(p1, environment, MOVE_POSITIVE);

    if ((IsKeyPressed(KEY_S) || IsKeyDown(KEY_S)) && p1->x_y.position_y < 810)//Move o player para baixo
        Position_Modifier_And_Hitbox_In_Y(p1, environment, MOVE_NEGATIVE);

}
//FIM.

void MousePositionForPlayerAttack(PLAYER *p1 ) {

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
                DrawRectangle(mouse_x, mouse_y, 50, 50, BLUE); //Lado A: SUL

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

