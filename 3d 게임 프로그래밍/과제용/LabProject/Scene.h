#pragma once

#include "GameObject.h"
#include "Player.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

	CPlayer						*m_pPlayer = NULL;

	int							m_nObjects = 0;
	CGameObject					**m_ppObjects = NULL;
	float						m_iObjectResponTime = 0;


	CWallsObject				*m_pWallsObject = NULL;

public:		//오브젝트를 생성, 소멸
	virtual void BuildObjects();							//오브젝트들을 생성합니다.
	virtual void ReleaseObjects();							//오브젝트들을 소멸시킵니다.

public:		//오브젝트들의 충돌체크
	virtual void CheckObjectByObjectCollisions();			//오브젝트들끼리의 충돌을 체크합니다.
	virtual void CheckObjectByWallCollisions();				//벽과의 충돌을 체크합니다.
	virtual void CheckObjectByBulletCollisions();			//총알과 오브젝트의 충돌을 체크합니다.

public:		//오브젝트들의 변화, 그리기
	virtual void Animate(float fElapsedTime);				//오브젝트들의 변화를 표시합니다.
	virtual void Render(HDC hDCFrameBuffer, CCamera *pCamera);	//오브젝트들을 화면에 그립니다.

	void ResponEnemy(float fElapsedTime);					//적들을 재생성 합니다.

public:		//마우스, 키보드 입력 처리
	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);


};

