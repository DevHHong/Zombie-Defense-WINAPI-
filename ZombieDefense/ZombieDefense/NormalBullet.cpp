#include "stdafx.h"
#include "NormalBullet.h"


CNormalBullet::CNormalBullet(Point pos)
{
	BitInfo = BITINFO{ "Bullet01" ,36,36,0,0,RGB(255, 0, 255) };
	Pos = pos;
	radian = float(BitInfo.sizex / 2);
	ExplosionState = ENUM_STATE::NON_STATE;
	Attack = 10;
}


CNormalBullet::~CNormalBullet()
{
}

void CNormalBullet::Create(HWND hWnd)
{
}

void CNormalBullet::Draw(HDC hdc)
{
	CBullet::Draw(hdc);
}

void CNormalBullet::Update(const float ftime)
{
	CBullet::Update(ftime);
}

void CNormalBullet::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CNormalBullet::Release()
{
}
