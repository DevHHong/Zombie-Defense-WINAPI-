#include "stdafx.h"
#include "BackGround.h"

CBackGround::CBackGround()
{
}

CBackGround::~CBackGround()
{
}

void CBackGround::Create(HWND hWnd)
{
	BitInfo.ID = "BackGround";

	for (int i = 0; i < COLUMN; ++i)
		for (int j = 0; j < ROW; ++j)
		{
			Board[i][j].rect = RECT{ X_START + (j*X_RECT),Y_START + (i * Y_RECT)
				,X_START + ((j + 1)*X_RECT) ,Y_START + ((i + 1) * Y_RECT) };
			Board[i][j].pt = POINT{ j, i };
			Board[i][j].bit = BITINFO{ "Fire" ,70,90,0,4,RGB(255, 0, 255) };
			Board[i][j].frameTime = 0.f;
		}
	MaxFrameTime = 0.2f;
	Grid = false;
}

void CBackGround::Draw(HDC hdc)
{
	BitBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, (*m_pMapBmp)[BitInfo.ID]->GetMemDC(), 0, 0, SRCCOPY);

	// Fire
	for (int i = 0; i < COLUMN; ++i)
		for (int j = 0; j < ROW-1; ++j)			// -1을 해주는 이유는 좀비 생성되는 곳이라.
			if (Board[i][j].fire)
			{
				TransparentBlt(hdc, Board[i][j].rect.left, Board[i][j].rect.top,
					Board[i][j].bit.sizex, Board[i][j].bit.sizey, (*m_pMapBmp)[Board[i][j].bit.ID]->GetMemDC(),
					Board[i][j].bit.curFrame * Board[i][j].bit.sizex, 0, Board[i][j].bit.sizex, Board[i][j].bit.sizey, Board[i][j].bit.color);
			}
	// 보드판
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	oldPen = (HPEN)SelectObject(hdc, hPen);
	auto old = SelectObject(hdc, GetStockObject(NULL_BRUSH));
	
	if (Grid)
	{
		for (int i = 0; i < COLUMN; ++i)
			for (int j = 0; j < ROW; ++j)
				Rectangle(hdc, Board[i][j].rect.left, Board[i][j].rect.top, Board[i][j].rect.right, Board[i][j].rect.bottom);
	}
	SelectObject(hdc, old);
	SelectObject(hdc, oldPen);
	DeleteObject(hPen);
}

void CBackGround::Update(const float ftime)
{
	for (int i = 0; i < COLUMN; ++i)
		for (int j = 0; j < ROW-1; ++j)
			if (Board[i][j].fire)
			{
				Board[i][j].frameTime += ftime;
				if (Board[i][j].frameTime > MaxFrameTime)
				{
					Board[i][j].bit.curFrame = (++Board[i][j].bit.curFrame) % Board[i][j].bit.maxFrame;
					Board[i][j].frameTime = 0.f;
				}
			}
}

void CBackGround::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CBackGround::Release()
{
}

void CBackGround::BoardShow()
{
	for (int i = 0; i < COLUMN; ++i)
	{
		for (int j = 0; j < ROW; ++j)
			cout << Board[i][j].being << "   ";
		cout << endl;
	}
	cout << endl;
}
