
#include "stdafx.h"


int main()
{
	GameFrameWork gw;

	while (gw.getState()!=GFWSTATE::EXIT)
	{
		gw.FrameAdvance();
	}

	system("cls");

	std::cout << "프로그램을 종료합니다." << std::endl;

	return 0;
}

