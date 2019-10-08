#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

void CBullet::Create(HWND hWnd)
{
}

void CBullet::Draw(HDC hdc)
{
	if (ExplosionState == ENUM_STATE::NON_STATE)
	{
		TransparentBlt
		(
			hdc, int(Pos.x - radian), int(Pos.y - radian), BitInfo.sizex, BitInfo.sizey
			, (*m_pMapBmp)[BitInfo.ID]->GetMemDC(), 0, 0, BitInfo.sizex, BitInfo.sizey, BitInfo.color
		);
	}
	else if (ExplosionState == ENUM_STATE::EXPLOSION_STATE)
		Explosion.EffectDraw(hdc, int(Pos.x - radian), int(Pos.y - radian), int(radian*2));
}

void CBullet::Update(const float ftime)
{
	if (ExplosionState == ENUM_STATE::NON_STATE)
		Pos.x += ftime * 100;
	else if (ExplosionState == ENUM_STATE::EXPLOSION_STATE)
		ExplosionState = Explosion.StateUpdate(ftime);

}

void CBullet::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CBullet::Release()
{
}
