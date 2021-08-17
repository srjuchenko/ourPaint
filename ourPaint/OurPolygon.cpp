#include "pch.h"
#include "OurPolygon.h"

IMPLEMENT_SERIAL(OurPolygon,CObject,1)

OurPolygon::OurPolygon(const CPoint& start, const CPoint& end, const COLORREF& bColor, const COLORREF& fcolor, const int& border, const int& numOfEdges)
	:OurShape(start,end,bColor,fcolor,border)
{
	edges = numOfEdges;
}

void OurPolygon::Serialize(CArchive& archive)
{
	OurShape::Serialize(archive);

	if (archive.IsStoring())
	{
		archive << edges;
	}
	else
	{
		archive >> edges;
	}
}
