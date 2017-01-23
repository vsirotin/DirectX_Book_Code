// ddAquaObj.cpp: implementation of the CDDAquaObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ddAqua.h"
#include "ddAquaObj.h"

#include "ddAquaBackground.h"
#include "ddAquaSprite.h"

#include "ddPCXFiller.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static char *ResolveName(char *name, char *ext)
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
    strcat(newname, ext);

    if (CFile::GetStatus(newname, status))
      {
      strcpy(newname, path[i]);
      strcat(newname, name);
      return newname;
      }
    }

  sprintf(newname, "FILE: %s not found", name);
  AfxMessageBox(newname);

  return name;
  }

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CDDAquaObj, CDDMainObj)
CDDAquaObj::CDDAquaObj()
  {
  }

CDDAquaObj::~CDDAquaObj()
  {
  }

bool CDDAquaObj::OnCreate()
  {
  //= Hintergrund erzeugen
  CDDAquaBackground *pBack = new CDDAquaBackground(this);
  if (pBack == NULL || !pBack->Create(ResolveName("AquaBackground.pcx", "")))
    return false;

  //= Alle Sprites anlegen
  CDDAquaSprite *pSprite, *pcSprite;
  
  pSprite = new CDDAquaSprite(this);
  if (pSprite == NULL || !pSprite->Create(510, 41, ResolveName("AquaFloraOne", "00.pcx"), 5, 350))
    return false;

  pSprite = new CDDAquaSprite(this);
  if (pSprite == NULL || !pSprite->Create(470, 218, ResolveName("AquaFloraTwo", "00.pcx") , 10, 300))
    return false;

  pcSprite = new CDDAquaSprite(this);
  if (pcSprite == NULL || !pcSprite->Clone(pSprite, 450, 220, 310))
    return false;

  pcSprite = new CDDAquaSprite(this);
  if (pcSprite == NULL || !pcSprite->Clone(pSprite, 445, 223, 290))
    return false;

  pcSprite = new CDDAquaSprite(this);
  if (pcSprite == NULL || !pcSprite->Clone(pSprite, 465, 230, 330))
    return false;

  pcSprite = new CDDAquaSprite(this);
  if (pcSprite == NULL || !pcSprite->Clone(pSprite, 458, 230, 320))
    return false;
  
  pSprite = new CDDAquaSprite(this);
  if (pSprite == NULL || !pSprite->Create(77, 310, ResolveName("AquaFloraThree", "00.pcx"), 5, 500))
    return false;

  return true;
  }

void CDDAquaObj::Capture() 
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

  DWORD j;
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
