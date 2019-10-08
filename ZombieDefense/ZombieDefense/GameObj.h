#pragma once
#include "BitMap.h"

class CGameObj
{
protected:
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	COLORREF pColor, bColor;	// 펜 색
	static map<string, CBitMap*>* m_pMapBmp;		// 게임 씬에서 비트맵 정보 가져오기.
	// 객체들 속성
	BITINFO BitInfo;
	Point Pos;
	ENUM_STATE ExplosionState;
	float MaxFrameTime;
	float FrameTime;
	float MaxHp;
	float Hp;
	float Attack;
public:
	CGameObj();
	virtual ~CGameObj();

	virtual void Create(HWND hWnd) = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void Update(const float ftime) = 0;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
	virtual void Release() = 0;

	static void SetBmp(map<string, CBitMap*>* bmp) { m_pMapBmp = bmp; }

	Point GetPos()const { return Pos; }
	ENUM_STATE GetExplosion()const { return ExplosionState; }
	void SetExplosion(ENUM_STATE explosion) { ExplosionState = explosion; }
	void SetDamage(float d) { Hp -= d; }
	void SetZeroHP() { Hp = 0; }
	float GetHP()const { return Hp; }
	float GetAttack()const { return Attack; }
};

