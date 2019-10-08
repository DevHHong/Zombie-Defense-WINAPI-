#pragma once
#include "stdafx.h"
class CBitMap
{
private:
	HDC			m_hdc, m_MemDC;
	HBITMAP		m_bitMap, m_oldbitMap;
public:
	CBitMap();
	~CBitMap();

	CBitMap* LoadBmp(HWND hwnd, PTCHAR pFileName);
	void Release();

	HDC GetMemDC()const { return m_MemDC; }

private:
	static CBitMap* m_hInstance;
public:
	static CBitMap* Instance()
	{
		if (m_hInstance == NULL)
			m_hInstance = new CBitMap();
		return m_hInstance;
	}

	void Destroy()
	{
		if (NULL != m_hInstance)
		{
			m_hInstance = NULL;
			delete m_hInstance;
		}
	}



};

