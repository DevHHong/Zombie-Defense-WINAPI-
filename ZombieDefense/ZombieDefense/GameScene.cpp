#include "stdafx.h"
#include "GameScene.h"
#include"GameFramework.h"
#include "BitMap.h"
#include "SunPlayer.h"
#include "AttackPlayer.h"
#include "ShieldPlayer.h"
#include "BombPlayer.h"
#include "SnowPlayer.h"
#include "ParabolaPlayer.h"
#include "NormalZombie.h"
#include "StrongZombie.h"
#include "Mineral.h"
#include "NormalBullet.h"
#include "SnowBullet.h"
#include "ParabolaBullet.h"

CGameScene::CGameScene(CGameFramework * ptFW)
	:CScene(ptFW)
{
}

CGameScene::~CGameScene()
{
	Release();
}

void CGameScene::Create(HWND hWnd)
{
	GameStart = true;
	Level = ENUM_LEVEL::LEVEL_1;
	Cardindex = -1;
	MaxMineralTime = 5.f;
	MineralTime = 3.f;
	MaxZombieTime = 10.f;
	ZombieTime = 3.f;
	BalanceTime = 0.f;
	mSound.Play(BGM2);
	CreateBitPath(hWnd);
	mBackGround.Create(hWnd);
	mCard.Create(hWnd);
	mUI.Create(hWnd);
	mUI.SetLevel(Level);
	for (int i = 0; i < LIFE_MAX; ++i)
		Life[i] = true;
}

void CGameScene::Draw(HDC hdc)
{
	mBackGround.Draw(hdc);
	mCard.Draw(hdc);
	mUI.Draw(hdc);
	for (int i = 0; i < PLAYER_MAX; ++i)
		if (mPlayer[i])
			mPlayer[i]->Draw(hdc);

	for (int i = 0; i < ZOMBIE_MAX; ++i)
		if (mZombie[i])
			mZombie[i]->Draw(hdc);

	for (int i = 0; i < BULLET_MAX; ++i)
		if (mBullet[i])
			mBullet[i]->Draw(hdc);

	for (int i = 0; i < MINERAL_MAX; ++i)
		if (mMineral[i])
			mMineral[i]->Draw(hdc);

	// 
	if (!GameStart)
		mUI.KeyDraw(hdc);
}

void CGameScene::Update(const float ftime)
{
	if (GameStart)
	{
		BalanceTime += ftime;
		if (BalanceTime > 30)
		{
			if (MaxZombieTime > 3)
			{
				MaxZombieTime -= 1.f;
				// 좀비 강화
				if (ENUM_LEVEL(Level) != ENUM_LEVEL::LEVEL_3)
				{
					mUI.SetLevel(++Level);
					mSound.Play(EFFECT6);
				}
			}
			BalanceTime = 0.f;
		}
		mBackGround.Update(ftime);
		mCard.Update(ftime);
		for (int i = 0; i < PLAYER_MAX; ++i)
			if (mPlayer[i])
			{
				mPlayer[i]->Update(ftime);
				if (dynamic_cast<CAttackPlayer*>(mPlayer[i]) || dynamic_cast<CSnowPlayer*>(mPlayer[i]) || dynamic_cast<CParabolaPlayer*>(mPlayer[i]))
					CreateBullect(mPlayer[i]);
				else if (dynamic_cast<CBombPlayer*>(mPlayer[i]))
				{
					BombAndZombieCollision(mPlayer[i]);
				}
				DeletePlayers(mPlayer[i]);
			}
		// Mineral
		MineralTime += ftime;
		for (int i = 0; i < MINERAL_MAX; ++i)
		{
			if (mMineral[i])
			{
				mMineral[i]->Update(ftime);
				DeleteMineral(mMineral[i]);
			}
			else
				CreateMineral(mMineral[i]);
		}
		// Zombie
		ZombieTime += ftime;
		for (int i = 0; i < ZOMBIE_MAX; ++i)
		{
			if (mZombie[i])
			{
				mZombie[i]->Update(ftime);
				ZombieAndPlayerCollision(mZombie[i]);
				DeleteZombie(mZombie[i]);
			}
			else
				CreateZombie(mZombie[i]);
		}
		// Bullect
		for (int i = 0; i < BULLET_MAX; ++i)
		{
			if (mBullet[i])
			{
				mBullet[i]->Update(ftime);
				DeleteBullect(mBullet[i]);
			}
		}
	}
}

