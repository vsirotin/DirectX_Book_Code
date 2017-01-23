// DIkeybTestView.cpp : Implementierung der Klasse CDIkeybTestView
//

#include "stdafx.h"
#include "DIkeybTest.h"

#include "DIkeybTestDoc.h"
#include "DIkeybTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CDIkeybTestView

IMPLEMENT_DYNCREATE(CDIkeybTestView, CView)

BEGIN_MESSAGE_MAP(CDIkeybTestView, CView)
	//{{AFX_MSG_MAP(CDIkeybTestView)
	ON_WM_TIMER()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDIkeybTestView Konstruktion/Destruktion

CDIkeybTestView::CDIkeybTestView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

	m_iDx = m_iDy = -1000;
}

CDIkeybTestView::~CDIkeybTestView()
{
	m_diKeybDev.Close();
}

BOOL CDIkeybTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDIkeybTestView Zeichnen

void CDIkeybTestView::OnDraw(CDC* pDC)
{
	CDIkeybTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen

	static int iXOld, iYOld;
	
	CRect rc;
	GetClientRect(&rc);

	if((m_iDx == -1000)&&(m_iDy == -1000))
	{
		//== Punkt in die Mitte des Fensters plazieren.

		iXOld = rc.Width()/2;;
		iYOld = rc.Height()/2;
		m_iDx = m_iDy = 0;
		
		return;
	}

	//== Neuen Abschnitt zeichnen

	pDC->MoveTo(iXOld, iYOld);
	iXOld = m_iDx + iXOld;
	iYOld = m_iDy + iYOld;

	pDC->LineTo(iXOld, iYOld);

	//== Außerhalb des Fensters? Dann Position korrigieren
	if(iXOld < 0)
		iXOld = rc.Width();

	if(iXOld > rc.Width())
		iXOld = 0;

	if(iYOld < 0)
		iYOld = rc.Height();

	if(iYOld > rc.Height())
		iYOld = 0;

	
}

/////////////////////////////////////////////////////////////////////////////
// CDIkeybTestView Drucken

BOOL CDIkeybTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CDIkeybTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Zusätzliche Initialisierung vor dem Drucken hier einfügen
}

void CDIkeybTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einfügen
}

/////////////////////////////////////////////////////////////////////////////
// CDIkeybTestView Diagnose

#ifdef _DEBUG
void CDIkeybTestView::AssertValid() const
{
	CView::AssertValid();
}

void CDIkeybTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDIkeybTestDoc* CDIkeybTestView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDIkeybTestDoc)));
	return (CDIkeybTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDIkeybTestView Nachrichten-Handler


void CDIkeybTestView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	
	m_iDx = m_iDy = -1000;
}

#define MY_TIMER 1000
void CDIkeybTestView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen

	if(bActivate)
	{
		m_diKeybDev.Acquire();
		SetTimer(MY_TIMER, 100, NULL);
	}
	else
	{
		KillTimer(MY_TIMER);
	}
	
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


#define PIXEL_FACTOR 5
void CDIkeybTestView::OnTimer(UINT nIDEvent) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	
	CView::OnTimer(nIDEvent);


	if(nIDEvent == MY_TIMER)
	{
		//== Beim erstem Mal initialisieren 
		if(!m_diKeybDev.IsOK())
		{
			m_diKeybDev.Create();
		}

		
		//== Zustand der Tastatur abfragen.
		if(!m_diKeybDev.GetState())
			return;

		
		if(m_diKeybDev.IsKeyDown(DIK_ESCAPE))
		{
			//== Wenn Escape gedrückt, 
			//== Koordinaten initialisieren.

			m_iDx = m_iDy = -1000;

			//== Fenster aufräumen
			Invalidate(TRUE);
			return;
		}
		
		m_iDx = m_iDy = 0;
		bool bIsDown = false;	
		//== Variable bIsDown wird auf true festgesetzt, 
		//== mindestens eine der folgenden Tasten gedrückt ist


		//== Pfeil "Oben"
		if(m_diKeybDev.IsKeyDown(DIK_UP))
		{
			m_iDy -= PIXEL_FACTOR;
			bIsDown = true;
		}
		
		//== Pfeil "Unten"
		if(m_diKeybDev.IsKeyDown(DIK_DOWN))
		{
			m_iDy += PIXEL_FACTOR;
			bIsDown = true;
		}


		//== Pfeil "Links"
		if(m_diKeybDev.IsKeyDown(DIK_LEFT))
		{
			m_iDx -= PIXEL_FACTOR;
			bIsDown = true;
		}
		
		//== Pfeil "Rechts"
		if(m_diKeybDev.IsKeyDown(DIK_RIGHT))
		{
			m_iDx += PIXEL_FACTOR;
			bIsDown = true;
		}


		if(bIsDown)
			Invalidate(FALSE);
		
	}

}


