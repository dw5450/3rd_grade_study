#include "stdafx.h"
#include "GameFrameWork.h"


GameFrameWork::GameFrameWork()
{

	myScene = new MenuScene;
}

GameFrameWork::~GameFrameWork()
{
	if (myScene) delete myScene;
}
void GameFrameWork::FrameAdvance()
{
	m_GameTimer.Tick(0.0f);					//게임의 시간

	myScene->ProcessInput();

	if (state == GFWSTATE::MENU)
	{
		size_t tempState;
		tempState = dynamic_cast<MenuScene *> (myScene)->getNextState();

		if (tempState == GFWSTATE::MENU)
			state = tempState;

		if (tempState == GFWSTATE::GAME) {
			state = tempState;
			delete myScene;
			myScene = new GameScene;
		}

		if (tempState == GFWSTATE::REPLAY) {
			if (std::ifstream("snakeRecordData.txt")) {
				state = tempState;
				delete myScene;
				myScene = new ReplayScene;
			}
		}
	}

	if (state == GFWSTATE::GAME)
	{
		if(!dynamic_cast<GameScene *> (myScene)->bActive){
			delete myScene;
			myScene = new MenuScene;
			state = GFWSTATE::MENU;
			system("cls");
		}

	}

	if (state == GFWSTATE::REPLAY)
	{

		if (dynamic_cast<ReplayScene *> (myScene)->bReturnMenu) {
			delete myScene;
			myScene = new MenuScene;
			state = GFWSTATE::MENU;
			system("cls");
		}
	}

	myScene->Animate(m_GameTimer.GetTimeElapsed());
	myScene->Render();
}