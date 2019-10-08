#include "stdafx.h"
#include "UI.h"


CUI::CUI()
{
}

CUI::~CUI()
{
}

void CUI::Create(HWND hWnd)
{
	mMineralFont.Create(L"", RECT{0,50, 60, 70 }, RGB(0, 0, 0), 20, 0);
	Mineral = 100;

	ZombieFont.Create(L"", RECT{ 650,30, 750, 70 }, RGB(0, 0, 0), 30, 0);

	Key[0].Create(L"[R] : ReGame", RECT{ 300,200, 500, 240 }, RGB(0, 0, 0), 30, 0);
	Key[1].Create(L"[Q] : Exit", RECT{ 300,250, 500, 290 }, RGB(0, 0, 0), 30, 0);
	Key[2].Create(L"[ESC] : ReSume", RECT{ 300,300, 510, 340 }, RGB(0, 0, 0), 30, 0);
}

void CUI::Draw(HDC hdc)
{
	mMineralFont.FontDraw(hdc, Mineral);
	ZombieFont.LevelFontDraw(hdc, Level);
}

void CUI::Update(const float ftime)
{
}

void CUI::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE: MouseMove(lParam); break;
	case WM_LBUTTONDOWN:
		LButtonClick(lParam); break;
	default:
		break;
	}
}

void CUI::Release()
{
}

void CUI::KeyDraw(HDC hdc)
{
	for (int i = 0; i < 3; ++i)
		Key[i].FontDraw(hdc);
}

void CUI::MouseMove(LPARAM lParam)
{
	POINT pt = POINT{ LOWORD(lParam),HIWORD(lParam) };
}

void CUI::LButtonClick(LPARAM lParam)
{
	POINT pt = POINT{ LOWORD(lParam),HIWORD(lParam) };
}

