// ddPuzzlesSprite.cpp: implementation of the CDDPuzzlesSprite class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ddpuzzles.h"
#include "ddMainObj.h"
#include "ddPuzzlesSprite.h"
#include "ddBackFiller.h"
#include "ddNullFiller.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CDDPuzzlesSprite, CDDSprite)
CDDPuzzlesSprite::CDDPuzzlesSprite(CDDMainObj *pOwner) : CDDSprite(pOwner)
  {
  }

CDDPuzzlesSprite::~CDDPuzzlesSprite()
  {
  }

bool CDDPuzzlesSprite::Create(int xs, int ys, int xorg, int yorg,
                              int iLugGapX, int iLugSizeX, 
                              int iLugGapY, int iLugSizeY, 
                              int iLugSizeH,
                              bool bFirstColumn, bool bFirstRow, 
                              bool  bLastColumn, bool bLastRow, 
                              CDDPuzzlesSprite *pDupl)
  {

  m_pSpriteDupl = pDupl;

  //= Die aktuelle Grˆﬂe des Sprites kalkulieren
  int xsActual = bFirstColumn ? xs : xs + iLugSizeH;
  int ysActual = bFirstRow ? ys : ys + iLugSizeH;

  //= Zuerst Basisklasse initiieren
  if (!CDDSprite::Create(xsActual, ysActual))
    return false;

  //= Die aktuelle Position des Sprites kalkulieren
  int xorgActual = bFirstColumn ? xorg : xorg - iLugSizeH;
  int yorgActual = bFirstRow ? yorg : yorg - iLugSizeH;

  //= Position sichern
  m_ptOrg = CPoint(xorgActual, yorgActual);

  //= Neue Position festlegen
  m_ptPose = m_ptOrg;

  //= Sprite - Parameter sichern
  m_iLugGapX  = iLugGapX;
  m_iLugSizeX = iLugSizeX;
  m_iLugRestX = xs - iLugGapX - iLugSizeX;
  m_iLugGapY  = iLugGapY;
  m_iLugSizeY = iLugSizeY;
  m_iLugRestY = ys - iLugGapY - iLugSizeY;

  m_iLugSizeH = iLugSizeH;

  m_bLastColumn = bLastColumn;
  m_bLastRow = bLastRow;

  //= Seitenwechseln nach dem Anlegen vermeiden
  m_bChanged = false;
  m_iState = 2;
  return true; //= OK
  }

bool CDDPuzzlesSprite::IsChanged()
  {
  if (m_iState == 1)
    {
    m_iState = 0;
    return true;
    }

  return false;
  }

