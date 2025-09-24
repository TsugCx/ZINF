 # **<span style="color: red;">Zelda - INF (ZINF)</span>**
 **Trabalho Final das Turmas A e B, da cadeira de Algoritmos e Programação – 2025/1 
 do Instituto de Informatica (INF) da Universidade Federal do Rio Grande do Sul (UFRGS)**

O objetivo é implementar uma versão simplificada do jogo conhecido como Lenda de Zelda, chamada Zelda - INF (ZINF), 
utilizando a biblioteca gráfica Raylib. Em ZINF, o jogador chamado deve matar todos os monstros para socorrer uma princesa 
chamada Zelda.

## **Nome do Projeto:<span style="color: blue;"> The Legend Of Adventure Time</span> (TLOAT)**

### Nota: As funções foram nomeadas com base na struct principal da qual elas manipulam, terminado seu nome (na maioria dos casos), com o nome da STRUCT.

## Logica base:

A função main inicializa as structs base que serão manipuladas durante o jogo, sendo elas:

MAP - Armazena todos os valores referentes aos mapas, monstros, corações, espada, matriz e contadores para fins de controle.
\
\
CONTROL - Armazena o nome do arquivo atual e seu recpectivo contador(usado para renomar o mapa para o seguinte, caso haja).
\
\
PLAYER - Controla os atributos do jogador.
\
\
MONSTER - É inicializado apenas indiretamente como um vetor dentro de MAP, em geral guarda os atributos pertencentes aos monstros in game.
\
\
No main existem dois loops(o interno tem o objetivo de controlar e ordenar asa funções do menu inicial que permitem o jogador Inicar, ver o Score(não foi implementado) e fechar o jogo).
\
Caso o jogo seja iniciado as STRUCTS são inicializadas o arquivo e renomeado para mapa01.txt, e ele e carregado para a matriz, após o joo entra no loop interno.
\
O segundo loop tem por objetivo controlar toda a lógica por trás do funcionamento da fases e é dividido em duas funções principais que controlam dois aspectos do jogo, a logica interna e a parte gráfica.
\
\
A função que controla o logica interna abrange o movimento do jogador, a ação de ataque pelo mouse, a movimentação dos monstros pelo mapa, a colisão [Jogador x Monstro]\
o tempo de invencibilidade caso o jogador sofra dano, a captura de itens(corações e espada) dentre outros demais aspectos.
\
\
\
A função grafica realiza a leitura das posições dos objetos do mapa e os atualiza visualmente, garantindo a fluides do jogo.



## Hierarquia:
O arquivo type.h, armazena todos os heardes e as funções das principais struct do jogo(MAP, ORG, PLAYER, MONSTER);
\
O arquivo core.h, Agrupa as funções de type.h para reduzir o conteudo do main, além de possuir algumas funções utilitarias para serem usadas
\
Os demais arquivos .c, implementam toda a logica por trâs das funcionalidades do jogo.
\
\
\
## Tutorial:
Controle de movimento:
\
W - CIMA,
\
S - BAIX0,
\
A - ESQUERDA,
\
D - DIREITA.
\
\
Controle de atque:
\
É realizado movendo o ponteiro do mouse sobre a tela, a direção indicada pelo ponteiro sera a direção do ataque.
\
O ataque possui areas verticais e horizontais de 3 tiles de 50 x 50 px.
\
Na vertical a area e reduzida para dois tiles, possibilitando assim um ataque octadirecional.
\
Para efetuar a ação de ataque apó escolher a posição com o mouse, basta apertar o botão esquerdo e o ataque sera realizado e os alvos atigindo serão eliminados.
\
\
Controle de pause:
\
TAB - Pausa toda a lógica do jogo até que a opção de continuar no menu seja selecionada.
\
\
Controle de navegação de menus:
\
A - Vai para a opção a esquerda no menu.
\
D - Vai para a opção a direita no menu.
\
ENTER - Confirma a opção selecionada no menu.
\

### Representação:
\
As paredes são representadas por dois tipos de retangulos cinzas.
\
\
As vidas são representadas por retangulos rosas.
\
\
A espada e representada por um retangulo vermelho.
\
\
Jogador e monstro são representados pelos seus rescpectivos sprites.
