// DSWave.cpp: Implementierung der Klasse CDSWave.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DSWave.h"
#include <windowsx.h>
#include <mmsystem.h>
#include <string.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CDSWave::CDSWave()
{
	m_dwSize = 0;
	m_pWave = NULL;
}

#define MAX_FILE_NAME 256
CDSWave::CDSWave(const CString& strFileName)
{
	char str[MAX_FILE_NAME];
	::strcpy(str, strFileName); 
	m_dwSize = 0;
	m_pWave = NULL;

	HMMIO           hMIMIO;
	MMCKINFO        ckInfoRIFF; 
	MMCKINFO        ckInfoChunk; 


	//== WAVE Datei Öffnen
//	hMIMIO = ::mmioOpen((char*)str, NULL, MMIO_ALLOCBUF | MMIO_READ);
	hMIMIO = ::mmioOpen((char*)str, NULL, MMIO_READ);

	if(hMIMIO == NULL)
		return;

	//== RIFF Blöcke finden
	ckInfoRIFF.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if(mmioDescend(hMIMIO, &ckInfoRIFF, NULL, MMIO_FINDRIFF) != MMSYSERR_NOERROR )
		return;
		
	//== Format - Block finden
    ckInfoChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if (mmioDescend(hMIMIO, &ckInfoChunk, &ckInfoRIFF, MMIO_FINDCHUNK) != MMSYSERR_NOERROR )
		return;
					
	//== Format - Block lesen

    long lCountBytesReaded = mmioRead(hMIMIO, (char*) &m_wavFormat,  sizeof(WAVEFORMATEX));

	if(lCountBytesReaded < 0) 
		return;

	//== Nach oben zur Struktur
	if(mmioAscend(hMIMIO, &ckInfoChunk, 0) != MMSYSERR_NOERROR)
		return;

	//==Nach unten zum Datenblock
	ckInfoChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if(mmioDescend(hMIMIO, &ckInfoChunk, &ckInfoRIFF, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
		return;

	m_dwSize = ckInfoChunk.cksize;

	//== Puffer füt Daten anlegen
	m_pWave = (char*)GlobalAllocPtr(GMEM_MOVEABLE, m_dwSize);
	if(m_pWave == NULL)
		return;

	//== Daten im Puffer lesen
	lCountBytesReaded = mmioRead(hMIMIO, (char*)m_pWave,  m_dwSize);
	mmioClose(hMIMIO, 0);

	if(lCountBytesReaded == (long)m_dwSize)
		return; //== OK

	m_dwSize = 0;
}

CDSWave::~CDSWave()
{
	if(m_pWave != NULL)
		GlobalFreePtr(m_pWave);

}

bool CDSWave::IsOK() const
{
	if(m_dwSize > 0)
		return true;
	else
		return false;
}

LPWAVEFORMATEX CDSWave::GetWaveFormat()
{
	return &m_wavFormat;
}

char* CDSWave::GetWave()
{
	return m_pWave;
}