#ifndef TYPE_H
#define TYPE_H

#include "raylib.h"
#include <stdint.h>
#include <stdbool.h>

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

typedef struct monster {

    char type;
    int8_t hit_count;
    POSITION x_y;
    Rectangle hitbox;

} MONSTER;


typedef struct map {

    int8_t count_map, count_obstacle, count_monster;
    char map_name[18];
    char phase_map[16][24];
    Rectangle collision_map[16 * 24];

    MONSTER Monster_list_on_the_map[10];

} MAP;

void RenameMap(MAP *environment);//Atualiza o nome atual do arquivo do mapa a ser chamado para execução no jogo.
void ReadMap(MAP *environment);//Com base no nome do arquivo, busca um arquivo .txt correspondente nos diretorios e salva seus dados na matriz phase_map.
void DrawMap(MAP *environment);//Desenha o mapa passado pela matriz utilizando os assets correspondes aos caracteres atrelados as posições [i][j].

void GlobalInit(MAP *environment);
void DrawMenu();
void DrawGameBar();


void PlayerControl(PLAYER *p1, MAP *environment);

void MousePositionForPlayerAttack(PLAYER *p1);

void InitMonster(int8_t tile_size, int8_t i, int8_t j, MAP *environment);
void RandomMovementGeneratorForMonsters(MAP *environment);




#endif //TYPE_H
