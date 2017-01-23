// d3dTexture.cpp : implementation file
//

#include "stdafx.h"

#include "d3dMainObj.h"
#include "d3dTexture.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DTexture

IMPLEMENT_DYNAMIC(CD3DTexture, CObject)

CD3DTexture::CD3DTexture()
  {
  m_lpTexture = NULL;
  m_pOwner = NULL;
  m_bChanged = false; 
  }

CD3DTexture::~CD3DTexture()
  {
//= Vom Besitzerobjekt entfernen
  if (m_pOwner != NULL)
    m_pOwner->RemoveTexture(this);
  
  D3DFREE(m_lpTexture);
  }

bool CD3DTexture::IsChanged()
  {
  bool bChanged = m_bChanged;
    
  m_bChanged = false;
  return bChanged;
  }

bool CD3DTexture::Create(CD3DMainObj *pOwner, LPCSTR filename, int iX, int iY,
                                D3DVALUE rvSizeX, D3DVALUE rvSizeY, 
                                bool transparency, D3DCOLOR transp_color)
  {
  if (pOwner == NULL)
    return false;

  pOwner->AddTexture(this); //= Beim Besitzerobjekt registrieren
  m_pOwner = pOwner;
  
  //= Textur-Objekt anlegen
  D3DTRY(m_pOwner->GetMainObject()->LoadTexture(filename, &m_lpTexture));

  //= Eigenschaften festlegen
  if (!SetOrigin(iX, iY))
    return false;
  if (!SetTransparency(transparency, transp_color))
    return false;
  if (!SetSize(rvSizeX, rvSizeY))
    return false;

  m_bChanged = true; 
  return true;
  }

bool CD3DTexture::SetTransparency(bool transparency, D3DCOLOR transp_color)
  {
  D3DTRY(m_lpTexture->SetDecalTransparency(transparency));
  
  m_bChanged = true; 

  if (!transparency)
    return true;

  D3DTRY(m_lpTexture->SetDecalTransparentColor(transp_color));

  return true;
  }

bool CD3DTexture::SetScale(bool scale)
  {
  m_bChanged = true; 
  D3DTRY(m_lpTexture->SetDecalScale(scale));

  return true;
  }

bool CD3DTexture::SetSize(D3DVALUE rvSizeX, D3DVALUE rvSizeY)
  {
  D3DTRY(m_lpTexture->SetDecalSize(rvSizeX, rvSizeY));

  m_bChanged = true; 

  return true;
  }

bool CD3DTexture::SetOrigin(int iX, int iY)
  {
  D3DTRY(m_lpTexture->SetDecalOrigin(iX, iY));

  m_bChanged = true; 

  return true;
  }

