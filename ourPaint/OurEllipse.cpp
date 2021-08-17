#include "pch.h"
#include "OurEllipse.h"

IMPLEMENT_SERIAL(OurEllipse,CObject,1)

OurEllipse::OurEllipse(const CPoint& start, const CPoint& end, const COLORREF& bColor, const COLORREF& fcolor, const int& border)
	:OurShape(start,end,bColor,fcolor,border)
{
}

void OurEllipse::draw(CDC * dc)
{
    CPen pen(PS_SOLID, borderSize, borderColor);
    CPen* old = dc->SelectObject(&pen);
    CBrush brush(fillColor);
    CBrush* oldB = dc->SelectObject(&brush);

    dc->Ellipse(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
    dc->SelectObject(old);
    dc->SelectObject(oldB);
}


