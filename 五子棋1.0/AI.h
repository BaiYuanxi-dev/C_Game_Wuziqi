#pragma once
#include"menu.h"
#include"gameService.h"
#include"game_file.h"

//initial the position struct
void initialPosition(Point position[], int* element);
//game function
struct rank* vsAi(int stone[][15], int* round, struct rank* head);
//computer calculate which point to choose
Point AI(Point position[], int element, int round);

//calculate the score in a special position
void getSumScore(Point position[], int* element, int stone[][15]);
int rowScore(int row, int col, int stone[][15]);
int colScore(int row, int col, int stone[][15]);
int posDiagonalScore(int row, int col, int stone[][15]);
int negDiagonalScore(int row, int col, int stone[][15]);

//change the 
void change(int s[], int len);

int getScore(int row[], int x);
void xzero(int* score, int row[], int x);
void xfirst(int* score, int row[], int x);
void xmiddle(int* score, int row[], int x);