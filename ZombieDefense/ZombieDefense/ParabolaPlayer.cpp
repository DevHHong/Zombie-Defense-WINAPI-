#include "stdafx.h"
#include "ParabolaPlayer.h"

CParabolaPlayer::CParabolaPlayer(BOARD b)
{
	BitInfo = BITINFO{ "Player06" ,70,90,0,3,RGB(255, 0, 255) };
	Board = b;
	Board.rect.top += 10;
	FrameTime = 0.f;
	MaxFrameTime = 0.3f;
	Hp = MaxHp = 170;
	Pos = Point{ float(Board.rect.left + 60),float(Board.rect.top + 20) };
	BulletTime = MaxBulletTime = 1.5f;
	ExplosionState = ENUM_STATE::NON_STATE;
	bBulletCreate = false;
}

CParabolaPlayer::~CParabolaPlayer()
{
}

void CParabolaPlayer::Create(HWND hWnd)
{
}

void CParabolaPlayer::Draw(HDC hdc)
{
	CPlayer::Draw(hdc);
}

void CParabolaPlayer::Update(const float ftime)
{
	CPlayer::Animate(ftime);
	CPlayer::CreateBulletUpdate(ftime);
}

void CParabolaPlayer::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CParabolaPlayer::Release()
{
}
