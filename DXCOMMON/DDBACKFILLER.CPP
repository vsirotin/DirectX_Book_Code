// ddBackFiller.cpp: implementation of the CDDBackFiller class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ddMainObj.h"
#include "ddSprite.h"
#include "ddBackFiller.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CDDBackFiller, CDDSurfaceFiller);
CDDBackFiller::CDDBackFiller(CDDMainObj *pObj)
  {
  m_pDDObj = pObj;
  }

CDDBackFiller::~CDDBackFiller()
  {
  }

bool CDDBackFiller::FillSurface(CDDSprite *pSprite, CPoint pPose, CSize pSize)
  {
  CRect rect(pPose, pSize);
  (pSprite->GetSurface())->BltFast(0, 0, m_pDDObj->GetBackSurface(), &rect, 
                                   DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);

  return true;
  }
