#include "stdafx.h"
#include"Point.h"

void Point::operator+=(const Point& rtmp)
{
	x += rtmp.x;
	y += rtmp.y;
}

Point normalize(const Point& tmp) {
	float tmpl = Length(tmp);
	Point returntmp(tmp.x, tmp.y);

	if (tmpl != 0)
	{
		returntmp.x /= tmpl;
		returntmp.y /= tmpl;
	}
	return returntmp;
}

bool Collision(Point a, Point b, float range)
{
	if (Length(a - b) < range)
		return true;
	else
		return false;
}

float Length(const Point& tmp) {
	return	sqrtf(tmp.x*tmp.x + tmp.y*tmp.y);
}


bool RectCollision(const RECT & rect1, const RECT & rect2)
{
	if (rect1.left > rect2.right)
		return false;
	else if (rect1.right < rect2.left)
		return false;
	else if (rect1.top > rect2.bottom)
		return false;
	else if (rect1.bottom < rect2.top)
		return false;
	return true;
}

bool PointAndRectCollision(const Point & pt, const RECT & rect)
{
	if (pt.x > rect.right)
		return false;
	else if (pt.x < rect.left)
		return false;
	else if (pt.y > rect.bottom)
		return false;
	else if (pt.y < rect.top)
		return false;
	return true;
}
