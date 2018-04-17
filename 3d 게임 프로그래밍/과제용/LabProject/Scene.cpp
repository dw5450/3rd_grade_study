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
	m_pWallsObject->m_pxmf4WallPlanes[4] = XMFLOAT4(0.0f, 0.0f, +1.0f, fHalfDepth);
	m_pWallsObject->m_pxmf4WallPlanes[5] = XMFLOAT4(0.0f, 0.0f, -1.0f, fHalfDepth);


	//ť�� ����
	CCubeMesh *pObjectCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);
	pObjectCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_nObjects = 30;
	m_ppObjects = new CGameObject*[m_nObjects];

	for (int i = 0; i < m_nObjects; i++) {
		m_ppObjects[i] = new CExplosiveObject();
		m_ppObjects[i]->m_bActive = false;
		m_ppObjects[i]->SetMesh(pObjectCubeMesh);
		m_ppObjects[i]->SetColor(RGB(255, 0, 0));
		m_ppObjects[i]->SetPosition(1000.0f, 1000.0f, 1000.0f);
		m_ppObjects[i]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
		m_ppObjects[i]->SetRotationSpeed(90.0f);
		m_ppObjects[i]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
		m_ppObjects[i]->SetMovingSpeed(10.5f);
	}

	
}

//������Ʈ ���� �����մϴ�.
void CScene::ReleaseObjects()
{
	for (int i = 0; i < m_nObjects; i++) if (m_ppObjects[i]) delete m_ppObjects[i];
	if (m_ppObjects) delete[] m_ppObjects;

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

void CScene::CheckObjectByBulletCollisions()
{
	for (int i = 0; i < MAXBULLETNUM; i++) m_pPlayer->m_pBullets[i]->m_pObjectCollided = NULL;				//�⺻������ ��� �浹���� �ʾҴٰ� ����
	
	for (int i = 0; i < MAXBULLETNUM; i++)														//��� ������Ʈ�� �浹üũ�մϴ�. 
	{
		if (m_pPlayer->m_pBullets[i]->bShoted) {
			for (int j = 0; j < m_nObjects; j++)
			{
				if (m_pPlayer->m_pBullets[i]->m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB))
				{
					m_pPlayer->m_pBullets[i]->m_pObjectCollided = m_ppObjects[j];								//�浹�ҽ� ���θ� �浹�� ������Ʈ�� ������ �ְ� �ȴ�.
					m_ppObjects[j]->m_pObjectCollided = m_pPlayer->m_pBullets[i];
				}
			}
		}
	}

	for (int i = 0; i < m_nObjects; i++)
	{
		if (m_ppObjects[i]->m_pObjectCollided)
		{
			m_ppObjects[i]->m_bActive = false;
			CExplosiveObject *pExplosiveObject = (CExplosiveObject *)m_ppObjects[i];
			pExplosiveObject->m_bBlowingUp = true;
		}
	}

	for (int i = 0; i < MAXBULLETNUM; i++) {
		if (m_pPlayer->m_pBullets[i]->m_pObjectCollided)
		{
			m_pPlayer->m_pBullets[i]->SetPosition(XMFLOAT3(-1000, -1000, -1000));
			m_pPlayer->m_pBullets[i]->m_pObjectCollided = NULL;
		}

	}
}


void CScene::Animate(float fElapsedTime)
{
	m_pWallsObject->Animate(fElapsedTime);
	if (m_pWallsObject->m_xmOOBB.Contains(XMLoadFloat3(&m_pPlayer->m_xmf3Position)) == DISJOINT) m_pWallsObject->SetPosition(m_pPlayer->m_xmf3Position);

	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Animate(fElapsedTime);

	CheckObjectByWallCollisions();

	CheckObjectByObjectCollisions();

	CheckObjectByBulletCollisions();

	m_iObjectResponTime += fElapsedTime;
	for (int i = 0; i < m_nObjects; i++) {
		if (m_iObjectResponTime > OBJECTRESPONTIME) {
			if (!m_ppObjects[i]->m_bActive) {
				m_ppObjects[i]->m_bActive = true;
				m_ppObjects[i]->SetPosition(XMFLOAT3(0.0f, -10.0f, -10 * i));
				m_iObjectResponTime = 0;
				break;
			}
			
		}
	}
}

void CScene::Render(HDC hDCFrameBuffer, CCamera *pCamera)
{
	m_pWallsObject->Render(hDCFrameBuffer, pCamera);

	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);
}
