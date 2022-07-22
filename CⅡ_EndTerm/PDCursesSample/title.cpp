//�^�C�g����ʂ̕\���A����
#pragma once
#include <curses.h>
#include <windows.h>
#include "read_char.h"
#include "struct.h"
#include "stage.h"

#define BUFFSIZE 1024

int title(void) {
	//�F�̐ݒ�
	start_color(); 
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	//�R���\�[���̍����A���̎擾
	int h, w;
	getmaxyx(stdscr, h, w);
	clear();//��ʃN���A
	

	//ini�t�@�C������X�e�[�W�̃p�����[�^���擾���č\���̂Ɋi�[
	char clear[BUFFSIZE]; //�N���A�������i�[
	char time[BUFFSIZE]; //�������Ԃ��i�[
	char dif[BUFFSIZE]; //�X�e�[�W��(��Փx)���i�[

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

	//�^�C�g����ʕ\��
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
	mvaddstr((h / 2) + 4, w / 4 - 3, "���L�[");


	mvaddstr(h / 2, 2*w / 4 - 3, "normal");
	mvaddstr((h / 2) + 2, 2*w / 4 - 3, normal.clear);
	mvaddstr((h / 2) + 4, 2*w / 4 - 3, "���L�[");

	mvaddstr(h / 2, 3*w / 4 - 3, "hard");
	mvaddstr((h / 2) + 2, 3*w / 4 - 3, hard.clear);
	mvaddstr((h / 2) + 4, 3*w / 4 - 3, "���L�[");

	mvaddstr((3*h / 4 +2) , w / 4 - 3, "���[���F�ӂ������̒���!!�}�[�N���o����f�������L�[��������");
	refresh();

	//�����ꂽ�L�[�ɂ���ăX�e�[�W�̓�Փx��ω�
	keypad(stdscr, TRUE);
	while (true) {
		switch (getch()) {
		case KEY_LEFT://���L�[:easy
			playGame(easy.limitTime, easy.stagename);

			return 0;
		
		case KEY_DOWN://���L�[:normal
			playGame(normal.limitTime, normal.stagename);

			return 0;

		case KEY_RIGHT://���L�[:hard
			playGame(hard.limitTime, hard.stagename);

			return 0;
			
		}

	}
}
