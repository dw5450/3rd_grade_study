// stdafx.h : ¿⁄¡÷ ªÁøÎ«œ¡ˆ∏∏ ¿⁄¡÷ ∫Ø∞Êµ«¡ˆ¥¬ æ ¥¬
// «•¡ÿ Ω√Ω∫≈€ ∆˜«‘ ∆ƒ¿œ π◊ «¡∑Œ¡ß∆Æ ∞¸∑√ ∆˜«‘ ∆ƒ¿œ¿Ã
// µÈæÓ ¿÷¥¬ ∆˜«‘ ∆ƒ¿œ¿‘¥œ¥Ÿ.
//

#pragma once

// æ∆∑° ¡ˆ¡§µ» «√∑ß∆˚ø° øÏº±«œ¥¬ «√∑ß∆˚¿ª ¥ÎªÛ¿∏∑Œ «œ¥¬ ∞ÊøÏ ¥Ÿ¿Ω ¡§¿«∏¶ ºˆ¡§«œΩ Ω√ø¿.
// ¥Ÿ∏• «√∑ß∆˚ø° ªÁøÎµ«¥¬ «ÿ¥Á ∞™¿« √÷Ω≈ ¡§∫∏¥¬ MSDN¿ª ¬¸¡∂«œΩ Ω√ø¿.
#ifndef WINVER				// Windows XP ¿ÃªÛø°º≠∏∏ ±‚¥…¿ª ªÁøÎ«“ ºˆ ¿÷Ω¿¥œ¥Ÿ.
#define WINVER 0x0501		// ¥Ÿ∏• πˆ¿¸¿« Windowsø° ∏¬µµ∑œ ¿˚«’«— ∞™¿∏∑Œ ∫Ø∞Ê«ÿ ¡÷Ω Ω√ø¿.
#endif

#ifndef _WIN32_WINNT		// Windows XP ¿ÃªÛø°º≠∏∏ ±‚¥…¿ª ªÁøÎ«“ ºˆ ¿÷Ω¿¥œ¥Ÿ.                   
#define _WIN32_WINNT 0x0501	// ¥Ÿ∏• πˆ¿¸¿« Windowsø° ∏¬µµ∑œ ¿˚«’«— ∞™¿∏∑Œ ∫Ø∞Ê«ÿ ¡÷Ω Ω√ø¿.
#endif						

#ifndef _WIN32_WINDOWS		// Windows 98 ¿ÃªÛø°º≠∏∏ ±‚¥…¿ª ªÁøÎ«“ ºˆ ¿÷Ω¿¥œ¥Ÿ.
#define _WIN32_WINDOWS 0x0410 // Windows Me ¿ÃªÛø° ∏¬µµ∑œ ¿˚«’«— ∞™¿∏∑Œ ∫Ø∞Ê«ÿ ¡÷Ω Ω√ø¿.
#endif

#ifndef _WIN32_IE			// IE 6.0 ¿ÃªÛø°º≠∏∏ ±‚¥…¿ª ªÁøÎ«“ ºˆ ¿÷Ω¿¥œ¥Ÿ.
#define _WIN32_IE 0x0600	// ¥Ÿ∏• πˆ¿¸¿« IEø° ∏¬µµ∑œ ¿˚«’«— ∞™¿∏∑Œ ∫Ø∞Ê«ÿ ¡÷Ω Ω√ø¿.
#endif

#define WIN32_LEAN_AND_MEAN		// ∞≈¿« ªÁøÎµ«¡ˆ æ ¥¬ ≥ªøÎ¿∫ Windows «Ï¥ıø°º≠ ¡¶ø‹«’¥œ¥Ÿ.
// Windows «Ï¥ı ∆ƒ¿œ:
#include <windows.h>

// C¿« ∑±≈∏¿” «Ï¥ı ∆ƒ¿œ¿‘¥œ¥Ÿ.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>
#include <random>

#include <d3d12.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>

#include <Mmsystem.h>

using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3d12.lib")

#define CLIENT_WIDTH			640
#define CLIENT_HEIGHT			480

#define DIR_FORWARD				0x01
#define DIR_BACKWARD			0x02
#define DIR_LEFT				0x04
#define DIR_RIGHT				0x08
#define DIR_UP					0x10
#define DIR_DOWN				0x20

#define RANDOM_COLOR			(0xFF000000 | ((rand() * 0xFFFFFF) / RAND_MAX))

#define EXPLOSION_DEBRISES		120