void CDDPuzzlesSprite::FillSurface()
  {
  //= Sprite von der Zelle kopieren
  CDDBackFiller filler(m_pOwner);
  filler.FillSurface(this, m_ptOrg, m_szSize);

  //= Farbschl¸ssel festlegen
  DDCOLORKEY ddck;
  ddck.dwColorSpaceLowValue = 0;
  ddck.dwColorSpaceHighValue = 0;
  
  SetColorKey(&ddck);
  int sx = m_szSize.cx, sy = m_szSize.cy;

  //= Oberste Seite
  SetColor(sx - m_iLugSizeH - m_iLugGapX - m_iLugSizeX - m_iLugRestX, 
           sy - m_iLugSizeH - m_iLugGapY - m_iLugSizeY - m_iLugRestY, 
           sx - m_iLugSizeX - m_iLugRestX + 1, 
           sy - m_iLugGapY - m_iLugSizeY - m_iLugRestY - 1);

  SetColor(sx - m_iLugRestX, 
           sy - m_iLugSizeH - m_iLugGapY - m_iLugSizeY - m_iLugRestY, 
           sx, 
           sy - m_iLugGapY - m_iLugSizeY - m_iLugRestY - 1);

  //= Linke Seite
  SetColor(sx - m_iLugSizeH - m_iLugGapX - m_iLugSizeX - m_iLugRestX, 
           sy - m_iLugSizeH - m_iLugGapY - m_iLugSizeY - m_iLugRestY, 
           sx - m_iLugGapX - m_iLugSizeX - m_iLugRestX, 
           sy - m_iLugSizeY - m_iLugRestY);

  SetColor(sx - m_iLugSizeH - m_iLugGapX - m_iLugSizeX - m_iLugRestX, 
           sy - m_iLugRestY, 
           sx - m_iLugGapX - m_iLugSizeX - m_iLugRestX, 
           sy);

  //= Untere Seite
  if (!m_bLastRow)
    {
    //= Alle Zeilen auﬂer der letzten
    SetColor(sx - m_iLugSizeX - m_iLugRestX + 1, 
             sy - m_iLugSizeH, 
             sx - m_iLugRestX, 
             sy);
    }

  //= Rechte Seite
  if (!m_bLastColumn)
    {
    //= Alle Spalten auﬂer der letzten
    SetColor(sx - m_iLugSizeH, 
             sy - m_iLugSizeY - m_iLugRestY + 1, 
             sx, 
             sy - m_iLugRestY - 1);
    }

  //= Anfangssituation
  if (m_pSpriteDupl == NULL)
    {
    m_iState = 2;
    m_ptPose = m_ptOrg;
    }
  else
    {
    m_iState = 1;
  
    //= Anfangsposition kalkulieren
    int x, y;

    x = 480 + (int)(((double)rand() / RAND_MAX) * 120);
    y =   0 + (int)(((double)rand() / RAND_MAX) * 400);

    //= Anfangsposition ‰ndern
    m_ptPose = CPoint(x, y);
    }

  }

bool CDDPuzzlesSprite::PtInSprite(CPoint point)
  {
  //= Wenn der Punkt innerhalb des Sprite-Rechtecks liegt
  CRect rect(m_ptPose, m_szSize);
  if (m_pSpriteDupl == NULL || m_iState == 2)
    return false;

  return rect.PtInRect(point) ? true : false;
  }

void CDDPuzzlesSprite::StartMove(CPoint point)
  {
  //= Cursorposition sichern
  m_ptCurrent = point;

  //= Sprite ist ge‰ndert
  m_iState = 1;

  //= Sprite in das Ende der Liste verschieben
  m_pOwner->MoveSpriteToEnd(this);
  }

void CDDPuzzlesSprite::Move(CPoint point)
  {
  //= Die Verzˆgerung der Maus kalkulieren
  CPoint p = m_ptCurrent - point;

  //= Aktuelle Position festlegen
  m_ptPose -= p;
  m_ptCurrent = point;

  m_iState = 1; //= Sprite sollte neue gezeigt werden
  }

void CDDPuzzlesSprite::EndMove(CPoint point)
  {
  //= Aktuelle Position festlegen
  CPoint p = m_ptCurrent - point;
  m_ptPose -= p;

  //= Wenn die Stelle nahe an der  Originalstelle liegt
  //=  Plazieren des Sprites auf der Originalstelle	
  CRect rect(m_ptOrg, m_szSize);
  CRect rect1(m_ptPose, m_szSize);

  rect1.DeflateRect(rect1.Width() / 5, rect1.Height() / 5);
  p = rect.CenterPoint();
  if (rect1.PtInRect(p))
    {
    m_iState = 2;
    m_ptPose = m_ptOrg;

    m_pSpriteDupl->m_iState = 1;
    return;
    }

  m_iState = 1;  //= Das Sprite muﬂ neue gezeichnet werden
  }

void CDDPuzzlesSprite::SetColor(int x0, int y0, int x1, int y1)
  {
  int X0, Y0, X1, Y1;

  X0 = max(x0, 0);
  Y0 = max(y0, 0);
  X1 = min(x1, m_szSize.cx);
  Y1 = min(y1, m_szSize.cy - 1);

  CDDNullFiller::FillRectangle(this, X0, Y0, X1, Y1);
  }

void CDDPuzzlesSprite::Draw()
  {
  if (m_iState != 2)
    CDDSprite::Draw();

  }