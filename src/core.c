#include "raylib.h"
#include "../headers/type.h"
#include "../headers/core.h"

#include <stdio.h>
#include <string.h>

#define BMO_BODY ((Color) {64, 124, 132, 255})
#define BMO_SCREEN ((Color) {139, 190, 147, 255})
#define BMO_DETAIL ((Color) {24, 58, 66, 255})
#define BMO_BOARD ((Color) {16, 30, 43, 255})

void LogicProcessingCore(MAP *environment, CONTROL *org, PLAYER *p1) {
    UpdateInvincibilityTime(p1);
    UpdateLevelStatus(p1);
    ControlPlayer(p1, environment);
    GetItensPlayer(environment, p1);
    RandomMovementGeneratorForMonsters(environment);
    KnockBackPlayer(p1, environment);
    CheckDeathMonster(environment);
    UpdateMap(environment, org, p1);
} //END LogicProcessingCore(...);.......................................................................................

void GraphicsProcessingCore(MAP *environment, CONTROL *org, PLAYER *p1, Texture2D finn, Texture2D zombie) {
    BeginDrawing();

    GameBarStatusPlayer(p1, org);
    DrawGameMap(environment);
    DrawObjectMap(environment, p1);
    DrawnMonsters(environment, zombie);
    DrawnPlayer(p1, finn);
    CallAttackPlayer(p1, environment);
    ClearBackground(BLACK);

    EndDrawing();
} //GraphicsProcessingCore(...).........................................................................................


void IntroductionMenu() {
    int select = 0;
    bool continuos = true;

    do {
        if (IsKeyPressed(KEY_A)) {
            select--;
            if (select < 0) { select = 2; }
        }

        if (IsKeyPressed(KEY_D)) {
            select++;
            if (select > 3) { select = 0; }
        }

        switch (select) {
            case 0:
                DrawMenu(select);

                if (IsKeyPressed(KEY_ENTER))
                    continuos = false;

                break;

            case 1:
                DrawMenu(select);
                break;

            case 2:
                DrawMenu(select);
                if (IsKeyPressed(KEY_ENTER))
                    CloseWindow();
                break;
            default:
                continue;
        }
    } while (continuos);
} //IntroductionMenu(...);..............................................................................................


void DrawMenu(int select) {
    BeginDrawing();
    DrawMenuScreen();

    DrawText("The Legend Of", 210, 200, 52, DARKBLUE);
    DrawText("Adventure Time", 210, 260, 100, BLUE);

    DrawText("Play", 360, 480, 30, DARKBLUE);
    DrawText("Score", 560, 480, 30, DARKBLUE);
    DrawText("Exit", 760, 480, 30, DARKBLUE);

    switch (select) {
        case 0:
            DrawRectangle(356, 516, 76, 4, BMO_BOARD);
            break;

        case 1:
            DrawRectangle(556, 516, 100, 4, BMO_BOARD);
            break;

        case 2:
            DrawRectangle(756, 516, 72, 4, BMO_BOARD);
            break;
        default:
            break;
    }

    ClearBackground(BLACK);
    EndDrawing();
} //END DrawMenu(...);..................................................................................................