void CGameScene::Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (wParam == VK_ESCAPE)
		GameStart = !GameStart;
	else if (!GameStart && wParam == 'q')
		PostQuitMessage(0);
	else if (!GameStart && wParam == 'r')
		m_pGameFramework->ChangeScene(ENUM_SCENEID::GAMESCENE);
	else if (wParam == 'p')
		mBackGround.SetGrid();
	if (GameStart)
	{
		switch (message)
		{
		case WM_LBUTTONDOWN: LButton(lParam); break;
		case WM_LBUTTONUP: LButtonUP(lParam); break;
		case WM_MOUSEMOVE:mCard.MouseMove(lParam); break;
		}
	}
}

void CGameScene::Release()
{
	for (int i = 0; i < PLAYER_MAX; ++i)
	{
		if (mPlayer[i])
		{
			delete mPlayer[i];
			mPlayer[i] = nullptr;
		}
	}
	for (int i = 0; i < ZOMBIE_MAX; ++i)
	{
		if (mZombie[i])
		{
			delete mZombie[i];
			mZombie[i] = nullptr;
		}
	}
	for (int i = 0; i < MINERAL_MAX; ++i)
	{
		if (mMineral[i])
		{
			delete mMineral[i];
			mMineral[i] = nullptr;
		}
	}
	for (int i = 0; i < BULLET_MAX; ++i)
	{
		if (mBullet[i])
		{
			delete mBullet[i];
			mBullet[i] = nullptr;
		}
	}
}

