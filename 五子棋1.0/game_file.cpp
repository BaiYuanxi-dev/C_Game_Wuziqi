//contain functions about file and sort
#include"menu.h"
#include"gameService.h"
#include"game_file.h"

//clean the review file;
void clean() {
	FILE* fp;
	fp = fopen("review.txt", "wt");
	if (fp == NULL) {
		exit(1);
	}
	fclose(fp);
}

//save the not closed game
void savePieces(int stone[][15], int round) {
	FILE* fp;
	int i, j;
	fp = fopen("game_stone.txt", "wt");
	if (fp == NULL) {
		exit(1);
	}

	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			fprintf(fp, "%d", stone[i][j]);
		}
	}
	fprintf(fp, "\n");
	fprintf(fp, "%d", round);
	fclose(fp);
}

//load the last game
void reLoading(int stone[][15], int* round) {
	FILE* fp;
	int i, j;
	char ch;
	fp = fopen("game_stone.txt", "rt");
	if (fp == NULL) {
		exit(1);
	}
	fseek(fp, 0L, SEEK_SET);
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			ch = fgetc(fp) - '0';
			stone[i][j] = (int)ch;
		}
	}
	fscanf(fp, "\n");
	ch = fgetc(fp) - '0';
	*round = (int)ch;
	fclose(fp);
}

//save for review
void saveAll(int stone[][15]) {
	FILE* fp;
	int i, j;
	fp = fopen("review.txt", "a+");
	if (fp == NULL) {
		exit(1);
	}
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			fprintf(fp, "%d", stone[i][j]);
		}
	}
	fprintf(fp, "\n");
	fclose(fp);
}

//review the game
void review(int stone[][15]) {
	FILE* fp;
	struct MOUSEMSG mp;
	int i, j;
	char ch = -1;
	char st;
	fp = fopen("review.txt", "rt");
	if (fp == NULL) {
		exit(1);
	}
	fseek(fp, 0L, SEEK_SET);
	fflush(stdin);
	while (!feof(fp)) {
		mp = GetMouseMsg();
		if (mp.uMsg == WM_LBUTTONDOWN) {
			for (i = 0; i < 15; i++) {
				for (j = 0; j < 15; j++) {
					st = fgetc(fp) - '0';
					stone[i][j] = (int)st;
				}
			}
			fscanf(fp, "\n");
			update(stone);
		}
	}
	quit();
	fclose(fp);
}

//get the player's id and round number
struct rank* inputUsers(struct rank* head, int round) {
	char s1[20];
	TCHAR c1[] = _T("请输入姓名");
	InputBox(s1, 20, c1);
	
	struct rank* p = head;

	while (p != NULL) {
		if (strcmp(p->id, s1) == 0) {
			p->round = round;
			break;
		}
		p = p->next;
	}
	if (p == NULL) {
		struct rank* newNode = (struct rank*)malloc(sizeof(struct rank));
		if (newNode == NULL) {
			exit(1);
		}
		strcpy(newNode->id, s1);

		newNode->round = round;
		newNode->rankNum = 0;
		if (head == NULL) {
			head = newNode;
		}
		else {
			newNode->next = head;
			head = newNode;
		}
	}
	return head;
}

//read the rank file into the link
struct rank* readRankFile() {
	FILE* fp;
	fp = fopen("rank.txt", "rt");
	if (fp == NULL) {
		exit(1);
	}
	struct rank* head = NULL;
	struct rank* tail = NULL;
	struct rank* newNode;

	fseek(fp, 0L, SEEK_SET);
	fflush(stdin);

	while (!feof(fp)) {
		newNode = (struct rank*)malloc(sizeof(struct rank));
		if (newNode == NULL) {
			exit(1);
		}
		fscanf(fp, "%d %s %d\n", &newNode->rankNum, newNode->id, &newNode->round);

		if (head == NULL) {
			head = newNode;
			tail = head;
		}
		else {
			tail->next = newNode;
		}
		tail = newNode;
		tail->next = NULL;
	}

	fclose(fp);
	return head;
}

//get the sorted linked list
struct rank* getRank(struct rank* head) {
	struct rank* newHead = NULL;
	struct rank* p;
	struct rank* oldNode = head;
	int i = 1;

	while (oldNode != NULL) {
		p = (struct rank*)malloc(sizeof(struct rank));
		p->round = oldNode->round;
		p->rankNum = oldNode->rankNum;
		strcpy(p->id, oldNode->id);
		oldNode = oldNode->next;
		newHead = insert(newHead, p);
	}
	p = newHead;
	while (p != NULL) {
		p->rankNum = i;
		i++;
		p = p->next;
	}

	return newHead;
}
//insert the old link into the new ordered list  
struct rank* insert(struct rank* newHead, struct rank* p) {
	struct rank* p1, * p2;
	p2 = newHead;
	if (newHead == NULL) {
		newHead = p;
		newHead->next = NULL;
	}
	else {
		while (p2 != NULL && p->round > p2->round) {
			p1 = p2;
			p2 = p2->next;
		}
		if (p2 == NULL) {
			p1->next = p;
			p->next = NULL;
		}
		else {
			if (p2 == newHead) {
				newHead = p;
			}
			else {
				p1->next = p;
			}
			p->next = p2;
		}
	}
	return newHead;
}
//save the rank file
void saveRank(struct rank* head) {
	FILE* fp;
	int i = 0;
	fp = fopen("rank.txt", "wt");
	if (fp == NULL) {
		exit(1);
	}
	struct rank* p = head;
	while (p != NULL && i < 10) {
		fprintf(fp, "%d %s %d\n", p->rankNum, p->id, p->round);
		i++;
		p = p->next;
	}
	fclose(fp);
}

//show the ordered list
void showRank(struct rank* head) {
	initgraph(640, 640, EW_SHOWCONSOLE);
	bkPicture();
	struct rank* p = head;
	int x = 100, y = 100;
	int i = 0;
	char s1[4], s2[4];
	TCHAR str[20] = _T("排行榜");
	TCHAR str1[10] = _T("排名");
	TCHAR str2[10] = _T("姓名");
	TCHAR str3[10] = _T("步数");
  
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(280, 12, str);
	outtextxy(90, 50, str1);
	outtextxy(190, 50, str2);
	outtextxy(290, 50, str3);

	while (p != NULL && i < 10) {
		itoa(p->rankNum, s1, 10);
		itoa(p->round, s2, 10);
		outtextxy(x, y, s1);
		outtextxy(x + 100, y, p->id);
		outtextxy(x + 200, y, s2);
		y += 30;
		i++;
		p = p->next;
	}
	quit();
}
