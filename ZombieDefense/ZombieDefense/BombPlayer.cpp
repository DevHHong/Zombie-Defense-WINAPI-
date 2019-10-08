#include "stdafx.h"
#include "BombPlayer.h"


CBombPlayer::CBombPlayer(BOARD b)
{
	BitInfo = BITINFO{ "Player04" ,70,90,0,3,RGB(255, 0, 255) };
	Board = b;
	Board.rect.top += 10;
	FrameTime = 0.f;
	MaxFrameTime = 0.3f;
	Hp = MaxHp = 100;
	ExplosionState = ENUM_STATE::NON_STATE;
	BombRange = RECT{ Board.rect.left - BitInfo.sizex, Board.rect.top - BitInfo.sizey, Board.rect.right + BitInfo.sizex, Board.rect.bottom + BitInfo.sizey };
	alphaColor = RGB(0, 255, 0);
	Sound = ENUM_MOUSESOUND::NON_SOUND;
}

CBombPlayer::~CBombPlayer()
{
}

void CBombPlayer::Create(HWND hWnd)
{
}

void CBombPlayer::Draw(HDC hdc)
{
	BombRangeAlphaDraw(hdc);
	CPlayer::Draw(hdc);
}

void CBombPlayer::Update(const float ftime)
{
	CPlayer::Animate(ftime);
}

void CBombPlayer::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CBombPlayer::Release()
{
}

void CBombPlayer::BombRangeAlphaDraw(HDC hdc)
{
	HBRUSH m_br = CreateSolidBrush(alphaColor);
	HBITMAP Ahbmp = CreateCompatibleBitmap(hdc, BombRange.left, BombRange.top);
	HDC Ahdc = CreateCompatibleDC(hdc);
	HBITMAP Aoldbmp = (HBITMAP)SelectObject(Ahdc, Ahbmp);
	auto oldbr = SelectObject(Ahdc, m_br);
	Rectangle(Ahdc, 0, 0, BombRange.left, BombRange.top);
	SelectObject(Ahdc, oldbr);
	BLENDFUNCTION bf;

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = 100;

	AlphaBlend(hdc, BombRange.left, BombRange.top, 70 * 3, 90 * 3, Ahdc, 0, 0, BombRange.left, BombRange.top, bf);
	SelectObject(Ahdc, Aoldbmp);
	DeleteObject(m_br);
	DeleteObject(Ahbmp);
	DeleteDC(Ahdc);
}
