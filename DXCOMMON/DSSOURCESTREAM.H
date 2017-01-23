// DSSourceStream.h: Schnittstelle für die Klasse CDSSourceStream.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSSourceStream_H__37D4DC09_6533_11D2_B890_0000B45EEBF9__INCLUDED_)
#define AFX_DSSourceStream_H__37D4DC09_6533_11D2_B890_0000B45EEBF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DSSource.h"
class CDSSourceStream : public CDSSource
{

public:

	CDSSourceStream();
	bool Create(const CString& strFileName, UINT uBuffSizeSec = 2);

	virtual ~CDSSourceStream();

	bool TryStream(LPDWORD lpdwCurrentPlayPos = NULL, bool* pbWriteAction = NULL, 
						  LPDWORD lpdwCurrentWritePosBuff = NULL , LPDWORD lpdwCurrentWritePosWave = NULL);
	
	bool Write(DWORD dwStartOfsBytes, DWORD dwSizeBytes); 

//Attribute
protected:
	DWORD m_dwLastSourcePosition;
	bool m_bWriteInFirstHalf;

};

#endif // !defined(AFX_DSSourceStream_H__37D4DC09_6533_11D2_B890_0000B45EEBF9__INCLUDED_)
