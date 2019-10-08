#pragma once
#include "Player.h"
class CSunPlayer :
	public CPlayer
{
	float MineralTime;		// Èå¸£´Â ½Ã°£ (»ý¼º)
	float MaxMineralTime;	// °íÁ¤ ½Ã°£
	bool CreateMineral;
	bool StopCreate;		// ¹Ì³×¶ö »ý¼º / ¸ØÃã
public:
	CSunPlayer(BOARD b);
	virtual ~CSunPlayer();

	virtual void Create(HWND hWnd) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(const float ftime) override;
	virtual void Message(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void Release()override;

	bool GetCreateMineral()const { return CreateMineral; }
	bool GetStopCreateMineral()const { return StopCreate; }
	void SetStopCreateMineral(bool b) { StopCreate = b; }
private:
	void MineralCreatUpdate(const float ftime);
};

