#pragma once
#include "GameObj.h"
class CUI:public CGameObj
{
	FontUI mMineralFont;
	int Mineral;
	FontUI ZombieFont;
	int Level;
	FontUI Key[3];
public:
	CUI();
	virtual ~CUI();

	virtual void Create(HWND hWnd) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(const float ftime) override;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Release() override;

	void KeyDraw(HDC hdc);

	int GetMineral()const { return Mineral; }
	void AddMineral(int m) { Mineral += m; }
	void SubMineral(int m) { Mineral -= m; }
	void SetLevel(int l) { Level = l; }
private:
	void MouseMove(LPARAM lParam);
	void LButtonClick(LPARAM lParam);
};

