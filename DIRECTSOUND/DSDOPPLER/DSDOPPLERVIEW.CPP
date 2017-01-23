// DSDopplerView.cpp : Implementierung der Klasse CDSDopplerView
//

#include "stdafx.h"
#include "DSDoppler.h"

#include "DSDopplerDoc.h"
#include "DSDopplerView.h"

#include "Set3DSourceDlg.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sys/timeb.h>


#define WORLD_SIZE 1000
#define MOUSE_TOLERANCE_PIX 4
#define PI 3.1415928

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSDopplerView

IMPLEMENT_DYNCREATE(CDSDopplerView, CView)

BEGIN_MESSAGE_MAP(CDSDopplerView, CView)
	//{{AFX_MSG_MAP(CDSDopplerView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSDopplerView Konstruktion/Destruktion

CDSDopplerView::CDSDopplerView()
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
}

CDSDopplerView::~CDSDopplerView()
{
}

BOOL CDSDopplerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDSDopplerView Zeichnen

void CDSDopplerView::OnDraw(CDC* pDC)
{
	CDSDopplerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen

	pDC->TextOut(20, 5, "Sie können die Einstellungen mit einem Rechtsklick ändern");
	if(m_uMinSizePix <= 0)
			return;
	
	static CString strSize;
	if(strSize.GetLength() == 0)
		strSize.Format(" - - %d m - - ", WORLD_SIZE);

	pDC->TextOut(m_uMinSizePix/2, m_uMinSizePix - 30, strSize);

	CString strTmp;
	strTmp.Format("Geschwindigkeit: %d km\\h ", m_uVelocity);
	pDC->TextOut(0, m_uMinSizePix - 30, strTmp);
	
		
//== Grenze rechts bzw. unten
		
	POINT P;
	P.x = WORLD_SIZE;
	P.y = 0;
	WorldToDP(&P);
	pDC->MoveTo(P.x, 0);
	pDC->LineTo(P);
	pDC->LineTo(0, P.y);
	
	Draw3DSource(pDC);	
	DrawListener(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CDSDopplerView Drucken

BOOL CDSDopplerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CDSDopplerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Zusätzliche Initialisierung vor dem Drucken hier einfügen
}

void CDSDopplerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einfügen
}

/////////////////////////////////////////////////////////////////////////////
// CDSDopplerView Diagnose

#ifdef _DEBUG
void CDSDopplerView::AssertValid() const
{
	CView::AssertValid();
}

void CDSDopplerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDSDopplerDoc* CDSDopplerView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDSDopplerDoc)));
	return (CDSDopplerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSDopplerView Nachrichten-Handler

//== Service - Methoden

bool CDSDopplerView::DPtoWorld(POINT* pPoint)
{

	if(m_uMinSizePix <= 0)
		return false;

	POINT p;
	p.x = pPoint->x*WORLD_SIZE/m_uMinSizePix; 
	p.y = WORLD_SIZE - pPoint->y*WORLD_SIZE/m_uMinSizePix;
	
	*pPoint = p;

	return true;
}

int CDSDopplerView::WorldToDP(float flVal)
{
	int iVal = int(flVal*m_uMinSizePix/WORLD_SIZE);
	return iVal;
}

void CDSDopplerView::WorldToDP(POINT* pPoint)
{
	POINT p;
	p.x = WorldToDP((float)pPoint->x);
	p.y = WorldToDP(float(WORLD_SIZE - pPoint->y));

	*pPoint = p;
}

void CDSDopplerView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen

		CSet3DSourceDlg dlg;

	//==  Varibalen im Dialog initiieren
	
	dlg.m_strFileName = m_strFileName;
	dlg.m_uDistMax = m_uDistMax;
	dlg.m_uDistMin = m_uDistMin;
	
	if(dlg.DoModal() == IDOK)
	{
		m_strFileName = dlg.m_strFileName;

		m_uDistMax = dlg.m_uDistMax;
		m_uDistMin = dlg.m_uDistMin;

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

			m_dsListener.SetPosition(WORLD_SIZE/2, WORLD_SIZE/2, 0); 
		}

		Invalidate();
	}

	m_ptLastPoint = CPoint(-1, -1);
}

