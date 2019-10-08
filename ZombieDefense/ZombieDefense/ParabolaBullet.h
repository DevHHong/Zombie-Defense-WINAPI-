#pragma once
#include "Bullet.h"
class CParabolaBullet :
	public CBullet
{
	Point Start;
	Point End;
	float distance;
	float Angle;
public:
	CParabolaBullet(Point pos, RECT rect);
	virtual ~CParabolaBullet();

	virtual void Create(HWND hWnd) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(const float ftime) override;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Release()override;

	float GetZombiePos()const { return End.y; }
};

