#include "../headers/map.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void InitMonster(int8_t tile_size, int8_t i, int8_t j, MAP *environment) {
    environment->monster_list[environment->count_monster].type = 'M';
    environment->monster_list[environment->count_monster].hit_count = 0;

    environment->monster_list[environment->count_monster].position.orientation = 'N';
    environment->monster_list[environment->count_monster].position.x = i * tile_size;
    environment->monster_list[environment->count_monster].position.y = 60 + j * tile_size;

    environment->monster_list[environment->count_monster].hitbox = (Rectangle) {i * tile_size, 60 + i * tile_size, tile_size, tile_size};

}


// #MON3$: Função internar de subnivel 2,
bool MonsterWallCollision(MAP *environment, int8_t monster_index) {
    //Verifica se a posição atual da hitbox coincide com uma hitbox de parede interando no array que armazena as paredes para colisão.

    for (int16_t i = 0; i < environment->count_obstacle; i++) {
        if (CheckCollisionRecs(environment->monster_list[monster_index].hitbox, environment->collision_map[i])) {
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
        } else if (CheckCollisionRecs(environment->monster_list[monster_index].hitbox, environment->monster_list[i].hitbox)) {
            return true;
        }
    }
    return false;
}

void MonsterPositionModifierAndHitboxInX(MAP *environment, int8_t MOVE, int8_t i) {
    //Recebe um valor positvo ou negativo e atualiza a posição do jogador e de sua hitbox em X.

    environment->monster_list[i].position.x += MOVE;
    environment->monster_list[i].hitbox.x = environment->monster_list[i].position.x;

    if (MonsterWallCollision(environment, i) || MonsterXMonsterCollision(environment, i)) {
        environment->monster_list[i].position.x -= MOVE;
        environment->monster_list[i].hitbox.x = environment->monster_list[i].position.x;
    }
}

// #MON2B: Função interna de subnivel 1,
void MonsterPositionModifierAndHitboxInY(MAP *environment, int8_t MOVE, int8_t i) {
    //Recebe um valor positvo ou negativo e atualiza a posição do jogador e de sua hitbox em Y.

    environment->monster_list[i].position.y -= MOVE;
    environment->monster_list[i].hitbox.y = environment->monster_list[i].position.y;

    if (MonsterWallCollision(environment, i) || MonsterXMonsterCollision(environment, i)) {
        environment->monster_list[i].position.y += MOVE;
        environment->monster_list[i].hitbox.y = environment->monster_list[i].position.y;
    }
}

void MovementMonsters(MAP *environment, int8_t randomNumber, int8_t i) {
    const int8_t MOVE_POSITIVE = 1, MOVE_NEGATIVE = -1;

        if (randomNumber == 0 && environment->monster_list[i].position.x < 1150)
            MonsterPositionModifierAndHitboxInX(environment, MOVE_POSITIVE, i);

        if (randomNumber == 1 && environment->monster_list[i].position.x > 0)
            MonsterPositionModifierAndHitboxInX(environment, MOVE_NEGATIVE, i);

        if (randomNumber == 2 && environment->monster_list[i].position.y > 60)
            MonsterPositionModifierAndHitboxInY(environment, MOVE_POSITIVE, i);

        if (randomNumber == 3 && environment->monster_list[i].position.y < 810)
            MonsterPositionModifierAndHitboxInY(environment, MOVE_NEGATIVE, i);
}

void RandomMovementGeneratorForMonsters(MAP *environment) {

    srand(time(NULL));

    for (int8_t i = 0; i < environment->count_monster; i++) {

        int move_or_wait = rand() % 2;

        if (move_or_wait == 0) {
            int randomNumber = rand() % 4;

            MovementMonsters(environment, randomNumber, i);
        } else {}

        DrawRectangle(environment->monster_list[i].position.x, environment->monster_list[i].position.y, 50, 50, PURPLE);

    }
}
