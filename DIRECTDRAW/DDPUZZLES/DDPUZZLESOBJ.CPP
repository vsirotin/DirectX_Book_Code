// ddPuzzlesObj.cpp: implementation of the CDDPuzzlesObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ddpuzzles.h"
#include "ddPuzzlesObj.h"
#include "ddPuzzlesBackground.h"
#include "ddPuzzlesSprite.h"

#include "ddPCXFiller.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

char *ResolveName(char *name)
  {
  static char newname[_MAX_PATH];
  static char *path[] = {"", "data\\", 
                         "..\\", "..\\data\\", 
                         "..\\..\\", "..\\..\\data\\",
                         "..\\..\\..\\", "..\\..\\..\\data\\",
                         "..\\..\\..\\..\\", "..\\..\\..\\..\\data\\"
                        };

  CFileStatus status;

  for (int i = 0; i < sizeof(path) / sizeof(path[0]); i++)
    {
    strcpy(newname, path[i]);
    strcat(newname, name);

    if (CFile::GetStatus(newname, status))
      return newname;
    }

  sprintf(newname, "FILE: %s not found", name);
  AfxMessageBox(newname);

  return name;
  }

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CDDPuzzlesObj, CDDMainObj);
CDDPuzzlesObj::CDDPuzzlesObj()
  {
  //=Am Anfang gibt es keine Sprites
  m_pDraggedSprite = NULL;

  //= Das Spiel startet jetzt 
  m_bStarted = false;
  }

CDDPuzzlesObj::~CDDPuzzlesObj()
  {
  }