#define BULLET_NUM				20

#define PLAYER_SPEED				30.0f

#define MAXBULLETNUM				20
#define BULLETCOOLTIME				0.3f
#define BULLETSPEED					120.0f
#define BULLETLIMITTIME				1.0f

#define OBJECTRESPONTIME			1.0f

<<<<<<< HEAD



=======
>>>>>>> parent of 52a1b07... 0418 3d Í≥ºÏ†ú, ÎûúÎç§ Ï†Å ÏÉùÏÑ± Íµ¨ÌòÑ
namespace Vector3
{
	inline XMFLOAT3 XMVectorToFloat3(XMVECTOR& xmvVector)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, xmvVector);
		return(xmf3Result);
	}

	inline XMFLOAT3 ScalarProduct(XMFLOAT3& xmf3Vector, float fScalar, bool bNormalize = true)
	{
		XMFLOAT3 xmf3Result;
		if (bNormalize)
			XMStoreFloat3(&xmf3Result, XMVector3Normalize(XMLoadFloat3(&xmf3Vector)) * fScalar);
		else
			XMStoreFloat3(&xmf3Result, XMLoadFloat3(&xmf3Vector) * fScalar);
		return(xmf3Result);
	}

	inline XMFLOAT3 Add(const XMFLOAT3& xmf3Vector1, const XMFLOAT3& xmf3Vector2)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMLoadFloat3(&xmf3Vector1) + XMLoadFloat3(&xmf3Vector2));
		return(xmf3Result);
	}

	inline XMFLOAT3 Add(XMFLOAT3& xmf3Vector1, XMFLOAT3& xmf3Vector2, float fScalar)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMLoadFloat3(&xmf3Vector1) + (XMLoadFloat3(&xmf3Vector2) * fScalar));
		return(xmf3Result);
	}

	inline XMFLOAT3 Subtract(XMFLOAT3& xmf3Vector1, XMFLOAT3& xmf3Vector2)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMLoadFloat3(&xmf3Vector1) - XMLoadFloat3(&xmf3Vector2));
		return(xmf3Result);
	}

	inline float DotProduct(XMFLOAT3& xmf3Vector1, XMFLOAT3& xmf3Vector2)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMVector3Dot(XMLoadFloat3(&xmf3Vector1), XMLoadFloat3(&xmf3Vector2)));
		return(xmf3Result.x);
	}

	inline XMFLOAT3 CrossProduct(XMFLOAT3& xmf3Vector1, XMFLOAT3& xmf3Vector2, bool bNormalize = true)
	{
		XMFLOAT3 xmf3Result;
		if (bNormalize)
			XMStoreFloat3(&xmf3Result, XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&xmf3Vector1), XMLoadFloat3(&xmf3Vector2))));
		else
			XMStoreFloat3(&xmf3Result, XMVector3Cross(XMLoadFloat3(&xmf3Vector1), XMLoadFloat3(&xmf3Vector2)));
		return(xmf3Result);
	}

	inline XMFLOAT3 Normalize(XMFLOAT3& xmf3Vector)
	{
		XMFLOAT3 m_xmf3Normal;
		XMStoreFloat3(&m_xmf3Normal, XMVector3Normalize(XMLoadFloat3(&xmf3Vector)));
		return(m_xmf3Normal);
	}

	inline float Length(XMFLOAT3& xmf3Vector)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMVector3Length(XMLoadFloat3(&xmf3Vector)));
		return(xmf3Result.x);
	}

	inline float Angle(XMVECTOR& xmvVector1, XMVECTOR& xmvVector2)
	{
		XMVECTOR xmvAngle = XMVector3AngleBetweenNormals(xmvVector1, xmvVector2);
		return(XMConvertToDegrees(acosf(XMVectorGetX(xmvAngle))));
	}

	inline float Angle(XMFLOAT3& xmf3Vector1, XMFLOAT3& xmf3Vector2)
	{
		return(Angle(XMLoadFloat3(&xmf3Vector1), XMLoadFloat3(&xmf3Vector2)));
	}

	inline XMFLOAT3 TransformNormal(XMFLOAT3& xmf3Vector, XMMATRIX& xmxm4x4Transform)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMVector3TransformNormal(XMLoadFloat3(&xmf3Vector), xmxm4x4Transform));
		return(xmf3Result);
	}

	inline XMFLOAT3 TransformNormal(XMFLOAT3& xmf3Vector, XMFLOAT4X4& xmmtx4x4Matrix)
	{
		return(TransformNormal(xmf3Vector, XMLoadFloat4x4(&xmmtx4x4Matrix)));
	}

	inline XMFLOAT3 TransformCoord(XMFLOAT3& xmf3Vector, XMMATRIX& xmxm4x4Transform)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMVector3TransformCoord(XMLoadFloat3(&xmf3Vector), xmxm4x4Transform));
		return(xmf3Result);
	}

	inline XMFLOAT3 TransformCoord(XMFLOAT3& xmf3Vector, XMFLOAT4X4& xmmtx4x4Matrix)
	{
		return(TransformCoord(xmf3Vector, XMLoadFloat4x4(&xmmtx4x4Matrix)));
	}
}

