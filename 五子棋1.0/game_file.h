//contain functions about file 
#pragma once
#include"menu.h"
#include"gameService.h"

void savePieces(int stone[][15], int round);//save the last no end game 
void reLoading(int stone[][15], int* round);//reload the last game
void saveAll(int stone[][15]);//save the last game
void review(int stone[][15]);//review the last game
void clean();//clean the file of review.txt

struct rank* readRankFile();//read the rank file

//insert
struct rank* insert(struct rank* newHead, struct rank* p);
struct rank* getRank(struct rank* head);

//save and show the rank file
void saveRank(struct rank* head);
void showRank(struct rank* head);

