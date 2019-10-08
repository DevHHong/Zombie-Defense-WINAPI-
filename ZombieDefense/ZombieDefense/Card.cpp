#include "stdafx.h"
#include "Card.h"

CCard::CCard()
{
}

CCard::~CCard()
{
}

void CCard::Create(HWND hWnd)
{
	ClickOn = false;
	// 카드 시작 위치
	POINT cardPos = POINT{ 62,8 };
	for (int i = 0; i < CARD_MAX; ++i)
	{
		Card[i].rect = RECT{ (i * X_CARD) + cardPos.x + (i * 5),cardPos.y,((i + 1) * X_CARD) + cardPos.x + (i * 5), cardPos.y + Y_CARD };
		Card[i].color = RGB(185, 122, 87);
		Card[i].bit1.sizex = 50;
		Card[i].bit1.sizey = 60;
		Card[i].bit2.sizex = 70;
		Card[i].bit2.sizey = 90;
		Card[i].bit2.color = RGB(255, 0, 255);
		Card[i].alphaSize = 65;
		Card[i].click = false;
		Card[i].CoolTimeStart = false;
		Card[i].sound = ENUM_MOUSESOUND::NON_SOUND;
		Card[i].type = ENUM_PLAYERS(i);
		if (Card[i].type == ENUM_PLAYERS::SUN)
		{
			Card[i].bit1.ID = "P01";
			Card[i].bit2.ID = "Player01";
			Card[i].price = 50;
		}
		else if (Card[i].type == ENUM_PLAYERS::PLANT)
		{
			Card[i].bit1.ID = "P02";
			Card[i].bit2.ID = "Player02";
			Card[i].price = 100;
		}
		else if (Card[i].type == ENUM_PLAYERS::SEED)
		{
			Card[i].bit1.ID = "P03";
			Card[i].bit2.ID = "Player03";
			Card[i].price = 50;
		}
		else if (Card[i].type == ENUM_PLAYERS::BOMB)
		{
			Card[i].bit1.ID = "P04";
			Card[i].bit2.ID = "Player04";
			Card[i].price = 150;
		}
		else if (Card[i].type == ENUM_PLAYERS::SNOW)
		{
			Card[i].bit1.ID = "P05";
			Card[i].bit2.ID = "Player05";
			Card[i].price = 175;
		}
		else if (Card[i].type == ENUM_PLAYERS::PARABOLA)
		{
			Card[i].bit1.ID = "P06";
			Card[i].bit2.ID = "Player06";
			Card[i].price = 200;
		}
	}

	// 삭제 카드
	DelCard.rect = RECT{ 425,0,495,70 };
	DelCard.bit1 = BITINFO{ "Del",65,69,0,0,RGB(255, 0, 255) };
	DelCard.sound = ENUM_MOUSESOUND::NON_SOUND;
}

void CCard::Draw(HDC hdc)
{
	// 카드
	for (int i = 0; i < CARD_MAX; ++i)
	{
		hPen = CreatePen(PS_SOLID, 3, Card[i].color);
		oldPen = (HPEN)SelectObject(hdc, hPen);
		auto old = SelectObject(hdc, GetStockObject(NULL_BRUSH));

		StretchBlt
		(
			hdc, Card[i].rect.left, Card[i].rect.top, Card[i].rect.right - Card[i].rect.left, Card[i].rect.bottom - Card[i].rect.top
			, (*m_pMapBmp)[Card[i].bit1.ID]->GetMemDC(), 0, 0, Card[i].bit1.sizex, Card[i].bit1.sizey, SRCCOPY
		);

		Rectangle(hdc, Card[i].rect.left, Card[i].rect.top, Card[i].rect.right, Card[i].rect.bottom);
		SelectObject(hdc, old);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		if (Card[i].CoolTimeStart)
			AlphaDraw(hdc, Card[i]);
	}

	for (int i = 0; i < CARD_MAX; ++i)
	{
		if (Card[i].click)
		{
			TransparentBlt
			(
				hdc, Card[i].rect.left + Card[i].pos.x, Card[i].rect.top + Card[i].pos.y
				, Card[i].bit2.sizex, Card[i].bit2.sizey, (*m_pMapBmp)[Card[i].bit2.ID]->GetMemDC()
				, 0, 0, Card[i].bit2.sizex, Card[i].bit2.sizey, Card[i].bit2.color
			);
		}
	}
	
	if (DelCard.click)
	{
		TransparentBlt
		(
			hdc, DelCard.rect.left + DelCard.pos.x, DelCard.rect.top + DelCard.pos.y
			, DelCard.bit1.sizex, DelCard.bit1.sizey, (*m_pMapBmp)[DelCard.bit1.ID]->GetMemDC(),
			0, 0, DelCard.bit1.sizex, DelCard.bit1.sizey, DelCard.bit1.color
		);
	}
}

