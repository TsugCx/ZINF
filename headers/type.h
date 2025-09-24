#ifndef TYPE_H
#define TYPE_H

#include "raylib.h"

#define MAXSCORES 5

#define LINES 16
#define COLUMNS 24
#define MONSTER_LIMIT 10
#define HEARTS_LIMIT 5
#define STRING_TAM 30

#define TILE_SIZE 50.0f
#define STATUS_BAR_DISTANCE 60.0f

#define LIMIT_INITIAL_X 0
#define LIMIT_FINAL_X 1200 - TILE_SIZE

#define LIMIT_INITIAL_Y 60
#define LIMIT_FINAL_Y 860 - TILE_SIZE

//######################################################################################################################
typedef struct score {
    char name[STRING_TAM];
    int score;
} SCORE;
//######################################################################################################################
typedef struct orientation {

    char vertical;
    char horizontal;

} ORIENTATION;
//######################################################################################################################


typedef struct status {

    int score;//............................... Representa a pontuação atual do jogador.
    int pv, pv_max;//.......................... Representam a vida atual do jogador e a vida máxima permitida, respectivamente.
    int lv, lv_max;//.......................... Representem o level atual do jogador e o level máximo permitido, respectivamente.

} STATUS;

typedef struct player {

    STATUS status;//........................... Representa as condições básicos do jogador que seão exibidos na barra.

    ORIENTATION direction;//........................ Representa a orientação atual do sprite do jogador in-game, podendo ser elas [N && E; N && W; S && E; S && W].
    Rectangle position;//...................... Representa a posição atual do jogador, bem como sua área de contato.
    Rectangle hit_areaA, hit_areaB;//.......... Representa as áreas mutáveis para verificar colisões de ataque do jogador contra monstros.

    bool weapon;//............................. Representa o estado do jogador sendo FALSE o estado em que não é possível realizar ataques e TRUE o oposto.
    int invincibility_time;//.................. Representa o tempo de invulnerabilidade do jogador após colidir com um monstro.

} PLAYER;

//######################################################################################################################

typedef struct monster {

    int pv;//.................................. Representa a vida atual do monstro.
    int score;//............................... Representa a pontuação a ser ganha ao eliminar o monstro
    Rectangle position;//...................... Representa a posição atual do monstro, bem como sua área de contato.
    ORIENTATION direction;//........................ Representa a orientação atual do sprite do jogador in-game, podendo ser elas [N && E; N && W; S && E; S && W].

} MONSTER;

//######################################################################################################################
typedef struct control {

    char map_name[STRING_TAM];//............... String que armazena o nome do arquivo mapa[00].txt atual.
    int count_map;//........................... Número que representa o mapa atual [01 - 99].


} CONTROL;

typedef struct map {


    int count_hearts;//........................ Número que representa a quantidade de corações presentes no mapa.
    int count_monster;//....................... Número que representa a quantidade de monstros presentes no mapa.
    int count_obstacle;//...................... Número que representa a quantidade de paredes no mapa [000 - (~384)].


    char phase_map[LINES][COLUMNS];//.......... Matriz que armazena a representação dos espaços livres e paredes do mapa atual.
    Rectangle collision_map[LINES * COLUMNS];// Vetor que armazena os retângulos para checagem de colisão.

    Rectangle hearts_list[HEARTS_LIMIT];//..... Vetor que armazena os retângulos referentes as posições das vidas extras do jogo.
    MONSTER monster_list[MONSTER_LIMIT];//..... Vetor que representa os monstros presentes no mapa e seus atributos.

    Rectangle sword_position;//................ Retângulo que armazena a posição da espada do jogador no mapa.

} MAP;
//######################################################################################################################
void SetupPlayer(PLAYER *p1);
void DrawnPlayer(PLAYER *p1, Texture2D finn);
int SpriteFramePlayer(PLAYER *p1);
void ControlPlayer(PLAYER *p1, const MAP *environment);
void ModifierPositionPlayer(PLAYER *p1, const MAP *environment, int move_x, int move_y);
bool WallCollisionPlayer(const PLAYER *p1, const MAP *environment);
void GetItensPlayer(MAP *environment, PLAYER *p1);

void CallAttackPlayer(PLAYER *p1, MAP *environment);
void PlayerAttack(PLAYER *p1, int direction, MAP *environment);
void CollisionAttackPlayer(PLAYER *p1, Rectangle object_a, Rectangle object_b, MAP *environment);
void KnockBackPlayer(PLAYER *p1, const MAP *environment);
void UpdateInvincibilityTime(PLAYER *p1);
void UpdateLevelStatus(PLAYER *p1);
void GameBarStatusPlayer(PLAYER *p1, CONTROL *org);

//______________________________________________________________________________________________________________________
void DrawnMonsters(const MAP *environment, Texture2D zombie);
int SpriteFrameMonsters(MAP *environment, const int index);
void RandomMovementGeneratorForMonsters(MAP *environment);
void MovementMonsters(MAP *environment, int randomNumber, int i);
void ModifierPositionMonster(MAP *environment, int move_x, int move_y, int index);
bool WallCollisionMonster(const MAP *environment, int index);
bool MonsterXMonsterCollision(const MAP *environment, int index);
void CheckDeathMonster(MAP *environment);
void OrganizerListMonster(MAP *environment, int index);

//______________________________________________________________________________________________________________________
int RenameMap(CONTROL *org);//Atualiza o nome atual do arquivo do mapa a ser chamado para execução no jogo.
int ReadMap(MAP *environment,CONTROL *org,  PLAYER *p1);//Com base no nome do arquivo, busca um arquivo .txt correspondente nos diretórios e salva seus dados na matriz phase_map.
int SetupObjectMap(MAP *environment, PLAYER *p1, char type, int i, int j);//Inicializa os objetos(Monstros, Corações e Espada) no mapa do jogo.
void DrawGameMap(const MAP *environment);//Desenha os tiles(chão e paredes) do cenário da fase.
void DrawObjectMap( const MAP *environment, const PLAYER *p1);
void OrganizerListHeartsMap(MAP *environment, int init);
void UpdateMap(MAP *environment, CONTROL *org,  PLAYER *p1);
/*[#]*/void ClearMap(MAP *environment,CONTROL *org, PLAYER *p1);
//______________________________________________________________________________________________________________________










#endif //TYPE_H
