#include"menu.h"
#include"gameService.h"
#include"model.h"
#include"game_file.h"

//initial the "stone" array which stand for the stone
void initial(int stone[][15]) {
	int i, j;
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			stone[i][j] = BLANK;
		}
	}
}
//change the GUI coordinate into the checkerboard coordinate 
int rangeX(int x) {
	int xAxis;
	if (x < 20 || x > 615) {
		xAxis = -1;
	}
	else {
		xAxis = (x - 25) / 42;
	}
	return xAxis;
}
int rangeY(int y) {
	int yAxis;
	if (y < 20 || y > 630) {
		yAxis = -1;
	}
	else {
		yAxis = (y - 25) / 42;
	}
	return yAxis;
}

//the game play function which control the game!
struct rank* play(int stone[][15], int* round, struct rank* head) {
	Point spPoint;
	spPoint.column = 0;
	spPoint.row = 0;
	int x, y;
	FlushMouseMsgBuffer();
	struct MOUSEMSG mp;
	do {
		mp = GetMouseMsg();
		if (mp.uMsg == WM_LBUTTONDOWN) {
			x = rangeX(mp.x);
			y = rangeY(mp.y);
			if (x >= 0 && x <= 14 && y >= 0 && y <= 14) {
				spPoint.row = x;
				spPoint.column = y;
				if (stone[spPoint.row][spPoint.column] != BLANK) {
					continue;
				}
				//the black stone goes 
				else if (*round % 2 == 0) {
					stone[spPoint.row][spPoint.column] = ABLACK;
					drawChess(spPoint.row, spPoint.column, (*round) % 2 + 1);
					saveAll(stone);
					(*round)++;
					//if black win
					if (judgeWinner(spPoint, stone) == 1) {
						head = inputUsers(head, *round);
						showWinner(ABLACK);
						break;
					}
					//draw
					else if (judgeDraw(stone)) {
						showDraw();
						break;
					}
				}
				//the white stone goes
				else if (*round % 2 == 1) {
					stone[spPoint.row][spPoint.column] = AWHITE;
					drawChess(spPoint.row, spPoint.column, (*round) % 2 + 1);
					saveAll(stone);
					(*round)++;
					//if white win
					if (judgeWinner(spPoint, stone) == 2) {
						head = inputUsers(head, *round);
						showWinner(AWHITE);
						break;
					}
				}
			}
		}
		else if (mp.uMsg == WM_RBUTTONDOWN) {
			if (mp.x >= 280 && mp.x <= 320 && mp.y >= 620 && mp.y <= 640) {
				savePieces(stone,*round);
				break;
			}
		}
	} while (1);
	return head;
}

//judge if the game has a winner
int judgeWinner(Point spPoint, int stone[][15]) {
	int winner = 0;
	int i;
	int count[4];
	count[0] = judgeColumn(spPoint, stone);
	count[1] = judgeRow(spPoint, stone);
	count[2] = judgePosDiagonal(spPoint, stone);
	count[3] = judgeNegDiagonal(spPoint, stone);
	for (i = 0; i < 4; i++) {
		if (count[i] >= 5) {
			winner = stone[spPoint.row][spPoint.column];
			break;
		}
	}
	return winner;
}

int judgeDraw(int stone[][15]) {
	int i, j;
	int draw = 1;
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			if (stone[i][j] == BLANK) {
				draw = 0;
			}
		}
	}
	return draw;
}

//judge if a column has 5 successive same stone
int judgeColumn(Point spPoint, int stone[][15]) {
	int temp1, temp2;
	int count = 1;
	temp1 = spPoint.row - 1;
	temp2 = spPoint.row + 1;
	while (temp1 >= 0) {
		if (stone[temp1][spPoint.column] == stone[spPoint.row][spPoint.column]) {
			count++;
			temp1--;
		}
		else {
			break;
		}
	}
	while (temp2 <= 14) {
		if (stone[temp2][spPoint.column] == stone[spPoint.row][spPoint.column]) {
			count++;
			temp2++;
		}
		else {
			break;
		}
	}
	return count;
}

//judge if a row has 5 successive same stone
int judgeRow(Point spPoint, int stone[][15]) {
	int temp1, temp2;
	int count = 1;
	temp1 = spPoint.column - 1;
	temp2 = spPoint.column + 1;
	while (temp1 >= 0) {
		if (stone[spPoint.row][temp1] == stone[spPoint.row][spPoint.column]) {
			count++;
			temp1--;
		}
		else {
			break;
		}
	}
	while (temp2 <= 14) {
		if (stone[spPoint.row][temp2] == stone[spPoint.row][spPoint.column]) {
			count++;
			temp2++;
		}
		else {
			break;
		}
	}

	return count;
}

//judge if a positive diagonal has 5 successive same stone
int judgePosDiagonal(Point spPoint, int stone[][15]) {
	int row1, row2, col1, col2;
	int count = 1;
	row1 = spPoint.row - 1;
	row2 = spPoint.row + 1;
	col1 = spPoint.column - 1;
	col2 = spPoint.column + 1;
	while (col1 >= 0 && row1 >= 0) {
		if (stone[row1][col1] == stone[spPoint.row][spPoint.column]) {
			count++;
			row1--;
			col1--;
		}
		else {
			break;
		}
	}
	while (row2 <= 14 && col2 <= 14) {
		if (stone[row2][col2] == stone[spPoint.row][spPoint.column]) {
			count++;
			row2++;
			col2++;
		}
		else {
			break;
		}
	}
	return count;
}

//judge if a negative diagonal has 5 successive same stone
int judgeNegDiagonal(Point spPoint, int stone[][15]) {
	int row1, row2, col1, col2;
	int count = 1;
	row1 = spPoint.row - 1;
	row2 = spPoint.row + 1;
	col1 = spPoint.column + 1;
	col2 = spPoint.column - 1;
	while (col1 <= 14 && row1 >= 0) {
		if (stone[row1][col1] == stone[spPoint.row][spPoint.column]) {
			count++;
			row1--;
			col1++;
		}
		else {
			break;
		}
	}
	while (row2 <= 14 && col2 >= 0) {
		if (stone[row2][col2] == stone[spPoint.row][spPoint.column]) {
			count++;
			row2++;
			col2--;
		}
		else {
			break;
		}
	}
	return count;
}

