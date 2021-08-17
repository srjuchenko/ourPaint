#include "pch.h"
#include "OurTriangle.h"

IMPLEMENT_SERIAL(OurTriangle,CObject,1)

OurTriangle::OurTriangle(const CPoint& start, const CPoint& end, const COLORREF& bColor, const COLORREF& fcolor, const int& border, const int& numOfEdges)
	:OurPolygon(start,end,bColor,fcolor,border,numOfEdges)
{
}

void OurTriangle::draw(CDC* dc)
{
	vertices[0].x = (getStartPointX() + getEndPointX()) / 2;
	vertices[0].y = getStartPointY();
	vertices[1].x = getStartPointX();
	vertices[1].y = getEndPointY();
	vertices[2].x = getEndPointX();
	vertices[2].y = getEndPointY();
	CPen pen(PS_SOLID, borderSize, borderColor);
	CPen* old = dc->SelectObject(&pen);
	CBrush brush(fillColor);
	CBrush* oldB = dc->SelectObject(&brush);

	dc->Polygon(vertices, 3);

	dc->SelectObject(old);
	dc->SelectObject(oldB);
}

void OurTriangle::Serialize(CArchive& archive)
{
    OurPolygon::Serialize(archive);

    if (archive.IsStoring())
    {
        for (int i = 0; i < edges; i++)
        {
            archive << vertices[i];
        }
    }
    else
    {
        for (int i = 0; i < edges; i++)
        {
            archive >> vertices[i];
        }
    }
}