namespace Vector4
{
	inline XMFLOAT4 Add(XMFLOAT4& xmf4Vector1, XMFLOAT4& xmf4Vector2)
	{
		XMFLOAT4 xmf4Result;
		XMStoreFloat4(&xmf4Result, XMLoadFloat4(&xmf4Vector1) + XMLoadFloat4(&xmf4Vector2));
		return(xmf4Result);
	}
}

namespace Matrix4x4
{
	inline XMFLOAT4X4 Identity()
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixIdentity());
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 Multiply(XMFLOAT4X4& xmmtx4x4Matrix1, XMFLOAT4X4& xmmtx4x4Matrix2)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMLoadFloat4x4(&xmmtx4x4Matrix1) * XMLoadFloat4x4(&xmmtx4x4Matrix2));
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 Multiply(XMFLOAT4X4& xmmtx4x4Matrix1, XMMATRIX& xmmtxMatrix2)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMLoadFloat4x4(&xmmtx4x4Matrix1) * xmmtxMatrix2);
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 Multiply(XMMATRIX& xmmtxMatrix1, XMFLOAT4X4& xmmtx4x4Matrix2)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, xmmtxMatrix1 * XMLoadFloat4x4(&xmmtx4x4Matrix2));
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 Multiply(XMMATRIX& xmmtxMatrix1, XMMATRIX& xmmtx4x4Matrix2)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, xmmtxMatrix1 * xmmtx4x4Matrix2);
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 RotationYawPitchRoll(float fPitch, float fYaw, float fRoll)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixRotationRollPitchYaw(XMConvertToRadians(fPitch), XMConvertToRadians(fYaw), XMConvertToRadians(fRoll)));
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 RotationAxis(XMFLOAT3& xmf3Axis, float fAngle)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixRotationAxis(XMLoadFloat3(&xmf3Axis), XMConvertToRadians(fAngle)));
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 Inverse(XMFLOAT4X4& xmmtx4x4Matrix)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixInverse(NULL, XMLoadFloat4x4(&xmmtx4x4Matrix)));
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 Transpose(XMFLOAT4X4& xmmtx4x4Matrix)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixTranspose(XMLoadFloat4x4(&xmmtx4x4Matrix)));
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 PerspectiveFovLH(float fFovAngleY, float fAspectRatio, float fNearZ, float fFarZ)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixPerspectiveFovLH(XMConvertToRadians(fFovAngleY), fAspectRatio, fNearZ, fFarZ));
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 LookAtLH(XMFLOAT3& xmf3EyePosition, XMFLOAT3& xmf3LookAtPosition, XMFLOAT3& xmf3UpDirection)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixLookAtLH(XMLoadFloat3(&xmf3EyePosition), XMLoadFloat3(&xmf3LookAtPosition), XMLoadFloat3(&xmf3UpDirection)));
		return(xmmtx4x4Result);
	}
}

namespace Triangle
{
	inline bool Intersect(XMFLOAT3& xmf3RayPosition, XMFLOAT3& xmf3RayDirection, XMFLOAT3& v0, XMFLOAT3& v1, XMFLOAT3& v2, float& fHitDistance)
	{
		return(TriangleTests::Intersects(XMLoadFloat3(&xmf3RayPosition), XMLoadFloat3(&xmf3RayDirection), XMLoadFloat3(&v0), XMLoadFloat3(&v1), XMLoadFloat3(&v2), fHitDistance));
	}
}

namespace Plane
{
	inline XMFLOAT4 Normalize(XMFLOAT4& xmf4Plane)
	{
		XMFLOAT4 xmf4Result;
		XMStoreFloat4(&xmf4Result, XMPlaneNormalize(XMLoadFloat4(&xmf4Plane)));
		return(xmf4Result);
	}
}
