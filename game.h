#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// board snake and leadders -- >
extern int snakeladder[101];

// global variable --->
extern int player1score;
extern int player2score;

void ini_snakeleadder();

int rolldice();

void board();

int move(int player , int dice);


