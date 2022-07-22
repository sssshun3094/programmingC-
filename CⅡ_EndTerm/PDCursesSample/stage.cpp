//�X�e�[�W���Ƃ̉�ʁA����A���e
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

int playGame(long limitTime, char* stageName) {//�Q�[�������s����, limitTime:��������, stagename:�X�e�[�W��(��Փx)
	clear();
	drawBack();
	int clear = -1;
	clear = drawSign(limitTime);//����:0, ���s:1

	//ini�t�@�C���ɃN���A�����X�e�[�W���L�^
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

	//�^�C�g����ʂɖ߂鎞�̏���
	init_pair(6, COLOR_BLACK, COLOR_WHITE);
	attron(COLOR_PAIR(6));
	int h, w;
	getmaxyx(stdscr, h, w);
	mvaddstr(h/2, w/2 -12, " Home�L�[�Ń^�C�g���ɖ߂� ");
	refresh();
	while (true) {
		if (getch() == KEY_HOME) {//Home�L�[�������ƃ^�C�g���ɖ߂�
			title();
		}
	}
	

	
	return 0;
}

//�w�i�̕`��
int drawBack(void) {
	start_color(); // �J���[�̐ݒ�
	
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
	init_pair(3, COLOR_CYAN, COLOR_CYAN);
	init_pair(4, COLOR_YELLOW, COLOR_RED);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_WHITE);
	
	int h, w;
	getmaxyx(stdscr, h, w);

	int i,j;
	//��̕`��
	attron(COLOR_PAIR(3));
	for (i = 0; i < h/4; i++) {
		for (j = 0; j <= w; j++) {			
			mvaddstr(i, j, " ");
		}
	}
	//�C�̕`��
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
	//�n�ʂ̕`��
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
	//�E�L�̕`��
	attron(COLOR_PAIR(4));
	i = 2 * h / 4;
	j = w / 2;
	mvaddstr(i, j, " ");
	i++;
	mvaddstr(i, j, " ");
	i++;
	mvaddstr(i, j-1, "---");
	//�Ƃ̕`��
	attron(COLOR_PAIR(5));
	for (i = (3 * h / 4)-2; i <= h; i++) {
		mvaddstr(i, w/2, " ");
		
	}
	//�ӂ������̕`��
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


//�Ƃ��グ�鍇�}�̕\���Ɓ��L�[���������Ƃ��̏���
int drawSign(long limitTime) {//limitTime:��������
	//�F�̑g�ݍ��킹�̒�`
	init_pair(6, COLOR_BLACK, COLOR_WHITE);
	init_pair(7, COLOR_RED, COLOR_WHITE);
	init_pair(8, COLOR_BLUE, COLOR_WHITE);
	attron(COLOR_PAIR(6));

	//�R���\�[���̍����A���̎擾
	int h, w;
	getmaxyx(stdscr, h, w);
	//�u�E�v�u�I�v��łʒu�̌���
	int h2 = h - 4;
	int w2 = (w / 2) + 5;
	int i,j;

	//���Ԋ֌W�̕ϐ��̒�`
	long otime, ntime,wtime,ttime;
	otime = clock();//��̎���
	srand((unsigned int)(time(NULL))* (time(NULL)));//�����̎�����Ԃ�2��ɂ��ă����_���������߂Ă���
	wtime = 4000 + (rand()%10000);//�҂����Ԃ�4����14�b�̃����_���l
	ttime = 1000;//1�b


	keypad(stdscr, TRUE);
	while (true) {//�u!!�v���o��O�A�o��Ƃ��̏���	

		ntime = clock() - otime;//�o�ߎ��� = ���݂̎��� - ��̎���
		if (ntime < wtime) {//wtime(ms)�o�߂��ĂȂ��ꍇ�A
			if (ntime > ttime) {//�o�ߎ��Ԃ�ttime����������u�E�v��\������ttime��1000���Z �� 1�b���ƂɁu�E�v��\���B
				for (i = -2; i <= 2; i++) {
					if (i == 0) {
						mvaddstr(h2, w2, "�E");
					}
					else {
						mvaddstr(h2 + i, w2, "  ");
					}

				}
				refresh();
				ttime += 1000; //+1�b
				w2+=2;
			}
		}
		else {//wtime(ms)�o������u!!�v��\��
			
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
			if (getch() == KEY_UP) {//�u!!�v���\�������O�Ɂ��L�[���������玸�s
				attron(COLOR_PAIR(8));
				mvaddstr(h2, w2, "miss");
				refresh();
				return 1;//���s
			}
		}
		
	}

	attron(COLOR_PAIR(7));
	long up = 0;
	otime = clock();

	

	while (true) {//�u!!�v���o����̏���
		ntime = clock() - otime;

		if (_kbhit()) {//_kbhit()�֐��ŁA�L�[�{�[�h��������Ă��Ȃ��Ƃ�getch()�ɂ���ăL�[���͂�҂��ăv���O�������~�܂��Ă��܂��̂�h��

			//���L�[��������Ă���Ƃ��J�E���g�A�b�v�������A�����ƃJ�E���g�̓[���ɂȂ�
			//�˃J�E���g��1�̂Ƃ��̂ݏ������s���悤�ɂ��邱�Ƃŉ������u�Ԃ݂̂������̑ΏۂƂȂ�B
			if (getch() == KEY_UP) {
				up++;
			}
			else {
				up = 0;
			}
		}
		

		if (ntime < limitTime) {//�������Ԉȓ��Ɂ��L�[���������琬������
			if (up == 1) {//���L�[���������u�Ԃ̂�
				mvaddstr(h2, w2, "get!");
				refresh();
				break;
			}
		}
		else {//�������Ԃ��߂����玸�s����
			attron(COLOR_PAIR(8));
			mvaddstr(h2, w2, "miss");
			refresh();
			return 1;//���s
		}
					
		
	}
	

	return 0;//����
}

