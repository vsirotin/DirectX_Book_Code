// DSMineFinderView.cpp : Implementierung der Klasse CDSMineFinderView
//

#include "stdafx.h"
#include "DSMineFinder.h"

#include "DSMineFinderDoc.h"
#include "DSMineFinderView.h"
#include "Set3DSourceDlg.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <math.h>

#define WORLD_SIZE 1000
#define MOUSE_TOLERANCE_PIX 4
#define PI 3.1415928
#define ARR_LENGTH 100

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSMineFinderView

IMPLEMENT_DYNCREATE(CDSMineFinderView, CView)

BEGIN_MESSAGE_MAP(CDSMineFinderView, CView)
	//{{AFX_MSG_MAP(CDSMineFinderView)
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSMineFinderView Konstruktion/Destruktion


CDSMineFinderView::CDSMineFinderView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

	m_bVisible = true;
	m_iRandOrUser = 1;
	m_uX = m_uY = WORLD_SIZE/2;
	m_uAngle = 0;
	m_uAnglInn = 360;
	m_uAnglOut = 0;
	m_uDistMax = WORLD_SIZE/4;
	m_uDistMin = WORLD_SIZE/100;

	m_uMinSizePix = 0;

	m_ptLastPoint = CPoint(-1, -1);
	m_bMouseMove = false;
}

CDSMineFinderView::~CDSMineFinderView()
{
}

BOOL CDSMineFinderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDSMineFinderView Zeichnen

void CDSMineFinderView::OnDraw(CDC* pDC)
{
	CDSMineFinderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen


	pDC->TextOut(20, 5, "Sie können die Einstellungen mit einem Rechtsmausklick ändern");
	if(m_uMinSizePix <= 0)
			return;
	
	pDC->TextOut(m_uMinSizePix/2, m_uMinSizePix - 30, "1000 m");
	
		
//== Grenze rechts bzw. unten
		
	POINT P;
	P.x = WORLD_SIZE;
	P.y = 0;
	WorldToDP(&P);
	pDC->MoveTo(P.x, 0);
	pDC->LineTo(P);
	pDC->LineTo(0, P.y);
	
	if((m_bVisible)&&(!m_bMouseMove))
		Draw3DSource(pDC);	
	
	DrawListener(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CDSMineFinderView Drucken

BOOL CDSMineFinderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CDSMineFinderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Zusätzliche Initialisierung vor dem Drucken hier einfügen
}

void CDSMineFinderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einfügen
}

/////////////////////////////////////////////////////////////////////////////
// CDSMineFinderView Diagnose

#ifdef _DEBUG
void CDSMineFinderView::AssertValid() const
{
	CView::AssertValid();
}

void CDSMineFinderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDSMineFinderDoc* CDSMineFinderView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDSMineFinderDoc)));
	return (CDSMineFinderDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSMineFinderView Nachrichten-Handler

void CDSMineFinderView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	CSet3DSourceDlg dlg;

	//== Initiieren der Variablen im Dialog
	
	dlg.m_strFileName = m_strFileName;
	dlg.m_bVisible = m_bVisible;
	dlg.m_iRandOrUser = m_iRandOrUser;
	dlg.m_uX = m_uX; 
	dlg.m_uY = m_uY;
	dlg.m_uAngle = m_uAngle;
	dlg.m_uAnglInn = m_uAnglInn;
	dlg.m_uAnglOut = m_uAnglOut;
	dlg.m_uDistMax = m_uDistMax;
	dlg.m_uDistMin = m_uDistMin;
	
	if(dlg.DoModal() == IDOK)
	{
		m_strFileName = dlg.m_strFileName;

		m_bVisible = dlg.m_bVisible;
		m_iRandOrUser = dlg.m_iRandOrUser;

		if(m_iRandOrUser == 1)
		{
			//== Benutzerdefinierte Eingabe von Dialog in Sicht überschreiben
			m_uX = dlg.m_uX; 
			m_uY = dlg.m_uY;
			m_uAngle = dlg.m_uAngle;
			m_uAnglInn = dlg.m_uAnglInn;
			m_uAnglOut = dlg.m_uAnglOut;
			m_uDistMax = dlg.m_uDistMax;
			m_uDistMin = dlg.m_uDistMin;
		}
		else
		{
			//== Zufallwerten

			double dRat = WORLD_SIZE/((double)RAND_MAX);
			srand( (unsigned)time( NULL ) );
			
			m_uX = UINT(dRat*rand());
			m_uY = UINT(dRat*rand());
			m_uDistMax = UINT(dRat*rand())/2;

			dRat = m_uDistMax/(2*(double)RAND_MAX);
			m_uDistMin = UINT(dRat*rand());

			dRat = 360/(2*(double)RAND_MAX);
			m_uAngle = UINT(dRat*rand());

			dRat = 60/(2*(double)RAND_MAX);
			m_uAnglInn = UINT(dRat*rand());

			dRat = 20/(2*(double)RAND_MAX);
			m_uAnglOut = UINT(dRat*rand());
		}

		if(!m_ds3D.IsOK())
		{
			//== Soundquelle initialisieren

			if(!m_ds3D.Create(m_strFileName))
				return;
		}

		//== Parameter der Soundquelle aktualisieren

		m_ds3D.SetPosition((float)m_uX, (float)m_uY, 0); 
		
		m_ds3D.SetConeOrientation2D((float)m_uAngle);
		
		m_ds3D.SetConeAngles(m_uAnglInn, m_uAnglInn + 2*m_uAnglOut);
		
		
		m_ds3D.SetMaxDistance((float)m_uDistMax);
		m_ds3D.SetMinDistance((float)m_uDistMin);

		m_ds3D.SetConeOutsideVolume(DSBVOLUME_MIN);

	
		if(!m_dsListener.IsOK())
		{
			//== Hörer initialisieren

			if(!m_dsListener.Create())
				return;
		}

		Invalidate();
	}

	m_ptLastPoint = CPoint(-1, -1);

	CView::OnRButtonUp(nFlags, point);
}


