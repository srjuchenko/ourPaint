#pragma once
#include "OurShape.h"
class OurLine : public OurShape
{
	DECLARE_SERIAL(OurLine)
public:
	OurLine() :OurShape() {}
	OurLine(const CPoint& start, const CPoint& end,const COLORREF& bColor, const int& border);

	virtual void draw(CDC* dc);
};

