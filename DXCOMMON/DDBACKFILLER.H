// ddBackFiller.h: interface for the CDDBackFiller class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDBACKFILLER_H__ADE2CD7E_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
#define AFX_DDBACKFILLER_H__ADE2CD7E_94E1_11D2_A3CF_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddSurfaceFiller.h"
class CDDMainObj;
class CDDBackFiller : public CDDSurfaceFiller  
  {
  DECLARE_DYNAMIC(CDDBackFiller);
  public:
    CDDBackFiller(CDDMainObj *pObj);
    virtual ~CDDBackFiller();
    virtual bool FillSurface(CDDSprite *pSprite, CPoint pPose, CSize pSize);
    
  protected:
    CDDMainObj *m_pDDObj;
  };

#endif // !defined(AFX_DDBACKFILLER_H__ADE2CD7E_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
