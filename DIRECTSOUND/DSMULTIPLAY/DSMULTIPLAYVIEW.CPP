// DSMultiPlayView.cpp : Implementierung der Klasse CDSMultiPlayView
//

#include "stdafx.h"
#include "DSMultiPlay.h"

#include "DSMultiPlayDoc.h"
#include "DSMultiPlayView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSMultiPlayView

IMPLEMENT_DYNCREATE(CDSMultiPlayView, CFormView)

BEGIN_MESSAGE_MAP(CDSMultiPlayView, CFormView)
	//{{AFX_MSG_MAP(CDSMultiPlayView)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_FREQUENCY, OnReleasedcaptureFrequency)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_PAN, OnReleasedcapturePan)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_VOLUME, OnReleasedcaptureVolume)
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSMultiPlayView Konstruktion/Destruktion

CDSMultiPlayView::CDSMultiPlayView()
	: CFormView(CDSMultiPlayView::IDD)
{
	//{{AFX_DATA_INIT(CDSMultiPlayView)
	//}}AFX_DATA_INIT
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

}

CDSMultiPlayView::~CDSMultiPlayView()
{
}

void CDSMultiPlayView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDSMultiPlayView)
	DDX_Control(pDX, IDC_VOLUME, m_sliderVol);
	DDX_Control(pDX, IDC_PAN, m_sliderPan);
	DDX_Control(pDX, IDC_FREQUENCY, m_sliderFreq);
	//}}AFX_DATA_MAP
}

BOOL CDSMultiPlayView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CFormView::PreCreateWindow(cs);
}

void CDSMultiPlayView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

	m_sliderVol.SetRange(DSBVOLUME_MIN, DSBVOLUME_MAX, TRUE);
	m_sliderVol.SetPos((DSBVOLUME_MIN + DSBVOLUME_MAX)/2);

	m_sliderPan.SetRange(DSBPAN_LEFT, DSBPAN_RIGHT, TRUE);
	m_sliderPan.SetPos(DSBPAN_CENTER);

	m_sliderFreq.SetRange(DSBFREQUENCY_MIN, DSBFREQUENCY_MAX, TRUE);
	m_sliderFreq.SetPos(DSBFREQUENCY_ORIGINAL);

}

/////////////////////////////////////////////////////////////////////////////
// CDSMultiPlayView Drucken

BOOL CDSMultiPlayView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CDSMultiPlayView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Zusätzliche Initialisierung vor dem Drucken hier einfügen
}

void CDSMultiPlayView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einfügen
}

void CDSMultiPlayView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Benutzerdefinierten Code zum Ausdrucken hier einfügen
}

/////////////////////////////////////////////////////////////////////////////
// CDSMultiPlayView Diagnose

#ifdef _DEBUG
void CDSMultiPlayView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDSMultiPlayView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDSMultiPlayDoc* CDSMultiPlayView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDSMultiPlayDoc)));
	return (CDSMultiPlayDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSMultiPlayView Nachrichten-Handler


void CDSMultiPlayView::OnReleasedcaptureFrequency(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	UpdateData(TRUE);
	int iPos = m_sliderFreq.GetPos();
	GetDocument()->m_dsSource.SetFrequency(iPos);

	*pResult = 0;
}


void CDSMultiPlayView::OnReleasedcapturePan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	UpdateData(TRUE);
	int iPos = m_sliderPan.GetPos();
	GetDocument()->m_dsSource.SetPan(iPos);


	*pResult = 0;
}

void CDSMultiPlayView::OnReleasedcaptureVolume(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	UpdateData(TRUE);
	int iPos = m_sliderVol.GetPos();
	GetDocument()->m_dsSource.SetVolume(DSBVOLUME_MAX - iPos + DSBVOLUME_MIN);
	
	*pResult = 0;
}
