//function showing menu and checkerboard
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<graphics.h>
#include<easyx.h>
#include<windows.h>
#pragma comment(lib,"winmm.lib")
#include"global.h"
#include"model.h"
#define UNICODE
#define _CRT_SECURE_NO_WARNINGS

//rank struct
struct rank {
	int rankNum;
	char id[20];
	int round;
	struct rank* next;
};

void rules();// show rules
void aboutUs();  //show about game 

void start();//show the start interface

//judge and print the black and white stone
void drawChess(int row, int col, int player);
void update(int stone[][15]);
void background();//show the checkerboard

void showWinner(int winner);//show winner
void showDraw();//show draw game

void quit();//click mouse and quit 
void bkPicture();//put a background picture
void newPicture();//put a picture
void circle();//draw some circle

//music 
void music();

