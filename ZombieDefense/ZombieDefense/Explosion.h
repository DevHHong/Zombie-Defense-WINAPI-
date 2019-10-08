#pragma once
#include "GameObj.h"
class CExplosion :
	public CGameObj
{
public:
	CExplosion();
	virtual ~CExplosion();

	virtual void Create(HWND hWnd) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(const float ftime) override;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Release()override;

	ENUM_STATE StateUpdate(const float ftime);
	void EffectDraw(HDC hdc, int posx, int posy, int size);
};

