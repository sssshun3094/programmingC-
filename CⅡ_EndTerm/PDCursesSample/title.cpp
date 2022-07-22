//タイトル画面の表示、操作
#pragma once
#include <curses.h>
#include <windows.h>
#include "read_char.h"
#include "struct.h"
#include "stage.h"

#define BUFFSIZE 1024

int title(void) {
	//色の設定
	start_color(); 
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	//コンソールの高さ、幅の取得
	int h, w;
	getmaxyx(stdscr, h, w);
	clear();//画面クリア
	

	//iniファイルからステージのパラメータを取得して構造体に格納
	char clear[BUFFSIZE]; //クリア履歴を格納
	char time[BUFFSIZE]; //制限時間を格納
	char dif[BUFFSIZE]; //ステージ名(難易度)を格納

	read_char(clear, "section1", "clear");
	read_char(time, "section1", "limittime");
	read_char(dif, "section1", "stagename");
	stageParam easy;
	sprintf_s(easy.clear, BUFFSIZE, clear);
	easy.limitTime = (long)atoi(time);
	sprintf_s(easy.stagename, BUFFSIZE, dif);

	read_char(clear, "section2", "clear");
	read_char(time, "section2", "limittime");
	read_char(dif, "section2", "stagename");
	stageParam normal;
	sprintf_s(normal.clear, BUFFSIZE, clear);
	normal.limitTime = (long)atoi(time);
	sprintf_s(normal.stagename, BUFFSIZE, dif);

	read_char(clear, "section3", "clear");
	read_char(time, "section3", "limittime");
	read_char(dif, "section3", "stagename");
	stageParam hard;
	sprintf_s(hard.clear, BUFFSIZE, clear);
	hard.limitTime = (long)atoi(time);
	sprintf_s(hard.stagename, BUFFSIZE, dif);

	//タイトル画面表示
	attron(COLOR_PAIR(1));
	int i, j;
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			mvaddstr(i, j, " ");
		}
	}

	mvaddstr(h / 4, w/2 - 4, "FISHING");

	mvaddstr(h / 2, w/4 - 3, "easy");
	mvaddstr((h / 2) + 2, w / 4 - 3, easy.clear);
	mvaddstr((h / 2) + 4, w / 4 - 3, "←キー");


	mvaddstr(h / 2, 2*w / 4 - 3, "normal");
	mvaddstr((h / 2) + 2, 2*w / 4 - 3, normal.clear);
	mvaddstr((h / 2) + 4, 2*w / 4 - 3, "↓キー");

	mvaddstr(h / 2, 3*w / 4 - 3, "hard");
	mvaddstr((h / 2) + 2, 3*w / 4 - 3, hard.clear);
	mvaddstr((h / 2) + 4, 3*w / 4 - 3, "→キー");

	mvaddstr((3*h / 4 +2) , w / 4 - 3, "ルール：ふきだしの中に!!マークが出たら素早く↑キーを押そう");
	refresh();

	//押されたキーによってステージの難易度を変化
	keypad(stdscr, TRUE);
	while (true) {
		switch (getch()) {
		case KEY_LEFT://←キー:easy
			playGame(easy.limitTime, easy.stagename);

			return 0;
		
		case KEY_DOWN://↓キー:normal
			playGame(normal.limitTime, normal.stagename);

			return 0;

		case KEY_RIGHT://→キー:hard
			playGame(hard.limitTime, hard.stagename);

			return 0;
			
		}

	}
}
