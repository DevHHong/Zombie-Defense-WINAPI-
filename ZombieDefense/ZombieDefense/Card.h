#pragma once
#include "GameObj.h"
#include "Sound.h"
class CCard :
	public CGameObj
{
	CARD Card[CARD_MAX];				// 고정된 위치의 카드
	CARD DelCard;
	int index{ -1 };
	bool ClickOn;
	CSound Sound;
public:
	CCard();
	virtual ~CCard();

	virtual void Create(HWND hWnd) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(const float ftime) override;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Release()override;

	int LButton(LPARAM lParam, const int& mineral);
	void MouseMove(LPARAM lParam);

	void SetClick(bool b) { ClickOn = b; }
	bool GetCardClick(int n) const { return Card[n].click; }
	void SetCardClick(int n, bool b) { Card[n].click = b; }
	void SetCoolTimeStart(int n, bool b) { Card[n].CoolTimeStart = b; }
	ENUM_PLAYERS GetType(int n)const { return Card[n].type; }
	int GetPrice(int n)const { return Card[n].price; }
	// 삭제 클릭
	bool GetDelClick()const { return DelCard.click; }
	void SetDelClick(bool b) { DelCard.click = b; }
private:
	void AlphaDraw(HDC hdc, CARD& c);
};

