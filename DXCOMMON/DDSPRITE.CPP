// ddSprite.cpp: implementation of the CDDSprite class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ddMainObj.h"
#include "ddSprite.h"
#include "ddSurfaceFiller.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CDDSprite, CObject);
CDDSprite::CDDSprite(CDDMainObj *pOwner)
  {
  //= Anfangswerte festlegen
  m_nOfFrames = 0;
  m_pSurface = NULL;
  m_pSurfaces = NULL;
  m_szSize = CSize(0, 0);
  m_ptPose = CPoint(0, 0);

  //= Sich beim Besitzer registrieren lassen
  m_pOwner = pOwner;
  m_pOwner->AddSprite(this);
  m_bColorKey = false;
  m_bClone = false;
  }
  
CDDSprite::~CDDSprite()
  {

  if (m_nOfFrames != 0)
    {
    if (!m_bClone)
      {
      for (int i = 0; i < m_nOfFrames; i++)
        m_pSurfaces[i]->Release();

      delete [] m_pSurfaces;
      }
    }
  }

bool CDDSprite::Create(int xs, int ys, int n_of_frames)
  {
  m_pSurfaces = new LPDIRECTDRAWSURFACE3 [n_of_frames];
  if (m_pSurfaces == NULL)
    return false;

  //= Oberflächeneigenschaften festlegen  
  DDSURFACEDESC ddSurfDesc;

  memset(&ddSurfDesc, 0, sizeof(DDSURFACEDESC));
  ddSurfDesc.dwSize = sizeof(DDSURFACEDESC);
  ddSurfDesc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
  ddSurfDesc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
  ddSurfDesc.dwWidth = xs;
  ddSurfDesc.dwHeight = ys;

  //= n_of_frames Exemplaren von Oberflächen anlegen
  for (int i = 0; i < n_of_frames; i++)
    {
    //= Außerbildschirmoberfläche erzeugen
    LPDIRECTDRAWSURFACE pSurf;
    DDTRY(m_pOwner->m_lpDD->CreateSurface(&ddSurfDesc, &pSurf, NULL));

    //= Den Zeiger auf der DirectDrawSurface3-Schnittstelle ermitteln
    bool res = DDCHECK(pSurf->QueryInterface(IID_IDirectDrawSurface3, (void **)(m_pSurfaces + i)));
    pSurf->Release();

    if (!res)
      return false;
    }

  //= Aktuelle Oberfläche festlegen
  m_pSurface = m_pSurfaces[0];
  m_nOfFrames = n_of_frames;
  m_iCurFrame = 0;

  //= Größe, Position und Zustand des Sprites festlegen
  m_szSize = CSize(xs, ys);
  m_bChanged = true;

  return true;
  }

bool CDDSprite::Clone(CDDSprite *pFather)
  {
  //= Den Zeiger auf der Oberfläche ermitteln und festlegen
  m_pSurfaces = pFather->m_pSurfaces;
  if (m_pSurfaces == NULL)
    return false;

  //= Andere Eigenschaften festlegen
  m_bClone = true;
  m_pSurface = m_pSurfaces[0];
  m_nOfFrames = pFather->m_nOfFrames;
  m_iCurFrame = 0;

  m_szSize = pFather->m_szSize;
  m_ptPose = pFather->m_ptPose;

  m_bColorKey = pFather->m_bColorKey;
  return true;
  }

bool CDDSprite::FillSurface(CDDSurfaceFiller *pFiller)
  {
  return pFiller->FillSurface(this, m_ptPose, m_szSize);
  }

void CDDSprite::SetColorKey(LPDDCOLORKEY lpddck) 
  {
  m_bColorKey = true;
  m_pSurface->SetColorKey(DDCKEY_SRCBLT, lpddck);
  }

bool CDDSprite::IsChanged()
  {
  if (m_bChanged)
    {
    m_bChanged = false;
    return true;
    }

  return false;
  }

CSize CDDSprite::GetSize() 
  {
  return m_szSize;
  }

void CDDSprite::Draw()
  {
  CPoint pose = m_ptPose;

  CRect rectSprite(pose, m_szSize);
  CRect rectScreen(0, 0, m_pOwner->m_szSize.cx, m_pOwner->m_szSize.cy);
  CRect rect;

  if (rect.IntersectRect(&rectSprite, &rectScreen))
    {
    CPoint pntScreen, pntSprite;
    if (pose.x >= 0)
      {
      pntScreen.x = pose.x;
      pntSprite.x = 0;
      }
    else
      {
      pntScreen.x = 0;
      pntSprite.x = -pose.x;
      }

    if (pose.y >= 0)
      {
      pntScreen.y = pose.y;
      pntSprite.y = 0;
      }
    else
      {
      pntScreen.y = 0;
      pntSprite.y = -pose.y;
      }

    CRect r(pntSprite, rect.Size());

    DWORD dwTrans = DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY;
    if (m_bColorKey)
      dwTrans |= DDBLTFAST_SRCCOLORKEY;

    m_pOwner->m_lpDDBackSurface->BltFast(pntScreen.x, pntScreen.y, m_pSurface, &r, dwTrans);
    }
  }

void CDDSprite::NextFrame()
  {
  if (++m_iCurFrame == m_nOfFrames)
    m_iCurFrame = 0;

  m_pSurface = m_pSurfaces[m_iCurFrame];
  }

void CDDSprite::PrevFrame()
  {
  if (--m_iCurFrame == -1)
    m_iCurFrame = m_nOfFrames - 1;

  m_pSurface = m_pSurfaces[m_iCurFrame];
  }

