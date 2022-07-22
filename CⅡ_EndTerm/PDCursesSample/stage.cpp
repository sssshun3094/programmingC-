//ステージごとの画面、操作、内容
#pragma once
#include <conio.h>
#include <stdio.h>
#include <curses.h>
#include <String.h>
#include <string>
#include <windows.h>
#include <time.h>
#include "title.h"
#include "read_char.h"
#define BUFFSIZE 1024

int playGame(long limitTime, char* stageName);
int drawBack(void);
int drawSign(long limitTime);

int playGame(long limitTime, char* stageName) {//ゲームを実行する, limitTime:制限時間, stagename:ステージ名(難易度)
	clear();
	drawBack();
	int clear = -1;
	clear = drawSign(limitTime);//成功:0, 失敗:1

	//iniファイルにクリアしたステージを記録
	char section[BUFFSIZE];
	char c[BUFFSIZE];
	sprintf_s(section, BUFFSIZE, stageName);
	if (strcmp(stageName, "easy") == 0) {
		sprintf_s(section, BUFFSIZE, "section1");
	}else if (strcmp(stageName, "normal") == 0) {
		sprintf_s(section, BUFFSIZE, "section2");
	}else if (strcmp(stageName, "hard") == 0) {
		sprintf_s(section, BUFFSIZE, "section3");
	}

	read_char(c, section, "clear");


	if (clear == 0 && strcmp(c, "not complete") == 0) {
		char currentDirectory[BUFFSIZE];
		GetCurrentDirectory(BUFFSIZE, currentDirectory);
		char settingFile[BUFFSIZE];
		sprintf_s(settingFile, BUFFSIZE, "%s\\setting.ini", currentDirectory);
		WritePrivateProfileString(section, "clear", "complete", settingFile);
	}

	//タイトル画面に戻る時の処理
	init_pair(6, COLOR_BLACK, COLOR_WHITE);
	attron(COLOR_PAIR(6));
	int h, w;
	getmaxyx(stdscr, h, w);
	mvaddstr(h/2, w/2 -12, " Homeキーでタイトルに戻る ");
	refresh();
	while (true) {
		if (getch() == KEY_HOME) {//Homeキーを押すとタイトルに戻る
			title();
		}
	}
	

	
	return 0;
}

//背景の描画
int drawBack(void) {
	start_color(); // カラーの設定
	
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
	init_pair(3, COLOR_CYAN, COLOR_CYAN);
	init_pair(4, COLOR_YELLOW, COLOR_RED);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_WHITE);
	
	int h, w;
	getmaxyx(stdscr, h, w);

	int i,j;
	//空の描画
	attron(COLOR_PAIR(3));
	for (i = 0; i < h/4; i++) {
		for (j = 0; j <= w; j++) {			
			mvaddstr(i, j, " ");
		}
	}
	//海の描画
	attron(COLOR_PAIR(1));
	for (i = h/4; i < 3*h/4; i++) {
		for (j = 0; j <= w; j++) {
			if ((i%2==0)&((i*i + j) % 8 == 1 || (i*i + j) % 8 == 2)) {
				mvaddstr(i, j, "~");
			}
			else {
				mvaddstr(i, j, " ");
			}
			
		}
	}
	//地面の描画
	attron(COLOR_PAIR(2));
	for (i = 3*h/4; i <=h; i++) {
		for (j = 0; j <= w; j++) {
			if (((i * i + j) % 4 == 1 || (i * i + j) % 4 == 2)) {
				mvaddstr(i, j, "/");
			}
			else {
				mvaddstr(i, j, " ");
			}
		}
	}
	//ウキの描画
	attron(COLOR_PAIR(4));
	i = 2 * h / 4;
	j = w / 2;
	mvaddstr(i, j, " ");
	i++;
	mvaddstr(i, j, " ");
	i++;
	mvaddstr(i, j-1, "---");
	//竿の描画
	attron(COLOR_PAIR(5));
	for (i = (3 * h / 4)-2; i <= h; i++) {
		mvaddstr(i, w/2, " ");
		
	}
	//ふきだしの描画
	int h2 = h - 4;
	int w2 = (w / 2) + 5;
	attron(COLOR_PAIR(6));
	mvaddstr(h-1, w2-1, " ");
	mvaddstr(h - 1, w2, " ");
	mvaddstr(h-2, w2 - 1, " ");
	for (j = 0; j < 30; j++)
		for (i = -2; i <= 2; i++) {
			mvaddstr(h2 + i, w2 + j, " ");
		}
	refresh();
	
	return 0;
}


