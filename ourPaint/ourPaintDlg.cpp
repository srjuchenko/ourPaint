
// ourPaintDlg.cpp : implementation file
//
//
#include "pch.h"
#include "framework.h"
#include "ourPaint.h"
#include "ourPaintDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


//constructor
CourPaintDlg::CourPaintDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OURPAINT_DIALOG, pParent)
{
	startP = 0;
	endP = 0;
	borderColor = RGB(0, 0, 0);
	fillColor = RGB(255, 255, 255);
	borderSize = 1;
	lButtonPressed = false;
	rButtonPressed = false;
	isEraserPressed = false;
	fillColorBtn.SetColor(RGB(255, 255, 255));
	oldpoint = 0;


	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CourPaintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OURBORDERCLRBTN, borderColorBtn);
	DDX_Control(pDX, IDC_FILLCOLORBTN, fillColorBtn);
	DDX_Control(pDX, IDC_COMBO1, BORDERSIZEBTN);
}

BEGIN_MESSAGE_MAP(CourPaintDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_OURNEWPAGE, &CourPaintDlg::OnOurnewpage)
	ON_COMMAND(ID_OURSAVEBTN, &CourPaintDlg::OnOursavebtn)
	ON_COMMAND(ID_OURLOADBTN, &CourPaintDlg::OnOurloadbtn)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_OURLINEBTN, &CourPaintDlg::OnOurlinebtn)
	ON_BN_CLICKED(IDC_OURBORDERCLRBTN, &CourPaintDlg::OnBnClickedOurborderclrbtn)
	ON_COMMAND(ID_OURELLIPSEBTN, &CourPaintDlg::OnOurellipsebtn)
	ON_COMMAND(ID_OURRECTANGLEBTN, &CourPaintDlg::OnOurrectanglebtn)
	ON_COMMAND(ID_OURMAGENDVDBTN, &CourPaintDlg::OnOurmagendvdbtn)
	ON_BN_CLICKED(IDC_FILLCOLORBTN, &CourPaintDlg::OnBnClickedFillcolorbtn)
	ON_COMMAND(ID_OURTRIANGLEBTN, &CourPaintDlg::OnOurtrianglebtn)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_OURERASEBTN, &CourPaintDlg::OnOurerasebtn)
	ON_COMMAND(ID_OURUNDOBTN, &CourPaintDlg::OnOurundobtn)
	ON_COMMAND(ID_OURREDOBTN, &CourPaintDlg::OnOurredobtn)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CourPaintDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CourPaintDlg message handlers

BOOL CourPaintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	if (!ourToolBar.CreateEx(this, TBSTYLE_FLAT,
		WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS |
		CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!ourToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		EndDialog(IDCANCEL);
	}
	ourToolBar.EnableToolTips(true);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);


	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	

	return TRUE;  
}

void CourPaintDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

//on paint
void CourPaintDlg::OnPaint()
{
	//creating an empty list
	CPaintDC dc(this);
	CPen newPen(PS_SOLID, 3, RGB(100, 100, 50));
	CPen* old = dc.SelectObject(&newPen);
	dc.Rectangle(LEFT_CANVAS_LIMIT, TOP_CANVAS_LIMIT, RIGHT_CANVAS_LIMIT, BOTTOM_CANVAS_LIMIT);
	dc.SelectObject(old);
	//////////////////////////

	for (int i = 0; i < shapesArr.GetSize(); i++)
	{
		shapesArr[i]->draw(&dc);
	}

	CDialogEx::OnPaint();
}

HCURSOR CourPaintDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//new page btn
void CourPaintDlg::OnOurnewpage()
{
	if (!(shapesArr.IsEmpty()))
	{
		shapesArr.RemoveAll();
	}
	Invalidate();
}


