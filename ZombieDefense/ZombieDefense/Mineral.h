#pragma once
#include "GameObj.h"
class CMineral :
	public CGameObj
{
	Point Pix;	// 고정된 위치
	Point Dir;
	float radian;
	float Size;
	bool bClick;
	bool bDelete;
	bool bDrop;
	int index;
	int Price;
public:
	CMineral(Point pos, int n);
	virtual ~CMineral();

	virtual void Create(HWND hWnd) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(const float ftime) override;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Release()override;

	bool GetDelete()const { return bDelete; }
	bool GetClick()const { return bClick; }
	void SetClick(bool click) { bClick = click; }
	bool GetDrop()const { return bDrop; }
	int GetIndex()const { return index; }
	float GetRadian()const { return radian; }
	int GetPrice()const { return Price; }
private:
	void Animate(const float ftime);
};

