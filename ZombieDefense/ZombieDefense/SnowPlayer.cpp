#include "stdafx.h"
#include "SnowPlayer.h"

CSnowPlayer::CSnowPlayer(BOARD b)
{
	BitInfo = BITINFO{ "Player05" ,70,90,0,3,RGB(255, 0, 255) };
	Board = b;
	Board.rect.top += 10;
	FrameTime = 0.f;
	MaxFrameTime = 0.3f;
	Hp = MaxHp = 170;
	ExplosionState = ENUM_STATE::NON_STATE;
	Pos = Point{ float(Board.rect.left + 60),float(Board.rect.top + 20) };
	BulletTime = MaxBulletTime = 1.5f;
	bBulletCreate = false;
}

CSnowPlayer::~CSnowPlayer()
{
}

void CSnowPlayer::Create(HWND hWnd)
{
}

void CSnowPlayer::Draw(HDC hdc)
{
	CPlayer::Draw(hdc);
}

void CSnowPlayer::Update(const float ftime)
{
	CPlayer::Animate(ftime);
	CPlayer::CreateBulletUpdate(ftime);
}

void CSnowPlayer::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CSnowPlayer::Release()
{
}