//竿を上げる合図の表示と↑キーを押したときの処理
int drawSign(long limitTime) {//limitTime:制限時間
	//色の組み合わせの定義
	init_pair(6, COLOR_BLACK, COLOR_WHITE);
	init_pair(7, COLOR_RED, COLOR_WHITE);
	init_pair(8, COLOR_BLUE, COLOR_WHITE);
	attron(COLOR_PAIR(6));

	//コンソールの高さ、幅の取得
	int h, w;
	getmaxyx(stdscr, h, w);
	//「・」「！」を打つ位置の決定
	int h2 = h - 4;
	int w2 = (w / 2) + 5;
	int i,j;

	//時間関係の変数の定義
	long otime, ntime,wtime,ttime;
	otime = clock();//基準の時間
	srand((unsigned int)(time(NULL))* (time(NULL)));//乱数の種を時間の2乗にしてランダム性を高めている
	wtime = 4000 + (rand()%10000);//待ち時間は4から14秒のランダム値
	ttime = 1000;//1秒


	keypad(stdscr, TRUE);
	while (true) {//「!!」が出る前、出るときの処理	

		ntime = clock() - otime;//経過時間 = 現在の時間 - 基準の時間
		if (ntime < wtime) {//wtime(ms)経過してない場合、
			if (ntime > ttime) {//経過時間がttimeを上回ったら「・」を表示してttimeに1000加算 ⇒ 1秒ごとに「・」を表示。
				for (i = -2; i <= 2; i++) {
					if (i == 0) {
						mvaddstr(h2, w2, "・");
					}
					else {
						mvaddstr(h2 + i, w2, "  ");
					}

				}
				refresh();
				ttime += 1000; //+1秒
				w2+=2;
			}
		}
		else {//wtime(ms)経ったら「!!」を表示
			
			attron(COLOR_PAIR(7));
			for (i = -2; i <= 2; i++) {
				if (i == 0) {
					mvaddstr(h2, w2, "!!");
				}
				else {
					mvaddstr(h2 + i, w2, "  ");
				}

			}
			refresh();
			break;
		}

		if (_kbhit()) {
			if (getch() == KEY_UP) {//「!!」が表示される前に↑キーを押したら失敗
				attron(COLOR_PAIR(8));
				mvaddstr(h2, w2, "miss");
				refresh();
				return 1;//失敗
			}
		}
		
	}

	attron(COLOR_PAIR(7));
	long up = 0;
	otime = clock();

	

	while (true) {//「!!」が出た後の処理
		ntime = clock() - otime;

		if (_kbhit()) {//_kbhit()関数で、キーボードが押されていないときgetch()によってキー入力を待ってプログラムが止まってしまうのを防ぐ

			//↑キーが押されているときカウントアップし続け、離すとカウントはゼロになる
			//⇒カウントが1のときのみ処理を行うようにすることで押した瞬間のみが処理の対象となる。
			if (getch() == KEY_UP) {
				up++;
			}
			else {
				up = 0;
			}
		}
		

		if (ntime < limitTime) {//制限時間以内に↑キーを押せたら成功判定
			if (up == 1) {//↑キーを押した瞬間のみ
				mvaddstr(h2, w2, "get!");
				refresh();
				break;
			}
		}
		else {//制限時間を過ぎたら失敗判定
			attron(COLOR_PAIR(8));
			mvaddstr(h2, w2, "miss");
			refresh();
			return 1;//失敗
		}
					
		
	}
	

	return 0;//成功
}

