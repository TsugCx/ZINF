#include "../headers/map.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void InitMonster(int8_t tile_size, int8_t i, int8_t j, MAP *environment) {
    environment->Monster_list_on_the_map[environment->count_monster].type = 'M';
    environment->Monster_list_on_the_map[environment->count_monster].hit_count = 0;

    environment->Monster_list_on_the_map[environment->count_monster].x_y.orientation = 'N';
    environment->Monster_list_on_the_map[environment->count_monster].x_y.position_x = i * tile_size;
    environment->Monster_list_on_the_map[environment->count_monster].x_y.position_y = 60 + j * tile_size;

    environment->Monster_list_on_the_map[environment->count_monster].hitbox.x = i * tile_size;
    environment->Monster_list_on_the_map[environment->count_monster].hitbox.y = 60 + i * tile_size;
    environment->Monster_list_on_the_map[environment->count_monster].hitbox.height = tile_size;
    environment->Monster_list_on_the_map[environment->count_monster].hitbox.width = tile_size;
}


// #MON3$: Função internar de subnivel 2,
bool MonsterWallCollision(MAP *environment, int8_t monster_index) {
    //Verifica se a posição atual da hitbox coincide com uma hitbox de parede interando no array que armazena as paredes para colisão.

    for (int16_t i = 0; i < environment->count_obstacle; i++) {
        if (CheckCollisionRecs(environment->Monster_list_on_the_map[monster_index].hitbox, environment->collision_map[i])) {
            return true;
        }
    }
    return false;
}

bool MonsterXMonsterCollision(MAP *environment, int8_t monster_index) {
    //Verifica se a posição atual da hitbox coincide com uma hitbox de parede interando no array que armazena as paredes para colisão.

    for (int16_t i = 0; i < environment->count_obstacle; i++) {
        if (i == monster_index) {
            continue;
        } else if (CheckCollisionRecs(environment->Monster_list_on_the_map[monster_index].hitbox, environment->Monster_list_on_the_map[i].hitbox)) {
            return true;
        }
    }
    return false;
}

void MonsterPositionModifierAndHitboxInX(MAP *environment, int8_t MOVE, int8_t i) {
    //Recebe um valor positvo ou negativo e atualiza a posição do jogador e de sua hitbox em X.

    environment->Monster_list_on_the_map[i].x_y.position_x += MOVE;
    environment->Monster_list_on_the_map[i].hitbox.x = environment->Monster_list_on_the_map[i].x_y.position_x;

    if (MonsterWallCollision(environment, i) || MonsterXMonsterCollision(environment, i)) {
        environment->Monster_list_on_the_map[i].x_y.position_x -= MOVE;
        environment->Monster_list_on_the_map[i].hitbox.x = environment->Monster_list_on_the_map[i].x_y.position_x;
    }
}

// #MON2B: Função interna de subnivel 1,
void MonsterPositionModifierAndHitboxInY(MAP *environment, int8_t MOVE, int8_t i) {
    //Recebe um valor positvo ou negativo e atualiza a posição do jogador e de sua hitbox em Y.

    environment->Monster_list_on_the_map[i].x_y.position_y -= MOVE;
    environment->Monster_list_on_the_map[i].hitbox.y = environment->Monster_list_on_the_map[i].x_y.position_y;

    if (MonsterWallCollision(environment, i) || MonsterXMonsterCollision(environment, i)) {
        environment->Monster_list_on_the_map[i].x_y.position_y += MOVE;
        environment->Monster_list_on_the_map[i].hitbox.y = environment->Monster_list_on_the_map[i].x_y.position_y;
    }
}

void MovementMonsters(MAP *environment, int8_t randomNumber, int8_t i) {
    const int8_t MOVE_POSITIVE = 1, MOVE_NEGATIVE = -1;

        if (randomNumber == 0 && environment->Monster_list_on_the_map[i].x_y.position_x < 1150)
            MonsterPositionModifierAndHitboxInX(environment, MOVE_POSITIVE, i);

        if (randomNumber == 1 && environment->Monster_list_on_the_map[i].x_y.position_x > 0)
            MonsterPositionModifierAndHitboxInX(environment, MOVE_NEGATIVE, i);

        if (randomNumber == 2 && environment->Monster_list_on_the_map[i].x_y.position_y > 60)
            MonsterPositionModifierAndHitboxInY(environment, MOVE_POSITIVE, i);

        if (randomNumber == 3 && environment->Monster_list_on_the_map[i].x_y.position_y < 810)
            MonsterPositionModifierAndHitboxInY(environment, MOVE_NEGATIVE, i);
}

void RandomMovementGeneratorForMonsters(MAP *environment) {

    srand(time(NULL));

    for (int8_t i = 0; i < environment->count_monster; i++) {
        int move_or_wait = (int) 0 + ((float) rand() / RAND_MAX) * (1 - 0);

        if (move_or_wait == 0) {
            int randomNumber = rand() % 4;

            MovementMonsters(environment, randomNumber, i);
        } else {}

        DrawRectangle(environment->Monster_list_on_the_map[i].x_y.position_x, environment->Monster_list_on_the_map[i].x_y.position_y, 50, 50, PURPLE);

    }
}