void CCard::Update(const float ftime)
{
	for (int i = 0; i < CARD_MAX; ++i)
	{
		if (Card[i].CoolTimeStart)
		{
			Card[i].alphaSize -= ftime*10;
			if (Card[i].alphaSize <= 0)
			{
				Card[i].alphaSize = 65;
				Card[i].CoolTimeStart = false;
			}
		}
		if (!Card[i].click)
			Card[i].pos = POINT{ 0,0 };
	}
	if (!DelCard.click)
		DelCard.pos = POINT{ 0,0 };
}

void CCard::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void CCard::Release()
{
}

int CCard::LButton(LPARAM lParam, const int& mineral)
{
	POINT pt = POINT{ LOWORD(lParam),HIWORD(lParam) };
	
	for (int i = 0; i < CARD_MAX; ++i)
	{
		if (PtInRect(&Card[i].rect, pt) && Card[i].price <= mineral && !Card[i].CoolTimeStart)
		{
			ClickOn = true;
			Card[i].click = true;
			index = i;
			Card[i].savePos.x = LOWORD(lParam);
			Card[i].savePos.y = HIWORD(lParam);
			Card[i].pos.x = LOWORD(lParam) - Card[i].savePos.x;
			Card[i].pos.y = HIWORD(lParam) - Card[i].savePos.y;
			Sound.Play(BUTTON1);
			return index;
		}
	}

	if (PtInRect(&DelCard.rect, pt))
	{
		ClickOn = true;
		DelCard.click = true;
		DelCard.savePos.x = LOWORD(lParam);
		DelCard.savePos.y = HIWORD(lParam);
		DelCard.pos.x = LOWORD(lParam) - DelCard.savePos.x;
		DelCard.pos.y = HIWORD(lParam) - DelCard.savePos.y;
		Sound.Play(BUTTON1);
	}
	return -1;
}

void CCard::MouseMove(LPARAM lParam)
{
	POINT pt = POINT{ LOWORD(lParam),HIWORD(lParam) };

	for (int i = 0; i < CARD_MAX; ++i)
	{
		if (Card[i].click)
		{
			Card[i].color = RGB(255, 0, 0);
			Card[i].pos.x = LOWORD(lParam) - Card[i].savePos.x;
			Card[i].pos.y = HIWORD(lParam) - Card[i].savePos.y;
		}
		else
		{
			if (PtInRect(&Card[i].rect, pt) && !ClickOn)
			{
				Card[i].color = RGB(255, 0, 0);
				if (Card[i].sound == ENUM_MOUSESOUND::NON_SOUND)
				{
					Card[i].sound = ENUM_MOUSESOUND::START_SOUND;
					Sound.Play(BUTTON3);
				}
			}
			else
			{
				Card[i].color = RGB(185, 122, 87);
				if (Card[i].sound == ENUM_MOUSESOUND::START_SOUND)
					Card[i].sound = ENUM_MOUSESOUND::NON_SOUND;
			}
		}
	}

	if (DelCard.click)
	{
		DelCard.pos.x = LOWORD(lParam) - DelCard.savePos.x;
		DelCard.pos.y = HIWORD(lParam) - DelCard.savePos.y;
	}
	else
	{
		if (PtInRect(&DelCard.rect, pt) && !ClickOn)
		{
			if (DelCard.sound == ENUM_MOUSESOUND::NON_SOUND)
			{
				DelCard.sound = ENUM_MOUSESOUND::START_SOUND;
				Sound.Play(BUTTON3);
			}
		}
		else
			if (DelCard.sound == ENUM_MOUSESOUND::START_SOUND)
				DelCard.sound = ENUM_MOUSESOUND::NON_SOUND;
	}
}

void CCard::AlphaDraw(HDC hdc, CARD & c)
{
	HBITMAP Ahbmp = CreateCompatibleBitmap(hdc, 100, 100);
	HDC Ahdc = CreateCompatibleDC(hdc);
	HBITMAP Aoldbmp = (HBITMAP)SelectObject(Ahdc, Ahbmp);
	
	BLENDFUNCTION bf;

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = 200;

	AlphaBlend(hdc, c.rect.left, c.rect.top, 45, int(c.alphaSize), Ahdc, 0, 0, 50, 50, bf);
	SelectObject(Ahdc, Aoldbmp);
	DeleteObject(Ahbmp);
	DeleteDC(Ahdc);
}
