/*
    Jogo interativo Tetris implementado em linguagem C para uso 
    no console (terminal de comandos)

    Para executar:
        > start programa.exe

    Autor: Augusto Luengo Pereira Nunes
    Data: 28/08/2019

*/

#include "tetris.h"
#include "display.h"
#define DEBUG 1

/*
    Parte principal do programa, responsável por iniciar e 
    chamar as funções auxiliares.
*/
int main(){
    char matrix[ROWS][COLUMNS];
    Bloco tijolo;
    int keypressed=0;

    //posicao inicial do personagem
    tijolo.i = 0;
    tijolo.j= COLUMNS/2;
    tijolo.tipo = TIPO_I;
    tijolo.orientacao = ORIENTACAO_LEFT;
    tijolo.width = 5;
    tijolo.height = 1;
    //inicializando matriz
    init(matrix);

    //apagar o cursor da tela
    ShowConsoleCursor(0);
    system("cls");

    //animação do jogo
    while(keypressed != ESC){        
        gotoxy(0,0);

    #if DEBUG == 1
        printf("posicao = (%d, %d)\n", tijolo.i, tijolo.j);
        printf("dimensao = (%d, %d)\n", tijolo.width, tijolo.height);
    #endif

        //posicionar o @ no meio da tela
        
        drawbar(matrix, tijolo, PIXEL);

        //mostro a matriz na tela
        printMatrix(matrix);

        //faça posição anterior do @ ser apagada
      
        drawbar(matrix, tijolo, EMPTY);

        //faço a posição da @ ir para a direita
        if(tijolo.i < (ROWS-1)) tijolo.i++;
        
         //lendo teclas
        keypressed = 0;
        if (kbhit()) keypressed = getch();
        if(keypressed==ARROWS) keypressed = getch();

        switch (keypressed){
            case TECLA_A:
            case TECLA_a:
            case LEFT:
                if(tijolo.j - ((tijolo.width/2))> 0) tijolo.j--; //vai para esquerda
            break;
            case TECLA_D:
            case TECLA_d:
            case RIGHT:
                if ((tijolo.j + (tijolo.width/2)) < (COLUMNS-1)) tijolo.j++; //vai para direita
             break;
             case TECLA_ESPACO:
                if(tijolo.orientacao == ORIENTACAO_RIGHT)
                    tijolo.orientacao = ORIENTACAO_UP;
                else
                tijolo.orientacao++;

            //inverte as dimensões do tijolo
            int aux = tijolo.width;
            tijolo.width = tijolo.height;
            tijolo.height = aux;

            //resolvendo bug dos cantos
            if(tijolo.j < (tijolo.width/2))
                tijolo.j = tijolo.width/2;    
            else if(tijolo.j > COLUMNS - (tijolo.width/2) - 1)
                tijolo.j = COLUMNS - (tijolo.width/2) - 1;
        }
   
    }

    system("pause");

    return 0;
}