#pragma once
#include "Player.h"
class CBombPlayer :
	public CPlayer
{
	RECT BombRange;
	DWORD alphaColor;
	ENUM_MOUSESOUND Sound;
public:
	CBombPlayer(BOARD b);
	virtual ~CBombPlayer();

	virtual void Create(HWND hWnd) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(const float ftime) override;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Release()override;

	RECT GetBombRect()const { return BombRange; }
	void SetRedColor() { alphaColor = RGB(255, 0, 0); }
	ENUM_MOUSESOUND GetBombSound()const { return Sound; }
	void SetBombSound(ENUM_MOUSESOUND b) { Sound = b; }
private:
	void BombRangeAlphaDraw(HDC hdc);
};

