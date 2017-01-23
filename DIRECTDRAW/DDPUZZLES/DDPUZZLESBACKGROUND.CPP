// ddPuzzlesBackground.cpp: implementation of the CDDPuzzlesBackground class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ddPuzzles.h"
#include "ddPuzzlesObj.h"
#include "ddPuzzlesBackground.h"

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

IMPLEMENT_DYNAMIC(CDDPuzzlesBackground, CDDSprite)
CDDPuzzlesBackground::CDDPuzzlesBackground(CDDMainObj *pOwner) : CDDSprite(pOwner)
  {
  }

CDDPuzzlesBackground::~CDDPuzzlesBackground()
  {
  }

bool CDDPuzzlesBackground::Create(int xs, int ys, int iCellsX, int iCellsY,
                                  int iCellsSizeX, int iCellsSizeY,
                                  int iLugGapX, int iLugSizeX, 
                                  int iLugGapY, int iLugSizeY, 
                                  int iLugSizeH)
  {
  //= Sprite für eine leere Zelle erzeugen
  if (!CDDSprite::Create(xs, ys))
    return false;

  m_ptPose.x = (480 - xs) / 2;
  m_ptPose.y = (480 - ys) / 2;

  m_iCellsX = iCellsX;
  m_iCellsY = iCellsY;

  m_iCellsSizeX = iCellsSizeX;
  m_iCellsSizeY = iCellsSizeY;

  m_iLugGapX = iLugGapX;
  m_iLugSizeX = iLugSizeX;
  m_iLugGapY = iLugGapY;
  m_iLugSizeY = iLugSizeY;

  m_iLugSizeH = iLugSizeH;

  //= Automatischen Seitenwechsel nach dem Anlegen vermeiden
  m_bChanged = false;
  return true;
  }

void CDDPuzzlesBackground::FillSurface()
  {
  //= Leere Zelle zeichnen
  DrawCells(RGB(148, 53, 19));

  //= Auf eigene Oberfläche alles kopieren
  
  CDDBackFiller pFiller(m_pOwner);
  pFiller.FillSurface(this, m_ptPose, m_szSize);
  }

void CDDPuzzlesBackground::Draw()
  {
  //= Hintergrund erzeugen
  CDDNullFiller::FillSurface(m_pOwner);

  //= Leere Zellen zeichnen
  CDDSprite::Draw();
  }

