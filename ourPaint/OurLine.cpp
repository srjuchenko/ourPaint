#include "pch.h"
#include "OurLine.h"

IMPLEMENT_SERIAL(OurLine,CObject,1)

OurLine::OurLine(const CPoint& start, const CPoint& end,const COLORREF& bColor, const int& border)
	:OurShape(start,end,bColor,RGB(255,255,255),border)
{

}

void OurLine::draw(CDC* dc)
{
	CPen newPen(PS_SOLID, borderSize, borderColor);
	CPen* oldPen = dc->SelectObject(&newPen);
	dc->MoveTo(startPoint);
	dc->LineTo(endPoint);
	dc->SelectObject(oldPen);
}
