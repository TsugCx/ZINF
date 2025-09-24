#include "raylib.h"
#include "../headers/type.h"
#include <math.h>
#include <stdbool.h>

void SetupPlayer(PLAYER *p1) {
    p1->status.score = 0;
    p1->status.lv = (p1->status.score / 400);
    p1->status.lv_max = 12;
    p1->status.pv = 3;
    p1->status.pv_max = (3 + p1->status.lv);

    p1->direction.horizontal = 'W';
    p1->direction.vertical = 'S';
    p1->weapon = false;

    p1->hit_areaA = (Rectangle){0};
    p1->hit_areaB = (Rectangle){0};
} //END SetupPlayer(...);...............................................................................................


void DrawnPlayer(PLAYER *p1, Texture2D finn) {
    int frame = SpriteFramePlayer(p1);
    Rectangle image_area = {frame * 50, 0, 50, 50};
    Vector2 image_pos = {p1->position.x, p1->position.y};
    DrawTextureRec(finn, image_area, image_pos, WHITE);


    //DrawRectangle((int) p1->position.x, (int) p1->position.y, TILE_SIZE, TILE_SIZE, SKYBLUE);
} //END DrawnPlayer(...);...............................................................................................

int SpriteFramePlayer(PLAYER *p1) {
    if (p1->direction.horizontal == 'W' && p1->direction.vertical == 'S') {
        return 0;
    } else if (p1->direction.horizontal == 'W' && p1->direction.vertical == 'N') {
        return 1;
    } else if (p1->direction.horizontal == 'E' && p1->direction.vertical == 'S') {
        return 2;
    } else if (p1->direction.horizontal == 'E' && p1->direction.vertical == 'N') {
        return 3;
    } else {
        p1->direction.horizontal = 'W';
        p1->direction.vertical = 'S';
        return 0;
    }
}


void ControlPlayer(PLAYER *p1, const MAP *environment) {
    const float MOVE_POSITIVE = 2.0, MOVE_NEGATIVE = -2.0;

    if ((IsKeyPressed(KEY_D) || IsKeyDown(KEY_D)) && p1->position.x < LIMIT_FINAL_X) {//Move o player para a direita
        p1->direction.horizontal = 'W';
        ModifierPositionPlayer(p1, environment, MOVE_POSITIVE, 0);
    }

    if ((IsKeyPressed(KEY_A) || IsKeyDown(KEY_A)) && p1->position.x > LIMIT_INITIAL_X) {//Move o player para a esquerda
        p1->direction.horizontal = 'E';
        ModifierPositionPlayer(p1, environment, MOVE_NEGATIVE, 0);
    }

    if ((IsKeyPressed(KEY_W) || IsKeyDown(KEY_W)) && p1->position.y > LIMIT_INITIAL_Y) {//Move o player para cima
        p1->direction.vertical = 'N';
        ModifierPositionPlayer(p1, environment, 0, MOVE_NEGATIVE);
    }
    if ((IsKeyPressed(KEY_S) || IsKeyDown(KEY_S)) && p1->position.y < LIMIT_FINAL_Y) {//Move o player para baixo
        p1->direction.vertical = 'S';
        ModifierPositionPlayer(p1, environment, 0, MOVE_POSITIVE);
    }
} //END PlayerControl(...);.............................................................................................


void ModifierPositionPlayer(PLAYER *p1, const MAP *environment, int move_x, int move_y) {
    p1->position.x += move_x;
    p1->position.y += move_y;

    bool verify_x_init = p1->position.x < LIMIT_INITIAL_X;
    bool verify_x_final = p1->position.x > LIMIT_FINAL_X;
    bool verify_y_init = p1->position.y < LIMIT_INITIAL_Y;
    bool verify_y_final = p1->position.y > LIMIT_FINAL_Y;

    if (WallCollisionPlayer(p1, environment) || verify_x_init || verify_x_final || verify_y_init || verify_y_final) {
        p1->position.x -= move_x;
        p1->position.y -= move_y;
    }
} //END ModifierPositionPlayer(...);....................................................................................


bool WallCollisionPlayer(const PLAYER *p1, const MAP *environment) {
    //Verifica se a posição atual do player colide com a posição da parede.

    for (int i = 0; i < environment->count_obstacle; i++) {
        if (CheckCollisionRecs(p1->position, environment->collision_map[i])) {
            return true;
        }
    }
    return false;
} //END DrawnPLayer(...);...............................................................................................


void GetItensPlayer(MAP *environment, PLAYER *p1) {
    if (!p1->weapon) {
        if (CheckCollisionRecs(p1->position, environment->sword_position)) {
            p1->weapon = true;
        }
    }

    if (environment->count_hearts >= 0) {
        for (int i = 0; i < environment->count_hearts; i++) {
            if (CheckCollisionRecs(p1->position, environment->hearts_list[i])) {
                if (p1->status.pv < p1->status.pv_max) p1->status.pv++;

                OrganizerListHeartsMap(environment, i);
                break;
            }
        }
    }
} //END GetItensPlayer(...);............................................................................................


