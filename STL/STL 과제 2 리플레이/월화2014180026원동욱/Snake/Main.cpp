
#include "stdafx.h"


int main()
{
	GameFrameWork gw;

	while (gw.getState()!=GFWSTATE::EXIT)
	{
		gw.FrameAdvance();
	}

	system("cls");

	std::cout << "���α׷��� �����մϴ�." << std::endl;

	return 0;
}

