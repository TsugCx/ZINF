#include "../headers/map.h"
#include "raylib.h"
#include <stdbool.h>


//INICIO: Grupo de funções que definem as colisões, o deslocamento e seus limites pelo mapa para o jogador.
bool PlayerWallCollision(const PLAYER *p1, const MAP *environment) {
    //Verifica se a posição atual da hitbox coincide com uma hitbox de parede interando no array que armazena as paredes para colisão.

    for (int16_t i = 0; i < environment->count_obstacle; i++) {
        if (CheckCollisionRecs(p1->hitbox, environment->collision_map[i])) {
            return true;
        }
    }
    return false;
}

void Knockback(PLAYER *player, MAP *environment) {

    for (int8_t i = 0; i < environment->count_monster; i++) {
        if (CheckCollisionRecs(player->hitbox, environment->monster_list[i].hitbox)) {

            const int8_t MOVE = 3;
            int16_t move_x = environment->monster_list[i].position.x - player->position.x;
            int16_t move_y = environment->monster_list[i].position.y - player->position.y;

            if (player->position.x < environment->monster_list[i].position.x && !PlayerWallCollision(player, environment)) {
                player->position.x -= move_x;
                player->hitbox.x = player->position.x;

            } else if (player->position.x > environment->monster_list[i].position.x && !PlayerWallCollision(player, environment)) {
                player->position.x += move_x;
                player->hitbox.x = player->position.x;
            }

            if (player->position.y < environment->monster_list[i].position.y && !PlayerWallCollision(player,  environment)) {
                player->position.y -= move_y;
                player->hitbox.y = player->position.y;

            } else if (player->position.y > environment->monster_list[i].position.y && !PlayerWallCollision(player, environment)) {
                player->position.y += move_y;
                player->hitbox.y = player->position.y;
            }

        }
    }
}

void Position_Modifier_And_Hitbox_In_X(PLAYER *p1, MAP *environment, int8_t MOVE) {
    //Recebe um valor positvo ou negativo e atualiza a posição do jogador e de sua hitbox em X.

    p1->position.x += MOVE;
    p1->hitbox.x = p1->position.x;

    if (PlayerWallCollision(p1, environment)) {
        p1->position.x -= MOVE;
        p1->hitbox.x = p1->position.x;
    }
}

void Position_Modifier_And_Hitbox_In_Y(PLAYER *p1, MAP *environment, int8_t MOVE) {
    //Recebe um valor positvo ou negativo e atualiza a posição do jogador e de sua hitbox em Y.

    p1->position.y -= MOVE;
    p1->hitbox.y = p1->position.y;

    if (PlayerWallCollision(p1, environment)) {
        p1->position.y += MOVE;
        p1->hitbox.y = p1->position.y;
    }
}

void PlayerControl(PLAYER *p1, MAP *environment) {
    const int8_t MOVE_POSITIVE = 3, MOVE_NEGATIVE = -3;

    if ((IsKeyPressed(KEY_D) || IsKeyDown(KEY_D)) && p1->position.x < 1150) //Move o player para a direita
        Position_Modifier_And_Hitbox_In_X(p1, environment, MOVE_POSITIVE);

    if ((IsKeyPressed(KEY_A) || IsKeyDown(KEY_A)) && p1->position.x > 0) //Move o player para a esquerda
        Position_Modifier_And_Hitbox_In_X(p1, environment, MOVE_NEGATIVE);

    if ((IsKeyPressed(KEY_W) || IsKeyDown(KEY_W)) && p1->position.y > 60) //Move o player para cima
        Position_Modifier_And_Hitbox_In_Y(p1, environment, MOVE_POSITIVE);

    if ((IsKeyPressed(KEY_S) || IsKeyDown(KEY_S)) && p1->position.y < 810) //Move o player para baixo
        Position_Modifier_And_Hitbox_In_Y(p1, environment, MOVE_NEGATIVE);
}

void AttackCollision(Rectangle object, MAP *enviroment) {

    for (int8_t i = 0; i < enviroment->count_monster; i++) {
        if (CheckCollisionRecs(object, enviroment->monster_list[i].hitbox)) {

            enviroment->monster_list[i].hit_count++;

        }
    }
}

