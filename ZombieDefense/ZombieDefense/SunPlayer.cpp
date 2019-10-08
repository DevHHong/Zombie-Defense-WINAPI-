#include "stdafx.h"
#include "SunPlayer.h"

CSunPlayer::CSunPlayer(BOARD b)
{
	BitInfo = BITINFO{ "Player01" ,70,90,0,3,RGB(255, 0, 255) };
	Board = b;
	Board.rect.top += 10;
	FrameTime = 0.f;
	MaxFrameTime = 0.3f;
	Hp = MaxHp = 100;
	MaxMineralTime = 5.f;
	MineralTime = 0.f;
	CreateMineral = false;
	StopCreate = false;
	Pos = Point{ float(Board.rect.left + 30), float(Board.rect.top+30) };
	ExplosionState = ENUM_STATE::NON_STATE;

}

CSunPlayer::~CSunPlayer()
{
}

void CSunPlayer::Create(HWND hWnd)
{
}

void CSunPlayer::Draw(HDC hdc)
{
	CPlayer::Draw(hdc);
}

void CSunPlayer::Update(const float ftime)
{
	CPlayer::Animate(ftime);
	if (!StopCreate)
		MineralCreatUpdate(ftime);
}

void CSunPlayer::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CSunPlayer::Release()
{
}

void CSunPlayer::MineralCreatUpdate(const float ftime)
{
	MineralTime += ftime;
	if (MineralTime > MaxMineralTime)
	{
		MineralTime = 0.f;
		CreateMineral = true;
	}
	else
		CreateMineral = false;
}
