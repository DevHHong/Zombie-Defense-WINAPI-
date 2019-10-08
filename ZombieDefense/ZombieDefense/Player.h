#pragma once
#include "GameObj.h"
#include "Explosion.h"
class CPlayer:public CGameObj
{
protected:
	BOARD Board;
	CExplosion Explosion;
	// 총알 생성 부분 만들기
	float BulletTime;
	float MaxBulletTime;
	bool bBulletCreate;
public:
	CPlayer();
	virtual ~CPlayer();

	virtual void Create(HWND hWnd) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(const float ftime) override;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Release()override;

	RECT GetRect()const { return Board.rect; }
	POINT GetPosIndex()const { return Board.pt; }
	bool GetBulletCreate()const { return bBulletCreate; }
	void SetBulletCreate(bool b) { bBulletCreate = b; }
protected:
	virtual void Init();
	virtual void Animate(const float ftime);
	virtual void HpDraw(HDC hdc);
	virtual void CreateBulletUpdate(const float ftime);
};

