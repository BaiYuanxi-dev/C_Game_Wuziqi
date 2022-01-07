#include"AI.h"
//game function
struct rank *vsAi(int stone[][15], int* round,struct rank* head) {
	Point position[225];
	Point best;
	int element = 0;

	Point spPoint;
	int x, y;
	spPoint.column = 0;
	spPoint.row = 0;

	struct MOUSEMSG mp;
	while (1) {
		//the black stone goes 
		if ((*round) % 2 == 0) {
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
					else {
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
				}
			}
		}
		else if ((*round) % 2 == 1) {
			getSumScore(position, &element, stone);//calculate the score
			best = AI(position, element, *round);//get best position
			spPoint.row = best.row;
			spPoint.column = best.column;
			stone[spPoint.row][spPoint.column] = AWHITE;
			saveAll(stone);
			drawChess(spPoint.row, spPoint.column, (*round) % 2 + 1);
			(*round)++;
			if (judgeWinner(spPoint, stone) == 2) {
				//head = inputUsers(head, *round);
				showWinner(AWHITE);
				break;
			}
		}
	}
	return head;
}
//初始化position
void initialPosition(Point position[], int* element) {
	for (*element = 0; *element < 225; (*element)++) {
		position[*element].row = 0;
		position[*element].column = 0;
		position[*element].score = 0;
	}
	*element = 0;
}
/*白棋下子的判定，传入结构体数组，比较每个的score大小
  找到position[].score最大的下标，
  将该位置的坐标值 赋值给best，并且作为返回值返回，
*/
Point AI(Point position[], int element, int round) {
	Point best;
	int maxScore = 0;
	int bestPoint = 0;
	int i;
	for (i = 0; i < element; i++) {
		if (position[i].score > maxScore) {
			maxScore = position[i].score;
			bestPoint = i;
		}
	}
	best.row = position[bestPoint].row;
	best.column = position[bestPoint].column;
	return best;
}

//感知：求四个方向的分数之和
void getSumScore(Point position[], int* element, int stone[][15]) {
	int sum = 0;
	initialPosition(position, element);
	int i, j;
	//遍历棋盘：
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			if (stone[i][j] != 0) {
				continue;
			}
			sum += rowScore(i, j, stone);
			sum += colScore(i, j, stone);
			sum += posDiagonalScore(i, j, stone);
			sum += negDiagonalScore(i, j, stone);
			if (sum != 0) {
				position[*element].row = i;
				position[*element].column = j;
				position[*element].score = sum;
				(*element)++;
				sum = 0;
			}
		}
	}
}

/*分四种情况计算分数：行，列，正、副对角
  参数row，col表示取到位置开始的 第五个棋子的（x，y）坐标,
  把这个位置分别当做0 1 2 3 4号位置去计算分数。
  例如[00000]0000,0[00000]000，00[00000]00 ……
*/
int rowScore(int row, int col, int stone[][15]) {
	int sum = 0;
	int s[5];
	int i, j;
	//遍历该行的每一个可以包含5个点的位置
	for (i = col - 4; i <= col; i++) { //数组取5次，分别计算每次的分值，当做col-i号位算
		if (i < 0 || i + 4 > 14) {
			continue;
		}
		else {
			for (j = 0; j < 5; j++) {
				s[j] = stone[row][i + j];
			}
			sum += getScore(s, col - i);
		}
	}
	return sum;
}
//列
int colScore(int row, int col, int stone[][15]) {
	int sum = 0;
	int s[5];
	int i, j;
	for (i = row - 4; i <= row; i++) {
		if (i < 0 || i + 4 > 14) {
			continue;
		}
		else {
			for (j = 0; j < 5; j++) {
				s[j] = stone[i + j][col];
			}
			sum += getScore(s, row - i);
		}
	}
	return sum;
}
//正对角
int posDiagonalScore(int row, int col, int stone[][15]) {
	int sum = 0;
	int i, j;
	int s[5];
	for (i = -4; i <= 0; i++) {
		if (col + i < 0 || col + i + 4 > 14 || row + i < 0 || row + i + 4 > 14) {
			continue;
		}
		else {
			for (j = 0; j < 5; j++) {
				s[j] = stone[row + i + j][col + i + j];
			}
			sum += getScore(s, -i);
		}
	}
	return sum;
}
//副对角
int negDiagonalScore(int row, int col, int stone[][15]) {
	int sum = 0;
	int i, j;
	int s[5];
	for (i = -4; i <= 0; i++) {
		if (col + i < 0 || col + i + 4 > 14 || row - i > 15 || row - i - 4 < 0) {
			continue;
		}
		else {
			for (j = 0; j < 5; j++) {
				s[j] = stone[row - i - j][col + i + j];
			}
			sum += getScore(s, -i);
		}
	}
	return sum;
}


