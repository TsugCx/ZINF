#include <stdio.h>

#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include "../headers/type.h"

void DrawnMonsters(const MAP *environment, Texture2D zombie) {
    for (int i = 0; i < environment->count_monster; i++) {

        int frame = SpriteFrameMonsters(environment, i);
        Rectangle image_area = {frame * 50, 0, 50, 50};
        Vector2 image_pos = {environment->monster_list[i].position.x, environment->monster_list[i].position.y};
        DrawTextureRec(zombie, image_area, image_pos, WHITE);

    }
} //END DrawnMonsters(...);.............................................................................................


int SpriteFrameMonsters(MAP *environment, const int index) {
    if (environment->monster_list[index].direction.horizontal == 'W' && environment->monster_list[index].direction.vertical == 'S') {
        return 0;
    } else if (environment->monster_list[index].direction.horizontal == 'W' && environment->monster_list[index].direction.vertical == 'N') {
        return 1;
    } else if (environment->monster_list[index].direction.horizontal == 'E' && environment->monster_list[index].direction.vertical == 'S') {
        return 2;
    } else if (environment->monster_list[index].direction.horizontal == 'E' && environment->monster_list[index].direction.vertical == 'N') {
        return 3;
    } else {
        environment->monster_list[index].direction.horizontal = 'W';
        environment->monster_list[index].direction.vertical = 'S';
        return 0;
    }
} //END SpriteFrameMonsters(...);.......................................................................................


void RandomMovementGeneratorForMonsters(MAP *environment) {
    srand((time(NULL)));
    for (int i = 0; i < environment->count_monster; i++) {
        int move_or_wait = rand() % 2;

        if (move_or_wait == 0) {
            int randomNumber = rand() % 4;

            MovementMonsters(environment, randomNumber, i);
        }
    }
} //END RandomMovementGeneratorForMonsters(...);........................................................................


void MovementMonsters(MAP *environment, int randomNumber, int i) {
    const int MOVE_POSITIVE = 1, MOVE_NEGATIVE = -1;
    if (randomNumber == 0 && environment->monster_list[i].position.x < LIMIT_FINAL_X) {
        environment->monster_list[i].direction.horizontal = 'W';
        ModifierPositionMonster(environment, MOVE_POSITIVE, 0, i);
    }
    if (randomNumber == 1 && environment->monster_list[i].position.x > LIMIT_INITIAL_X) {
        environment->monster_list[i].direction.horizontal = 'E';
        ModifierPositionMonster(environment, MOVE_NEGATIVE, 0, i);
    }
    if (randomNumber == 2 && environment->monster_list[i].position.y > LIMIT_INITIAL_Y) {
        environment->monster_list[i].direction.vertical = 'N';
        ModifierPositionMonster(environment, 0, MOVE_POSITIVE, i);
    }
    if (randomNumber == 3 && environment->monster_list[i].position.y < LIMIT_FINAL_Y) {
        environment->monster_list[i].direction.vertical = 'S';
        ModifierPositionMonster(environment, 0, MOVE_NEGATIVE, i);
    }
} //END MovementMonsters(...);..........................................................................................


void ModifierPositionMonster(MAP *environment, int move_x, int move_y, int index) {
    environment->monster_list[index].position.x += move_x;
    environment->monster_list[index].position.y -= move_y;

    if (WallCollisionMonster(environment, index) || MonsterXMonsterCollision(environment, index)) {
        environment->monster_list[index].position.x -= move_x;
        environment->monster_list[index].position.y += move_y;
    }
} //END ModifierPositionMonster(...);...................................................................................


bool WallCollisionMonster(const MAP *environment, int index) {
    //Verifica se a posição atual do player colide com a posição da parede.

    for (int i = 0; i < environment->count_obstacle; i++) {

        if (CheckCollisionRecs(environment->monster_list[index].position, environment->collision_map[i])) {
            return true;
        }
    }
    return false;
} //END WallCollisionMonster(...);......................................................................................


bool MonsterXMonsterCollision(const MAP *environment, int index) {
    //Verifica se a posição atual do hit-box coincide com uma hit-box de parede interando no array que armazena as paredes para colisão.

    for (int i = 0; i < environment->count_obstacle; i++) {
        if (i == index) {
            continue;
        } else if (CheckCollisionRecs(environment->monster_list[index].position, environment->monster_list[i].position)) {
            return true;
        }
    }
    return false;
} //END MonsterXMonsterCollision(...);..................................................................................

void CheckDeathMonster(MAP *environment) {

    for (int i = 0; i < environment->count_monster; i++) {
        if (environment->monster_list[i].pv <= 0) {
            OrganizerListMonster(environment, i);
            break;
        }
    }
}

void OrganizerListMonster(MAP *environment, int index) {

    for (int i = index; i < environment->count_monster - 1; i++) {
        MONSTER aux = environment->monster_list[i + 1];
        environment->monster_list[i] = aux;
    }

    environment->count_monster--;

}