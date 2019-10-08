#pragma once
#include "Scene.h"

class COverScene : public CScene
{
	FontUI mFontUI[4];
	CTwoColor mColor{ 255,100,255,255,255,0 };		// 색상 초기화
	CTwoColor mFadein{ 0,0,0,64,0,128 };		// 색상 초기화
	float mColorTime{ 0.f };
	bool bFadeIn{ true };
	bool bSceneChainge;
	ENUM_MOUSESOUND MouseSound[2];
public:
	COverScene(CGameFramework * ptFW);
	virtual ~COverScene();

	virtual void Create(HWND hWnd) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(const float ftime) override;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Release() override;

private:
	void BackGround(HDC hdc);
	void Menu(HDC hdc);
	void FadeIn(HDC hdc);
	void MouseMove(LPARAM lParam);
	void LButtonClick(LPARAM lParam);
};

