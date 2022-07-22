//釣りの反射神経ゲーム
#include <curses.h>
#include "title.h"
#define BUFFSIZE 1024

int main(void)//main関数
{

	initscr(); // 端末制御の開始

	title();//タイトル画面の表示

	return 0;
}


