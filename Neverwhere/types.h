#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

//Lista de bibliotecas utilizadas.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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



//Define todas as propriedades do jogador, e suas funções para alteração.
typedef struct player {

    int8_t pv, pv_Max;
    int16_t px, py, score;
    bool weapon;
    char orientation;

} PLAYER;

void PlayerControl(PLAYER *p1);




typedef struct monster {

    uint8_t type;
    int16_t px, py, pv;
    char orientation;


    Rectangle hitbox;

} MONSTER;



#endif // TYPES_H_INCLUDED
