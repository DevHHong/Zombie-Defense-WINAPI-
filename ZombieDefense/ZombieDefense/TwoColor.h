#pragma once
class CTwoColor
{
	UCHAR m_colorA[3];
	UCHAR m_colorB[3];
public:
	CTwoColor(UCHAR Ar, UCHAR Ag, UCHAR Ab, UCHAR Br, UCHAR Bg, UCHAR Bb);
	virtual ~CTwoColor();
	COLORREF GetDeltaColor(float delta);
};