void CDDPuzzlesBackground::DrawCells(COLORREF color)
  {
  CDC dc;
  if (m_pOwner->GetDC(dc))
    {
    CPen pen, *pOldPen;
    pen.CreatePen(PS_SOLID, 0, color);
    pOldPen = dc.SelectObject(&pen);

    int xs, ys, xsize, ysize;
    xs = m_iCellsSizeX; 
    ys = m_iCellsSizeY; 

    for (int i = 0; i < m_iCellsX; i++)
      {
      if (i == m_iCellsX - 1)
        xsize = m_szSize.cx - xs * (m_iCellsX - 1);
      else
        xsize = xs;

      for (int j = 0; j < m_iCellsY; j++)
        {
        if (j == m_iCellsY - 1)
          ysize = m_szSize.cy - ys * (m_iCellsY - 1);
        else
          ysize = ys;

        //= Obere Grenze
        dc.MoveTo(m_ptPose.x + xs * i, m_ptPose.y + ys * j);
        if (j == 0)
          dc.LineTo(m_ptPose.x + xs * i + xsize - 1, m_ptPose.y + ys * j);
        else
          {
          dc.LineTo(m_ptPose.x + xs * i + m_iLugGapX + 1, 
                    m_ptPose.y + ys * j);
          dc.LineTo(m_ptPose.x + xs * i + m_iLugGapX + 1, 
                    m_ptPose.y + ys * j - m_iLugSizeH);
          dc.LineTo(m_ptPose.x + xs * i + m_iLugGapX + m_iLugSizeX - 1, 
                    m_ptPose.y + ys * j - m_iLugSizeH);
          dc.LineTo(m_ptPose.x + xs * i + m_iLugGapX + m_iLugSizeX - 1, 
                    m_ptPose.y + ys * j);
          dc.LineTo(m_ptPose.x + xs * i + xsize - 1, m_ptPose.y + ys * j);
          }
        
        //= Untere Grenze
        dc.MoveTo(m_ptPose.x + xs * i, m_ptPose.y + ys * j + ysize - 1);
        if (j == m_iCellsY - 1)
          dc.LineTo(m_ptPose.x + xs * i + xsize - 1, m_ptPose.y + ys * j + ysize - 1);
        else
          {
          dc.LineTo(m_ptPose.x + xs * i + m_iLugGapX, 
                    m_ptPose.y + ys * j + ysize - 1);
          dc.LineTo(m_ptPose.x + xs * i + m_iLugGapX, 
                    m_ptPose.y + ys * j + ysize - 1 - m_iLugSizeH);
          dc.LineTo(m_ptPose.x + xs * i + m_iLugGapX + m_iLugSizeX, 
                    m_ptPose.y + ys * j + ysize - 1 - m_iLugSizeH);
          dc.LineTo(m_ptPose.x + xs * i + m_iLugGapX + m_iLugSizeX, 
                    m_ptPose.y + ys * j + ysize - 1);
          dc.LineTo(m_ptPose.x + xs * i + xsize - 1, m_ptPose.y + ys * j + ysize - 1);
          }

        //= Linke Grenze
        dc.MoveTo(m_ptPose.x + xs * i, m_ptPose.y + ys * j);
        if (i == 0)
          dc.LineTo(m_ptPose.x + xs * i, m_ptPose.y + ys * j + ysize - 1);
        else
          {
          dc.LineTo(m_ptPose.x + xs * i, 
                    m_ptPose.y + ys * j + m_iLugGapY + 1);
          dc.LineTo(m_ptPose.x + xs * i - m_iLugSizeH, 
                    m_ptPose.y + ys * j + m_iLugGapY + 1);
          dc.LineTo(m_ptPose.x + xs * i - m_iLugSizeH, 
                    m_ptPose.y + ys * j + m_iLugGapY + m_iLugSizeY - 1);
          dc.LineTo(m_ptPose.x + xs * i, 
                    m_ptPose.y + ys * j + m_iLugGapY + m_iLugSizeY - 1);
          dc.LineTo(m_ptPose.x + xs * i, m_ptPose.y + ys * j + ysize - 1);
          }
        
        //= Rechte Grenze
        dc.MoveTo(m_ptPose.x + xs * i + xsize - 1, m_ptPose.y + ys * j);
        if (i == m_iCellsX - 1)
          dc.LineTo(m_ptPose.x + xs * i + xsize - 1, m_ptPose.y + ys * j + ysize);
        else
          {
          dc.LineTo(m_ptPose.x + xs * i + xsize - 1, 
                    m_ptPose.y + ys * j + m_iLugGapY);
          dc.LineTo(m_ptPose.x + xs * i + xsize - 1 - m_iLugSizeH, 
                    m_ptPose.y + ys * j + m_iLugGapY);
          dc.LineTo(m_ptPose.x + xs * i + xsize - 1 - m_iLugSizeH, 
                    m_ptPose.y + ys * j + m_iLugGapY + m_iLugSizeY);
          dc.LineTo(m_ptPose.x + xs * i + xsize - 1, 
                    m_ptPose.y + ys * j + m_iLugGapY + m_iLugSizeY);
          dc.LineTo(m_ptPose.x + xs * i + xsize - 1, m_ptPose.y + ys * j + ysize);
          }
        }
      }

    dc.SelectObject(pOldPen);
    pen.DeleteObject();

    m_pOwner->ReleaseDC(dc);
    }
  }