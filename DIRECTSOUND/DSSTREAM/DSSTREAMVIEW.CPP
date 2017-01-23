// DSStreamView.cpp : Implementierung der Klasse CDSStreamView
//

#include "stdafx.h"
#include "DSStream.h"

#include "DSStreamDoc.h"
#include "DSStreamView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSStreamView

IMPLEMENT_DYNCREATE(CDSStreamView, CView)

BEGIN_MESSAGE_MAP(CDSStreamView, CView)
	//{{AFX_MSG_MAP(CDSStreamView)
	ON_COMMAND(ID_EDIT_PLAY, OnEditPlay)
	ON_WM_TIMER()
	ON_COMMAND(ID_EDIT_STOP, OnEditStop)
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSStreamView Konstruktion/Destruktion

CDSStreamView::CDSStreamView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

	m_dwCurrPlayPos = 0;
	m_dwCurrWritePosBuf = 0;
	m_dwCurrWritePosWave = 0;
	m_dwWaveSize = 0;
	m_dwBufferSizeBytes = 0;
	m_bWriteAction = 0;
}

CDSStreamView::~CDSStreamView()
{
}

BOOL CDSStreamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDSStreamView Zeichnen

void CDSStreamView::OnDraw(CDC* pDC)
{
	CDSStreamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen


	if(m_dwBufferSizeBytes == 0)
		return; //== Puffer ist noch nicht angelegt 

	CRect rcGab;
	GetClientRect(&rcGab);

	int iMargin = 10;
	int iHeight = 20;

//== Darstellung der Audiodatei

	UINT uDxPix = rcGab.Width() - 2*iMargin;
	CRect rcFile(iMargin, iMargin, uDxPix, iMargin + iHeight);
	pDC->Rectangle(rcFile);

	double dZoom = (double)uDxPix/(m_dwWaveSize);


	UINT uDxBuffPix = UINT(m_dwBufferSizeBytes*dZoom);

//== Darstellung des Soundpuffers (Soundquelle)

	CRect rcHead(rcGab.Width()/2 - uDxBuffPix, 20*iMargin, rcGab.Width()/2 + uDxBuffPix, 20*iMargin + iHeight);
	pDC->Rectangle(rcHead);
	pDC->MoveTo(rcGab.Width()/2, 20*iMargin);
	pDC->LineTo(rcGab.Width()/2, 20*iMargin + iHeight);

//== Darstellung der Play - Position

	UINT uX0Play = UINT(m_dwCurrPlayPos*dZoom*2 + rcHead.left);
	pDC->MoveTo(uX0Play, rcHead.top - 10);
	pDC->LineTo(uX0Play, rcHead.bottom + 10);

	CString strPlay;
	strPlay.Format("Play: %d",  m_dwCurrPlayPos);
	pDC->TextOut(rcGab.Width()/2, 20*iMargin + 2*iHeight, strPlay);

//== Darstellung der Schreibeposition
	if(m_bWriteAction)
	{
		UINT uX0 = UINT(m_dwCurrWritePosWave*dZoom + rcFile.left);
		pDC->MoveTo(uX0, rcFile.bottom);
		
		UINT uX1 = UINT(m_dwCurrWritePosBuf*dZoom*2 + rcHead.left);
		pDC->LineTo(uX1, rcHead.top);

		CString strWrite;
		strWrite.Format("Write: %d",  m_dwCurrWritePosWave);
		pDC->TextOut(rcGab.Width()/2, 20*iMargin + 4*iHeight, strWrite);
		
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// CDSStreamView Drucken

BOOL CDSStreamView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CDSStreamView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Zusätzliche Initialisierung vor dem Drucken hier einfügen
}

void CDSStreamView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einfügen
}

/////////////////////////////////////////////////////////////////////////////
// CDSStreamView Diagnose

#ifdef _DEBUG
void CDSStreamView::AssertValid() const
{
	CView::AssertValid();
}

void CDSStreamView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDSStreamDoc* CDSStreamView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDSStreamDoc)));
	return (CDSStreamDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSStreamView Nachrichten-Handler

#define MY_TIMER 10000
void CDSStreamView::OnEditPlay() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	
	static bDSCreated = false;

	if(!bDSCreated)
	{
		bDSCreated = m_dsSource.Create(GetDocument()->m_strFileName);
		if(!bDSCreated)
			return;
			
		m_dwWaveSize = m_dsSource.GetWaveSize();
		m_dwBufferSizeBytes = m_dsSource.GetBufferSize();

	}

	if(!m_dsSource.IsPlay())
		m_dsSource.PlayLoop();
	
	SetTimer(MY_TIMER, 300, NULL);
}

void CDSStreamView::OnEditStop() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	if(m_dsSource.IsPlay())
		m_dsSource.Stop();

	KillTimer(MY_TIMER);
}


void CDSStreamView::OnTimer(UINT nIDEvent) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen

	if(nIDEvent == MY_TIMER)
	{
		
		if(m_dsSource.TryStream(&m_dwCurrPlayPos, &m_bWriteAction, 
						  &m_dwCurrWritePosBuf, &m_dwCurrWritePosWave))
		{
			Invalidate();
		}
		
	}
	
	CView::OnTimer(nIDEvent);
}

