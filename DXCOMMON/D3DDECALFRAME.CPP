// d3dDecalFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dDecalFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DDecalFrame

IMPLEMENT_DYNAMIC(CD3DDecalFrame, CD3DFrame)

CD3DDecalFrame::CD3DDecalFrame()
  {
  }

CD3DDecalFrame::~CD3DDecalFrame()
  {
  }

bool CD3DDecalFrame::Create(CD3DMainObj *pOwner, CD3DTexture *tex)
  {
  if (!CD3DFrame::Create(pOwner))
    return false;

  //= Poster-Frame zu Direct3D hinzufügen  
  if (!AddDecalVisual(tex))
    return false;

  return true;
  }

