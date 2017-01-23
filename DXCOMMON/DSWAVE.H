// DSWave.h: Schnittstelle für die Klasse CDSWave.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSWAVE_H__7853E2B1_4768_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSWAVE_H__7853E2B1_4768_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <mmsystem.h>

class CDSWave  
{
public:
	DWORD m_dwSize;

protected:
	char* m_pWave;
	WAVEFORMATEX m_wavFormat;

public:
	CDSWave();
	CDSWave(const CString& strFileName);
	virtual ~CDSWave();

	bool IsOK() const;
	LPWAVEFORMATEX GetWaveFormat();
	char* GetWave();

};

#endif // !defined(AFX_DSWAVE_H__7853E2B1_4768_11D2_B890_0000B45EEBF9__INCLUDED_)