void PauseMenu(bool *game_running) {
    int select = 0;

    while (true) {

        DrawPauseMenu(select);
        if (IsKeyPressed(KEY_A)) {
            select--;
            if (select < 0) { select = 2; }
        }

        if (IsKeyPressed(KEY_D)) {
            select++;
            if (select > 2) { select = 0; }
        }

        if (IsKeyPressed(KEY_ENTER)) {
            if (select == 0) {
                *game_running = false;
                break;

            } else if (select == 1) {
                // implementar retorno ao menu principal

            } else if (select == 2) {
                CloseWindow();
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawPauseMenu(select);
        EndDrawing();
    }
} //END PauseMenu(...);.................................................................................................


void DrawPauseMenu(int select) {
    DrawMenuScreen();
    DrawText("[!] PAUSED", 300, 260, 100, BLUE);

    DrawText("Continue", 260, 480, 30, DARKBLUE);
    DrawText("Go to main menu", 500, 480, 30, DARKBLUE);
    DrawText("Exit", 860, 480, 30, DARKBLUE);

    switch (select) {
        case 0:
            DrawRectangle(254, 516, 140, 4, BMO_BOARD);
            break;

        case 1:
            DrawRectangle(494, 516, 250, 4, BMO_BOARD);
            break;

        case 2:
            DrawRectangle(854, 516, 72, 4, BMO_BOARD);
            break;
    }
} //END DrawPauseMenu(...);.............................................................................................


void DrawMenuScreen() {
    DrawRectangle(0, 0, 1200, 860, BMO_BODY);

    Rectangle screen_border = {150.0f, 60.0f, 900.0f, 600.0f};
    Rectangle screen_space = {170.0f, 80.0f, 860.0f, 560.0f};

    //Borda da Tela e Tela.
    DrawRectangleRounded(screen_border, 0.09, 1, BMO_BOARD);
    DrawRectangleRounded(screen_space, 0.09, 1, BMO_SCREEN);

    //Detalhes.
    DrawRectangle(170, 720, 630, 80, BMO_BOARD);
    DrawRectangle(185, 735, 600, 50, BMO_DETAIL);
    DrawCircle(920, 760, 45, BMO_BOARD);
    DrawCircle(920, 760, 35, DARKBLUE);
} //END DrawMenuScreen(...);............................................................................................


void GameBarStatusPlayer(PLAYER *p1, CONTROL *org) {

    //Apenas utilizasse de retangulos, e textos formatados para exibir as informações importantes para o jogador.
    DrawRectangle(0, 0, 1200, 60, BMO_BOARD);
    DrawRectangle(0, 2, 1200, 56, BMO_BODY);

    Rectangle screen_border = {4.0f, 4.0f, 1192.0f, 52.0f};
    Rectangle screen_space = {8.0f, 6.0f, 1184.0f, 48.0f};

    DrawRectangleRounded(screen_border, 0.09, 1, BMO_BOARD);
    DrawRectangleRounded(screen_space, 0.09, 1, BMO_SCREEN);


    DrawText("FINN", 80, 10, 20, BMO_BOARD);


    int value_life_bar = (int) (180.0f * p1->status.pv / p1->status.pv_max);

    DrawRectangle(16, 30, 180, 20, SKYBLUE);
    DrawRectangle(16, 30, value_life_bar, 20, DARKBLUE);

    Color text_style;
    if (p1->invincibility_time > 0) {
        text_style = GOLD;
    } else {
        text_style = WHITE;
    }
    DrawText(TextFormat(" %i / %i ", p1->status.pv, p1->status.pv_max), 80, 32, 16, text_style);

    DrawText(TextFormat("Level: %i\nScore: %i ", p1->status.lv, p1->status.score), 210, 10, 20, BMO_BOARD);
    DrawText(TextFormat("Phase: %i", org->count_map, p1->status.lv, p1->status.score), 1040, 16, 28, BMO_BOARD);
} //END GameBarStatusPlayer(...);.......................................................................................

void EndGameCore(PLAYER p1, SCORE finalist) {
    KeyBoardInputCore(finalist);
    char arq_name[20] = "scores.gin";
    finalist.score = p1.status.score;
    SCORE highscores[MAXSCORES];

    ReadArqCore( highscores, arq_name);
    UpdateHighscores(highscores, finalist);
    RewriteFileCore(highscores, finalist, arq_name);


}


void KeyBoardInputCore(SCORE finalist) {
    while (true)
    {
        int key;
        int count_key = 0;
        while ((key = GetCharPressed()) != 0)
        {
            // Se for caractere imprimível e ainda houver espaço
            if (count_key < STRING_TAM && (key >= 32 && key <= 125))
            {
                finalist.name[count_key++] = (char)key;
                finalist.name[count_key] = '\0';
            }
        }

        if (IsKeyPressed(KEY_ENTER)) {
            break;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawMenuScreen();
        DrawText("DIGITE SEU APELIDO:", 350, 300, 60, BMO_DETAIL);
        DrawText(finalist.name, 20, 60, 30, BLACK);


        EndDrawing();
    }
}


void ReadArqCore(SCORE *scores, char nome_arq) {

    FILE *arqv = fopen(nome_arq, "rb");

    if(arqv == NULL){//Caso apresente erro na abertura do arquivo;
        printf("Erro ao abrir arquivo");

    } else {

        rewind(arqv);

        for(int i = 0; i < 5; i++){
            if(fread(&scores[i], sizeof(SCORE), 1, arqv) == 1);
        }
    }
    fclose(arqv);
}


void UpdateHighscores(SCORE highscores[5], SCORE novo_score) {

    if(highscores[4].score < novo_score.score) {

        for(int i = 0; i < 5; i++) {

            if(highscores[i].score < novo_score.score){
                int aux = i;

                for(int j = 4; j > i; j--) {
                    highscores[j] = highscores[j - 1];
                }

                highscores[i] = novo_score;
                break;
            }
        }
    }

}


void RewriteFileCore(SCORE scores[MAXSCORES], SCORE finalist, char *nome_arq) {


    scores[0] = finalist;

    FILE *arq = fopen(nome_arq, "wb");

    if(arq == NULL){//Caso apresente erro na abertura do novo arquivo;
        printf("Erro ao criar arquivo");

    } else {
        rewind(arq);

        for(int i = 0; i < 5; i++){
            if(fwrite(&scores[i], sizeof(SCORE), 1, arq) != 1) printf("Erro de escrita!");
        }
    }
    fclose(arq);
}