void CDSMineFinderView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen

	if(m_ds3D.IsOK())
		m_ds3D.Stop();

	m_ptLastPoint = CPoint(-1, -1);

	m_bMouseMove = false;
	Invalidate(TRUE);
	
	CView::OnLButtonUp(nFlags, point);
}

void CDSMineFinderView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen

	if(nFlags != MK_LBUTTON)
		return;
	
	m_ptCurPoint = point;

	m_bMouseMove = true;
	
	CSize szDif = m_ptLastPoint - m_ptCurPoint;

	if((max(abs(szDif.cx), abs(szDif.cy)) > MOUSE_TOLERANCE_PIX)
		&&(m_dsListener.IsOK()))
	{
		DPtoWorld(&point);
	
		m_dsListener.SetPosition((float)point.x, (float)point.y, 0);

		float flOrientRad = (float)::atan2(m_ptCurPoint.y - m_ptLastPoint.y, 
			m_ptCurPoint.x - m_ptLastPoint.x);

		m_dsListener.SetOrientation2D(flOrientRad);

		Invalidate(FALSE);
	}

	if(m_ds3D.IsOK())
		m_ds3D.PlayLoop();


	CView::OnMouseMove(nFlags, point);
}

void CDSMineFinderView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen

	m_uMinSizePix = min(cx,cy);
	m_ptLastPoint = CPoint(-1, -1);
	
}

//== Draw - Methoden

void CDSMineFinderView::Draw3DSource(CDC* pDC)
{

	if(!m_ds3D.IsOK())
		return;

	float flX, flY, flZ;

	if(!m_ds3D.GetPosition(&flX, &flY, &flZ))
		return;


	if((fabs(flX) > WORLD_SIZE)||(fabs(flY) > WORLD_SIZE))
		return;

	float flDMax, flDMin;

	if(!m_ds3D.GetMinDistance(&flDMin))
		return;

	if(!m_ds3D.GetMaxDistance(&flDMax))
		return;

	
	POINT ptPos;
	ptPos.x = (long)flX;
	ptPos.y = (long)flY;

	WorldToDP(&ptPos);

	int iXC = ptPos.x;
	int iYC = ptPos.y;

	int iRmin = WorldToDP(flDMin);
	int iRmax = WorldToDP(flDMax);

	CRect rectMax(iXC - iRmax, iYC - iRmax, iXC + iRmax, iYC + iRmax);

	static CBrush BrushSmall(RGB(200, 200, 200));
	static CBrush BrushBig(RGB(220, 220, 220));
	CBrush* pBrushOld =  pDC->SelectObject(&BrushBig);

//== Maximale und minimale Distanzen
	
	pDC->Ellipse(rectMax);
	CRect rectMin(iXC - iRmin, iYC - iRmin, iXC + iRmin, iYC + iRmin);
	

	pDC->SelectObject(&BrushSmall);
	pDC->Ellipse(rectMin);


	DWORD dwInsideConeAngle, dwOutsideConeAngle;
	if(!m_ds3D.GetConeAngles(&dwInsideConeAngle, &dwOutsideConeAngle))
		return; 

	float flOrientRad;
	if(!m_ds3D.GetConeOrientation2D(&flOrientRad))
		return;

//== Orientierung 

	static CPen PenCentLine(PS_DASH, 1, RGB(255, 0, 0));   
	CPen* pPenOld = pDC->SelectObject(&PenCentLine);

	DrawLinePolar(pDC, iXC, iYC, flOrientRad, iRmax);

//== Interner Kegel
	static CPen PenInsideCone(PS_SOLID, 2, RGB(0, 255, 0));   
	pDC->SelectObject(&PenInsideCone);
	
	DrawLinePolar(pDC, iXC, iYC, float(flOrientRad + dwInsideConeAngle*PI/(180*2)), iRmax);
	DrawLinePolar(pDC, iXC, iYC, float(flOrientRad - dwInsideConeAngle*PI/(180*2)), iRmax);	
	
//== Äußerer Kegel

	static CPen PenOutsideCone(PS_SOLID, 1, RGB(0, 0, 255));   
	pDC->SelectObject(&PenOutsideCone);

	DrawLinePolar(pDC, iXC, iYC, float(flOrientRad + dwOutsideConeAngle*PI/(180*2)), iRmax);
	DrawLinePolar(pDC, iXC, iYC, float(flOrientRad - dwOutsideConeAngle*PI/(180*2)), iRmax);	

	pDC->SelectObject(pPenOld);
	pDC->SelectObject(pBrushOld);

}

