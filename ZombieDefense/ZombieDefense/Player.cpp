#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Create(HWND hWnd)
{


}

void CPlayer::Draw(HDC hdc)
{
	TransparentBlt(hdc, Board.rect.left, Board.rect.top,
		BitInfo.sizex, BitInfo.sizey, (*m_pMapBmp)[BitInfo.ID]->GetMemDC(),
		BitInfo.curFrame * BitInfo.sizex, 0, BitInfo.sizex, BitInfo.sizey, BitInfo.color);

	if (ExplosionState == ENUM_STATE::EXPLOSION_STATE)
		Explosion.EffectDraw(hdc, Board.rect.left, Board.rect.top, BitInfo.sizey);

	HpDraw(hdc);
}

void CPlayer::Update(const float ftime)
{
	
}

void CPlayer::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CPlayer::Release()
{
}

void CPlayer::Init()
{
}

void CPlayer::Animate(const float ftime)
{
	FrameTime += ftime;
	if (FrameTime > MaxFrameTime)
	{
		BitInfo.curFrame = (++BitInfo.curFrame) % BitInfo.maxFrame;
		FrameTime = 0.f;
	}

	if (ExplosionState == ENUM_STATE::EXPLOSION_STATE)
		ExplosionState = Explosion.StateUpdate(ftime);
}

void CPlayer::HpDraw(HDC hdc)
{
	HBRUSH m_br = CreateSolidBrush(RGB(1, 1, 255));
	HBITMAP Ahbmp = CreateCompatibleBitmap(hdc, 100, 100);
	HDC Ahdc = CreateCompatibleDC(hdc);
	HBITMAP Aoldbmp = (HBITMAP)SelectObject(Ahdc, Ahbmp);
	auto oldbr = SelectObject(Ahdc, m_br);
	Rectangle(Ahdc, 0, 0, 100, 100);
	SelectObject(Ahdc, oldbr);
	BLENDFUNCTION bf;

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = 150;

	float hpRate = Hp / MaxHp;			// 현재 hp 비율
	float start = 0;					// 시작 점
	float end = 80;						// 끝점
	int curHp = int(start * (1.f - hpRate) + end * hpRate);		// 선형보간법 공식

	AlphaBlend(hdc, Board.rect.left, Board.rect.bottom - 10, curHp, 10, Ahdc, 0, 0, 50, 50, bf);
	SelectObject(Ahdc, Aoldbmp);
	DeleteObject(m_br);
	DeleteObject(Ahbmp);
	DeleteDC(Ahdc);
}

void CPlayer::CreateBulletUpdate(const float ftime)
{
	BulletTime += ftime;
	if (BulletTime > MaxBulletTime)
	{
		bBulletCreate = true;
		BulletTime = 0.f;
	}
	else
		bBulletCreate = false;
}