/*感知，假设感知一排5个子(分四种情况计算分数：行，列，正、副对角)，
  表示：无子为0，黑为1，白为2，未知为？
  函数中传入一个大小为5的数组，一个表示该下子位置的变量
*/


/*由对称性：x = 0 等价于 x = 4；x = 1等价于 x = 3；x = 2 等价于 x = 2
  当x = 3 或 4 时，该函数用来对称操作：
  把位置对称，再把5个位置的棋子状况对称
*/
void change(int s[], int len) {
	int temp;
	int i, j;
	for (i = 0, j = len - 1; i <= j; i++, j--) {
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
}



//对于x = 0,1,2时，棋子的分布和在该位置下子的优劣来判分
//返回分值
/*标准：成五子：1000；成活四：90； 成活三：50；
		成眼三：40 成活二：15  一子：0；
	  阻碍黑五：500；阻碍活四：70；阻碍冲四：60；
	  阻碍活三：30；阻碍活二：5

*/
int getScore(int s[], int x) {
	int score = 0;
	if (x > 2) {
		//由对称性：x = 3,4时等价于x = 1，0时
		change(s, 5);
		x = 4 - x;
	}
	//首位置
	if (x == 0) {
		xzero(&score, s, x);
	}
	//第二位置
	else if (x == 1) {
		xfirst(&score, s, x);
	}
	else if (x == 2) {
		xmiddle(&score, s, x);
	}
	return score;
}







void xzero(int* score, int s[], int x) {
	if (s[1] == 2 && (s[2] == 2 || s[2] == 0) &&
		(s[3] == 2 || s[3] == 0) && (s[4] == 2 || s[4] == 0))
	{
		if (s[x + 2] == 0) { //_20??   成活二
			*score = 15;
		}
		else if (s[x + 3] == 0) { //_220? 成活三
			*score = 50;
		}
		else if (s[x + 4] == 0) { //_2220 成活四
			*score = 90;
		}
		else {   //_2222   成五
			*score = 1000;
		}

	}
	else if (s[1] == 1 && (s[2] == 1 || s[2] == 0) &&
		(s[3] == 1 || s[3] == 0) && (s[4] == 1 || s[4] == 0))
	{
		if (s[x + 2] == 0) { //_10??   阻碍活二
			*score = 5;
		}
		else if (s[x + 3] == 0) { //_110?   阻碍活三
			*score = 30;
		}
		else if (s[x + 4] == 0) { //_1110   阻碍活四
			*score = 70;
		}
		else {   //_1111   阻碍五子
			*score = 500;
		}
	}
}

void xfirst(int* score, int s[], int x) {
	if ((s[0] == 2 || s[0] == 0) && (s[2] == 2 || s[2] == 0) &&
		(s[3] == 2 || s[3] == 0) && (s[4] == 2 || s[4] == 0))
	{
		if (s[0] == 2) {
			if (s[2] == 0) {   // 2_0??  成活二
				*score = 15;
			}
			else if (s[3] == 0) {  //2_20? 成活三
				*score = 50;
			}
			else if (s[4] == 0) {  //2_220 成活四
				*score = 90;
			}
			else {                //2_222 成五
				*score = 1000;
			}
		}
		else {
			if (s[2] == 0) {       // 0_0??  无
				*score = 0;
			}
			else if (s[3] == 0) {  //0_20? 成活二
				*score = 15;
			}
			else if (s[4] == 0) {  //0_220 成活三
				*score = 50;
			}
			else {                  //0_222 成活四
				*score = 90;
			}
		}
	}
	if ((s[0] == 1 || s[0] == 0) && (s[2] == 1 || s[2] == 0) &&
		(s[3] == 1 || s[3] == 0) && (s[4] == 1 || s[4] == 0))
	{
		if (s[0] == 1) {
			if (s[2] == 0) {   // 1_0??  阻碍活二
				*score = 5;
			}
			else if (s[3] == 0) {  //1_10? 阻碍活三
				*score = 30;
			}
			else if (s[4] == 0) {  //1_110 阻碍活四
				*score = 70;
			}
			else {                //1_111 阻碍五子
				*score = 500;
			}
		}
		else {
			if (s[2] == 0) {       // 0_0??  无
				*score = 0;
			}
			else if (s[3] == 0) {  //0_10? 阻碍活二
				*score = 5;
			}
			else if (s[4] == 0) {  //0_110 阻碍活三
				*score = 30;
			}
			else {                   //0_111 阻碍冲四
				*score = 60;
			}
		}
	}
}

void xmiddle(int* score, int s[], int x) {
	if ((s[0] == 2 || s[0] == 0) && (s[1] == 2 || s[1] == 0) &&
		(s[3] == 2 || s[3] == 0) && (s[4] == 2 || s[4] == 0))
	{
		if (s[1] == 2) {
			if (s[3] == 2) {
				if (s[0] == 2) {
					if (s[4] == 2) {    //22_22 成五 
						*score = 1000;
					}
					else {     //s4 = 0  //22_20 成活四
						*score = 90;
					}
				}
				else {                    // s0 = 0
					if (s[4] == 2) {
						*score = 90;      //02_22 成活四
					}
					else {
						*score = 50;      //02_20 成活三
					}
				}
			}
			else {                        //s3 = 0
				if (s[0] == 2) {
					*score = 40;          //22_0?  成眼三
				}
				else {
					*score = 15;          //02_0?  成活二
				}
			}
		}
		else {                           //s1 = 0
			if (s[3] == 2) {
				if (s[4] == 2) {       //?0_22
					*score = 40;         //成眼三
				}
				else {                   //?0_20
					*score = 15;         // 成活二
				}
			}
		}
	}
	else if ((s[0] == 1 || s[0] == 0) && (s[1] == 1 || s[1] == 0) &&
		(s[3] == 1 || s[3] == 0) && (s[4] == 1 || s[4] == 0))
	{
		if (s[1] == 1) {
			if (s[3] == 1) {
				if (s[0] == 1) {
					if (s[4] == 1) {    //11_11 阻碍成五 
						*score = 500;
					}
					else {     //s4 = 0  //11_10 阻碍活四
						*score = 70;
					}
				}
				else {                    // s0 = 0
					if (s[4] == 2) {
						*score = 70;      //01_11 阻碍活四
					}
					else {
						*score = 30;      //01_10 阻碍活三
					}
				}
			}
			else {                        //s3 = 0
				if (s[0] == 2) {
					*score = 20;          //11_0?  阻碍眼三
				}
				else {
					*score = 5;          //02_0?  阻碍活二
				}
			}
		}
		else {                           //s1 = 0
			if (s[3] == 2) {
				if (s[4] == 2) {         //?0_11
					*score = 20;         //阻碍眼三
				}
				else {                   //?0_10
					*score = 5;         // 阻碍活二
				}
			}
		}
	}
}

