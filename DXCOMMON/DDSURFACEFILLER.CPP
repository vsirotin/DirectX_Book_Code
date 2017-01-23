// ddSurfaceFiller.cpp: implementation of the CDDSurfaceFiller class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ddSurfaceFiller.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CDDSurfaceFiller, CObject);
CDDSurfaceFiller::CDDSurfaceFiller()
  {
  }

CDDSurfaceFiller::~CDDSurfaceFiller()
  {
  }

bool CDDSurfaceFiller::FillSurface(CDDSprite *pSprite, CPoint pPose, CSize pSize)
  {
  //= Basisklasse tut nichts
  return true;
  }
