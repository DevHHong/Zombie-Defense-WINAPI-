#pragma once
#include "Player.h"
class CParabolaPlayer :
	public CPlayer
{
public:
	CParabolaPlayer(BOARD b);
	virtual ~CParabolaPlayer();

	virtual void Create(HWND hWnd) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(const float ftime) override;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Release()override;
};

