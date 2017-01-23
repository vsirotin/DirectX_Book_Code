// ddPuzzles2Obj.cpp: implementation of the CDDPuzzles2Obj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ddPuzzles2.h"
#include "ddPuzzles2Obj.h"

#include "ddPuzzlesBackground.h"
#include "ddPuzzlesSprite.h"

#include "ddPCXFiller.h"
#include "ddNullFiller.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CDDPuzzles2Obj::CDDPuzzles2Obj()
  {
  }

CDDPuzzles2Obj::~CDDPuzzles2Obj()
  {
  }

bool CDDPuzzles2Obj::OnCreate()
  {
  //= Anfangszustand auf dem Hintergrundpuffer zeichnen
  CDDPCXFiller pcxFiller;

  //= PCX-Datei öffnen

  if (!pcxFiller.Create(ResolveName("room.pcx")))
    return false;

  //= Die Größe des Bildes ermitteln
  int iWidth, iHeight;
  pcxFiller.GetSize(&iWidth, &iHeight);

  //= Anzahl der Zellen berechnen
  int iCellSizeX = 40;
  int iCellSizeY = 37;
  int iCellsX = iWidth % iCellSizeX == 0 ? iWidth / iCellSizeX : iWidth / iCellSizeX + 1;
  int iCellsY = iHeight % iCellSizeY == 0 ? iHeight / iCellSizeY : iHeight / iCellSizeY + 1;

  //= Sprite-Eigenschaften festlegen
  int iLugGapX = 13;
  int iLugSizeX = 14;
  int iLugGapY = 12;
  int iLugSizeY = 13;
  int iLugSizeH = 7;

  //= Position des Bildes sichern
  CPoint ptPose = CPoint((480 - iWidth) / 2, (480 - iHeight) / 2);

  //= Hintergrund anlegen und initialisieren
  CDDPuzzlesBackground *pBack = new CDDPuzzlesBackground(this);
  if (pBack == NULL)
    return false;

  if (!pBack->Create(iWidth, iHeight, iCellsX, iCellsY, iCellSizeX, iCellSizeY,
                     iLugGapX, iLugSizeX, iLugGapY, iLugSizeY, iLugSizeH))
    return false;

  //= Bild laden und auf Hintergrund kopieren
  if (!pcxFiller.FillSurface(pBack))
    return false;

  //= Alle Puzzleteile anlegen
  int xsize, ysize;
  for (int i = 0; i < iCellsX; i++)
    {
    if (i == iCellsX - 1)
      xsize = iWidth - iCellSizeX * (iCellsX - 1);
    else
      xsize = iCellSizeX;

    for (int j = 0; j < iCellsY; j++)
      {
      if (j == iCellsY - 1)
        ysize = iHeight - iCellSizeY * (iCellsY - 1);
      else
        ysize = iCellSizeY;

      CDDPuzzlesSprite *pSprite = new CDDPuzzlesSprite(this);

      if (pSprite != NULL)
        {
        if (!pSprite->Create(xsize, ysize, 
                            ptPose.x + iCellSizeX * i, 
                            ptPose.y + iCellSizeY * j,
                            iLugGapX, iLugSizeX, 
                            iLugGapY, iLugSizeY, 
                            iLugSizeH,
                            (i == 0),
                            (j == 0),
                            (i == (iCellsX - 1)),
                            (j == (iCellsY - 1)), NULL))
          return false;
        }

      CDDPuzzlesSprite *pSpriteDupl = new CDDPuzzlesSprite(this);

      if (pSpriteDupl != NULL)
        {
        if (!pSpriteDupl->Create(xsize, ysize, 
                                 ptPose.x + iCellSizeX * i, 
                                 ptPose.y + iCellSizeY * j,
                                 iLugGapX, iLugSizeX, 
                                 iLugGapY, iLugSizeY, 
                                 iLugSizeH,
                                 (i == 0),
                                 (j == 0),
                                 (i == (iCellsX - 1)),
                                 (j == (iCellsY - 1)), pSprite))
          return false;
        }
      }
    }

  //= OK
  return true;
  }

void CDDPuzzles2Obj::Start()
  {
  //= Bildschierm - Zelle in das Sprite kopieren
  POSITION pos = m_SpriteList.GetHeadPosition();
  while (pos != NULL)
    {
    CDDSprite *pSprite = m_SpriteList.GetNext(pos);
    if (pSprite->IsKindOf(RUNTIME_CLASS(CDDPuzzlesBackground)))
      continue;

    //= Puzzle initialisieren
    ((CDDPuzzlesSprite *)pSprite)->FillSurface();

    //= Nächstes Sprite überspriungen (duplicate)
    m_SpriteList.GetNext(pos);
    }

  //= Zweites Sprite initiieren
  pos = m_SpriteList.GetHeadPosition();
  while (pos != NULL)
    {
    CDDSprite *pSprite = m_SpriteList.GetNext(pos);
    if (pSprite->IsKindOf(RUNTIME_CLASS(CDDPuzzlesBackground)))
      {
      ((CDDPuzzlesBackground *)pSprite)->DrawCells(RGB(255, 255, 255));
    
      //= Nächstes Sprite überspriungen
      m_SpriteList.GetNext(pos);
      continue;
      }

    //= Nächstes Sprite überspriungen (duplicate)
    ((CDDPuzzlesSprite *)pSprite)->FillSurface();
    if (pos != NULL)
      m_SpriteList.GetNext(pos);
    }

  pos = m_SpriteList.GetHeadPosition();
  while (pos != NULL)
    {
    CDDSprite *pSprite = m_SpriteList.GetNext(pos);
    if (pSprite->IsKindOf(RUNTIME_CLASS(CDDPuzzlesBackground)))
      {
      //= Hintergrund initiieren
      CDDNullFiller::FillSurface(pSprite);
      CDDNullFiller::FillSurface(this);
      ((CDDPuzzlesBackground *)pSprite)->FillSurface();
      break;
      }
    }

  //= Man kann jetzt die Sprites zeichnen
  m_bStarted = true;
  }

