#include "pch.h"
#include "OurRectangle.h"

IMPLEMENT_SERIAL(OurRectangle,CObject,1)

OurRectangle::OurRectangle(const CPoint& start, const CPoint& end, const COLORREF& bColor, const COLORREF& fcolor, const int& border, const int& numOfEdges)
	:OurPolygon(start,end,bColor,fcolor,border,numOfEdges)
{
}

void OurRectangle::draw(CDC* dc)
{
    CPen pen(PS_SOLID, borderSize, borderColor);
    CPen* old = dc->SelectObject(&pen);
    CBrush brush(fillColor);
    CBrush* oldB = dc->SelectObject(&brush);

    dc->Rectangle(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
    dc->SelectObject(old);
    dc->SelectObject(oldB);
}
