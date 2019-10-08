#include "stdafx.h"
#include "SnowBullet.h"


CSnowBullet::CSnowBullet(Point pos)
{
	BitInfo = BITINFO{ "Bullet02" ,35,35,0,0,RGB(255, 0, 255) };
	Pos = pos;
	radian = float(BitInfo.sizex / 2);
	ExplosionState = ENUM_STATE::NON_STATE;
	Attack = 15;
}

CSnowBullet::~CSnowBullet()
{
}

void CSnowBullet::Create(HWND hWnd)
{
}

void CSnowBullet::Draw(HDC hdc)
{
	CBullet::Draw(hdc);
}

void CSnowBullet::Update(const float ftime)
{
	CBullet::Update(ftime);
}

void CSnowBullet::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CSnowBullet::Release()
{
}
