#include "../headers/map.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//INICIO: Grupo de funções que controlam as chamadas de mapa, sua leitura e desenho na tela.
void RenameMap(MAP *environment) {//Subfunção de ReadMap();

    if (environment->count_map < 1)//Garante que nenhum mapa fora do escopo seja chamado [1 - 99]
        environment->count_map = 1;

    if (environment->count_map < 10 && environment->count_map > 0) {//Renomeia o arquivo para casos em que o contador esteja no intervalo de [1 - 9]
        sprintf(environment->map_name, "../maps/mapa0%d.txt", environment->count_map);

    } else if (environment->count_map > 9 && environment->count_map <= 99) {//Renomeia o arquivo para casos em que o contador esteja no intervalo de [10 - 99]
        sprintf(environment->map_name, "../maps/mapa%d.txt", environment->count_map);
    }

}

void ReadMap(MAP *environment) {
    FILE *arq = fopen(environment->map_name, "r");

    if (arq != NULL) {

        int caractere;
        for(int8_t i = 0; i < 16; i++)
            for (int8_t j = 0; j < 24; j++) {

                caractere = getc(arq);

                environment->phase_map[i][j] = caractere;

                while (j == 23 && (caractere != '\n' && caractere != EOF)) {
                    caractere = getc(arq);
                }
            }
    }
    fclose(arq);
}

void GlobalInit(MAP *environment) {



}

void DrawMap(MAP *environment) {

    const int8_t lines = 16, columns = 24, tile_size = 50;
    environment->count_obstacle = 0;

    for (int8_t i = 0; i <  columns; i++)
        for (int8_t j = 0; j < lines; j++) {

            switch (environment->phase_map[j][i]) {
                case '\n':
                    environment->phase_map[j][i] = ' ';
                break;


                case 'P':
                    environment->collision_map[environment->count_obstacle] = (Rectangle){i * tile_size, 60 + j * tile_size, tile_size, tile_size};
                    environment->count_obstacle++;

                    if (j < columns && environment->phase_map[j + 1][i] == 'P') {
                        DrawRectangle(0 + tile_size * i, 60 + tile_size * j, tile_size, tile_size, DARKGRAY);

                    } else {
                        DrawRectangle(0 + tile_size * i, 60 + tile_size * j, tile_size, tile_size, GRAY);
                    }
                break;

                case 'M':
                    InitMonster(tile_size, i, j, environment);
                    environment->count_monster++;
                    environment->phase_map[j][i] = ' ';

                case ' ':
                    DrawRectangle(0 + tile_size * i, 60 + tile_size * j, tile_size, tile_size, DARKGREEN);
                break;

                case 'V':
                    DrawRectangle(0 + 50 * i, 60 + 50 * j, 50, 50, PINK);
                    break;

                default:
                    DrawRectangle(0 + tile_size * i, 60 + tile_size * j, tile_size, tile_size, DARKGREEN);
                break;
            }
        }

}
//FIM.



void DrawGameBar(){

    DrawRectangle(0, 0, 1200, 60, BLACK);
    DrawText("FINN",10, 20, 32, WHITE);
    DrawText("PV",230, 30, 16, WHITE);
    DrawRectangle(260, 30, 140, 16, DARKBLUE);
    DrawRectangle(260, 30, 140, 16, BLUE);

}