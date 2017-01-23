// d3dDirectionalLight.cpp : implementation file
//

#include "stdafx.h"
#include "d3dDirectionalLight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DDirectionalLight

IMPLEMENT_DYNAMIC(CD3DDirectionalLight, CD3DLightFrame)

CD3DDirectionalLight::CD3DDirectionalLight()
  {
  m_LType = D3DRMLIGHT_DIRECTIONAL;
  }

CD3DDirectionalLight::~CD3DDirectionalLight()
  {
  }

