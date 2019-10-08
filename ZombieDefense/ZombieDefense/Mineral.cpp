#include "stdafx.h"
#include "Mineral.h"


CMineral::CMineral(Point pos, int n)
{
	BitInfo = BITINFO{ "SunItem" ,70,70,0,4,RGB(255, 0, 255) };
	radian = 70 / 2;
	Pos = pos;
	Pix = Point{ 10,10 };
	MaxFrameTime = 0.3f;
	FrameTime = 0;
	bClick = false;
	bDelete = false;
	index = n;
	Price = 50;
	if (index == -1)
	{
		Size = 0;
		bDrop = true;
	}
	else
	{
		Size = 60;
		bDrop = false;
	}
}

CMineral::~CMineral()
{
}

void CMineral::Create(HWND hWnd)
{
}

void CMineral::Draw(HDC hdc)
{
	TransparentBlt
	(
		hdc, int(Pos.x - radian - Size), int(Pos.y - radian - Size), int(BitInfo.sizex + Size), int(BitInfo.sizey + Size)
		, (*m_pMapBmp)[BitInfo.ID]->GetMemDC(), BitInfo.curFrame * BitInfo.sizex, 0, BitInfo.sizex, BitInfo.sizey, BitInfo.color
	);
	//Ellipse(hdc, Pos.x - radian, Pos.y - radian, Pos.x + radian, Pos.y + radian);
}

void CMineral::Update(const float ftime)
{
	Animate(ftime);

	if (bClick)
	{
		Dir = Point{ Pix - Pos };
		Dir = normalize(Dir);
		if (Collision(Pix, Pos, 30)) bDelete = true;
		Pos += Dir * 400 * ftime;
	}

	if (bDrop)
		Pos.y += ftime * 100;
	else
	{
		if (Size >= 0)
			Size -= ftime * 50;
		else
			Size = 0;
	}
}

void CMineral::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CMineral::Release()
{
}

void CMineral::Animate(const float ftime)
{
	FrameTime += ftime;
	if (FrameTime > MaxFrameTime)
	{
		BitInfo.curFrame = (++BitInfo.curFrame) % BitInfo.maxFrame;
		FrameTime = 0.f;
	}
}
