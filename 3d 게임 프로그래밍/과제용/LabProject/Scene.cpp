#include "stdafx.h"
#include "Scene.h"
//장면을 그립니다
//오브젝트들을 생성, 위치 시킵니다.
//충돌체크를 실행합니다.

CScene::CScene()
{

}

CScene::~CScene()
{
}

void CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

//오브젝트들을 생성합니다.
void CScene::BuildObjects()
{
	CExplosiveObject::PrepareExplosion();

	//벽설정
	float fHalfWidth = 45.0f, fHalfHeight = 45.0f, fHalfDepth = 500.0f;									//1.0f 당 1m
	CWallMesh *pWallCubeMesh = new CWallMesh(fHalfWidth * 2.0f, fHalfHeight * 2.0f, fHalfDepth * 2.0f, 20);
	pWallCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth * 0.1f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_pWallsObject = new CWallsObject();
	m_pWallsObject->SetPosition(0.0f, 0.0f, 0.0f);
	m_pWallsObject->SetMesh(pWallCubeMesh);
	m_pWallsObject->SetColor(RGB(0, 0, 0));
	m_pWallsObject->m_pxmf4WallPlanes[0] = XMFLOAT4(+1.0f, 0.0f, 0.0f, fHalfWidth);
	m_pWallsObject->m_pxmf4WallPlanes[1] = XMFLOAT4(-1.0f, 0.0f, 0.0f, fHalfWidth);
	m_pWallsObject->m_pxmf4WallPlanes[2] = XMFLOAT4(0.0f, +1.0f, 0.0f, fHalfHeight);
	m_pWallsObject->m_pxmf4WallPlanes[3] = XMFLOAT4(0.0f, -1.0f, 0.0f, fHalfHeight);
	m_pWallsObject->m_pxmf4WallPlanes[4] = XMFLOAT4(0.0f, 0.0f, +1.0f, 10);
	m_pWallsObject->m_pxmf4WallPlanes[5] = XMFLOAT4(0.0f, 0.0f, -1.0f, 10);


	//큐브 설정
	CCubeMesh *pObjectCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);
	pObjectCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_nObjects = 30;
	m_ppObjects = new CGameObject*[m_nObjects];

	for (int i = 0; i < m_nObjects; i++) {
		m_ppObjects[i] = new CExplosiveObject();
		m_ppObjects[i]->m_bActive = false;
		m_ppObjects[i]->SetMesh(pObjectCubeMesh);
		m_ppObjects[i]->SetColor(RGB(35, 120, 35));
		m_ppObjects[i]->SetPosition(1000.0f, 1000.0f, 1000.0f);
		//m_ppObjects[i]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
		m_ppObjects[i]->SetRotationSpeed(90.0f);
		//m_ppObjects[i]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));*/
		m_ppObjects[i]->SetMovingSpeed(10.5f);
	}

	
}

//오브젝트 들을 삭제합니다.
void CScene::ReleaseObjects()
{

	if (m_ppObjects)
		for (int i = 0; i < m_nObjects; i++)
			delete m_ppObjects[i];

	if (m_pWallsObject) delete m_pWallsObject;
}

//충돌을 체크합니다.
void CScene::CheckObjectByObjectCollisions()
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->m_pObjectCollided = NULL;				//기본적으로 모두 충돌하지 않았다고 가정
	for (int i = 0; i < m_nObjects; i++)														//모든 오브젝트들 충돌체크합니다. 
	{
		for (int j = (i + 1); j < m_nObjects; j++)
		{
			if (m_ppObjects[i]->m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB))					
			{
				m_ppObjects[i]->m_pObjectCollided = m_ppObjects[j];								//충돌할시 서로를 충돌한 오브젝트로 가지고 있게 되어지빈다.
				m_ppObjects[j]->m_pObjectCollided = m_ppObjects[i];	
			}
		}
	}

	//모든 오브젝트들이 충돌할시 팅기게 설정해둠
	for (int i = 0; i < m_nObjects; i++)
	{
		if (m_ppObjects[i]->m_pObjectCollided)
		{
			XMFLOAT3 xmf3MovingDirection = m_ppObjects[i]->m_xmf3MovingDirection;
			float fMovingSpeed = m_ppObjects[i]->m_fMovingSpeed;
			m_ppObjects[i]->m_xmf3MovingDirection = m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection;
			m_ppObjects[i]->m_fMovingSpeed = m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection = xmf3MovingDirection;
			m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed = fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_pObjectCollided = NULL;
			m_ppObjects[i]->m_pObjectCollided = NULL;
		}
	}
}

