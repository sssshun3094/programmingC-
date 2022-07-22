#pragma once
#include <stdio.h>
#include <Windows.h>
#define CHARBUFF 128

//iniファイルから文字列を読み込む関数
int read_char(char* str, const char* section, const char* keyWord)//*str:読み込んだ文字列の格納場所, section:セクション名, keyWord:キーの名前
{
	char currentDirectory[CHARBUFF];
	GetCurrentDirectory(CHARBUFF, currentDirectory);
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);
	char keyValue[CHARBUFF];
	if (GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile) != 0) {
		sprintf_s(str, CHARBUFF, "%s", keyValue);
	}
	return 0;
}

