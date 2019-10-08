#include "stdafx.h"
#include "AttackPlayer.h"


CAttackPlayer::CAttackPlayer(BOARD b)
{
	BitInfo = BITINFO{ "Player02" ,70,90,0,3,RGB(255, 0, 255) };
	Board = b;
	Board.rect.top += 10;
	FrameTime = 0.f;
	MaxFrameTime = 0.3f;
	Hp = MaxHp = 150;
	ExplosionState = ENUM_STATE::NON_STATE;
	Pos = Point{ float(Board.rect.left + 60),float(Board.rect.top + 20) };
	BulletTime = MaxBulletTime = 1.5f;
	bBulletCreate = false;
}

CAttackPlayer::~CAttackPlayer()
{
}

void CAttackPlayer::Create(HWND hWnd)
{
}

void CAttackPlayer::Draw(HDC hdc)
{
	CPlayer::Draw(hdc);
}

void CAttackPlayer::Update(const float ftime)
{
	CPlayer::Animate(ftime);
	CPlayer::CreateBulletUpdate(ftime);
}

void CAttackPlayer::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CAttackPlayer::Release()
{
}
