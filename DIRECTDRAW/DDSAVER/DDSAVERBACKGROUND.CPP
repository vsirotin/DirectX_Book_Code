// ddSaverBackground.cpp: implementation of the CDDSaverBackground class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ddSaver.h"
#include "ddSaverBackground.h"

#include "ddMainObj.h"
#include "ddNullFiller.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CDDSaverBackground, CDDSprite)
CDDSaverBackground::CDDSaverBackground(CDDMainObj *pOwner) : CDDSprite(pOwner)
  {
  m_pSurface = pOwner->GetBackSurface();
  }

CDDSaverBackground::~CDDSaverBackground()
  {
  m_pSurface = NULL;
  }

void CDDSaverBackground::Draw(void)
  {
  CDDNullFiller::FillSurface(this);
  }

