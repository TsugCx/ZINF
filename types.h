//
// Created by gutsa on 05/06/2025.
//

#ifndef TYPE_H
#define TYPE_H

//Lista de bibliotecas utilizadas.
#include "raylib.h"
#include <stdint.h>
#include <stdbool.h>


//Define a posição dos objetos no mapa, o nivel atual e a chamada de menu
typedef struct global {

    char map_call[24][16];
    int8_t map_count;
    bool menu_call;

} GLOBAL;

void GlobalInit(GLOBAL *environment);
void DrawMenu();
void DrawGameBar();

typedef struct position {

    float px, py;
    char orientation;

} POSITION;

//Define todas as propriedades do jogador, e suas funções para alteração.
typedef struct player {

    int8_t pv, pv_Max;
    bool weapon;
    POSITION xy;
    Rectangle hitbox;


} PLAYER;

void PlayerControl(PLAYER *p1);

void MousePositionForPlayerAttack(PLAYER *p1);


typedef struct monster {

    uint8_t type;
    int16_t px, py, pv;
    char orientation;


    Rectangle hitbox;

} MONSTER;




#endif //TYPE_H
