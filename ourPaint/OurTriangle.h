#pragma once
#include "OurPolygon.h"
class OurTriangle : public OurPolygon
{
	DECLARE_SERIAL(OurTriangle)
protected:
	CPoint vertices[3];
public:
	OurTriangle() :OurPolygon() {}
	OurTriangle(const CPoint& start, const CPoint& end, const COLORREF& bColor, const COLORREF& fcolor, const int& border, const int& numOfEdges);

	virtual void draw(CDC* dc);
	virtual void Serialize(CArchive& archive);
};

