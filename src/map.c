#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../headers/type.h"
#include "../headers/core.h"
#define MAX_LINE (COLUMNS + 2)

#include <string.h>


int RenameMap(CONTROL *org) {
    //Renomeia o nome do arquivo mapa.txt atual para o seguinte.

    if (org->count_map < 1) //Garante que nenhum mapa fora do escopo seja chamado [1 - 99].
        org->count_map = 1;

    if (org->count_map > 0 && org->count_map < 10) {
        //Renomeia o arquivo para casos em que o contador esteja no intervalo de [01 - 09].
        sprintf(org->map_name, "../maps/mapa0%d.txt", org->count_map);
        return 0;
    } else if (org->count_map > 9 && org->count_map <= 99) {
        //Renomeia o arquivo para casos em que o contador esteja no intervalo de [10 - 99]
        sprintf(org->map_name, "../maps/mapa%d.txt", org->count_map);
        return 0;
    }

    return 1;
} //END RenameMap(..);..................................................................................................


int ReadMap(MAP *environment, CONTROL *org, PLAYER *p1) {
/*Le o arquivo que contem a matriz do mapa e caso, haja caracateres a mais na linha, estes são ignorados, não afetando os salvamento dos demais
Caso falte caracateres na linha, os espaços vagos são prenchedos com o caracter de ' ', afim de manter a estrutura do mapa.
*/

    FILE *arq = fopen(org->map_name, "r");
    if (!arq) return 1;

    environment->count_obstacle = 0;
    environment->count_monster  = 0;
    environment->count_hearts   = 0;

    char line[MAX_LINE];
    for (int i = 0; i < LINES; i++) {
        if (!fgets(line, sizeof line, arq)) {

            for (int j = 0; j < COLUMNS; j++)
                environment->phase_map[i][j] = ' ';
            continue;
        }

        // Garante que a linha termina com '\n'
        size_t len = strlen(line);
        if (len && line[len - 1] != '\n' && len == sizeof line - 1) {
            int c;
            while ((c = getc(arq)) != '\n' && c != EOF) {}
        }

        for (int j = 0; j < COLUMNS; j++) {
            char ch = (j < len && line[j] != '\n') ? line[j] : ' ';
            environment->phase_map[i][j] = ch;
            switch (ch) {
                case 'J': case 'E': case 'V': case 'P': case 'M':
                    SetupObjectMap(environment, p1, ch, i, j);
                break;
                default:
                    break;
            }
        }
    }
    fclose(arq);
    return 0;
} //END ReadMap(...);...................................................................................................


int SetupObjectMap(MAP *environment, PLAYER *p1, char character, int i, int j) {
    /*Acessa as propriedades das structs MAP e Player, e com base nos argumentos lidos na função ReadMap, utiliza seus
     *indices para calcular a posição e contabilizar a quantidade de objetos estáticos e dinâmicos no mapa do jogo.*/

    float x = j * TILE_SIZE;
    float y = i * TILE_SIZE + STATUS_BAR_DISTANCE;

    Rectangle map_layout_Objects = {x, y, TILE_SIZE, TILE_SIZE,};

    switch (character) {
        case 'J': //Inicializa a posição do jogador no mapa.

            p1->position = map_layout_Objects;
            return 0;

        case 'E': //Inicializa a espada do jogador na posição indicada no mapa.

            environment->sword_position = map_layout_Objects;
            return 0;

        case 'V': //Inicializa a lista de vidas na posição indicada no mapa.

            environment->hearts_list[environment->count_hearts] = map_layout_Objects;

            environment->hearts_list[environment->count_hearts].x,
                    environment->hearts_list[environment->count_hearts].y;

            environment->count_hearts++;
            return 0;

        case 'P':

            environment->collision_map[environment->count_obstacle] = map_layout_Objects;
            environment->count_obstacle++;
            return 0;

        case 'M': //Inicializa a lista de monstros na posição indicada no mapa.

            environment->monster_list[environment->count_monster] = (MONSTER) {
                1,((rand() % 100) + 1),map_layout_Objects, {'L', 'S'}
            };

            environment->count_monster++;

            return 0;

        default:
            return 1;
    }
} //END SetupObjectMap(...);............................................................................................


void DrawGameMap(const MAP *environment) {
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            int x = j * TILE_SIZE, y = i * TILE_SIZE + STATUS_BAR_DISTANCE;

            if (environment->phase_map[i][j] == 'P') {
                if ((i + 1) < 16 && environment->phase_map[i + 1][j] == 'P') {
                    DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, DARKGRAY);
                } else {
                    DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, GRAY);
                }
            } else {
                DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, LIME);
            }
        }
    }
} //END DrawGameMap(...);...............................................................................................


void DrawObjectMap(const MAP *environment, const PLAYER *p1) {
    if (!p1->weapon) {
        DrawRectangle(environment->sword_position.x, environment->sword_position.y, TILE_SIZE, TILE_SIZE, RED);
    }

    for (int i = 0; i < environment->count_hearts; i++) {
        DrawRectangle(environment->hearts_list[i].x, environment->hearts_list[i].y, TILE_SIZE, TILE_SIZE, PINK);
    }
} //END DrawObjectMap(...);.............................................................................................


void OrganizerListHeartsMap(MAP *environment, int init) {
    for (int i = init; i < environment->count_hearts - 1; i++) {
        Rectangle aux = environment->hearts_list[i + 1];
        environment->hearts_list[i] = aux;
    }

    environment->count_hearts--;
} //END OrganizerListHeartsPlayer(...);.................................................................................


void UpdateMap(MAP *environment, CONTROL *org, PLAYER *p1) {

    //Caso o contador de monstros seja menor o igual a zero, incrementa o em +1, renomaia o mapa e chama o arquivo, caso existe ele e carregado e o jogo continua
    //Caso não exista arquivo a função de Fim de Jogo e Chamada.
    if (environment->count_monster <= 0) {

        *environment = (MAP){0};
        ClearMap( environment, org,  p1);

        org->count_map++;
        p1->weapon = false;
        p1->position = (Rectangle){0};

        RenameMap(org);

        int result = ReadMap(environment, org, p1);

        if (result != 0) {
            SCORE finalist = {0};
            EndGameCore(*p1, finalist);
        }
    }
} //END UpdateMap(...);.................................................................................................

void ClearMap(MAP *environment, CONTROL *org, PLAYER *p1) {
    //Limpa os valores de campos referentes a dados do mapa atual para que novos dados possam ser escritos.

    p1->weapon = false;
    p1->position = (Rectangle){0};

    //Limpa todos os contadores com exceção de [count_map].
    environment->count_hearts = 0;
    environment->count_monster = 0;
    environment->count_obstacle = 0;


    //Limpa todos os vetores e matrizes.
    memset(environment->phase_map, 0, sizeof environment->phase_map);
    memset(environment->hearts_list, 0, sizeof environment->hearts_list);
    memset(environment->monster_list, 0, sizeof environment->monster_list);
    memset(environment->collision_map, 0, sizeof environment->collision_map);
} //END ClearMap(...);..................................................................................................