void CScene::CheckObjectByWallCollisions()
{
	for (int i = 0; i < m_nObjects; i++)																			//모든 오브젝트에 대해서 체크
	{
		ContainmentType containType = m_pWallsObject->m_xmOOBB.Contains(m_ppObjects[i]->m_xmOOBB);					//벽으로 충돌을 체크
		switch (containType)
		{
		case DISJOINT:			//만나지 않을 경우
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
				if (intersectType == BACK)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)					//충돌할시
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);			//오브젝트의 방향과 벽의 반사 벡터를 구함
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);					//오브젝트의 이동 방향을 반사 벡터로 적용시킴
			}
			break;
		}
		case INTERSECTS:						//만날경우?
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
				if (intersectType == INTERSECTING)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case CONTAINS:					//포함될 경우
			break;
		}
	}
}

void CScene::CheckPlayerByWallCollisions()
{
	ContainmentType containType = m_pWallsObject->m_xmOOBB.Contains(m_pPlayer->m_xmOOBB);					//벽으로 충돌을 체크
	switch (containType)
	{
	case DISJOINT:			//만나지 않을 경우
	{
		int nPlaneIndex = -1;
		for (int j = 0; j < 6; j++)
		{
			PlaneIntersectionType intersectType = m_pPlayer->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
			if (intersectType == BACK)
			{
				nPlaneIndex = j;
				break;
			}
		}
		if (nPlaneIndex < 0 )
			break;

		else if (nPlaneIndex < 4) {
			m_pPlayer->m_xmf3Position = XMFLOAT3(0, 0, m_pPlayer->GetPosition().z);
			XMVECTOR look = XMLoadFloat3(&m_pPlayer->m_xmf3Look);
			XMVECTOR up = XMLoadFloat3(&m_pPlayer->m_xmf3Up);
			XMVECTOR position = XMLoadFloat3(&m_pPlayer->m_xmf3Position);
			XMStoreFloat3(&m_pPlayer->m_pCamera->m_xmf3Position, position + (-15 * look) + ( 5 * up));
		}

		else if (nPlaneIndex < 6)					//충돌할시
		{
			m_pWallsObject->SetPosition(0.0f, 0.0f, m_pPlayer->GetPosition().z);
			break;
		}
		
		break;
	}
	case INTERSECTS:						//만날경우?
	{
		int nPlaneIndex = -1;
		for (int j = 0; j < 6; j++)
		{
			PlaneIntersectionType intersectType = m_pPlayer->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
			if (intersectType == INTERSECTING)
			{
				nPlaneIndex = j;
				break;
			}
		}
		for (int j = 0; j < 6; j++)
		{
			PlaneIntersectionType intersectType = m_pPlayer->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
			if (intersectType == BACK)
			{
				nPlaneIndex = j;
				break;
			}
			if (nPlaneIndex < 0)
				break;

			else if (nPlaneIndex < 4) {
				m_pPlayer->m_xmf3Position = XMFLOAT3(0, 0, m_pPlayer->GetPosition().z);
				XMVECTOR look = XMLoadFloat3(&m_pPlayer->m_xmf3Look);
				XMVECTOR up = XMLoadFloat3(&m_pPlayer->m_xmf3Up);
				XMVECTOR position = XMLoadFloat3(&m_pPlayer->m_xmf3Position);
				XMStoreFloat3(&m_pPlayer->m_pCamera->m_xmf3Position, position + (-15 * look) + (5 * up));
			}

			else if (nPlaneIndex < 6)					//충돌할시
			{
				m_pWallsObject->SetPosition(0.0f, 0.0f, m_pPlayer->GetPosition().z);
				break;
			}
		}
	}
	case CONTAINS:					//포함될 경우
		break;
	}
}

