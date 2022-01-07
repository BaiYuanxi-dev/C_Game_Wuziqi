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
//��ʼ��position
void initialPosition(Point position[], int* element) {
	for (*element = 0; *element < 225; (*element)++) {
		position[*element].row = 0;
		position[*element].column = 0;
		position[*element].score = 0;
	}
	*element = 0;
}
/*�������ӵ��ж�������ṹ�����飬�Ƚ�ÿ����score��С
  �ҵ�position[].score�����±꣬
  ����λ�õ�����ֵ ��ֵ��best��������Ϊ����ֵ���أ�
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

//��֪�����ĸ�����ķ���֮��
void getSumScore(Point position[], int* element, int stone[][15]) {
	int sum = 0;
	initialPosition(position, element);
	int i, j;
	//�������̣�
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

/*�������������������У��У��������Խ�
  ����row��col��ʾȡ��λ�ÿ�ʼ�� ��������ӵģ�x��y������,
  �����λ�÷ֱ���0 1 2 3 4��λ��ȥ���������
  ����[00000]0000,0[00000]000��00[00000]00 ����
*/
int rowScore(int row, int col, int stone[][15]) {
	int sum = 0;
	int s[5];
	int i, j;
	//�������е�ÿһ�����԰���5�����λ��
	for (i = col - 4; i <= col; i++) { //����ȡ5�Σ��ֱ����ÿ�εķ�ֵ������col-i��λ��
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
//��
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
//���Խ�
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
//���Խ�
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


/*��֪�������֪һ��5����(�������������������У��У��������Խ�)��
  ��ʾ������Ϊ0����Ϊ1����Ϊ2��δ֪Ϊ��
  �����д���һ����СΪ5�����飬һ����ʾ������λ�õı���
*/


/*�ɶԳ��ԣ�x = 0 �ȼ��� x = 4��x = 1�ȼ��� x = 3��x = 2 �ȼ��� x = 2
  ��x = 3 �� 4 ʱ���ú��������ԳƲ�����
  ��λ�öԳƣ��ٰ�5��λ�õ�����״���Գ�
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



//����x = 0,1,2ʱ�����ӵķֲ����ڸ�λ�����ӵ��������з�
//���ط�ֵ
/*��׼�������ӣ�1000���ɻ��ģ�90�� �ɻ�����50��
		��������40 �ɻ����15  һ�ӣ�0��
	  �谭���壺500���谭���ģ�70���谭���ģ�60��
	  �谭������30���谭�����5

*/
int getScore(int s[], int x) {
	int score = 0;
	if (x > 2) {
		//�ɶԳ��ԣ�x = 3,4ʱ�ȼ���x = 1��0ʱ
		change(s, 5);
		x = 4 - x;
	}
	//��λ��
	if (x == 0) {
		xzero(&score, s, x);
	}
	//�ڶ�λ��
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
		if (s[x + 2] == 0) { //_20??   �ɻ��
			*score = 15;
		}
		else if (s[x + 3] == 0) { //_220? �ɻ���
			*score = 50;
		}
		else if (s[x + 4] == 0) { //_2220 �ɻ���
			*score = 90;
		}
		else {   //_2222   ����
			*score = 1000;
		}

	}
	else if (s[1] == 1 && (s[2] == 1 || s[2] == 0) &&
		(s[3] == 1 || s[3] == 0) && (s[4] == 1 || s[4] == 0))
	{
		if (s[x + 2] == 0) { //_10??   �谭���
			*score = 5;
		}
		else if (s[x + 3] == 0) { //_110?   �谭����
			*score = 30;
		}
		else if (s[x + 4] == 0) { //_1110   �谭����
			*score = 70;
		}
		else {   //_1111   �谭����
			*score = 500;
		}
	}
}

void xfirst(int* score, int s[], int x) {
	if ((s[0] == 2 || s[0] == 0) && (s[2] == 2 || s[2] == 0) &&
		(s[3] == 2 || s[3] == 0) && (s[4] == 2 || s[4] == 0))
	{
		if (s[0] == 2) {
			if (s[2] == 0) {   // 2_0??  �ɻ��
				*score = 15;
			}
			else if (s[3] == 0) {  //2_20? �ɻ���
				*score = 50;
			}
			else if (s[4] == 0) {  //2_220 �ɻ���
				*score = 90;
			}
			else {                //2_222 ����
				*score = 1000;
			}
		}
		else {
			if (s[2] == 0) {       // 0_0??  ��
				*score = 0;
			}
			else if (s[3] == 0) {  //0_20? �ɻ��
				*score = 15;
			}
			else if (s[4] == 0) {  //0_220 �ɻ���
				*score = 50;
			}
			else {                  //0_222 �ɻ���
				*score = 90;
			}
		}
	}
	if ((s[0] == 1 || s[0] == 0) && (s[2] == 1 || s[2] == 0) &&
		(s[3] == 1 || s[3] == 0) && (s[4] == 1 || s[4] == 0))
	{
		if (s[0] == 1) {
			if (s[2] == 0) {   // 1_0??  �谭���
				*score = 5;
			}
			else if (s[3] == 0) {  //1_10? �谭����
				*score = 30;
			}
			else if (s[4] == 0) {  //1_110 �谭����
				*score = 70;
			}
			else {                //1_111 �谭����
				*score = 500;
			}
		}
		else {
			if (s[2] == 0) {       // 0_0??  ��
				*score = 0;
			}
			else if (s[3] == 0) {  //0_10? �谭���
				*score = 5;
			}
			else if (s[4] == 0) {  //0_110 �谭����
				*score = 30;
			}
			else {                   //0_111 �谭����
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
					if (s[4] == 2) {    //22_22 ���� 
						*score = 1000;
					}
					else {     //s4 = 0  //22_20 �ɻ���
						*score = 90;
					}
				}
				else {                    // s0 = 0
					if (s[4] == 2) {
						*score = 90;      //02_22 �ɻ���
					}
					else {
						*score = 50;      //02_20 �ɻ���
					}
				}
			}
			else {                        //s3 = 0
				if (s[0] == 2) {
					*score = 40;          //22_0?  ������
				}
				else {
					*score = 15;          //02_0?  �ɻ��
				}
			}
		}
		else {                           //s1 = 0
			if (s[3] == 2) {
				if (s[4] == 2) {       //?0_22
					*score = 40;         //������
				}
				else {                   //?0_20
					*score = 15;         // �ɻ��
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
					if (s[4] == 1) {    //11_11 �谭���� 
						*score = 500;
					}
					else {     //s4 = 0  //11_10 �谭����
						*score = 70;
					}
				}
				else {                    // s0 = 0
					if (s[4] == 2) {
						*score = 70;      //01_11 �谭����
					}
					else {
						*score = 30;      //01_10 �谭����
					}
				}
			}
			else {                        //s3 = 0
				if (s[0] == 2) {
					*score = 20;          //11_0?  �谭����
				}
				else {
					*score = 5;          //02_0?  �谭���
				}
			}
		}
		else {                           //s1 = 0
			if (s[3] == 2) {
				if (s[4] == 2) {         //?0_11
					*score = 20;         //�谭����
				}
				else {                   //?0_10
					*score = 5;         // �谭���
				}
			}
		}
	}
}

