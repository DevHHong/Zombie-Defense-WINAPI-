#include "stdafx.h"
#include "StrongZombie.h"


CStrongZombie::CStrongZombie(BOARD b, ENUM_LEVEL level)
{
	CZombie::Init();
	Board = b;
	Board.rect.top += 10;
	StateChainge(State);
	Speed = 20.f;
	Pos = Point{ float(Board.pt.x),float(Board.pt.y) };
	switch (level)
	{
	case ENUM_LEVEL::LEVEL_1: Hp = MaxHp = 200.f; Attack = 20; break;
	case ENUM_LEVEL::LEVEL_2: Hp = MaxHp = 300.f; Attack = 25; break;
	case ENUM_LEVEL::LEVEL_3: Hp = MaxHp = 400.f; Attack = 35; break;
	}
}

CStrongZombie::~CStrongZombie()
{
}

void CStrongZombie::Create(HWND hWnd)
{
}

void CStrongZombie::Draw(HDC hdc)
{
	CZombie::Draw(hdc);
}

void CStrongZombie::Update(const float ftime)
{
	StateChainge(State);
	CZombie::Animate(ftime, State);
	CZombie::MoveUpdate(ftime);
}

void CStrongZombie::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CStrongZombie::Release()
{
}

void CStrongZombie::StateChainge(ENUM_ANIM_STATE & state)
{
	if (state != OldState)
	{
		if (state == ENUM_ANIM_STATE::ALIVE)
		{
			BitInfo = BITINFO{ "Z2Alive" ,70,90,0,10,RGB(255, 0, 255) };
		}
		else if (state == ENUM_ANIM_STATE::WALK)
		{
			BitInfo = BITINFO{ "Z2Walk" ,70,90,0,8,RGB(255, 0, 255) };
		}
		else if (state == ENUM_ANIM_STATE::ATTACK)
		{
			BitInfo = BITINFO{ "Z2Attack" ,70,90,0,8,RGB(255, 0, 255) };
		}
		else if (state == ENUM_ANIM_STATE::DIE)
		{
			BitInfo = BITINFO{ "Z2Die" ,70,90,0,8,RGB(255, 0, 255) };
		}
		OldState = state;
	}
}
