#include "stdafx.h"
#include "OverScene.h"
#include"GameFramework.h"

COverScene::COverScene(CGameFramework * ptFW)
	:CScene(ptFW)
{
}


COverScene::~COverScene()
{
}

void COverScene::Create(HWND hWnd)
{
	// StartButton Pos
	RECT Button[2];
	Button[0] = RECT{ CLIENT_WIDTH / 2 - 100,CLIENT_HEIGHT / 2 + 70,CLIENT_WIDTH / 2 + 100,CLIENT_HEIGHT / 2 + 120 };
	Button[1] = RECT{ CLIENT_WIDTH / 2 - 100,Button[0].top + 70,CLIENT_WIDTH / 2 + 100,Button[0].bottom + 70 };
	mFontUI[0].Create(L"ReStart", Button[0], RGB(255, 200, 0), 50, 0);
	mFontUI[1].Create(L"Exit", Button[1], RGB(255, 200, 0), 50, 0);

	// Title
	RECT rect = RECT{ CLIENT_WIDTH / 2 - 300,CLIENT_HEIGHT / 2 - 100,CLIENT_WIDTH / 2 + 300,CLIENT_HEIGHT / 2 + 50 };
	mFontUI[2].Create(L"OVER", rect, 0, 150, 0);

	rect = RECT{ CLIENT_WIDTH / 2 - 300,CLIENT_HEIGHT / 2 - 230,CLIENT_WIDTH / 2 + 300,CLIENT_HEIGHT / 2 };
	mFontUI[3].Create(L"GAME", rect, 0, 130, 0);
	bFadeIn = true;
	MouseSound[0] = ENUM_MOUSESOUND::NON_SOUND;
	MouseSound[1] = ENUM_MOUSESOUND::NON_SOUND;
	bSceneChainge = false;
}

void COverScene::Draw(HDC hdc)
{
	if (bFadeIn) FadeIn(hdc);
	else Menu(hdc);
}

void COverScene::Update(const float ftime)
{
	if (mColorTime > 100.f)
		mColorTime = 0.f;
	mColorTime += ftime;
	if (bSceneChainge)
		m_pGameFramework->ChangeScene(ENUM_SCENEID::GAMESCENE);
}

void COverScene::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE: MouseMove(lParam); break;
	case WM_LBUTTONDOWN: LButtonClick(lParam); break;
	default:
		break;
	}
}

void COverScene::Release()
{
}

void COverScene::BackGround(HDC hdc)
{
	hBrush = CreateSolidBrush(RGB(64, 0, 128));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

void COverScene::Menu(HDC hdc)
{
	BackGround(hdc);

	// Button
	for (int i = 0; i < 2; ++i)
	{
		mFontUI[i].FontDraw(hdc);
	}
	// Title
	float recolortime = abs(sin(mColorTime));
	mFontUI[2].SetColor(mColor.GetDeltaColor(recolortime));
	mFontUI[2].FontDraw(hdc);
	mFontUI[3].SetColor(mColor.GetDeltaColor(recolortime));
	mFontUI[3].FontDraw(hdc);
}

void COverScene::FadeIn(HDC hdc)
{
	float recolortime = abs(sin(mColorTime));
	if (mFadein.GetDeltaColor(recolortime) >= RGB(60, 0, 120))
	{
		bFadeIn = false;
		// Sound
		mSound.Play(BGM3);
	}
	hBrush = CreateSolidBrush(mFadein.GetDeltaColor(recolortime));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

void COverScene::MouseMove(LPARAM lParam)
{
	POINT pt = POINT{ LOWORD(lParam),HIWORD(lParam) };

	for (int i = 0; i < 2; ++i)
	{
		if (PtInRect(&mFontUI[i].GetRect(), pt))
		{
			mFontUI[i].SetAngle(45);
			mFontUI[i].SetColor(RGB(255, 0, 0));
			if (MouseSound[i] == ENUM_MOUSESOUND::NON_SOUND)
			{
				MouseSound[i] = ENUM_MOUSESOUND::START_SOUND;
				mSound.Play(BUTTON1);
			}
		}
		else
		{
			mFontUI[i].SetAngle(0);
			mFontUI[i].SetColor(RGB(255, 200, 0));
			if (MouseSound[i] == ENUM_MOUSESOUND::START_SOUND)
				MouseSound[i] = ENUM_MOUSESOUND::NON_SOUND;
		}
	}
}

void COverScene::LButtonClick(LPARAM lParam)
{
	POINT pt = POINT{ LOWORD(lParam),HIWORD(lParam) };

	if (PtInRect(&mFontUI[0].GetRect(), pt))
	{
		mSound.Play(BUTTON2);
		bSceneChainge = true;
		Sleep(500);
	}
	else if (PtInRect(&mFontUI[1].GetRect(), pt))
		PostQuitMessage(0);
}
