#include "stdafx.h"
#include "ParabolaBullet.h"


CParabolaBullet::CParabolaBullet(Point pos, RECT rect)
{
	BitInfo = BITINFO{ "Bullet03" ,40,40,0,0,RGB(255, 0, 255) };
	Pos = pos;
	radian = float(BitInfo.sizex / 2);
	ExplosionState = ENUM_STATE::NON_STATE;
	Attack = 30;

	// ±¸Çö
	Angle = 180;
	Start = pos;
	End = Point{ float(rect.left+10) ,float(rect.top) };
	distance = (End.x - Start.x) / 2;
}

CParabolaBullet::~CParabolaBullet()
{
}

void CParabolaBullet::Create(HWND hWnd)
{

}

void CParabolaBullet::Draw(HDC hdc)
{
	CBullet::Draw(hdc);
}

void CParabolaBullet::Update(const float ftime)
{
	if (ExplosionState == ENUM_STATE::NON_STATE)
	{
		Angle += ftime * 150;
		if (Angle > 360)
			ExplosionState = ENUM_STATE::EXPLOSION_STATE;
		Pos.x = (Start.x) + cos(Angle*PI / 180) * distance + distance;
		Pos.y = Start.y + sin(Angle*PI / 180) * 150;
	}
		
	else if (ExplosionState == ENUM_STATE::EXPLOSION_STATE)
		ExplosionState = Explosion.StateUpdate(ftime);
}

void CParabolaBullet::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CParabolaBullet::Release()
{
}
