#pragma once
#include <stdio.h>
#include <Windows.h>
#define CHARBUFF 128

//ini�t�@�C�����當�����ǂݍ��ފ֐�
int read_char(char* str, const char* section, const char* keyWord)//*str:�ǂݍ��񂾕�����̊i�[�ꏊ, section:�Z�N�V������, keyWord:�L�[�̖��O
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