void CGameScene::CreateBitPath(HWND hWnd)
{
	m_MapBmp["BackGround"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Background1.bmp");
	// 카드
	m_MapBmp["P01"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Peashooter01.bmp");
	m_MapBmp["P02"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Peashooter02.bmp");
	m_MapBmp["P03"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Peashooter03.bmp");
	m_MapBmp["P04"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Peashooter04.bmp");
	m_MapBmp["P05"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Peashooter05.bmp");
	m_MapBmp["P06"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Peashooter06.bmp");

	// 삽
	m_MapBmp["Del"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Delete.bmp");

	// 플레이어
	m_MapBmp["Player01"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Player01.bmp");
	m_MapBmp["Player02"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Player02.bmp");
	m_MapBmp["Player03"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Player03.bmp");
	m_MapBmp["Player04"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Player04.bmp");
	m_MapBmp["Player05"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Player05.bmp");
	m_MapBmp["Player06"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Player06.bmp");


	// 총알 
	m_MapBmp["Bullet01"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/plantbullet.bmp");
	m_MapBmp["Bullet02"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/bullet01.bmp");
	m_MapBmp["Bullet03"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/bullet02.bmp");

	// 아이템
	m_MapBmp["SunItem"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/SunItem.bmp");

	// 좀비
	m_MapBmp["Z1Alive"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Zom1_Alive.bmp");
	m_MapBmp["Z1Walk"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Zom1_Walk.bmp");
	m_MapBmp["Z1Attack"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Zom1_Attack.bmp");
	m_MapBmp["Z1Die"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Zom1_Die.bmp");

	m_MapBmp["Z2Alive"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Zom2_Alive.bmp");
	m_MapBmp["Z2Walk"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Zom2_Walk.bmp");
	m_MapBmp["Z2Attack"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Zom2_Attack.bmp");
	m_MapBmp["Z2Die"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Zom2_Die.bmp");
	// 폭발
	m_MapBmp["Explosion"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/explosion01.bmp");

	m_MapBmp["Fire"] = (new CBitMap)->LoadBmp(hWnd, (PTCHAR)L"../Texture/Fire.bmp");

	// map정보 알아오기.
	CGameObj::SetBmp(&m_MapBmp);
}

void CGameScene::LButton(LPARAM lParam)
{
	Point pt = Point{ float(LOWORD(lParam)),float(HIWORD(lParam)) };
	Cardindex = mCard.LButton(lParam, mUI.GetMineral());
	for (int i = 0; i < MINERAL_MAX; ++i)
	{
		if (mMineral[i])
		{
			if (Collision(mMineral[i]->GetPos(), pt, mMineral[i]->GetRadian()))
			{
				if (mMineral[i]->GetIndex() != -1)
				{
					int num = mMineral[i]->GetIndex();
					if (mPlayer[num])
						dynamic_cast<CSunPlayer*>(mPlayer[num])->SetStopCreateMineral(false);
				}
				mMineral[i]->SetClick(true);
				mUI.AddMineral(mMineral[i]->GetPrice());
				mSound.Play(EFFECT2);
			}
		}
	}
}

void CGameScene::LButtonUP(LPARAM lParam)
{
	if (Cardindex != -1 && mCard.GetCardClick(Cardindex))
		CreatePlayers(lParam);
	for (int i = 0; i < CARD_MAX; ++i)
		mCard.SetCardClick(i, false);

	if (mCard.GetDelClick())
	{
		DeletePlayers(lParam);
		mCard.SetDelClick(false);
	}
	mCard.SetClick(false);
}

void CGameScene::CreatePlayers(LPARAM lParam)
{
	POINT pt = POINT{ LOWORD(lParam),HIWORD(lParam) };
	int x = ((pt.x - X_START) / X_RECT);
	int y = ((pt.y - Y_START) / Y_RECT);
	if (!Life[y])
		return;
	if (x <= 0 || x >= ROW - 1)		// 좀비 나오는 곳에서 생성 못하게 막는다.
		return;
	if (PtInRect(&mBackGround.GetRect(x, y), pt))
	{
		if (!mBackGround.GetBeing(x, y))
		{
			int count = (y * COLUMN) + x;	// 플레이어가 놓일 인덱스 값
			if (mCard.GetType(Cardindex) == ENUM_PLAYERS::SUN)
				mPlayer[count] = new CSunPlayer(mBackGround.GetBoard(x, y));
			else if (mCard.GetType(Cardindex) == ENUM_PLAYERS::PLANT)
				mPlayer[count] = new CAttackPlayer(mBackGround.GetBoard(x, y));
			else if (mCard.GetType(Cardindex) == ENUM_PLAYERS::SEED)
				mPlayer[count] = new CShieldPlayer(mBackGround.GetBoard(x, y));
			else if (mCard.GetType(Cardindex) == ENUM_PLAYERS::BOMB)
				mPlayer[count] = new CBombPlayer(mBackGround.GetBoard(x, y));
			else if (mCard.GetType(Cardindex) == ENUM_PLAYERS::SNOW)
				mPlayer[count] = new CSnowPlayer(mBackGround.GetBoard(x, y));
			else if (mCard.GetType(Cardindex) == ENUM_PLAYERS::PARABOLA)
				mPlayer[count] = new CParabolaPlayer(mBackGround.GetBoard(x, y));
			mBackGround.SetBeing(x, y, true);
			mCard.SetCoolTimeStart(Cardindex, true);
			mUI.SubMineral(mCard.GetPrice(Cardindex));
			mSound.Play(EFFECT1);
			// 콘솔에다 보드판 그리기
			mBackGround.BoardShow();
		}
	}
}

void CGameScene::DeletePlayers(LPARAM lParam)
{
	POINT pt = POINT{ LOWORD(lParam),HIWORD(lParam) };
	int x = ((pt.x - X_START) / X_RECT);
	int y = ((pt.y - Y_START) / Y_RECT);

	if (PtInRect(&mBackGround.GetRect(x, y), pt))
	{
		if (mBackGround.GetBeing(x, y))
		{
			int count = (y * COLUMN) + x;	// 플레이어가 놓일 인덱스 값
			delete mPlayer[count];
			mPlayer[count] = nullptr;
			mBackGround.SetBeing(x, y, false);
			mSound.Play(EFFECT1);
			// 좀비가 플레이어를 공격중일 때 삽으로 삭제시 좀비 상태 변화 시키기.
			for (int j = 0; j < ZOMBIE_MAX; ++j)
			{
				if (mZombie[j] && mZombie[j]->GetIndex() == count)
					mZombie[j]->SetState(ENUM_ANIM_STATE::WALK);
			}
			// 콘솔에다 보드판 그리기
			mBackGround.BoardShow();
		}
	}
}

void CGameScene::DeletePlayers(CPlayer *& player)
{
	if (player->GetExplosion() == ENUM_STATE::DELETE_STATE)
	{
		POINT p = player->GetPosIndex();
		delete player;
		player = nullptr;
		mBackGround.SetBeing(p.x, p.y, false);
	}
}

void CGameScene::CreateMineral(CMineral* &mineral)
{
	if (MineralTime > MaxMineralTime && !mineral)
	{
		float x = float(rand() % 650 + 100);
		mineral = new CMineral(Point{ x,0 }, -1);
		MineralTime = 0;
	}

	// Sun에서 생성
	if (!mineral)
	{
		for (int i = 0; i < PLAYER_MAX; ++i)
		{
			if (dynamic_cast<CSunPlayer*>(mPlayer[i]) && !dynamic_cast<CSunPlayer*>(mPlayer[i])->GetStopCreateMineral()
				&& dynamic_cast<CSunPlayer*>(mPlayer[i])->GetCreateMineral())
			{
				mineral = new CMineral(mPlayer[i]->GetPos(), i);
				dynamic_cast<CSunPlayer*>(mPlayer[i])->SetStopCreateMineral(true);
			}
		}
	}
}

void CGameScene::DeleteMineral(CMineral* &mineral)
{
	if (mineral && (mineral->GetPos().y > 600|| mineral->GetDelete()))
	{
		delete mineral;
		mineral = nullptr;
	}
}

void CGameScene::CreateZombie(CZombie* &zombie)
{
	if (ZombieTime > MaxZombieTime && !zombie)
	{
		int type = rand() % 2;
		int y = rand() % 5;
		if (Life[y])
		{
			if (type == 0)
				zombie = new CNormalZombie(mBackGround.GetBoard(ROW - 1, y), ENUM_LEVEL(Level));
			else
				zombie = new CStrongZombie(mBackGround.GetBoard(ROW - 1, y), ENUM_LEVEL(Level));
			ZombieTime = 0;
		}
	}
}

void CGameScene::DeleteZombie(CZombie *& zombie)
{
	if (zombie)
	{
		int y = int(zombie->GetPos().y);
		// 좀비 왼쪽에 도달했을 때 
		if (RectCollision(zombie->GetRect(), mBackGround.GetRect(0, y)) &&
			zombie->GetExplosion() == ENUM_STATE::NON_STATE)
		{
			Life[y] = false;
			// 좀비 삭제
			for (int i = 0; i < ZOMBIE_MAX; ++i)
			{
				if (mZombie[i])
				{
					if (mZombie[i]->GetPos().y == y)
					{
						mZombie[i]->SetZeroHP();
						mZombie[i]->SetState(ENUM_ANIM_STATE::DIE);
						mZombie[i]->SetExplosion(ENUM_STATE::EXPLOSION_STATE);
					}
				}
			}
			// 플레이어 삭제
			for (int i = 0; i < PLAYER_MAX; ++i)
			{
				if (mPlayer[i])
				{
					if (mPlayer[i]->GetPosIndex().y == y)
					{
						if (mPlayer[i]->GetExplosion() == ENUM_STATE::NON_STATE)
						{
							mPlayer[i]->SetZeroHP();
							mPlayer[i]->SetExplosion(ENUM_STATE::EXPLOSION_STATE);
						}
					}
				}
			}
			// 불 바다 만들기
			for (int i = 0; i < ROW - 1; ++i)
				mBackGround.SetFire(i, y, true);
		}	
		else if (zombie->GetExplosion() == ENUM_STATE::DELETE_STATE)
		{
			delete zombie;
			zombie = nullptr;

			int count = 0;
			for (int i = 0; i < LIFE_MAX; ++i)
			{
				if (!Life[i])
					++count;
			}
			// 게임오버
			if (count == LIFE_MAX)
				m_pGameFramework->ChangeScene(ENUM_SCENEID::OVERSCENE);
		}
	}
}

void CGameScene::CreateBullect(CPlayer *& player)
{
	bool isNormalBullect = dynamic_cast<CAttackPlayer*>(player) && dynamic_cast<CAttackPlayer*>(player)->GetBulletCreate();
	bool isSnowBullect = dynamic_cast<CSnowPlayer*>(player) && dynamic_cast<CSnowPlayer*>(player)->GetBulletCreate();
	bool isParabolaBullect = dynamic_cast<CParabolaPlayer*>(player) && dynamic_cast<CParabolaPlayer*>(player)->GetBulletCreate();

	if (ZombieBeing(player))
	{
		for (int i = 0; i < BULLET_MAX; ++i)
		{
			if (!mBullet[i])
			{
				if (isNormalBullect)
				{
					mBullet[i] = new CNormalBullet(player->GetPos());
					break;
				}
				else if (isSnowBullect)
				{
					mBullet[i] = new CSnowBullet(player->GetPos());
					break;
				}
				else if (isParabolaBullect)
				{
					mBullet[i] = new CParabolaBullet(player->GetPos(), mZombie[ZombieIndex]->GetRect());
					break;
				}
			}
		}
	}
}

bool CGameScene::ZombieBeing(CPlayer *& player)
{
	for (int i = 0; i < ZOMBIE_MAX; ++i)
	{
		if (mZombie[i])
		{
			bool isX = player->GetPos().x <= mZombie[i]->GetRect().right;
			bool isY = player->GetPosIndex().y == mZombie[i]->GetPosIndex().y;
			bool isResult = isX && isY;
			if (isResult &&  mZombie[i]->GetState() != ENUM_ANIM_STATE::DIE)
			{
				if (dynamic_cast<CParabolaPlayer*>(player))
					ZombieIndex = i;
				return true;
			}
		}
	}
	return false;
}

void CGameScene::DeleteBullect(CBullet *& bullect)
{
	if (bullect->GetPos().x > CLIENT_WIDTH || bullect->GetExplosion() == ENUM_STATE::DELETE_STATE)
	{
		delete bullect;
		bullect = nullptr;
	}
	else if(bullect->GetExplosion() == ENUM_STATE::NON_STATE)
	{
		BulletAndZombieCollision(bullect);
	}
}

void CGameScene::ZombieAndPlayerCollision(CZombie *& zombie)
{
	for (int i = 0; i < PLAYER_MAX; ++i)
	{
		if (mPlayer[i])
		{
			bool isNotPass = mPlayer[i]->GetRect().left <= zombie->GetRect().left;
			if (isNotPass && RectCollision(zombie->GetRect(), mPlayer[i]->GetRect()))
			{
				if (zombie->GetState() == ENUM_ANIM_STATE::WALK)
				{
					zombie->SetState(ENUM_ANIM_STATE::ATTACK);
					zombie->SetIndex(i);
				}
				if (zombie->GetState() == ENUM_ANIM_STATE::ATTACK && zombie->GetAttackMotion() == 4 && zombie->GetAttackDamage())
				{
					mPlayer[i]->SetDamage(zombie->GetAttack());
					zombie->SetAttackDamage(false);
					mSound.Play(EFFECT4);
				}
				else if (zombie->GetAttackMotion() == 5)
					zombie->SetAttackDamage(true);

				if (mPlayer[i]->GetHP() <= 0)
				{
					for (int j = 0; j < ZOMBIE_MAX; ++j)
					{
						if (mZombie[j] && mZombie[j]->GetIndex() == i)
							mZombie[j]->SetState(ENUM_ANIM_STATE::WALK);
					}
					if(mPlayer[i]->GetExplosion() == ENUM_STATE::NON_STATE)
						mPlayer[i]->SetExplosion(ENUM_STATE::EXPLOSION_STATE);
				}
			}
		}
	}
}

void CGameScene::BulletAndZombieCollision(CBullet *& bullet)
{
	for (int i = 0; i < ZOMBIE_MAX; ++i)
	{
		if (mZombie[i])
		{
			if (mZombie[i]->GetState() == ENUM_ANIM_STATE::ATTACK || mZombie[i]->GetState() == ENUM_ANIM_STATE::WALK)
			{
				// 포물선 총알
				float y = float(mZombie[i]->GetRect().top);
				if (dynamic_cast<CParabolaBullet*>(bullet))
				{
					if (y == dynamic_cast<CParabolaBullet*>(bullet)->GetZombiePos())
					{
						if (PointAndRectCollision(bullet->GetPos(), mZombie[i]->GetRect()))
						{
							mZombie[i]->SetDamage(bullet->GetAttack());
							bullet->SetExplosion(ENUM_STATE::EXPLOSION_STATE);
							mSound.Play(EFFECT3);
							if (mZombie[i]->GetHP() <= 0 && mZombie[i]->GetState() != ENUM_ANIM_STATE::DIE)
								mZombie[i]->SetState(ENUM_ANIM_STATE::DIE);
							break;
						}
					}
				}
				else
				{
					if (PointAndRectCollision(bullet->GetPos(), mZombie[i]->GetRect()))
					{
						if (dynamic_cast<CSnowBullet*>(bullet))
							mZombie[i]->SetStopMove(true);
						mZombie[i]->SetDamage(bullet->GetAttack());
						bullet->SetExplosion(ENUM_STATE::EXPLOSION_STATE);
						mSound.Play(EFFECT3);
						if (mZombie[i]->GetHP() <= 0 && mZombie[i]->GetState() != ENUM_ANIM_STATE::DIE)
							mZombie[i]->SetState(ENUM_ANIM_STATE::DIE);
						break;
					}
				}
			}
		}
	}
}

void CGameScene::BombAndZombieCollision(CPlayer *& bomb)
{
	for (int i = 0; i < ZOMBIE_MAX; ++i)
	{
		if (mZombie[i])
		{
			if (RectCollision(dynamic_cast<CBombPlayer*>(bomb)->GetBombRect(), mZombie[i]->GetRect()))
			{
				dynamic_cast<CBombPlayer*>(bomb)->SetRedColor();
				mZombie[i]->SetZeroHP();
				mZombie[i]->SetState(ENUM_ANIM_STATE::DIE);
				mZombie[i]->SetExplosion(ENUM_STATE::EXPLOSION_STATE);
				if (dynamic_cast<CBombPlayer*>(bomb)->GetBombSound() == ENUM_MOUSESOUND::NON_SOUND)
				{
					mSound.Play(EFFECT5);
					dynamic_cast<CBombPlayer*>(bomb)->SetBombSound(ENUM_MOUSESOUND::START_SOUND);
				}
				bomb->SetZeroHP();
				bomb->SetExplosion(ENUM_STATE::EXPLOSION_STATE);
			}
		}
	}
}
