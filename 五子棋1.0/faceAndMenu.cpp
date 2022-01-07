//the basic interface
#include"menu.h"
#include"game_file.h"

//show rules
void rules() {
    char str[9][120];
    int i;
    int x = 30;
    int y = 50;
    initgraph(640, 640);
    //drawBk();
    bkPicture();
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    strcpy(str[0], "(1)  Renju is played by two players against each other.");
    strcpy(str[1], "(2)  Black stone move first, followed by white.");
    strcpy(str[2], "(3)  Board: 15×15.");
    strcpy(str[3], "(4)  The Winner is the first player to get an unbroken row of five stones horizontally, vertically or diagonally.");
    strcpy(str[4], "(5)  A draw occurs when both players will not get an unbroken row of five stones.");
    strcpy(str[5], "(6)  Columm numbers are letters, while row numbers are numeric.");
    strcpy(str[6], "(7)  The player who slecets black color stone moves first.");
    strcpy(str[7], "(8)  Player can start game if select Start Game.");
    strcpy(str[8], "(9)  Move stone: player click the point on the chackerboard.");
    for (i = 0; i < 9; i++) {
        outtextxy(x, y + i * 50, str[i]);
    }
    quit();
}
//show message about the game 
void aboutUs() {
    initgraph(640, 640);
    bkPicture();
    setbkmode(TRANSPARENT);//background of string
    settextcolor(BLACK);//color of string
    settextstyle(32, 0, _T("Consolas"));//style of string

    TCHAR str1[30] = _T("Five - in - a - row 1.0");
    TCHAR str2[30] = _T("Author: 神魔恋");
    outtextxy(120, 200, str1);
    outtextxy(200, 400, str2);
    quit();
}

//show the checkerboard
void background() {
    initgraph(640, 640);
    IMAGE img;
    TCHAR str[20] = _T("保存并退出");
    bkPicture();
    loadimage(&img, _T("D:\\VS\\五子棋1.0\\五子棋1.0\\0.jpg"), 640, 640);
    putimage(0, 0, &img);
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    settextstyle(20, 0, _T("Consolas"));
    outtextxy(280, 620, str);
}

//show the start interface
void start() {
    initgraph(640, 640);
    bkPicture();           //background picture
    newPicture();          // another picture
    circle();              // other decorate 
    
    IMAGE img[9];
    loadimage(&img[0], _T("D:\\VS\\五子棋1.0\\五子棋1.0\\0.3.jpg"), 400, 80); 
    loadimage(&img[1], _T("D:\\VS\\五子棋1.0\\五子棋1.0\\0.2.jpg"), 90, 30);
    loadimage(&img[2], _T("D:\\VS\\五子棋1.0\\五子棋1.0\\0.4.jpg"), 90, 30);
    loadimage(&img[3], _T("D:\\VS\\五子棋1.0\\五子棋1.0\\0.5.jpg"), 95, 30);
    loadimage(&img[4], _T("D:\\VS\\五子棋1.0\\五子棋1.0\\0.6.jpg"), 90, 30);
    loadimage(&img[5], _T("D:\\VS\\五子棋1.0\\五子棋1.0\\0.7.jpg"), 90, 30);
    loadimage(&img[6], _T("D:\\VS\\五子棋1.0\\五子棋1.0\\0.8.jpg"), 90, 30);
    loadimage(&img[7], _T("D:\\VS\\五子棋1.0\\五子棋1.0\\0.9.jpg"), 90, 30);
    loadimage(&img[8], _T("D:\\VS\\五子棋1.0\\五子棋1.0\\0.1.jpg"), 90, 30);

    putimage(110, 10, &img[0]);
    putimage(100, 100, &img[1]);
    putimage(100, 150, &img[2]);
    putimage(100, 200, &img[3]);
    putimage(100, 250, &img[4]);
    putimage(100, 300, &img[5]);
    putimage(100, 350, &img[6]);
    putimage(100, 400, &img[7]);
    putimage(100, 450, &img[8]);
}
     
//update the checkerboard
void update(int stone[][15]) {
    background();
    int i, j;
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (stone[i][j] != 0) {
                drawChess(i, j, stone[i][j]);
            }
        }
    }
}

//draw the stone
void drawChess(int row, int col, int player) {
    if (player == 1) {
        setfillcolor(BLACK);
        fillcircle(10, 10, 8);
    }
    else if (player == 2) {
        setfillcolor(WHITE);
        fillcircle(10, 10, 8);
    }
    fillcircle(row * 42 + 25, col * 42 + 25, 10);
}

//show the winner
void showWinner(int winner) {
    struct MOUSEMSG mp;
    FlushMouseMsgBuffer();
    TCHAR str[30] = _T("Quit");
    TCHAR str1[30] = _T("The Winner is Black Stone");
    TCHAR str2[30] = _T("The Winner is White Stone");
    if (winner == 1) {
        outtextxy(250, 250, str1);
        outtextxy(250, 270, str);
        quit();
    }
    else if (winner == 2) {
        outtextxy(250, 250, str2);
        outtextxy(250, 270, str);
        quit();
    }
}
//show the draw 
void showDraw() {
    TCHAR str[30] = _T("The Game is over!");
    outtextxy(250, 250, str);
}


void quit() {
    struct MOUSEMSG mp;
    while (true)
    {
        mp = GetMouseMsg();
        if (mp.uMsg == WM_LBUTTONDOWN) {
            break;
        }
    }
}
void bkPicture() {
    IMAGE img1;
    loadimage(&img1, _T("D:\\VS\\五子棋1.0\\五子棋1.0\\1.1.jpg"), 640, 640);
    putimage(0, 0, &img1);
}

void newPicture() {
    IMAGE img;
    loadimage(&img, _T("D:\\VS\\五子棋1.0\\五子棋1.0\\2.0.jpg"), 300, 300);
    putimage(300, 100, &img);
}

void circle() {
    int x = 80;
    int y = 115;
    int i;
    for (i = 0; i < 8; i++) {
        if (i % 2 == 0) {
            setfillcolor(BLACK);
        }
        else {
            setfillcolor(WHITE);
        }
        fillcircle(x, y, 10);
        y += 50;
    }
}

void music() {
    struct MOUSEMSG mp;
    mciSendString("open mus.wma alias mymusic", NULL, 0, NULL);
    mciSendString("play mymusic", NULL, 0, NULL);    
}

