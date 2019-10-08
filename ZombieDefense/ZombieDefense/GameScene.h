#pragma once
#include "Scene.h"
#include "BackGround.h"
#include "Card.h"
#include "UI.h"

class CPlayer;
class CZombie;
class CMineral;
class CBullet;

class CGameScene:public CScene
{
	CBackGround mBackGround;
	CCard mCard;
	CUI mUI;
	int Cardindex;		// 카드
	
	CPlayer* mPlayer[PLAYER_MAX] = { nullptr };
	CZombie* mZombie[ZOMBIE_MAX] = { nullptr };
	CMineral* mMineral[MINERAL_MAX] = { nullptr };
	CBullet* mBullet[BULLET_MAX] = { nullptr };
	// 시간
	float MineralTime;		// 흐르는 시간 (생성)
	float MaxMineralTime;	// 고정 시간
	float ZombieTime;		// 좀비 생성 시간
	float MaxZombieTime;
	// 목숨
	bool Life[LIFE_MAX];

	// 좀비 인덱스
	int ZombieIndex;
	// 전체 시간 
	float BalanceTime;
	int Level;
	bool GameStart;
public:
	CGameScene(CGameFramework * ptFW);
	virtual ~CGameScene();

	virtual void Create(HWND hWnd) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(const float ftime) override;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Release() override;

private:
	void CreateBitPath(HWND hWnd);
	void LButton(LPARAM lParam);
	void LButtonUP(LPARAM lParam);
	void CreatePlayers(LPARAM lParam);
	void DeletePlayers(LPARAM lParam);
	void DeletePlayers(CPlayer*& player);
	void CreateMineral(CMineral*& mineral);
	void DeleteMineral(CMineral*& mineral);
	void CreateZombie(CZombie*& zombie);
	void DeleteZombie(CZombie*& zombie);
	void CreateBullect(CPlayer*& player);
	bool ZombieBeing(CPlayer*& player);
	void DeleteBullect(CBullet*& bullet);

	// 충돌 체크
	void ZombieAndPlayerCollision(CZombie*& zombie);
	void BulletAndZombieCollision(CBullet*& bullet);
	void BombAndZombieCollision(CPlayer*& bomb);
};

