#pragma once
#include "OurPolygon.h"
class OurRectangle : public OurPolygon
{
	DECLARE_SERIAL(OurRectangle)
public:
	OurRectangle() :OurPolygon() {}
	OurRectangle(const CPoint& start, const CPoint& end, const COLORREF& bColor, const COLORREF& fcolor, const int& border, const int& numOfEdges);
	~OurRectangle() {}
	virtual void draw(CDC* dc);

};

