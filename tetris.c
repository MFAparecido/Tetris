/*
    Jogo interativo Tetris implementado em linguagem C para uso 
    no console (terminal de comandos)

    Autor: Augusto Luengo Pereira Nunes
    Data: 28/08/2019

*/

#include "tetris.h"

/*
    Inicializa a matriz principal com 'espaços vazios'
*/
void init(char matrix[ROWS][COLUMNS])
{
    int i, j;

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLUMNS; j++)
        {
            matrix[i][j] = ' ';
        }
    }
}

/*
    Mostra o conteúdo da matriz principal na tela 
    do computador.
*/
void printMatrix(char matrix[ROWS][COLUMNS])
{
    int i, j;

    printf("\t\t\t\t\t");
    //Linha de cima
    for (j = 0; j < COLUMNS + 2; j++)
    {
        printf("*");
    }
    printf("\n");

    //Matriz do jogo
    for (i = 0; i < ROWS; i++)
    {
        printf("\t\t\t\t\t*");
        for (j = 0; j < COLUMNS; j++)
        {
            printf("%c", matrix[i][j]);
        }
        printf("*\n");
    }

    printf("\t\t\t\t\t");
    //Linha de baixo
    for (j = 0; j < COLUMNS + 2; j++)
    {
        printf("*");
    }
    printf("\n");
}

/*
    Desenhar uma barra usando o simbolo do caracter ASCII
    passado por parâmetro.
*/
void drawbar(char matrix[ROWS][COLUMNS], Bloco barra, int simbolo)
{
    switch (barra.orientacao)
    {
    case ORIENTACAO_DOWN:
    case ORIENTACAO_UP:
        if (barra.i - 4 >= 0)
            matrix[barra.i - 4][barra.j] = simbolo;
        if (barra.i - 3 >= 0)
            matrix[barra.i - 3][barra.j] = simbolo;
        if (barra.i - 2 >= 0)
            matrix[barra.i - 2][barra.j] = simbolo;
        if (barra.i - 1 >= 0)
            matrix[barra.i - 1][barra.j] = simbolo;
        matrix[barra.i][barra.j] = simbolo;

        break;
    case ORIENTACAO_RIGHT:
    case ORIENTACAO_LEFT:
        if (barra.j + 1 >= 0)
            matrix[barra.i][barra.j + 1] = simbolo;
        if (barra.j + 2 >= 0)
            matrix[barra.i][barra.j + 2] = simbolo;
        if (barra.j - 1 >= 0)
            matrix[barra.i][barra.j - 1] = simbolo;
        if (barra.j - 2 >= 0)
            matrix[barra.i][barra.j - 2] = simbolo;
        matrix[barra.i][barra.j] = simbolo;

        break;
    }
}

void initBar(Bloco *barra)
{
    barra->i = 0;
    barra->j = COLUMNS / 2;
    barra->tipo = TIPO_I;
    barra->orientacao = ORIENTACAO_LEFT;
    barra->width = 5;
    barra->height = 1;

#if DEBUG == 1
    printf("posI: %d    posJ: %d \n", barra->i, barra->j);
    system("pause");
#endif
}

void rotate(Bloco *barra)
{

    if (barra->orientacao == ORIENTACAO_RIGHT)
        barra->orientacao = ORIENTACAO_UP;
    else
        barra->orientacao++;

    //inverte as dimensões do tijolo
    int aux = barra->width;
    barra->width = barra->height;
    barra->height = aux;

    //resolvendo bug dos cantos
    if (barra->j < (barra->width / 2))
        barra->j = barra->width / 2;
    else if (barra->j > COLUMNS - (barra->width / 2) - 1)
        barra->j = COLUMNS - (barra->width / 2) - 1;
}
/*
    verifica a colisão de blocos
*/
int collisionDetect(char matrix[ROWS][COLUMNS], Bloco barra){
    int retorno = 0;

    //colisão com a base
    if((barra.i + 1) >=  ROWS)
        retorno = 1;
        
    //colisão entre peças
    if(matrix[barra.i + 1][barra.j] != EMPTY)
        retorno =1;

    int t2 = barra.width / 2;
    if (matrix[barra.i+1][barra.j + t2] != EMPTY)
        retorno = 1;
    if (matrix[barra.i+1][barra.j - t2] != EMPTY)
        retorno =1;
        
    return retorno;
}