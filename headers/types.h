#ifndef TYPE_H
#define TYPE_H

#include "../cmake-build-debug/_deps/raylib-src/src/raylib.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct global {

    int8_t count_map;
    char map_name[18];
    char phase_map[16][24];

} GLOBAL;

void RenameMap(GLOBAL *environment);//Atualiza o nome atual do arquivo do mapa a ser chamado para execução no jogo.
void ReadMap(GLOBAL *environment);//Com base no nome do arquivo, busca um arquivo .txt correspondente nos diretorios e salva seus dados na matriz phase_map
void DrawMap(GLOBAL *environment);

void GlobalInit(GLOBAL *environment);
void DrawMenu();
void DrawGameBar();

typedef struct position {

    int16_t position_x, position_y;
    char orientation;

} POSITION;

//Define todas as propriedades do jogador, e suas funções para alteração.
typedef struct player {

    int8_t pv, pv_Max;
    bool weapon;
    POSITION x_y;
    Rectangle hitbox;

} PLAYER;

void PlayerControl(PLAYER *p1);

void MousePositionForPlayerAttack(PLAYER *p1);


typedef struct monster {

    char type;
    int8_t hit_count;
    int16_t px, py;
    char orientation;
    Rectangle hitbox;

} MONSTER;




#endif //TYPE_H
