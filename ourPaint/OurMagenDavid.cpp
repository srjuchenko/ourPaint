#include "pch.h"
#include "OurMagenDavid.h"

IMPLEMENT_SERIAL(OurMagenDavid, CObject, 1)

OurMagenDavid::OurMagenDavid(const CPoint& start, const CPoint& end, const COLORREF& bColor, const COLORREF& fcolor, const int& border, const int& numOfEdges)
	:OurPolygon(start,end,bColor,fcolor,border,numOfEdges)
{
	
}

void OurMagenDavid::draw(CDC* dc)
{
    CPoint center = startPoint + endPoint;
    center.x /= 2.0; center.y /= 2.0;
    double radius = abs(startPoint.x - endPoint.x) < abs(startPoint.y - endPoint.y) ? abs(startPoint.x - endPoint.x) / 2.0 : abs(startPoint.y - endPoint.y) / 2.0;
    double two_pi = atan(1) * 8;
    for (int i = 0; i < 12; i++)
    {
        if (i % 2 == 0)
        {
            vertices[i].x = center.x + radius / sqrt(3) * cos(two_pi / 12 * i);
            vertices[i].y = center.y + radius / sqrt(3) * sin(two_pi / 12 * i);
        }
        else
        {
            vertices[i].x = center.x + radius * cos(two_pi / 12 * i);
            vertices[i].y = center.y + radius * sin(two_pi / 12 * i);
        }
    }
    CPen pen(PS_SOLID, borderSize, borderColor);
    CPen* old = dc->SelectObject(&pen);
    CBrush brush(fillColor);
    CBrush* oldB = dc->SelectObject(&brush);

    dc->Polygon(vertices, 12);

    dc->SelectObject(old);
    dc->SelectObject(oldB);
}

void OurMagenDavid::Serialize(CArchive& archive)
{
    OurPolygon::Serialize(archive);

    if (archive.IsStoring())
    {
        archive << center;
        for (int i = 0; i < edges; i++)
        {
            archive << vertices[i];
        }
    }
    else
    {
        archive >> center;
        for (int i = 0; i < edges; i++)
        {
            archive >> vertices[i];
        }
    }

}
