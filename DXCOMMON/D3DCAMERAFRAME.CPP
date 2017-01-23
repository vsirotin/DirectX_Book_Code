// d3dCameraFrame.cpp : implementation file
//

#include "stdafx.h"

#include "d3dMainObj.h"
#include "d3dCameraFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CD3DCameraFrame

IMPLEMENT_DYNAMIC(CD3DCameraFrame, CD3DFrame)

CD3DCameraFrame::CD3DCameraFrame()
  {
  }

CD3DCameraFrame::~CD3DCameraFrame()
  {
  }

bool CD3DCameraFrame::Create(CD3DMainObj *pOwner)
  {
  if (!CD3DFrame::Create(pOwner))
    return false;

  if (!AddToFrame(pOwner))
    return false;
  
  return true;
  }


