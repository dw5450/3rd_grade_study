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

public:		//������Ʈ�� ����, �Ҹ�
	virtual void BuildObjects();							//������Ʈ���� �����մϴ�.
	virtual void ReleaseObjects();							//������Ʈ���� �Ҹ��ŵ�ϴ�.

public:		//������Ʈ���� �浹üũ
	virtual void CheckObjectByObjectCollisions();			//������Ʈ�鳢���� �浹�� üũ�մϴ�.
	virtual void CheckObjectByWallCollisions();				//������ �浹�� üũ�մϴ�.
	virtual void CheckObjectByBulletCollisions();			//�Ѿ˰� ������Ʈ�� �浹�� üũ�մϴ�.

public:		//������Ʈ���� ��ȭ, �׸���
	virtual void Animate(float fElapsedTime);				//������Ʈ���� ��ȭ�� ǥ���մϴ�.
	virtual void Render(HDC hDCFrameBuffer, CCamera *pCamera);	//������Ʈ���� ȭ�鿡 �׸��ϴ�.

	void ResponEnemy(float fElapsedTime);					//������ ����� �մϴ�.

public:		//���콺, Ű���� �Է� ó��
	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);


};

