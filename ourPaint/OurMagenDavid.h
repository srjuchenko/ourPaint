#pragma once
#include "OurPolygon.h"
class OurMagenDavid : public OurPolygon
{
	DECLARE_SERIAL(OurMagenDavid)
protected:
	CPoint vertices[12];
	CPoint center;

public:
	OurMagenDavid() : OurPolygon() {}
	OurMagenDavid(const CPoint& start, const CPoint& end, const COLORREF& bColor, const COLORREF& fcolor, const int& border, const int& numOfEdges);


	virtual void draw(CDC* dc);

	virtual void Serialize(CArchive& archive);

};

