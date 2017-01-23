// d3dParallelPointLight.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dParallelPointLight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DParallelPointLight

IMPLEMENT_DYNAMIC(CD3DParallelPointLight, CD3DLightFrame)

CD3DParallelPointLight::CD3DParallelPointLight()
  {
  m_LType = D3DRMLIGHT_PARALLELPOINT;
  }

CD3DParallelPointLight::~CD3DParallelPointLight()
  {
  }

