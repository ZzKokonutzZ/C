#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
struct chess
{
    char pieces[64];
    int colors[64];
};
typedef struct chess chessboard;

void color(int value)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,value);
}

void colorbook()
{
    for (int i=0;i<16;i+=1 )
    {
        color(i);
        printf("[%d]Hello World\n",i);
    }
}



void initboard(chessboard* game)
{
    for(int i=0;i<8;i+=1)
    {
        for (int ii=0;ii<8;ii+=1)
        {
            (*game).pieces[i+8*ii]='0';
            (*game).colors[i+8*ii]=0;
        }
    }
    for (int i=0;i<8;i+=1)
    {
        (*game).pieces[i+8]='p';
        (*game).colors[i+8]=8;
        (*game).colors[i]=8;

        (*game).pieces[i+8*6]='p';
        (*game).colors[i+8*6]=7;
        (*game).colors[i+8*7]=7;
    }
    (*game).pieces[0]='T';
    (*game).pieces[7]='T';
    (*game).pieces[56]='T';
    (*game).pieces[63]='T';

    (*game).pieces[1]='C';
    (*game).pieces[6]='C';
    (*game).pieces[57]='C';
    (*game).pieces[62]='C';

    (*game).pieces[2]='F';
    (*game).pieces[5]='F';
    (*game).pieces[58]='F';
    (*game).pieces[61]='F';

    (*game).pieces[3]='D';
    (*game).pieces[4]='R';
    (*game).pieces[59]='D';
    (*game).pieces[60]='R';
}

void printboard(chessboard game)
{
    for (int i=0;i<8;i+=1)
    {
        for (int ii=0; ii<8;ii+=1 )
        {
            color(3);
            printf("[");
            if (game.pieces[i*8+ii]=='0')
            {
                printf(" ");
            }
            else
            {
                color(game.colors[i*8+ii]);
                printf("%c",game.pieces[i*8+ii]);
            }
            color(3);
            printf("]");
            
        }
        printf("\n");
    }
}

void play(chessboard* game)
{
    char pos1[3];
    scanf("%s",pos1);
    int ipos1=(int)pos1[0]-97+8*(7-(int)pos1[1]+49);
    if (ipos1<0 | ipos1>63 | (*game).colors[ipos1]=='0')
    {
        printf("position incorrecte");
        return;
    }
    printf("%d\n",ipos1);
    char pos2[3];
    scanf("%s",pos2);
    int ipos2=(int)pos2[0]-97+8*(7-(int)pos2[1]+49);
    if (ipos2<0 | ipos2>63 )
    {
        printf("position incorrecte");
        return;
    }
    printf("%d\n",ipos2);
    (*game).colors[ipos2]=(*game).colors[ipos1];
    (*game).pieces[ipos2]=(*game).pieces[ipos1];
    (*game).colors[ipos1]=0;
    (*game).pieces[ipos1]='0';
}



int main()
{
    chessboard game;
    initboard(&game);
    printboard(game);
    printf("%d",(int)'0');
    int i=0;
    play(&game);
    printboard(game);
    return 0;
}