bool CDDPuzzlesObj::OnCreate()
  {
  //= Festlegen des Anfangszustandes auf der zusätzlichen Oberfläche
  CDDPCXFiller pcxFiller;

  //= Öffnen der PCX-Datei
  if (!pcxFiller.Create(ResolveName("room.pcx")))
    return false;

  //= Ermitteln der Größe des Bildes
  int iWidth, iHeight;
  pcxFiller.GetSize(&iWidth, &iHeight);

  //= Bild auf der zusätzliche Oberfläche ausfüllen
  if (!pcxFiller.FillSurface(this, (480 - iWidth) / 2, (480 - iHeight) / 2))
    return false;

  //= Palette festlegen
  PALETTEENTRY palette[256];
  pcxFiller.GetDirectDrawPalette(palette);
  if (!SetPalette(palette))
    return false;

  //= Bild auf dem Bildschirm anzeigen
  Flip();

  //= Anzahl der Zellen jeder Dimension entlang rechnen 
  int iCellSizeX = 40;
  int iCellSizeY = 37;
  int iCellsX = iWidth % iCellSizeX == 0 ? iWidth / iCellSizeX : iWidth / iCellSizeX + 1;
  int iCellsY = iHeight % iCellSizeY == 0 ? iHeight / iCellSizeY : iHeight / iCellSizeY + 1;

  //= Die Größe der Sprites festlegen
  int iLugGapX = 13;
  int iLugSizeX = 14;
  int iLugGapY = 12;
  int iLugSizeY = 13;
  int iLugSizeH = 7;

  //= Position des Bildes für die weitere Verwendung sichern
  CPoint ptPose = CPoint((480 - iWidth) / 2, (480 - iHeight) / 2);

  //= Hintergrund anlegen
  CDDPuzzlesBackground *pBack = new CDDPuzzlesBackground(this);
  if (pBack == NULL)
    return false;

  if (!pBack->Create(iWidth, iHeight, iCellsX, iCellsY, iCellSizeX, iCellSizeY,
                     iLugGapX, iLugSizeX, iLugGapY, iLugSizeY, iLugSizeH))
    return false;

  //= Alle Puzzleteile erzeugen
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

void CDDPuzzlesObj::Start()
  {
  //= Bildschirmbereiche in Sprites kopieren
  POSITION pos = m_SpriteList.GetHeadPosition();
  while (pos != NULL)
    {
    CDDSprite *pSprite = m_SpriteList.GetNext(pos);
    if (pSprite->IsKindOf(RUNTIME_CLASS(CDDPuzzlesBackground)))
      {
      //= Hintergrund initialisieren
      ((CDDPuzzlesBackground *)pSprite)->FillSurface();
      Flip();
      continue;
      }

    //= Puzzle initialisieren
    ((CDDPuzzlesSprite *)pSprite)->FillSurface();

    
    m_SpriteList.GetNext(pos);
    }

  
  pos = m_SpriteList.GetHeadPosition();
  while (pos != NULL)
    {
    CDDSprite *pSprite = m_SpriteList.GetNext(pos);
    if (pSprite->IsKindOf(RUNTIME_CLASS(CDDPuzzlesBackground)))
      {
      ((CDDPuzzlesBackground *)pSprite)->DrawCells(RGB(255, 255, 255));
    
      //= Zum nächsten Sprite übergehen
      m_SpriteList.GetNext(pos);
      continue;
      }

    //= Das Puzzle initialisieren
    ((CDDPuzzlesSprite *)pSprite)->FillSurface();
    if (pos != NULL)
      m_SpriteList.GetNext(pos);
    }

  //= Jetzt kann der Benutzer das Puzzleteil ziehen
  m_bStarted = true;
  }

int CDDPuzzlesObj::OnMouseMove(UINT nFlags, CPoint point) 
  {
  if (!m_bStarted)
    return 0;     //= Spiel ist nicht gestartet

  //= Wir ziehen keine Sprites 
  if (m_pDraggedSprite == NULL)
    {
    //= Cursorposition checken
    POSITION pos = m_SpriteList.GetHeadPosition();
    CDDPuzzlesSprite *pSprite = (CDDPuzzlesSprite *)m_SpriteList.GetNext(pos);
    while (pos != NULL)
      {
      pSprite = (CDDPuzzlesSprite *)m_SpriteList.GetNext(pos);

      //= Wenn sich der Cursor auf einem Sprite befindet,
	  //= ändert sich sein Aussehen
      if (pSprite->PtInSprite(point))
        return 1;
      }

    return 0;
    }

  //= Wir ziehen hier ein Sprite
  m_pDraggedSprite->Move(point);
  return 2;
  }

int CDDPuzzlesObj::OnLButtonDown(UINT nFlags, CPoint point) 
  {
  if (!m_bStarted)
    return 0;         //= Spiel ist nicht gestartet.

  m_pDraggedSprite = NULL;

  //= Cursorposition checken
  POSITION pos = m_SpriteList.GetHeadPosition();

  //= Erstes Sprite wird übersprungen. 
  //= Das ist ein Hintergrund.
  CDDPuzzlesSprite *pSprite = (CDDPuzzlesSprite *)m_SpriteList.GetNext(pos);
  while (pos != NULL)
    {
    pSprite = (CDDPuzzlesSprite *)m_SpriteList.GetNext(pos);

    if (pSprite->PtInSprite(point))
      m_pDraggedSprite = pSprite;
    }

  //= Wenn der Cursor sich auf einem Sprite befindet,
  //= machen wir die Verschiebung.
  if (m_pDraggedSprite != NULL)
    {
    m_pDraggedSprite->StartMove(point);
    return 1;                            //= Cursortyp ändern
    }

  return 0;
  }

int CDDPuzzlesObj::OnLButtonUp(UINT nFlags, CPoint point) 
  {
  if (!m_bStarted)
    return 0;       //= Spiel ist nicht gestartet.

  if (m_pDraggedSprite != NULL)
    {
    //= Ein Sprite ist verschoben.
    m_pDraggedSprite->EndMove(point);
    m_pDraggedSprite = NULL;
    return 1;       //= Cursortyp ändern
    }

  return 0;
  }

void CDDPuzzlesObj::Capture() 
  {
  static int ncapt = 0;
  char fname[256];
  sprintf(fname, "capt%d.pcx", ncapt++);
  CPCX pcx;

  DDSURFACEDESC   ddsd;
  BYTE           *b;

  ZeroMemory(&ddsd, sizeof(ddsd));
  ddsd.dwSize = sizeof(ddsd);
  DDCHECK(m_lpDDPrimarySurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL));

  bool res = pcx.Init(8, 1, 0, 0, ddsd.dwWidth, ddsd.dwHeight);
  res = pcx.Write(fname);

  b = (BYTE *)ddsd.lpSurface;
  int j;
  for (j = 0; j < ddsd.dwHeight; j++, b += ddsd.lPitch)
    if (!pcx.PutLine(b))
      break;

  DDCHECK(m_lpDDPrimarySurface->Unlock(NULL));
  IMGPAL pal[256];
  for (int i = 0; i < 256; i++)
    pal[i].r = pal[i].g = pal[i].b = i;

  res = pcx.WritePal(pal);
  return;
  }
