#pragma once
#include "stdafx.h"

class GameFrameWork
{
private:
	size_t state = GFWSTATE::MENU;
	Scene * myScene;
	CGameTimer					m_GameTimer;

public:
	size_t getState() const { return state; }
	

public:
	GameFrameWork();
	~GameFrameWork();

	void FrameAdvance();

};

