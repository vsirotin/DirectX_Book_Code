// ddNullFiller.cpp: implementation of the CDDNullFiller class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ddMainObj.h"
#include "ddSprite.h"
#include "ddNullFiller.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CDDNullFiller, CDDSurfaceFiller);
CDDNullFiller::CDDNullFiller()
  {
  }

CDDNullFiller::~CDDNullFiller()
  {
  }

bool CDDNullFiller::FillSurface(CDDSprite *pSprite)
  {
  LPDIRECTDRAWSURFACE3 pSurface = pSprite->GetSurface();
  return FillSurface(pSurface);
  }

bool CDDNullFiller::FillSurface(CDDMainObj *pDDObj)
  {
  LPDIRECTDRAWSURFACE3 pSurface = pDDObj->GetBackSurface();
  return FillSurface(pSurface);
  }

bool CDDNullFiller::FillRectangle(CDDSprite *pSprite, int x0, int y0, int x1, int y1)
  {
  LPDIRECTDRAWSURFACE3 pSurface = pSprite->GetSurface();
  return FillRectangle(pSurface, x0, y0, x1, y1);
  }

bool CDDNullFiller::FillSurface(LPDIRECTDRAWSURFACE3 pSurface)
  {
  DDSURFACEDESC  ddsd;
  BYTE          *b;

  //= Zugriff zum Speicher ermitteln
  ZeroMemory(&ddsd, sizeof(ddsd));
  ddsd.dwSize = sizeof(ddsd);
  DDTRY(pSurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL));

  //= Mit einem Null-Wert die Oberfläche ausfüllen (Nur 256 Farben)
  b = (BYTE *)ddsd.lpSurface;
  for (unsigned int j = 0; j < ddsd.dwHeight; j++, b += ddsd.lPitch)
    ZeroMemory(b, ddsd.lPitch);

  return DDCHECK(pSurface->Unlock(NULL));
  }

bool CDDNullFiller::FillRectangle(LPDIRECTDRAWSURFACE3 pSurface, int x0, int y0, int x1, int y1)
  {
  DDSURFACEDESC  ddsd;
  BYTE          *b;

  ZeroMemory(&ddsd, sizeof(ddsd));
  ddsd.dwSize = sizeof(ddsd);
  DDTRY(pSurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL));

  b = (BYTE *)ddsd.lpSurface + y0 * ddsd.lPitch + x0 * (ddsd.ddpfPixelFormat.dwRGBBitCount / 8);
  for (int j = y0; j <= y1; j++, b += ddsd.lPitch)
    FillMemory(b, (x1 - x0) * (ddsd.ddpfPixelFormat.dwRGBBitCount / 8), 0);

  return DDCHECK(pSurface->Unlock(NULL));
  }