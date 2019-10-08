#pragma once
#include "GameObj.h"
#include "Explosion.h"
class CBullet :
	public CGameObj
{
protected:
	float radian;
	CExplosion Explosion;
public:
	CBullet();
	virtual ~CBullet();

	virtual void Create(HWND hWnd) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(const float ftime) override;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Release()override;
};

