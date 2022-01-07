#include"menu.h"
#include"gameService.h"
#include"game_file.h"
#include"AI.h"
int main() {
	int stone[15][15];
	int round = 0;
	struct MOUSEMSG mp;
    int y;//stand for choice
	
	//circle();
	struct rank* head ;
	head = readRankFile();
	initial(stone);
	music();
	start();
	while (1) {
		mp = GetMouseMsg();
		if (mp.uMsg == WM_LBUTTONDOWN) {
			mciSendString("stop mymusic", NULL, 0, NULL);
			mciSendString("close mymusic", NULL, 0, NULL);
			break;
		}
	}
	FlushMouseMsgBuffer();
    
	while (1) {
		mp = GetMouseMsg();
		//game play
		y = (mp.y - 100) / 50 + 1;
		if (y == 1 && mp.x >= 100 && mp.x <= 180) {
			if (mp.uMsg == WM_LBUTTONDOWN) {
				initial(stone);
				round = 0;
				background();
				clean();
				head = play(stone, &round, head);
				start();
			}
		}
		//show rank
		else if (y == 2 && mp.x >= 100 && mp.x <= 180) {
		    if (mp.uMsg == WM_LBUTTONDOWN) {
			    head = getRank(head);
				saveRank(head);
				showRank(head);
				start();
			}
	    }
		//reload the last game
		else if (y == 3 && mp.x >= 100 && mp.x <= 180) {
			 if (mp.uMsg == WM_LBUTTONDOWN) {
				 reLoading(stone,&round);
				 update(stone);
				 head = play(stone, &round, head);
				 start(); 
			 }
		}
		//review the game
		else if(y == 4 && mp.x >= 100 && mp.x <= 180) {
			if (mp.uMsg == WM_LBUTTONDOWN) {
				review(stone);
				start();
			}
			//start();
		}
		//VS computer
		else if (y == 5 && mp.x >= 100 && mp.x <= 180) {
			if (mp.uMsg == WM_LBUTTONDOWN) {
				background();
				initial(stone);
				round = 0;
				clean();
				head = vsAi(stone, &round,head);

				start();
			}
		}
		//rules
		else if (y == 6 && mp.x >= 100 && mp.x <= 180) {
			if (mp.uMsg == WM_LBUTTONDOWN) {
				rules();
				start();
			}
			//start();
		}
		else if (y == 7 && mp.x >= 100 && mp.x <= 180) {
			if (mp.uMsg == WM_LBUTTONDOWN) {
				aboutUs();
				start();
			}
		}
		//quit
		else if (y == 8 && mp.x >= 100 && mp.x <= 180) {
			 if (mp.uMsg == WM_LBUTTONDOWN) {
				 closegraph();
				 break;
			 }
		}
	}
	mciSendString("stop mymusic", NULL, 0, NULL);
	mciSendString("close mymusic", NULL, 0, NULL);
	return 0;
}