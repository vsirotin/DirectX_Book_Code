// DSSource.h: Schnittstelle für die Klasse CDSSource.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSSOURCE_H__37D4DC09_6533_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSSOURCE_H__37D4DC09_6533_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DSMainObj.h"
#include "DSWave.h"

class CDSSource  
{

public:

	CDSSource();
	CDSSource(CDSSource& dsSource);
	

	virtual ~CDSSource();

//Attribute

protected:
	DWORD m_dwBufferBytes;

	CDSWave* m_pDsWave;
	char* m_pWaveData;

	CDSMainObj m_DSMainObj;
	LPDIRECTSOUNDBUFFER m_pDSBuffer;
	

//Operationen:

public:
	
	bool CDSSource::Create(const CString& strFileName, DWORD dwFlags = DSBCAPS_STATIC|DSBCAPS_CTRLDEFAULT);

	bool Play();
	bool PlayLoop();
	bool IsPlay();
	bool GetCurrentPosition(LPDWORD lpdwCurrentPlayPos, LPDWORD lpdwCurrentWritePos);
	bool SetCurrentPosition(DWORD dwCurrentPlayPos);

	bool IsOK() const;
	bool Stop();

	bool SetFrequency(DWORD dwFrequency);
	bool SetPan(LONG lPAN);
	bool SetVolume(LONG lVolume);

	int GetBufferSize();
	DWORD GetWaveSize();

	bool CDSSource::CheckBuffer(const CString& strFile, int iLine);


protected:

	LPDIRECTSOUNDBUFFER Duplicate();


};

#endif // !defined(AFX_DSSOURCE_H__37D4DC09_6533_11D2_B890_0000B45EEBF9__INCLUDED_)
