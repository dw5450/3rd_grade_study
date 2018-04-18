#pragma once

struct VIEWPORT
{
	int							m_xStart;
	int							m_yStart;
	int							m_nWidth;
	int							m_nHeight;
};

class CPlayer;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CCamera
{
public:
	CCamera();
	virtual ~CCamera();

	XMFLOAT3					m_xmf3Position;
	XMFLOAT3					m_xmf3Right;
	XMFLOAT3					m_xmf3Up;
	XMFLOAT3					m_xmf3Look;

	XMFLOAT4X4					m_xmf4x4View;
	XMFLOAT4X4					m_xmf4x4Projection;
	XMFLOAT4X4					m_xmf4x4ViewProject;

	VIEWPORT					m_Viewport;


public:		//변환 행렬 생성 
	void GenerateViewMatrix();						//카메라 변환 행렬 생성
	void GenerateProjectionMatrix(float fNearPlaneDistance, float fFarPlaneDistance, float fFOVAngle);	//투영 변환 행렬 설정
	
public:		//카메라 변환 행렬 생성을 위한 설정 
	void SetViewport(int xStart, int yStart, int nWidth, int nHeight);	//화면 크기 설정
	void SetLookAt(XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up);				//바라보는 방향 설정
	void SetLookAt(XMFLOAT3& vPosition, XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up);	//바라보는 방향 설정

public:		//카메라의 변경점을 적용 
	void Move(XMFLOAT3& xmf3Shift);				//카메라의 이동
	void Move(float x, float y, float z);		//카메라의 이동
	void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f);		//카메라의 회전
	void Update(CPlayer *pPlayer, XMFLOAT3& xmf3LookAt, float fTimeElapsed = 0.016f);	//변경점 적용
};


