#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_


//stand for blank, black stone,white stone
enum PointStatus {
	STATUS_BLANK,
	STATUS_BLACK,
	STATUS_WHITE
};

typedef struct Point {
	int row;   //row number
	int column;//column number
	int score; //the score of ai in this position;
}Point;

#endif   //#ifndef _MODEL_H_