void CDSMineFinderView::DrawListener(CDC* pDC)
{
	if(!m_dsListener.IsOK())
		return;

	static CPoint ptOrientOld(-1, -1);
	static CPoint ptCurPointOld(-1, -1);

	if(m_ptLastPoint.x > 0)
	{

		//== Teil der Strecke

		pDC->MoveTo(m_ptLastPoint);
		pDC->LineTo(m_ptCurPoint);

		//== Pfeil			
		CPen* pPenOld;
		CPen PenOrient(PS_SOLID, 3, RGB(0,0, 255));
		pPenOld = pDC->SelectObject(&PenOrient);
		
		int iROP2old = pDC->SetROP2(R2_NOTXORPEN);
	
	
		if(ptOrientOld.x > 0)
		{
	
		//== Spur des alten Pfeils aufräumen
		
			pDC->MoveTo(ptCurPointOld);
			pDC->LineTo(ptOrientOld);
			
		}


		float flOrientRad;
		
		if(!m_dsListener.GetOrientation2D(&flOrientRad))
			return;


		CPoint ptOrient(int(ARR_LENGTH*cos(flOrientRad)), int(ARR_LENGTH*sin(flOrientRad)));
		
		ptOrient.Offset(m_ptCurPoint);

		//== Neues Pfeil zeichnen
	
		pDC->MoveTo(m_ptCurPoint);
		pDC->LineTo(ptOrient);

		ptOrientOld = m_ptCurPoint;
		ptCurPointOld = ptOrient;
		

		pDC->SetROP2(iROP2old);
		pDC->SelectObject(pPenOld);

	}
	else
	{
		ptOrientOld = CPoint(-1, -1);
	}
	
	m_ptLastPoint = m_ptCurPoint;

}

void CDSMineFinderView::DrawLinePolar(CDC* pDC, int iXC, int iYC, float flOrientRad, int iR)
{

	CPoint ptCentre = CPoint(iXC, iYC);
	CPoint ptOrient = CPoint(int(iR*cos(flOrientRad)), int(-iR*sin(flOrientRad)));


	ptOrient.Offset(ptCentre);

	pDC->MoveTo(ptCentre);
	pDC->LineTo(ptOrient);
}


//== Service - Methoden

bool CDSMineFinderView::DPtoWorld(POINT* pPoint)
{

	if(m_uMinSizePix <= 0)
		return false;

	POINT p;
	p.x = pPoint->x*WORLD_SIZE/m_uMinSizePix; 
	p.y = WORLD_SIZE - pPoint->y*WORLD_SIZE/m_uMinSizePix;
	
	*pPoint = p;

	return true;
}

int CDSMineFinderView::WorldToDP(float flVal)
{
	int iVal = int(flVal*m_uMinSizePix/WORLD_SIZE);
	return iVal;
}

void CDSMineFinderView::WorldToDP(POINT* pPoint)
{
	POINT p;
	p.x = WorldToDP(float(pPoint->x));
	p.y = WorldToDP(float(WORLD_SIZE - pPoint->y));

	*pPoint = p;
}


