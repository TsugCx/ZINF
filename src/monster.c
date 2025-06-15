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

void RandomMovementGeneratorForMonsters(MAP *environment);
