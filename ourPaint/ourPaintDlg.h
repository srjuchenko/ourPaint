
// ourPaintDlg.h : header file
//

#pragma once

//canvas limits
#define LEFT_CANVAS_LIMIT  0
#define TOP_CANVAS_LIMIT  50
#define RIGHT_CANVAS_LIMIT 900
#define BOTTOM_CANVAS_LIMIT 730
//canvas limits


#include "OurShape.h"
#include "OurLine.h"
#include "OurEllipse.h"
#include "OurPolygon.h"
#include "OurRectangle.h"
#include "OurMagenDavid.h"
#include "OurTriangle.h"
// CourPaintDlg dialog
class CourPaintDlg : public CDialogEx
{
protected:
	CToolBar ourToolBar;

	CPoint startP;
	CPoint endP;
	COLORREF borderColor;
	COLORREF fillColor;
	int borderSize;
	enum SHAPES{NOTHING,LINE,RECTANGLE,ELLIPSE,TRIANGLE,MAGENDAVID};
	SHAPES currentShape = NOTHING;


	CTypedPtrArray<CObArray, OurShape*> shapesArr;
	CTypedPtrArray<CObArray, OurShape*> tmpShapesArr;

	bool lButtonPressed;
	bool rButtonPressed;
	bool isEraserPressed;
 
	bool isInside(CPoint& point,int& index);
	void saveShapeIntoCanvas(const CPoint& start, const CPoint& end);
	bool isStartPointOnCanvas(const CPoint& startPoint);
	CPoint setEndPoint(const CPoint& endP);

	CPoint oldpoint;

// Construction
public:
	CourPaintDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OURPAINT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOurnewpage();
	afx_msg void OnOursavebtn();
	afx_msg void OnOurloadbtn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnOurlinebtn();
	CMFCColorButton borderColorBtn;
	afx_msg void OnBnClickedOurborderclrbtn();
	afx_msg void OnOurellipsebtn();
	afx_msg void OnOurrectanglebtn();
	afx_msg void OnOurmagendvdbtn();
	afx_msg void OnBnClickedFillcolorbtn();
	CMFCColorButton fillColorBtn;
	afx_msg void OnOurtrianglebtn();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnOurerasebtn();
	afx_msg void OnOurundobtn();
	afx_msg void OnOurredobtn();
	CComboBox BORDERSIZEBTN;
	afx_msg void OnCbnSelchangeCombo1();
};
