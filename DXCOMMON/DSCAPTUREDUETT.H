// CDSCaptureDuett.h: Schnittstelle für die Klasse CCDSCaptureDuett.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDSCaptureDuett_H__13C45C4D_A8D2_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_CDSCaptureDuett_H__13C45C4D_A8D2_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DSSource.h"

#define DSCAPTURE_COUNT_NOTIFY_POS 2

class CDSCaptureDuett : public CDSSource  
{
public:
	CDSCaptureDuett();
	virtual ~CDSCaptureDuett();

//== Attributes

protected:


	CDSSource m_dssOriginal;

	LPDIRECTSOUNDCAPTURE        m_pDSCaptureObj;
	LPDIRECTSOUNDCAPTUREBUFFER  m_pDSCaptureBuffer;
	LPDIRECTSOUNDNOTIFY m_pDsNotifyCapture;

	HANDLE m_arrEvents[DSCAPTURE_COUNT_NOTIFY_POS];
	bool m_bCaptureRun;
	bool m_bCanCapture;

//== Implementierung

public:
	bool Create(const CString& strFileName);
	bool StartCapture();
	bool StopCapture();
	bool CanCapture();

	bool Play();
	bool PlayCapturedResult();
	bool Stop();

protected:
	bool CheckCaptureBuffer(const CString& strFile, int iLine);
	bool Clear();

	friend UINT DSCaptureThreadProc(LPVOID pParam);

};


#endif // !defined(AFX_CDSCaptureDuett_H__13C45C4D_A8D2_11D2_B890_0000B45EEBF9__INCLUDED_)
