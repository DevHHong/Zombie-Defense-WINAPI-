#pragma once
#include "stdafx.h"

class FontUI
{
	HFONT hFont, oldFont;
	LPCTSTR name;
	RECT rect;
	DWORD color;
	int size;
	int angle;
public:
	FontUI() {}
	~FontUI() {}
	void Create(LPCTSTR n, RECT r, DWORD c, int s = 50, int a = 0)
	{
		name = n;
		rect = r;
		color = c;
		size = s;
		angle = a;
	}
	void FontDraw(HDC hdc)
	{
		hFont = CreateFont(size, 0, angle, 0, 800, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("Arial Rounded MT Bold"));
		oldFont = (HFONT)SelectObject(hdc, hFont);
		SetBkMode(hdc, TRANSPARENT);		// πŸ≈¡ ≈ı∏Ì
		SetTextColor(hdc, color);
		DrawText(hdc, name, -1, &rect, DT_CENTER);
		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
	}
	void FontDraw(HDC hdc, int mineral)
	{
		wchar_t wcTmp[128];
		hFont = CreateFont(size, 0, angle, 0, 800, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("Arial Rounded MT Bold"));
		oldFont = (HFONT)SelectObject(hdc, hFont);
		SetBkMode(hdc, TRANSPARENT);		// πŸ≈¡ ≈ı∏Ì
		SetTextColor(hdc, color);
		swprintf(wcTmp, 128, L"%d", mineral);
		DrawText(hdc, wcTmp, -1, &rect, DT_CENTER);
		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
	}
	void LevelFontDraw(HDC hdc, int level)
	{
		wchar_t wcTmp[128];
		hFont = CreateFont(size, 0, angle, 0, 800, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("Arial Rounded MT Bold"));
		oldFont = (HFONT)SelectObject(hdc, hFont);
		SetBkMode(hdc, TRANSPARENT);		// πŸ≈¡ ≈ı∏Ì
		SetTextColor(hdc, color);
		swprintf(wcTmp, 128, L"Level %d", level);
		DrawText(hdc, wcTmp, -1, &rect, DT_CENTER);
		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
	}
	RECT GetRect()const { return rect; }
	void SetAngle(int a) { angle = a; }
	void SetColor(DWORD c) { color = c; }
};