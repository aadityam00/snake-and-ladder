#include "game.h"

int player1score = 1;
int player2score = 1;

// board snake and leadders -- >
int snakeladder[101] = { 0 };

int rolldice()
{
    return rand() % 6 + 1;
}

void board()
{
    int Board[100];
    for (int i = 99; i >= 0; i--)
    {
        Board[i] = i + 1;
        if (Board[i] == player1score)
        {
            printf("| #p1 ");
        }
        else if (Board[i] == player2score)
        {
            printf("| #p2 ");
        }
        else if (Board[i] == player1score && Board[i] == player2score)
        {
            printf("|#p1&p2");
        }
        else
        {
            printf("|%4d ", Board[i]);
        }

        if ((100 - i + 1 )% 10 == 0)
        {
            printf("|\n");
        }
    }
    printf("\n\n\n");
}

void ini_snakeleadder() 
{
    snakeladder[6] = 40;
    snakeladder[23] = -10;
    snakeladder[45] = 20;
    snakeladder[61] = -18;
    snakeladder[66] = -8;
    snakeladder[77] = 5;
    snakeladder[98] = -88;
}


int move(int player, int dice)
{
    int position = player + dice;
    if (position > 100)
    {
        return player;
    }

    int newscore = position + snakeladder[position];

    if (newscore > 100)
    {
        return player;
    }
    if (newscore < 1)
    {
        newscore = 1;
    }


    return newscore;
}