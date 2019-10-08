#include "stdafx.h"
#include "ShieldPlayer.h"

CShieldPlayer::CShieldPlayer(BOARD b)
{
	BitInfo = BITINFO{ "Player03" ,70,90,0,3,RGB(255, 0, 255) };
	Board = b;
	Board.rect.top += 10;
	FrameTime = 0.f;
	MaxFrameTime = 0.3f;
	Hp = MaxHp = 250;
	ExplosionState = ENUM_STATE::NON_STATE;
}

CShieldPlayer::~CShieldPlayer()
{
}

void CShieldPlayer::Create(HWND hWnd)
{
}

void CShieldPlayer::Draw(HDC hdc)
{
	CPlayer::Draw(hdc);
}

void CShieldPlayer::Update(const float ftime)
{
	CPlayer::Animate(ftime);
}

void CShieldPlayer::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CShieldPlayer::Release()
{
}
