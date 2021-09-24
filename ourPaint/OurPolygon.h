#pragma once
#include "OurShape.h" 
class OurPolygon: public OurShape
{
	DECLARE_SERIAL(OurPolygon)
protected:
	int edges;

public:
	OurPolygon() :OurShape() { edges = 0; }
	OurPolygon(const CPoint& start, const CPoint& end, const COLORREF& bColor, const COLORREF& fcolor, const int& border, const int& numOfEdges);
	~OurPolygon() {}
	virtual void Serialize(CArchive& archive);
};

