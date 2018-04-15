#include "StdAfx.h"
#include "GameObject.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
CGameObject::CGameObject() 
{ 
	m_pMesh = NULL; 
	m_xmf4x4World = Matrix4x4::Identity();					//월드 변환 행렬

	m_dwColor = RGB(0, 0, 0);								//오브젝트의 색갈

	m_xmf3MovingDirection = XMFLOAT3(0.0f, 0.0f, 1.0f);		//오브젝트의 방향 백터 (기본적으로 z축 바라보게)
	m_fMovingSpeed = 0.0f;									//속력
	m_fMovingRange = 0.0f;									//이동 거리

	m_xmf3RotationAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);		//좌표계 설정 설정
	m_fRotationSpeed = 0.05f;								
}

CGameObject::CGameObject(CMesh *pMesh) : CGameObject()		//매쉬 설정
{
	m_pMesh = pMesh; 
}

CGameObject::~CGameObject()									//소멸자
{
	if (m_pMesh) m_pMesh->Release();
}

void CGameObject::SetPosition(float x, float y, float z) // 위치 벡터 설정 (x,y,z로)
{
	m_xmf4x4World._41 = x; 
	m_xmf4x4World._42 = y; 
	m_xmf4x4World._43 = z; 
}

void CGameObject::SetPosition(XMFLOAT3& xmf3Position)	//위치 벡터 설정 // 벡터 값으
{ 
	m_xmf4x4World._41 = xmf3Position.x; 
	m_xmf4x4World._42 = xmf3Position.y; 
	m_xmf4x4World._43 = xmf3Position.z; 
}

XMFLOAT3 CGameObject::GetPosition()					//현제 위치 반환
{ 
	return(XMFLOAT3(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43)); 
}

XMFLOAT3 CGameObject::GetLook()						//현재 z축 방향 벡터 반환
{ 	
	XMFLOAT3 xmf3LookAt(m_xmf4x4World._31, m_xmf4x4World._32, m_xmf4x4World._33);
	xmf3LookAt = Vector3::Normalize(xmf3LookAt);
	return(xmf3LookAt);
}

XMFLOAT3 CGameObject::GetUp()						//현제 y축 방향 벡터 반환
{ 	
	XMFLOAT3 xmf3Up(m_xmf4x4World._21, m_xmf4x4World._22, m_xmf4x4World._23);
	xmf3Up = Vector3::Normalize(xmf3Up);
	return(xmf3Up);
}

XMFLOAT3 CGameObject::GetRight()					//현제 x축 방향 벡터 반환
{ 	
	XMFLOAT3 xmf3Right(m_xmf4x4World._11, m_xmf4x4World._12, m_xmf4x4World._13);
	xmf3Right = Vector3::Normalize(xmf3Right);
	return(xmf3Right);
}

void CGameObject::MoveStrafe(float fDistance)					//x축 이동 , 이동 방향과 x축을 내적하여 x축 이동 거리를 구하고 방향을 곱해줌
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Right = GetRight();
	xmf3Position = Vector3::Add(xmf3Position, Vector3::ScalarProduct(xmf3Right, fDistance));
	CGameObject::SetPosition(xmf3Position);
}

void CGameObject::MoveUp(float fDistance)						//y축 이동 , 이동 방향과 x축을 내적하여 x축 이동 거리를 구하고 방향을 곱해줌
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Up = GetUp();
	xmf3Position = Vector3::Add(xmf3Position, Vector3::ScalarProduct(xmf3Up, fDistance));
	CGameObject::SetPosition(xmf3Position);
}

void CGameObject::MoveForward(float fDistance)					//z축 이동 , 이동 방향과 x축을 내적하여 x축 이동 거리를 구하고 방향을 곱해줌
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3LookAt = GetLook();
	xmf3Position = Vector3::Add(xmf3Position, Vector3::ScalarProduct(xmf3LookAt, fDistance));
	CGameObject::SetPosition(xmf3Position);
}

void CGameObject::Rotate(float fPitch, float fYaw, float fRoll)								//x축 각도, y축 각도. z축 각도로 회전
{
	XMFLOAT4X4 mtxRotate = Matrix4x4::RotationYawPitchRoll(fYaw, fPitch, fRoll);
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

void CGameObject::Rotate(XMFLOAT3& xmf3RotationAxis, float fAngle)							//회전 벡터와 그곱으로 계산
{
	XMFLOAT4X4 mtxRotate = Matrix4x4::RotationAxis(xmf3RotationAxis, fAngle);
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

void CGameObject::Move(XMFLOAT3& vDirection, float fSpeed)									//이동
{
	SetPosition(m_xmf4x4World._41 + vDirection.x * fSpeed, m_xmf4x4World._42 + vDirection.y * fSpeed, m_xmf4x4World._43 + vDirection.z * fSpeed);
}

void CGameObject::Animate(float fElapsedTime)										//
{
	if (m_fRotationSpeed != 0.0f) Rotate(m_xmf3RotationAxis, m_fRotationSpeed * fElapsedTime);						//회전
	if (m_fMovingSpeed != 0.0f) Move(m_xmf3MovingDirection, m_fMovingSpeed * fElapsedTime);							//이동
	
	if (m_pMesh)																									//바운딩 박스 설정
	{
		m_pMesh->m_xmOOBB.Transform(m_xmOOBB, XMLoadFloat4x4(&m_xmf4x4World));
		XMStoreFloat4(&m_xmOOBB.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmOOBB.Orientation)));
	}
}

void CGameObject::Render(HDC hDCFrameBuffer, CCamera *pCamera)									//매쉬를 그리는 함수
{
	if (m_pMesh)
	{
		HPEN hPen = ::CreatePen(PS_SOLID, 0, m_dwColor);
		HPEN hOldPen = (HPEN)::SelectObject(hDCFrameBuffer, hPen);
		m_pMesh->Render(hDCFrameBuffer, m_xmf4x4World, pCamera);
		::SelectObject(hDCFrameBuffer, hOldPen);
		::DeleteObject(hPen);
	}
}