void CDSDopplerView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen

	if(nFlags != MK_LBUTTON)
		return;
	
	m_ptCurPoint = point;

	CPoint ptDif = m_ptCurPoint - m_ptLastPoint;

	if((max(abs(ptDif.x), abs(ptDif.y)) < MOUSE_TOLERANCE_PIX)
		||(!m_dsListener.IsOK()))
		return;
	

	static struct _timeb t0, t1;
	static bool bInit = false;

	if(!bInit)
	{	
		//== Initialisierung des Anfanangszeitpunkt
	   _ftime( &t0);
	   bInit = true;
	   return;
	}

	//== Rechnen des Zeitintervalles

	_ftime( &t1);
	long lTimeAll = t1.time*1000 + t1.millitm - (t0.time*1000 + t0.millitm);
	double dTimeDif = lTimeAll/1000.0;
	
	t0 = t1;

	CPoint ptCurr(m_ptCurPoint);
	DPtoWorld(&ptCurr);

	m_ds3D.SetPosition((float)ptCurr.x, (float)ptCurr.y, 0);
		
	CPoint ptLast(m_ptLastPoint);
	DPtoWorld(&ptLast);

	//== Bechner der aktuellen Geschwindigkeit
	CPoint ptDiff = ptCurr - ptLast;
	int iVelXMetrSek = int(ptDiff.x/dTimeDif);
	int iVelYMetrSek = int(ptDiff.y/dTimeDif);

	//== "Stabilisierung" der Geschwindigkeit 
	static int iVelXMetrSekLast = 0;
	static int iVelYMetrSekLast = 0;
	int iVelXMetrSekSum = int(ptDiff.x/dTimeDif + iVelXMetrSekLast)/2;
	int iVelYMetrSekSum = int(ptDiff.y/dTimeDif + iVelYMetrSekLast)/2;

	iVelXMetrSekLast = iVelXMetrSek;
	iVelYMetrSekLast = iVelYMetrSek;	
	

	m_ds3D.SetVelocity((float)iVelXMetrSekSum, (float)iVelYMetrSekSum, 0);
		

	//== Rechner der Skalar - Geschwindigkeit in Km/Stunde

	int iVelXKmH = iVelXMetrSekSum*1000/3600;
	int iVelYKmH = iVelXMetrSekSum*1000/3600;

	m_uVelocity = (UINT)sqrt(iVelXKmH*iVelXKmH + iVelYKmH*iVelYKmH);
	if(m_uVelocity < 5)
	{
		iVelXMetrSekLast = 0;
		iVelYMetrSekLast = 0;
		m_uVelocity = 0;
	}

	Invalidate(TRUE);
		
	m_ptLastPoint = m_ptCurPoint;

	if(m_ds3D.IsOK())
		m_ds3D.PlayLoop();

	CView::OnMouseMove(nFlags, point);
}

void CDSDopplerView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen

	if(m_ds3D.IsOK())
		m_ds3D.Stop();

	m_ptLastPoint = CPoint(-1, -1);
	Invalidate(TRUE);
	
	CView::OnLButtonUp(nFlags, point);
}

void CDSDopplerView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen

	m_uMinSizePix = min(cx,cy);
	m_ptLastPoint = CPoint(-1, -1);
}


void CDSDopplerView::Draw3DSource(CDC* pDC)
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
	pDC->Ellipse(rectMax);

	CRect rectMin(iXC - iRmin, iYC - iRmin, iXC + iRmin, iYC + iRmin);
	pDC->Ellipse(rectMin);
}

void CDSDopplerView::DrawListener(CDC* pDC)
{
	if(!m_dsListener.IsOK())
		return;

	float flX, flY, flZ;

	if(!m_dsListener.GetPosition(&flX, &flY, &flZ))
		return;


	if((fabs(flX) > WORLD_SIZE)||(fabs(flY) > WORLD_SIZE))
		return;

	
	POINT ptPos;
	ptPos.x = (long)flX;
	ptPos.y = (long)flY;

	WorldToDP(&ptPos);

	int iXC = ptPos.x;
	int iYC = ptPos.y;

	int iR = 10;

	CRect rectMax(iXC - iR, iYC - iR, iXC + iR, iYC + iR);
	pDC->Ellipse(rectMax);


}