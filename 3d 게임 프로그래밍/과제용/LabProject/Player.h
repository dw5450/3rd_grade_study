#pragma once

#include "GameObject.h"



class CBullet : public CGameObject
{
public:
	CBullet();
	virtual ~CBullet();

public:
	float	fElapseTime = 0.0f;								//��� �ð�.


};



class CPlayer : public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer();

	XMFLOAT3					m_xmf3Position;
	XMFLOAT3					m_xmf3Right;
	XMFLOAT3					m_xmf3Up;
	XMFLOAT3					m_xmf3Look;

	XMFLOAT3					m_xmf3CameraOffset;
	XMFLOAT3					m_xmf3Velocity;
	float						m_fFriction = 125.0f;

	float           			m_fPitch = 0.0f;
	float           			m_fYaw = 0.0f;
	float           			m_fRoll = 0.0f;

	CCamera						*m_pCamera = NULL;

	bool						m_bShotedBullet = false;
	float						m_fBulletCoolTime = -1.0f;
	CBullet						*m_pBullets[MAXBULLETNUM];

	void SetPosition(float x, float y, float z);
	void Move(DWORD dwDirection, float fDistance);
	void Move(XMFLOAT3& xmf3Shift, bool bUpdateVelocity);
	void Move(float x, float y, float z);
	void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f);
	void SetCameraOffset(XMFLOAT3& xmf3CameraOffset);
	void Animate(float fElapsedTime);
	void Update(float fTimeElapsed=0.016f);

	void ShotBullet(float fTimeElapsed);

	virtual void Render(HDC hDCFrameBuffer, CCamera *pCamera);
};