/*
void PlayerAttack(PLAYER *p1, uint8_t direction, MAP *environment) {

    switch (direction) {

        case 0://Norte
            p1->hit_areaA  =  (Rectangle){p1->position.x, p1->position.y - 150, 50, 150};
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            DrawRectangle(p1->position.x, p1->position.y - 150, 50, 150, GOLD);

            if (AttackCollision(p1->hit_areaA, environment)) {
                environment
            };
        }
            for (int8_t i = 0; i)
            break;

         case 1:
             p1->hit_areaA  =  (Rectangle){p1->position.x, p1->position.y + 50, 50, 150};

            break;

         case 2:
            break;

         case 3:
            break;

         case 4:
            break;

         case 5:
            break;

         case 6:
            break;

         case 7:
            break;
    }
}
*/


void MousePositionForPlayerAttack(PLAYER *p1, MAP *environment) {
/*Inicializa 9 Rectangles, 8 direções, 2 verticais, 2 horizontais e 4 diagonais e por ultimo o mouse, e posiciona esses
 Rectagles, ao Norte, Sul, Oeste, Leste, Nordeste, Sudestes, Noroeste, Sudoeste respectivamente, ao efetuar a achar de
 pressionar o botão do mouse e feita uma comparação até achar a colisão do mouse com algun dos rectangulos pela tela
 executando assim uma de 8 possiveis ações. */

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

        int mouse_x = GetMouseX(), mouse_y = GetMouseY();

        Rectangle mouse = {mouse_x, mouse_y, 1, 1};

        Rectangle north = {p1->position.x - 30, p1->position.y - 810, 110, 810};//Vertical, acima do jogador
        Rectangle south = {p1->position.x - 30, p1->position.y, 110, 810};//Vertical, abaixo do jogador

        if (CheckCollisionRecs(mouse, north)) {//Zonas verticais
           // PlayerAttack(p1, 0);

        } else if (CheckCollisionRecs(mouse, south)) {
            DrawRectangle(p1->position.x - 30, p1->position.y + 50, 110, 810, RED);

        } else {//Zonas horizontais
            Rectangle east = {p1->position.x + 50, p1->position.y - 75, 1200, 250};//Horizontal, a direita do jogador
            Rectangle west = {p1->position.x - 1200, p1->position.y - 100, 1225, 250};//Horizontal, a esquerda do jogador

            if (CheckCollisionRecs(mouse, east)){
                DrawRectangle(p1->position.x + 50, p1->position.y - 100, 1200, 250, PINK);

            } else if (CheckCollisionRecs(mouse, west)) {
                DrawRectangle(p1->position.x - 1200, p1->position.y - 100, 1200, 250, PINK);

            } else {
                //Zonas diagonais Nordeste e Sudeste.
                Rectangle Northeast = {p1->position.x + 50, p1->position.y - 800, 1200, 800};
                Rectangle Southeast = {p1->position.x + 50, p1->position.y + 50, 1200, 800};

                if (CheckCollisionRecs(mouse, Northeast)) {
                    DrawRectangle(p1->position.x + 50, p1->position.y - 800, 1200, 800, MAGENTA);

                } else if (CheckCollisionRecs(mouse, Southeast)) {
                    DrawRectangle(p1->position.x + 50, p1->position.y + 50, 1200, 800, MAGENTA);
                }

                //Zonas diagonais Noroeste e Sudoeste.
                Rectangle Northwest = {p1->position.x - 1225, p1->position.y - 800, 1225, 800};
                Rectangle Southwest = {p1->position.x - 1225, p1->position.y + 50, 1225, 800};

                if (CheckCollisionRecs(mouse, Northwest)) {
                    DrawRectangle(p1->position.x - 1225, p1->position.y - 800, 1225, 800, MAGENTA);

                } else if (CheckCollisionRecs(mouse, Southwest)) {
                    DrawRectangle(p1->position.x - 1225, p1->position.y + 50, 1225, 800, MAGENTA);
                }
                /*Nota:Vendo a dispoição oferecida pelos if's e else's, pode se idealizar uma função com o minimu de 4
                 *triangulos, apenas alterando a sua forma para da if, matendo a funcionalidade e reduzindo a alocação
                 *de memoria que e usada nos triangulos inutilizados dos if externos*/
            }
        }
    }
}