void CallAttackPlayer(PLAYER *p1, MAP *environment) {
    /*Inicializa 9 Rectangles, 8 direções, 2 verticais, 2 horizontais e 4 diagonais e por último o mouse, e posiciona esses
     Retângulos ao, Norte, Sul, Oeste, Leste, Nordeste, Sudeste, Noroeste, Sudoeste respectivamente, ao efetuar a achar de
     pressionar o botão do mouse e feita uma comparação até achar a colisão do mouse com algum dos retângulos pela tela
     executando assim uma de 8 possíveis ações. */

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && p1->weapon) {
        int mouse_x = GetMouseX(), mouse_y = GetMouseY();

        Rectangle mouse = {mouse_x, mouse_y, 1, 1};

        Rectangle north = {p1->position.x - 30, p1->position.y - 810, 110, 810}; //Vertical, acima do jogador
        Rectangle south = {p1->position.x - 30, p1->position.y, 110, 810}; //Vertical, abaixo do jogador

        //Zonas Norte e sul.
        if (CheckCollisionRecs(mouse, north)) {
            PlayerAttack(p1, 0, environment);
            return;
        } else if (CheckCollisionRecs(mouse, south)) {
            PlayerAttack(p1, 1, environment);
            return;
        }
        Rectangle east = {p1->position.x + 50, p1->position.y - 75, 1200, 250}; //Horizontal, á direita do jogador
        Rectangle west = {p1->position.x - 1200, p1->position.y - 100, 1225, 250};

        //Zonas horizontais Leste e Oeste.
        if (CheckCollisionRecs(mouse, east)) {
            PlayerAttack(p1, 2, environment);
            return;
        } else if (CheckCollisionRecs(mouse, west)) {
            PlayerAttack(p1, 3, environment);
            return;
        }
        Rectangle Northeast = {p1->position.x + 50, p1->position.y - 800, 1200, 800};
        Rectangle Southeast = {p1->position.x + 50, p1->position.y + 50, 1200, 800};

        //Zonas diagonais nordeste e sudeste.
        if (CheckCollisionRecs(mouse, Northeast)) {
            PlayerAttack(p1, 4, environment);
            return;
        } else if (CheckCollisionRecs(mouse, Southeast)) {
            PlayerAttack(p1, 5, environment);
            return;
        }
        Rectangle Northwest = {p1->position.x - 1225, p1->position.y - 800, 1225, 800};
        Rectangle Southwest = {p1->position.x - 1225, p1->position.y + 50, 1225, 800};

        //Zonas diagonais Noroeste e Sudoeste.
        if (CheckCollisionRecs(mouse, Northwest)) {
            PlayerAttack(p1, 6, environment);
            return;
        } else if (CheckCollisionRecs(mouse, Southwest)) {
            PlayerAttack(p1, 7, environment);
            return;
        }
        /*Nota: Vendo a disposição oferecida pelos if's e else's, pode se idealizar uma função com o minimo de 4
         *triângulos, apenas alterando a sua forma para da if, mantendo a funcionalidade e reduzindo a alocação
         *de mémoria que, é usada nos triângulos inutilizados dos if externos*/
    }
} //END CallAttackPlayer(...);..........................................................................................


