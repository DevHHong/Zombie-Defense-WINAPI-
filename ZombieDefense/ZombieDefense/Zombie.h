#pragma once
#include "GameObj.h"
#include "Explosion.h"
class CZombie :
	public CGameObj
{
protected:
	BOARD Board;
	ENUM_ANIM_STATE State;
	ENUM_ANIM_STATE OldState;
	CExplosion Explosion;
	float Speed;
	int playerIndex;			// 플레이어의 인덱스 정보를 알아내서 판단한다.
	bool bAttackDamage;			// 딱 한번 데미지를 주기위한 bool값
	bool StopMove;
	float Stoptime;
public:
	CZombie();
	virtual ~CZombie();

	virtual void Create(HWND hWnd) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(const float ftime) override;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Release()override;

	RECT GetRect()const { return Board.rect; }
	POINT GetPosIndex()const { return Board.pt; }
	ENUM_ANIM_STATE GetState()const { return State; }
	void SetState(ENUM_ANIM_STATE s) { State = s; }
	int GetIndex()const { return playerIndex; }
	void SetIndex(int n) { playerIndex = n; }
	int GetAttackMotion()const { return BitInfo.curFrame; }

	bool GetAttackDamage() { return bAttackDamage; }
	void SetAttackDamage(bool b) { bAttackDamage = b; }

	// 파란색 총알에 맞으면 멈춤
	void SetStopMove(bool b) { StopMove = b; }
protected:
	virtual void Init();
	virtual void StateChainge(ENUM_ANIM_STATE& state) = 0;
	virtual void Animate(const float ftime, ENUM_ANIM_STATE& state);
	virtual void MoveUpdate(const float ftime);
	virtual void HpDraw(HDC hdc);
};

