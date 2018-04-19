#include "stdafx.h"
#include "Scene.h"
//����� �׸��ϴ�
//������Ʈ���� ����, ��ġ ��ŵ�ϴ�.
//�浹üũ�� �����մϴ�.

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

//������Ʈ���� �����մϴ�.
void CScene::BuildObjects()
{
	CExplosiveObject::PrepareExplosion();

	//������
	float fHalfWidth = 45.0f, fHalfHeight = 45.0f, fHalfDepth = 500.0f;									//1.0f �� 1m
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


	//ť�� ����
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

//������Ʈ ���� �����մϴ�.
void CScene::ReleaseObjects()
{

	if (m_ppObjects)
		for (int i = 0; i < m_nObjects; i++)
			delete m_ppObjects[i];

	if (m_pWallsObject) delete m_pWallsObject;
}

//�浹�� üũ�մϴ�.
void CScene::CheckObjectByObjectCollisions()
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->m_pObjectCollided = NULL;				//�⺻������ ��� �浹���� �ʾҴٰ� ����
	for (int i = 0; i < m_nObjects; i++)														//��� ������Ʈ�� �浹üũ�մϴ�. 
	{
		for (int j = (i + 1); j < m_nObjects; j++)
		{
			if (m_ppObjects[i]->m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB))					
			{
				m_ppObjects[i]->m_pObjectCollided = m_ppObjects[j];								//�浹�ҽ� ���θ� �浹�� ������Ʈ�� ������ �ְ� �Ǿ������.
				m_ppObjects[j]->m_pObjectCollided = m_ppObjects[i];	
			}
		}
	}

	//��� ������Ʈ���� �浹�ҽ� �ñ�� �����ص�
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
	for (int i = 0; i < m_nObjects; i++)																			//��� ������Ʈ�� ���ؼ� üũ
	{
		ContainmentType containType = m_pWallsObject->m_xmOOBB.Contains(m_ppObjects[i]->m_xmOOBB);					//������ �浹�� üũ
		switch (containType)
		{
		case DISJOINT:			//������ ���� ���
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
			if (nPlaneIndex != -1)					//�浹�ҽ�
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);			//������Ʈ�� ����� ���� �ݻ� ���͸� ����
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);					//������Ʈ�� �̵� ������ �ݻ� ���ͷ� �����Ŵ
			}
			break;
		}
		case INTERSECTS:						//�������?
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
		case CONTAINS:					//���Ե� ���
			break;
		}
	}
}

void CScene::CheckPlayerByWallCollisions()
{
	ContainmentType containType = m_pWallsObject->m_xmOOBB.Contains(m_pPlayer->m_xmOOBB);					//������ �浹�� üũ
	switch (containType)
	{
	case DISJOINT:			//������ ���� ���
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

		else if (nPlaneIndex < 6)					//�浹�ҽ�
		{
			m_pWallsObject->SetPosition(0.0f, 0.0f, m_pPlayer->GetPosition().z);
			break;
		}
		
		break;
	}
	case INTERSECTS:						//�������?
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

			else if (nPlaneIndex < 6)					//�浹�ҽ�
			{
				m_pWallsObject->SetPosition(0.0f, 0.0f, m_pPlayer->GetPosition().z);
				break;
			}
		}
	}
	case CONTAINS:					//���Ե� ���
		break;
	}
}

void CScene::CheckObjectByBulletCollisions()
{
	for (int i = 0; i < MAXBULLETNUM; i++) m_pPlayer->m_pBullets[i]->m_pObjectCollided = NULL;	//�⺻������ ��� �浹���� �ʾҴٰ� ����
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->m_pObjectCollided = NULL;

	for (int i = 0; i < MAXBULLETNUM; i++)														//��� ������Ʈ�� �浹üũ�մϴ�. 
	{
		if (m_pPlayer->m_pBullets[i]->m_bActive) {
			for (int j = 0; j < m_nObjects; j++)
			{
				CExplosiveObject * eo = (CExplosiveObject *)m_ppObjects[j];
				if (m_pPlayer->m_pBullets[i]->m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB) && m_ppObjects[j]->m_bActive && !eo->m_bBlowingUp)
				{
					m_pPlayer->m_pBullets[i]->m_pObjectCollided = m_ppObjects[j];								//�浹�ҽ� ���θ� �浹�� ������Ʈ�� ������ �ְ� �ȴ�.
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


	//���� �浹�Ͻ�
	CheckObjectByWallCollisions();
	CheckPlayerByWallCollisions();

	//������Ʈ���� �浹�ҽ�
	CheckObjectByObjectCollisions();

	//�Ѿ˰� �浹�ҽ�
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
