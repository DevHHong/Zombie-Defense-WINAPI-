#include "stdafx.h"
#include "NormalZombie.h"


CNormalZombie::CNormalZombie(BOARD b, ENUM_LEVEL level)
{
	CZombie::Init();
	Board = b;
	Board.rect.top += 10;
	StateChainge(State);
	Pos = Point{ float(Board.pt.x),float(Board.pt.y) };
	Speed = 10.f;
	switch (level)
	{
	case ENUM_LEVEL::LEVEL_1: Hp = MaxHp = 100.f; Attack = 10; break;
	case ENUM_LEVEL::LEVEL_2: Hp = MaxHp = 150.f; Attack = 15; break;
	case ENUM_LEVEL::LEVEL_3: Hp = MaxHp = 250.f; Attack = 20; break;
	}
}

CNormalZombie::~CNormalZombie()
{
}

void CNormalZombie::Create(HWND hWnd)
{
}

void CNormalZombie::Draw(HDC hdc)
{
	CZombie::Draw(hdc);
}

void CNormalZombie::Update(const float ftime)
{
	StateChainge(State);
	CZombie::Animate(ftime, State);
	CZombie::MoveUpdate(ftime);
}

void CNormalZombie::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CNormalZombie::Release()
{
}

void CNormalZombie::StateChainge(ENUM_ANIM_STATE & state)
{
	if (state != OldState)
	{
		if (state == ENUM_ANIM_STATE::ALIVE)
		{
			BitInfo = BITINFO{ "Z1Alive" ,70,90,0,10,RGB(255, 0, 255) };
		}
		else if (state == ENUM_ANIM_STATE::WALK)
		{
			BitInfo = BITINFO{ "Z1Walk" ,70,90,0,10,RGB(255, 0, 255) };
		}
		else if (state == ENUM_ANIM_STATE::ATTACK)
		{
			BitInfo = BITINFO{ "Z1Attack" ,70,90,0,7,RGB(255, 0, 255) };
		}
		else if (state == ENUM_ANIM_STATE::DIE)
		{
			BitInfo = BITINFO{ "Z1Die" ,70,90,0,8,RGB(255, 0, 255) };
		}
		OldState = state;
	}
}
