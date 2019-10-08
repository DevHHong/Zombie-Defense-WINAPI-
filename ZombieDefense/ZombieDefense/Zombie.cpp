#include "stdafx.h"
#include "Zombie.h"


CZombie::CZombie()
{
}


CZombie::~CZombie()
{
}

void CZombie::Create(HWND hWnd)
{
}

void CZombie::Draw(HDC hdc)
{
	//Rectangle(hdc, Board.rect.left, Board.rect.top, Board.rect.right, Board.rect.bottom);
	TransparentBlt(hdc, Board.rect.left - 10, Board.rect.top,
		BitInfo.sizex, BitInfo.sizey, (*m_pMapBmp)[BitInfo.ID]->GetMemDC(),
		BitInfo.curFrame * BitInfo.sizex, 0, BitInfo.sizex, BitInfo.sizey, BitInfo.color);

	if (ExplosionState == ENUM_STATE::EXPLOSION_STATE)
		Explosion.EffectDraw(hdc, Board.rect.left - 10, Board.rect.top, BitInfo.sizex);
	HpDraw(hdc);
}

void CZombie::Update(const float ftime)
{
}

void CZombie::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CZombie::Release()
{
}

void CZombie::Init()
{
	StopMove = false;
	State = ENUM_ANIM_STATE::ALIVE;
	OldState = ENUM_ANIM_STATE::NON_ANIM;
	MaxFrameTime = 0.3f;
	FrameTime = 0;
	ExplosionState = ENUM_STATE::NON_STATE;
	bAttackDamage = true;
	Stoptime = 0.f;
}

void CZombie::Animate(const float ftime, ENUM_ANIM_STATE & state)
{
	if (!StopMove)
		FrameTime += ftime;
	else
	{
		Stoptime += ftime;
		if (Stoptime > 1.0)
		{
			Stoptime = 0;
			StopMove = false;
		}
	}
	if (FrameTime > MaxFrameTime)
	{
		if (state == ENUM_ANIM_STATE::ALIVE)
		{
			if (++BitInfo.curFrame == BitInfo.maxFrame)
				state = ENUM_ANIM_STATE::WALK;
		}
		else if (state == ENUM_ANIM_STATE::WALK || state == ENUM_ANIM_STATE::ATTACK)
		{
			BitInfo.curFrame = (++BitInfo.curFrame) % BitInfo.maxFrame;
		}
		else if (state == ENUM_ANIM_STATE::DIE)
		{
			if (++BitInfo.curFrame == BitInfo.maxFrame)
				ExplosionState = ENUM_STATE::DELETE_STATE;
		}
		FrameTime = 0.f;
	}
}

void CZombie::MoveUpdate(const float ftime)
{
	if (State == ENUM_ANIM_STATE::WALK && !StopMove)
	{
		Board.rect.left = int(Board.rect.left - ftime * Speed);
		Board.rect.right = int(Board.rect.right - ftime * Speed);
	}

	if (ExplosionState == ENUM_STATE::EXPLOSION_STATE)
		ExplosionState = Explosion.StateUpdate(ftime);
}

void CZombie::HpDraw(HDC hdc)
{
	HBRUSH m_br = CreateSolidBrush(RGB(255, 1, 1));
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

	AlphaBlend(hdc, Board.rect.left - 10, Board.rect.bottom - 10, curHp, 10, Ahdc, 0, 0, 50, 50, bf);
	SelectObject(Ahdc, Aoldbmp);
	DeleteObject(m_br);
	DeleteObject(Ahbmp);
	DeleteDC(Ahdc);
}
