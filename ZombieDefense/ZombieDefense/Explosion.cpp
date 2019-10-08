#include "stdafx.h"
#include "Explosion.h"


CExplosion::CExplosion()
{
	BitInfo = BITINFO{ "Explosion" ,60,60,0,6,RGB(0, 0, 0) };
	MaxFrameTime = 0.15f;
	FrameTime = 0;
}

CExplosion::~CExplosion()
{
}

void CExplosion::Create(HWND hWnd)
{
}

void CExplosion::Draw(HDC hdc)
{
}

void CExplosion::Update(const float ftime)
{
	
}

void CExplosion::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CExplosion::Release()
{
}

ENUM_STATE CExplosion::StateUpdate(const float ftime)
{
	FrameTime += ftime;
	if (FrameTime > MaxFrameTime)
	{
		if (++BitInfo.curFrame > BitInfo.maxFrame)
			return ENUM_STATE::DELETE_STATE;
		FrameTime = 0.f;
	}
	return ENUM_STATE::EXPLOSION_STATE;
}

void CExplosion::EffectDraw(HDC hdc, int posx, int posy, int size)
{
	TransparentBlt(hdc, posx, posy,
		size, size, (*m_pMapBmp)[BitInfo.ID]->GetMemDC(),
		BitInfo.curFrame * BitInfo.sizex, 0, BitInfo.sizex, BitInfo.sizey, BitInfo.color);
}