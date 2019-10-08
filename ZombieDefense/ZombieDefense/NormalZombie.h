#pragma once
#include "Zombie.h"
class CNormalZombie :
	public CZombie
{
public:
	CNormalZombie(BOARD b, ENUM_LEVEL level);
	virtual ~CNormalZombie();

	virtual void Create(HWND hWnd) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(const float ftime) override;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Release()override;

	virtual void StateChainge(ENUM_ANIM_STATE& state)override;
};

