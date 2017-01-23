// ddAquaBackground.cpp: implementation of the CDDAquaBackground class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mmsystem.h"

#include "ddAqua.h"
#include "ddAquaObj.h"
#include "ddAquaBackground.h"

#include "ddPCXFiller.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CDDAquaBackground, CDDSprite)
CDDAquaBackground::CDDAquaBackground(CDDMainObj *pOwner) : CDDSprite(pOwner)
  {
  }

CDDAquaBackground::~CDDAquaBackground()
  {
  }

bool CDDAquaBackground::Create(char *filename)
  {
  CDDPCXFiller pcxFiller;
  //= PCX-Datei öffnen
  if (!pcxFiller.Create(filename))
    return false;

  //= Größe des Bildes ermitteln
  int iWidth, iHeight;
  pcxFiller.GetSize(&iWidth, &iHeight);

  if (!CDDSprite::Create(iWidth, iHeight))
    return false;

  //= Daten aus Datei lesen 
  if (!pcxFiller.FillSurface(this))
    return false;

  //= Paletten-Einträge festlegen
  PALETTEENTRY palette[256];
  pcxFiller.GetDirectDrawPalette(palette);

  for (int i = 129; i <= 138; i++)
    {
    palette[i].peRed = 4;
    palette[i].peGreen = 127;
    palette[i].peBlue = 201;
    }

  if (!m_pOwner->SetPalette(palette))
    return false;

  m_curColor = 129;
  m_dwCurTime = timeGetTime();
  m_dwTime = 30;

  return true;
  }

bool CDDAquaBackground::IsChanged()
  {
  DWORD dw = timeGetTime();
  if (dw - m_dwCurTime < m_dwTime)
    return false;

  m_dwCurTime = dw;
  m_pOwner->SetPaletteEntry(m_curColor, 4, 127, 201);
  if (++m_curColor == 139)
    m_curColor = 129;

  m_pOwner->SetPaletteEntry(m_curColor, 255, 255, 255);
  return true;
  }
