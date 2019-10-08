#include "stdafx.h"
#include "TwoColor.h"

CTwoColor::CTwoColor(UCHAR Ar, UCHAR Ag, UCHAR Ab, UCHAR Br, UCHAR Bg, UCHAR Bb)
{
	m_colorA[0] = Ar;
	m_colorA[1] = Ag;
	m_colorA[2] = Ab;

	m_colorB[0] = Br;
	m_colorB[1] = Bg;
	m_colorB[2] = Bb;
}

CTwoColor::~CTwoColor()
{
}

COLORREF CTwoColor::GetDeltaColor(float delta)
{
	float tempDelta = CLIP(0.f, delta, 1.f);		// 0<delta<1 

	UCHAR tempcolor[3];		// °á°ú°ª

	for (int i = 0; i < 3; ++i)
	{
		int colorD = m_colorB[i] - m_colorA[i];
		tempcolor[i] = UCHAR(m_colorA[i] + colorD * tempDelta);
	}

	return RGB(tempcolor[0], tempcolor[1], tempcolor[2]);
}
