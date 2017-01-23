// DDSaverObj.cpp: implementation of the CDDSaverObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ddSaver.h"
#include "ddSaverObj.h"
#include "mmsystem.h"

#include "ddSaverSprite.h"
#include "ddSaverBackground.h"

#include "ddBackFiller.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CDDSaverObj, CDDMainObj);
CDDSaverObj::CDDSaverObj()
  {
  }

CDDSaverObj::~CDDSaverObj()
  {
  }

bool CDDSaverObj::OnCreate()
  {
  //= Hintergrund erzeugend 
  CDDSaverBackground *pBack = new CDDSaverBackground(this);
  if (pBack == NULL)
    return false;

  int xSize = m_szSize.cx / m_Param.m_iCells;
  int ySize = m_szSize.cy / m_Param.m_iCells;

  //= Alle Sprites anlegen
  for (int i = 0; i < m_Param.m_iCells; i++)
    {
    int xs;

    if (i == m_Param.m_iCells - 1)
      //= Letzte Spalte
      xs = m_szSize.cx - xSize * (m_Param.m_iCells - 1);
    else 
      //= Alle anderen Spalten
      xs = xSize;

    for (int j = 0; j < m_Param.m_iCells; j++)
      {
      int ys;

      if (j == m_Param.m_iCells - 1)
        //= Letzte Zeile
        ys = m_szSize.cy - ySize * (m_Param.m_iCells - 1);
      else 
        //= Alle andere Zeilen
        ys = ySize;

      CDDSaverSprite *pSprite = new CDDSaverSprite(this);
      if (pSprite == NULL || !pSprite->Create(xs, ys, 
                                              xSize * i, ySize * j, 
                                              m_Param.m_iSpeed))
        return false;
      }
    }

  //= Zustand festlegen
  m_iState = 0;
  m_lTime = timeGetTime();

  //= Zufall-Generator festlegen
  srand((unsigned)time(NULL));

  //= Inhalt des Sprites ausfüllen
  FillSprites();
  return true;
  }

void CDDSaverObj::Loop()
  {
  CDDMainObj::Loop();
  if (m_iState == 0 || m_iState == 2)
    {
    if (timeGetTime() - m_lTime < m_Param.m_iWait * 1000)
      return;

    m_iState++;
    m_lTime = timeGetTime();
    //= Zustand aller Sprites ändern
    POSITION pos = m_SpriteList.GetHeadPosition();
    while (pos != NULL)
      {
      CDDSprite *pSprite = m_SpriteList.GetNext(pos);

      if (pSprite->IsKindOf(RUNTIME_CLASS(CDDSaverSprite)))
        ((CDDSaverSprite *)pSprite)->SetState(m_iState);
      }
    }
  else if (m_iState == 1 || m_iState == 3)
    {
    //= Zustand der Sprites checken
    POSITION pos = m_SpriteList.GetHeadPosition();
    while (pos != NULL)
      {
      CDDSprite *pSprite = m_SpriteList.GetNext(pos);
      if (pSprite->IsKindOf(RUNTIME_CLASS(CDDSaverSprite)))
        if (((CDDSaverSprite *)pSprite)->GetState() == m_iState)
          break;
      }
    
    if (pos == NULL && ++m_iState == 4)
      {
      m_iState = 0;
      FillSprites();
      }
    }
  }

void CDDSaverObj::FillSprites()
  {
  //= Festlegen des Anfangszustandes 
  CDC dc;
  if (GetDC(dc))
    {
    dc.FillSolidRect(0, 0, m_szSize.cx, m_szSize.cy, m_Param.m_cBack);
    if (m_Param.m_iType == 1)
      {
      CTime cur_time;
      cur_time = CTime::GetCurrentTime();
      m_Param.m_sText = cur_time.Format("%H:%M");
      }
    
    CFont fnt, *pOldFont;
    fnt.CreateFontIndirect(&m_Param.m_fFont);
    pOldFont = dc.SelectObject(&fnt);

    dc.SetTextColor(m_Param.m_cFore);
    CRect rect(0, 0, m_szSize.cx, m_szSize.cy);
    dc.DrawText(m_Param.m_sText, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
    dc.SelectObject(pOldFont);
    fnt.DeleteObject();

    ReleaseDC(dc);
    }


  CDDBackFiller pBackFiller(this);

  //= Bildschirm-Zelle im Sprite kopieren
  POSITION pos = m_SpriteList.GetHeadPosition();
  while (pos != NULL)
    {
    CDDSprite *pSprite = m_SpriteList.GetNext(pos);
    if (pSprite->IsKindOf(RUNTIME_CLASS(CDDSaverSprite)))
      ((CDDSaverSprite *)pSprite)->FillSurface(&pBackFiller);
    }

  Flip();
  }
