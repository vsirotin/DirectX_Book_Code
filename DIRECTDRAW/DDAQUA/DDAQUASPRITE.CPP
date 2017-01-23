// ddAquaSprite.cpp: implementation of the CDDAquaSprite class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mmsystem.h"

#include "ddAqua.h"
#include "ddAquaObj.h"
#include "ddAquaSprite.h"

#include "ddPCXFiller.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CDDAquaSprite, CDDSprite)
CDDAquaSprite::CDDAquaSprite(CDDMainObj *pOwner) : CDDSprite(pOwner)
  {
  }

CDDAquaSprite::~CDDAquaSprite()
  {
  }

bool CDDAquaSprite::Create(int xorg, int yorg, char *fileName, 
                           int nOfFrames, DWORD time)
  {
  char curFileName[_MAX_PATH];

  for (int i = 0; i < nOfFrames; i++)
    {
    //= Dateiname konstruieren
    sprintf(curFileName, "%s%d%d.pcx", fileName, i / 10, i % 10);

    CDDPCXFiller pcxFiller;
    //= PCX-Datei öffnen 
    if (!pcxFiller.Create(curFileName))
      return false;

    if (i == 0)
      {
      //= Sprite erzeugen
      int iWidth, iHeight;
      pcxFiller.GetSize(&iWidth, &iHeight);

      if (!CDDSprite::Create(iWidth, iHeight, nOfFrames))
        return false;

      }

    //= Daten von der Datei lesen
    if (!pcxFiller.FillSurface(this))
      return false;

    //= Farbschlüssel lesen
    DDCOLORKEY ddck;
    ddck.dwColorSpaceLowValue = 255;
    ddck.dwColorSpaceHighValue = 255;
  
    SetColorKey(&ddck);

    NextFrame();
    }
  
  m_ptPose = CPoint(xorg, yorg);
  m_State = 0;
  m_dwCurTime = timeGetTime();
  m_dwTime = time;
  return true;
  }

bool CDDAquaSprite::Clone(CDDSprite *pFather, int xorg, int yorg, DWORD time)
  {
  if (!CDDSprite::Clone(pFather))
    return false;

  m_ptPose = CPoint(xorg, yorg);
  m_State = 0;
  m_dwCurTime = timeGetTime();
  m_dwTime = time;
  return true;
  }

bool CDDAquaSprite::IsChanged()
  {
  DWORD dw = timeGetTime();
  if (dw - m_dwCurTime < m_dwTime)
    return false;

  m_dwCurTime = dw;
  if (m_State == 0)
    {
    NextFrame();
    if (m_iCurFrame == m_nOfFrames - 1)
      m_State = 1;

    }
  else 
    {
    PrevFrame();
    if (m_iCurFrame == 0)
      m_State = 0;

    }

  return true;
  }