void PlayerAttack(PLAYER *p1, int direction, MAP *environment) {
    /*Essa função e feita para receber uma das direções presentes em "MousePositionForPlayerAttack(PLAYER *p1, MAP *environment)"
     *e com base nisso mudar o formato de dois rectangles e verificar a colisão dos mesmo com a lista de monstros, decrementando
     *1 da vida, deles caso haja*/

    switch (direction) {
        case 0: //Norte
            p1->hit_areaA = (Rectangle){p1->position.x, p1->position.y - 150, 50, 150};
            p1->hit_areaB = p1->hit_areaA;

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                DrawRectangle(p1->position.x, p1->position.y - 150, 50, 150, GOLD);
            }

            CollisionAttackPlayer(p1, p1->hit_areaA, p1->hit_areaB, environment);
            break;

        case 1: //Sul
            p1->hit_areaA = (Rectangle){p1->position.x, p1->position.y + 50, 50, 150};
            p1->hit_areaB = p1->hit_areaA;

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                DrawRectangle(p1->position.x, p1->position.y + 50, 50, 150, GOLD);
            }

            CollisionAttackPlayer(p1, p1->hit_areaA, p1->hit_areaB, environment);
            break;

        case 2: //Leste
            p1->hit_areaA = (Rectangle){p1->position.x + 50, p1->position.y, 150, 50};
            p1->hit_areaB = p1->hit_areaA;

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                DrawRectangle(p1->position.x + 50, p1->position.y, 150, 50, GOLD);
            }
            CollisionAttackPlayer(p1, p1->hit_areaA, p1->hit_areaB, environment);
            break;

        case 3: //Oeste
            p1->hit_areaA = (Rectangle){p1->position.x - 150, p1->position.y, 150, 50};
            p1->hit_areaB = p1->hit_areaA;

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                DrawRectangle(p1->position.x - 150, p1->position.y, 150, 50, GOLD);
            }
            CollisionAttackPlayer(p1, p1->hit_areaA, p1->hit_areaB, environment);
            break;

        case 4: //Nordeste
            p1->hit_areaA = (Rectangle){p1->position.x + 50, p1->position.y - 50, 50, 50};
            p1->hit_areaB = (Rectangle){p1->position.x + 100, p1->position.y - 100, 50, 50};

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                DrawRectangle(p1->hit_areaA.x, p1->hit_areaA.y, p1->hit_areaA.width, p1->hit_areaB.height, GOLD);
                DrawRectangle(p1->hit_areaB.x, p1->hit_areaB.y, p1->hit_areaB.width, p1->hit_areaB.height, GOLD);
            }
            CollisionAttackPlayer(p1, p1->hit_areaA, p1->hit_areaB, environment);
            break;

        case 5: //Sudeste
            p1->hit_areaA = (Rectangle){p1->position.x + 50, p1->position.y + 50, 50, 50};
            p1->hit_areaB = (Rectangle){p1->position.x + 100, p1->position.y + 100, 50, 50};

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                DrawRectangle(p1->hit_areaA.x, p1->hit_areaA.y, p1->hit_areaA.width, p1->hit_areaB.height, GOLD);
                DrawRectangle(p1->hit_areaB.x, p1->hit_areaB.y, p1->hit_areaB.width, p1->hit_areaB.height, GOLD);
            }
            CollisionAttackPlayer(p1, p1->hit_areaA, p1->hit_areaB, environment);
            break;

        case 6: //Noroeste
            p1->hit_areaA = (Rectangle){p1->position.x - 50, p1->position.y - 50, 50, 50};
            p1->hit_areaB = (Rectangle){p1->position.x - 100, p1->position.y - 100, 50, 50};

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                DrawRectangle(p1->hit_areaA.x, p1->hit_areaA.y, p1->hit_areaA.width, p1->hit_areaB.height, GOLD);
                DrawRectangle(p1->hit_areaB.x, p1->hit_areaB.y, p1->hit_areaB.width, p1->hit_areaB.height, GOLD);
            }
            CollisionAttackPlayer(p1, p1->hit_areaA, p1->hit_areaB, environment);
            break;

        case 7: //Sudoeste
            p1->hit_areaA = (Rectangle){p1->position.x - 50, p1->position.y + 50, 50, 50};
            p1->hit_areaB = (Rectangle){p1->position.x - 100, p1->position.y + 100, 50, 50};

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                DrawRectangle(p1->hit_areaA.x, p1->hit_areaA.y, p1->hit_areaA.width, p1->hit_areaB.height, GOLD);
                DrawRectangle(p1->hit_areaB.x, p1->hit_areaB.y, p1->hit_areaB.width, p1->hit_areaB.height, GOLD);
            }
            CollisionAttackPlayer(p1, p1->hit_areaA, p1->hit_areaB, environment);
            break;
        default:
            return;
    }
} //END PlayerAttack(...);..............................................................................................


void CollisionAttackPlayer(PLAYER *p1, Rectangle object_a, Rectangle object_b, MAP *environment) {
    for (int i = 0; i < environment->count_monster; i++) {
        if (CheckCollisionRecs(object_a, environment->monster_list[i].position) || CheckCollisionRecs(
                object_b, environment->monster_list[i].position)) {
            p1->status.score += environment->monster_list[i].score;
            environment->monster_list[i].pv--;
            break;
        }
    }
} //END CollisionAttackPlayer(...);.....................................................................................


void KnockBackPlayer(PLAYER *p1, const MAP *environment) {
    for (int i = 0; i < environment->count_monster; i++) {
        if (CheckCollisionRecs(p1->position, environment->monster_list[i].position)) {
            if (p1->invincibility_time == 0) {
                p1->status.pv -= 1;
                p1->invincibility_time = 90;
            }

            const float MOVE = 10;

            float dx = p1->position.x - environment->monster_list[i].position.x;
            float dy = p1->position.y - environment->monster_list[i].position.y;

            float euclidean_distance = sqrtf(dx * dx + dy * dy);

            dx /= euclidean_distance;
            dy /= euclidean_distance;

            int move_x = lroundf((dx * MOVE));
            int move_y = lroundf((dy * MOVE));

            // p1->position.x += dx * MOVE;
            //p1->position.y += dy * MOVE;
            ModifierPositionPlayer(p1, environment, move_x, move_y);
        }
    }
} //END KnockBackPlayer(...);...........................................................................................

void UpdateInvincibilityTime(PLAYER *p1) {
    if (p1->invincibility_time > 0) {
        p1->invincibility_time -= 1;
    } else if (p1->invincibility_time < 0) {
        p1->invincibility_time = 0;
    }
}

void UpdateLevelStatus(PLAYER *p1) {
    if (p1->status.lv < p1->status.lv_max) {
        p1->status.lv = (p1->status.score / 250);
        p1->status.pv_max = (3 + p1->status.lv);
    }
}

void GameOverPlayer(PLAYER *p1) {
    if (p1->status.pv <= 0) {
    }
}
