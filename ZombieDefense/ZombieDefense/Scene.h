#pragma once
#include "stdafx.h"
#include "Sound.h"
class CGameFramework;
class CBitMap;

class CScene
{
protected:
	CGameFramework * m_pGameFramework;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	map<string, CBitMap*> m_MapBmp;
	CSound mSound;
public:
	CScene(CGameFramework * ptFW) :m_pGameFramework(ptFW) {};
	virtual ~CScene() {};

	virtual void Create(HWND hWnd) = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void Update(const float ftime) = 0;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
	virtual void Release() = 0;
};