//save btn
void CourPaintDlg::OnOursavebtn()
{
	CFileDialog dlg(FALSE, _T(".shapes"), NULL, 0, _T("Shapes (*.shapes)|*.shapes|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeCreate | CFile::modeWrite);
		CArchive archive(&file, CArchive::store);
		shapesArr.Serialize(archive);
		archive.Close();
		file.Close();
	}
}


//load btn
void CourPaintDlg::OnOurloadbtn()
{
	CFileDialog dlg(TRUE, _T(".shapes"), NULL, 0, _T("Shapes (*.shapes)|*.shapes|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeRead);
		CArchive archive(&file, CArchive::load);
		shapesArr.Serialize(archive);
		archive.Close();
		file.Close();
		Invalidate();
	}
}

//left mouse btn down 
void CourPaintDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (currentShape == NOTHING)
	{
		lButtonPressed = false;
	}
	else //if we chosed some shape before left btn 
	{
		lButtonPressed = true;
	}

	if (lButtonPressed && isEraserPressed)
	{
		int index = 0;
		if (isInside(point, index))
		{
			tmpShapesArr.Add(shapesArr[index]);
			shapesArr.RemoveAt(index, 1);
			Invalidate();
			
		}
		lButtonPressed = false;
	}
	
	
	if (lButtonPressed && currentShape != NOTHING)
	{
		startP = endP = point;
		if (isStartPointOnCanvas(startP))
		{
			switch (currentShape)
			{
			case LINE:
				shapesArr.Add(new OurLine(startP, endP, borderColor, borderSize));
				break;
			case ELLIPSE:
				shapesArr.Add(new OurEllipse(startP, endP, borderColor, fillColor, borderSize));
				break;

			case RECTANGLE:
				shapesArr.Add(new OurRectangle(startP, endP, borderColor, fillColor, borderSize, 4)); // 4 its a number of edges
				break;
			case MAGENDAVID:
				shapesArr.Add(new OurMagenDavid(startP, endP, borderColor, fillColor, borderSize, 12));// 12 its a number of edges
				break;
			case TRIANGLE:
				shapesArr.Add(new OurTriangle(startP, endP, borderColor, fillColor, borderSize, 3));//3 its a number of edges
				break;
			}
		}
		else
		{
			lButtonPressed = false;
		}
		
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

//mouse move event
void CourPaintDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (lButtonPressed && currentShape != NOTHING)
	{
		endP = setEndPoint(point);
		
		shapesArr[shapesArr.GetSize() - 1]->Redefine(startP, endP); //changes the end point everytime when mouse moves.
		
		//invalidate around our new added object
		RECT r;
		r.left = min(shapesArr[shapesArr.GetSize() - 1]->getStartPointX() ,shapesArr[shapesArr.GetSize() - 1]->getEndPointX())-30;
		r.right = max(shapesArr[shapesArr.GetSize() - 1]->getStartPointX(), shapesArr[shapesArr.GetSize() - 1]->getEndPointX()) + 30;
		r.top = min(shapesArr[shapesArr.GetSize() - 1]->getStartPointY(), shapesArr[shapesArr.GetSize() - 1]->getEndPointY()) - 30;
		r.bottom = max(shapesArr[shapesArr.GetSize() - 1]->getStartPointY(), shapesArr[shapesArr.GetSize() - 1]->getEndPointY()) + 30;
		InvalidateRect(&r);
	}

	// shifhting shape
	if (rButtonPressed && currentShape != NOTHING)
	{
		
		CPoint diff = point - oldpoint;
		shapesArr[shapesArr.GetSize() - 1]->shift(diff.x, diff.y); 
		
		RECT r;
		r.left = min(shapesArr[shapesArr.GetSize() - 1]->getStartPointX(), shapesArr[shapesArr.GetSize() - 1]->getEndPointX()) - 30;
		r.right = max(shapesArr[shapesArr.GetSize() - 1]->getStartPointX(), shapesArr[shapesArr.GetSize() - 1]->getEndPointX()) + 30;
		r.top = min(shapesArr[shapesArr.GetSize() - 1]->getStartPointY(), shapesArr[shapesArr.GetSize() - 1]->getEndPointY()) - 30;
		r.bottom = max(shapesArr[shapesArr.GetSize() - 1]->getStartPointY(), shapesArr[shapesArr.GetSize() - 1]->getEndPointY()) + 30;
		InvalidateRect(&r);
		oldpoint = point;
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

//left mouse btn up
void CourPaintDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (lButtonPressed && currentShape != NOTHING)
	{
		endP = setEndPoint(point);
		lButtonPressed = false;
		shapesArr[shapesArr.GetSize() - 1]->Redefine(startP, endP);
		Invalidate();
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

//line btn
void CourPaintDlg::OnOurlinebtn()
{
	setPressedOnBtn(3);
	currentShape = LINE;
	isEraserPressed = false;
}

//border color btn 
void CourPaintDlg::OnBnClickedOurborderclrbtn()
{
	borderColor = borderColorBtn.GetColor();
	isEraserPressed = false;
}

//helping function, returns if the start point is on the canvas
bool CourPaintDlg::isStartPointOnCanvas(const CPoint& startPoint)
{
	if (startPoint.y < TOP_CANVAS_LIMIT)
		return false;
	if (startPoint.x > RIGHT_CANVAS_LIMIT)
		return false;
	if (startPoint.y > BOTTOM_CANVAS_LIMIT)
		return false;
	if (startPoint.x < LEFT_CANVAS_LIMIT)
		return false;

	//if the start point on canvas
	return true;

}

//helping function, changes the end point if the user draws after the limit 
CPoint CourPaintDlg::setEndPoint(const CPoint& endP)
{
	CPoint tmp=endP;
	if (endP.y < TOP_CANVAS_LIMIT)
	{
		tmp.y = TOP_CANVAS_LIMIT;
		return tmp;
	}
	if (endP.x > RIGHT_CANVAS_LIMIT)
	{
		tmp.x = RIGHT_CANVAS_LIMIT;
		return tmp;
	}
	if (endP.y > BOTTOM_CANVAS_LIMIT)
	{
		tmp.y = BOTTOM_CANVAS_LIMIT;
		return tmp;
	}
	return tmp;
}

//ellipse btn
void CourPaintDlg::OnOurellipsebtn()
{
	setPressedOnBtn(4);
	currentShape = ELLIPSE;
	isEraserPressed = false;
}

//rectangle btn
void CourPaintDlg::OnOurrectanglebtn()
{
	setPressedOnBtn(5);
	currentShape = RECTANGLE;
	isEraserPressed = false;
}

//magen david btn
void CourPaintDlg::OnOurmagendvdbtn()
{
	setPressedOnBtn(6);
	currentShape = MAGENDAVID;
	isEraserPressed = false;
}

//fill color btn 
void CourPaintDlg::OnBnClickedFillcolorbtn()
{
	fillColor = fillColorBtn.GetColor();
	isEraserPressed = false;
}

//triangle btn
void CourPaintDlg::OnOurtrianglebtn()
{
	setPressedOnBtn(7);
	currentShape = TRIANGLE;
	isEraserPressed = false;
}

//right mouse btn down
void CourPaintDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (lButtonPressed == false)
	{
		rButtonPressed = true;
	}
	
	int index=0; //index of the relevant shape
	if (rButtonPressed && isInside(point,index))
	{
		CClientDC dc(this);
		
		CPen newPen(PS_DASHDOT, 0.7, RGB(128, 128, 128));
		CPen* oldPen = dc.SelectObject(&newPen);
		dc.Rectangle(shapesArr[index]->getStartPointX()- (shapesArr[index]->getBorderSize()+3)
			, shapesArr[index]->getStartPointY()- (shapesArr[index]->getBorderSize() + 3)
			, shapesArr[index]->getEndPointX()+ (shapesArr[index]->getBorderSize() + 3)
			, shapesArr[index]->getEndPointY()+ (shapesArr[index]->getBorderSize() + 3));
		
		dc.SelectObject(oldPen);
		shapesArr[index]->draw(&dc);
		shapesArr.Add(shapesArr[index]);
		shapesArr.RemoveAt(index, 1);
		
		oldpoint = point;
	}

	CDialogEx::OnRButtonDown(nFlags, point);
}

//right mouse btn up
void CourPaintDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (rButtonPressed)
	{
		CPoint diff = point - oldpoint;
		shapesArr[shapesArr.GetSize() - 1]->shift(diff.x, diff.y);
		saveShapeIntoCanvas(shapesArr[shapesArr.GetSize() - 1]->getStartPoint(), shapesArr[shapesArr.GetSize() - 1]->getEndPoint());

		rButtonPressed = false;
		Invalidate();
	}

	CDialogEx::OnRButtonUp(nFlags, point);
}

//helping function, returns if the current point of the cursor is inside the shape and changes the index by reference  
bool CourPaintDlg::isInside(CPoint& point,int &index)
{
	for (int i = shapesArr.GetSize() - 1; i >= 0; i--)
	{
		if (shapesArr[i]->isInside(point))
		{
			index = i;
			return true;
		}
	}
}

//helping function, changes the shape position if the user moves the shape above the limits
void CourPaintDlg::saveShapeIntoCanvas(const CPoint& start, const CPoint& end)
{
	int diff=0;

	if (end.x > RIGHT_CANVAS_LIMIT )
	{
		diff = end.x - RIGHT_CANVAS_LIMIT;
		shapesArr[shapesArr.GetSize() - 1]->shift((-1)*diff,0);
	}
	else if (end.y > BOTTOM_CANVAS_LIMIT)
	{
		diff = end.y - BOTTOM_CANVAS_LIMIT;
		shapesArr[shapesArr.GetSize() - 1]->shift(0, (-1)*diff);
	}
	else if (start.y < TOP_CANVAS_LIMIT)
	{
		diff = start.y - TOP_CANVAS_LIMIT;
		shapesArr[shapesArr.GetSize() - 1]->shift(0, (-1) * diff);
	}
	else if (start.x < LEFT_CANVAS_LIMIT)
	{
		diff = start.x - LEFT_CANVAS_LIMIT;
		shapesArr[shapesArr.GetSize() - 1]->shift((-1) * diff, 0);
	}

	//shapesArr[shapesArr.GetSize() - 1]->shift((-1) * diff, (-1)*diff);

	diff = 0;
	if (start.x > RIGHT_CANVAS_LIMIT)
	{
		diff = start.x - RIGHT_CANVAS_LIMIT;
	}
	else if (start.y > BOTTOM_CANVAS_LIMIT)
	{
		diff = start.y - BOTTOM_CANVAS_LIMIT;
	}
	else if (end.y < TOP_CANVAS_LIMIT)
	{
		diff = end.y - TOP_CANVAS_LIMIT;
	}
	else if (end.x < LEFT_CANVAS_LIMIT)
	{
		diff = end.x - LEFT_CANVAS_LIMIT;
	}

	shapesArr[shapesArr.GetSize() - 1]->shift((-1) * diff, (-1) * diff);
}

//erase btn
void CourPaintDlg::OnOurerasebtn()
{
	setPressedOnBtn(8);
	isEraserPressed = true;
}

//undo btn
void CourPaintDlg::OnOurundobtn()
{
	int lastIndex = shapesArr.GetSize() - 1;
	if (!shapesArr.IsEmpty())
	{
		tmpShapesArr.Add(shapesArr[lastIndex]);
		shapesArr.RemoveAt(lastIndex, 1);
		Invalidate();
	}
}

//redo btn
void CourPaintDlg::OnOurredobtn()
{
	int lastIndex = tmpShapesArr.GetSize() - 1;
	if (!tmpShapesArr.IsEmpty())
	{
		shapesArr.Add(tmpShapesArr[lastIndex]);
		tmpShapesArr.RemoveAt(lastIndex, 1);
		Invalidate();
	}

}

//border size btn
void CourPaintDlg::OnCbnSelchangeCombo1()
{
	CString borderString;
	BORDERSIZEBTN.GetLBText(BORDERSIZEBTN.GetCurSel(), borderString);
	borderSize = _wtoi(borderString);
}

//this function display which button is checked 
void CourPaintDlg::setPressedOnBtn(int index)
{
	for (int i = 3; i <= 8; i++)
	{
		ourToolBar.SetButtonStyle(i, TBBS_BREAK);
	}
	ourToolBar.SetButtonStyle(index, TBBS_PRESSED);
}