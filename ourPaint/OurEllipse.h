#pragma once
#include "OurShape.h"
class OurEllipse : public OurShape
{
	DECLARE_SERIAL(OurEllipse)
public:
	OurEllipse() :OurShape() {}
	OurEllipse(const CPoint& start, const CPoint& end, const COLORREF& bColor, const COLORREF& fcolor, const int& border);
	~OurEllipse() {}
	virtual void draw(CDC* dc);
};

