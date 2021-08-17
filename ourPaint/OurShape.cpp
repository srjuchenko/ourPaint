#include "pch.h"
#include "OurShape.h"

IMPLEMENT_SERIAL(OurShape,CObject,1)

OurShape::OurShape()
{
	borderColor = RGB(0, 0, 0);
	fillColor = RGB(255, 255, 255);
	borderSize = 1;
}

OurShape::OurShape(const CPoint& start, const CPoint& end,const COLORREF& bColor,const COLORREF& fColor,const int& border)
{
	startPoint = start;
	endPoint = end;
	borderColor = bColor;
	fillColor = fColor;
	borderSize = border;
}

void OurShape::Serialize(CArchive& archive)
{
	CObject::Serialize(archive);
	if (archive.IsStoring())
	{
		archive << startPoint;
		archive << endPoint;
		archive << borderColor;
		archive << fillColor;
		archive << borderSize;
	}
	else
	{
		archive >> startPoint;
		archive >> endPoint;
		archive >> borderColor;
		archive >> fillColor;
		archive >> borderSize;
	}
}

bool OurShape::isInside(const CPoint& P) const
{
	return (startPoint.x <= P.x && P.x <= endPoint.x || startPoint.x >= P.x && P.x >= endPoint.x) &&
		(startPoint.y <= P.y && P.y <= endPoint.y || startPoint.y >= P.y && P.y >= endPoint.y);
}

void OurShape::shift(int dx,int dy)
{
	startPoint = startPoint + CPoint(dx, dy);
	endPoint = endPoint + CPoint(dx, dy);
}

