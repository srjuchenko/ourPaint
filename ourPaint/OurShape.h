#pragma once
class OurShape : public CObject
{
	DECLARE_SERIAL(OurShape)
protected:
	CPoint startPoint;
	CPoint endPoint;                     

	COLORREF borderColor;
	COLORREF fillColor;
	
	int borderSize;

public:
	OurShape();
	OurShape(const CPoint& start, const CPoint& end,const COLORREF& bColor,const COLORREF& fcolor, const int& border);
	virtual ~OurShape() {}

	int getStartPointX() { return startPoint.x; }
	int getStartPointY() { return startPoint.y; }
	int getEndPointX() { return endPoint.x; }
	int getEndPointY() { return endPoint.y; }
	CPoint getStartPoint() { return startPoint; }
	CPoint getEndPoint() { return endPoint; }
	int getBorderSize() { return borderSize; }

	virtual void draw(CDC* dc) {}
	virtual void Serialize(CArchive& archive);
	
	virtual void Redefine(CPoint& p1, CPoint& p2) { startPoint = p1; endPoint = p2;}
	virtual bool isInside(const CPoint& P) const;
	virtual void shift(int dx, int dy);
};

