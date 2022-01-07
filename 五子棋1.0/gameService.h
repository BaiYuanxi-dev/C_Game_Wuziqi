#pragma once
//play the game needed
#include"global.h"
#include"model.h"

void initial(int stone[][15]);       //initial the array

 //the play game function
struct rank* play(int stone[][15], int* round, struct rank* head);

//let the user input his or her message
struct rank* inputUsers(struct rank* head, int round);

//judge if there are five stones in a row,a column or a diagonal
int judgeColumn(Point spPoint, int stone[][15]);
int judgeRow(Point spPoint, int stone[][15]);
int judgePosDiagonal(Point spPoint, int stone[][15]);
int judgeNegDiagonal(Point spPoint, int stone[][15]);

//judge if the game is over and get the winner
int judgeWinner(Point spPoint, int stone[][15]);

int judgeDraw(int stone[][15]);

//GUI,let the coordinate become the checkerboard point
int rangeX(int x);
int rangeY(int y);
