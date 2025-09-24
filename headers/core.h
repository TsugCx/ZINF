#ifndef CORE_H
#define CORE_H
#include "..\\headers/type.h"


void LogicProcessingCore(MAP *environment, CONTROL *org, PLAYER *p1);
void GraphicsProcessingCore(MAP *environment, CONTROL *org, PLAYER *p1, Texture2D finn,  Texture2D zombie);



void IntroductionMenu();
void DrawMenu(int select);
void DrawMenuScreen();
void PauseMenu(bool *game_running);
void DrawPauseMenu(int select);
void GameBarStatusPlayer(PLAYER *p1, CONTROL *org);

void EndGameCore(PLAYER p1, SCORE finalist);
void KeyBoardInputCore(SCORE finalist);
void ReadArqCore(SCORE *scores, char nome_arq);
void UpdateHighscores(SCORE highscores[5], SCORE novo_score);
void RewriteFileCore(SCORE scores[MAXSCORES], SCORE finalist, char *nome_arq);
#endif //CORE_H