void CScene::CheckObjectByBulletCollisions()
{
	for (int i = 0; i < MAXBULLETNUM; i++) m_pPlayer->m_pBullets[i]->m_pObjectCollided = NULL;	//기본적으로 모두 충돌하지 않았다고 가정
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->m_pObjectCollided = NULL;

	for (int i = 0; i < MAXBULLETNUM; i++)														//모든 오브젝트들 충돌체크합니다. 
	{
		if (m_pPlayer->m_pBullets[i]->m_bActive) {
			for (int j = 0; j < m_nObjects; j++)
			{
				CExplosiveObject * eo = (CExplosiveObject *)m_ppObjects[j];
				if (m_pPlayer->m_pBullets[i]->m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB) && m_ppObjects[j]->m_bActive && !eo->m_bBlowingUp)
				{
					m_pPlayer->m_pBullets[i]->m_pObjectCollided = m_ppObjects[j];								//충돌할시 서로를 충돌한 오브젝트로 가지고 있게 된다.
					m_pPlayer->m_pBullets[i]->m_bActive = false;
					m_ppObjects[j]->m_pObjectCollided = m_pPlayer->m_pBullets[i];
				}
			}
		}
	}

	for (int i = 0; i < m_nObjects; i++)
	{
		if (m_ppObjects[i]->m_pObjectCollided)
		{
			CExplosiveObject *pExplosiveObject = (CExplosiveObject *)m_ppObjects[i];
			pExplosiveObject->m_bBlowingUp = true;
		}
	}
}


void CScene::Animate(float fElapsedTime)
{

	TracingPlayer(fElapsedTime);

	m_pWallsObject->Animate(fElapsedTime);
	m_pPlayer->Animate(fElapsedTime);
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Animate(fElapsedTime);


	//벽과 충돌하시
	CheckObjectByWallCollisions();
	CheckPlayerByWallCollisions();

	//오브젝트끼리 충돌할시
	CheckObjectByObjectCollisions();

	//총알과 충돌할시
	CheckObjectByBulletCollisions();

	ResponEnemy(fElapsedTime);
}

void CScene::Render(HDC hDCFrameBuffer, CCamera *pCamera)
{
	m_pWallsObject->Render(hDCFrameBuffer, pCamera);

	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);
}

void CScene::ResponEnemy(float fElapsedTime)
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> ufr(-WALL_HALF_SIZE, WALL_HALF_SIZE);
	std::uniform_real_distribution<float> ufrRotaionAngle(0.0f, 360.0f);

	m_iObjectResponTime += fElapsedTime;
	for (int i = 0; i < m_nObjects; i++) {
		if (m_iObjectResponTime > OBJECTRESPONTIME) {
			if (!m_ppObjects[i]->m_bActive) {
				m_ppObjects[i]->m_bActive = true;
				m_ppObjects[i]->SetPosition(XMFLOAT3(ufr(dre), ufr(dre), m_pPlayer->GetPosition().z +145 + ufr(dre)));
				m_ppObjects[i]->SetPosition(XMFLOAT3(ufr(dre), ufr(dre), m_pPlayer->GetPosition().z + 145 + ufr(dre)));
				m_ppObjects[i]->SetRotationAxis(XMFLOAT3(ufrRotaionAngle(dre), ufrRotaionAngle(dre), ufrRotaionAngle(dre)));
				m_iObjectResponTime = 0;
				break;
			}

		}
	}
}

void CScene::TracingPlayer(float fElapsedTime)
{
	for (int i = 0; i < m_nObjects; i++)
	{
		if (m_ppObjects[i]->m_bActive)
			m_ppObjects[i]->SetMovingDirection(Vector3::Subtract(m_pPlayer->GetPosition(), m_ppObjects[i]->GetPosition()));
	}
}
