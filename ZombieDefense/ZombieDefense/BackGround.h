#pragma once
#include "GameObj.h"
class CBackGround:public CGameObj
{
	BOARD Board[COLUMN][ROW];
	bool Grid;
public:
	CBackGround();
	virtual ~CBackGround();

	virtual void Create(HWND hWnd) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(const float ftime) override;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Release()override;

	BOARD GetBoard(int x,int y)const { return Board[y][x]; }
	RECT GetRect(int x, int y)const { return Board[y][x].rect; }
	bool GetBeing(int x, int y)const { return Board[y][x].being; }
	void SetBeing(int x, int y, bool b) { Board[y][x].being = b; }
	void SetFire(int x, int y, bool b) { Board[y][x].fire = b; }
	void BoardShow();

	void SetGrid() { Grid = !Grid; }
};

