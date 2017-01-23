// ddSurfaceFiller.h: interface for the CDDSurfaceFiller class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDSURFACEFILLER_H__ADE2CD7A_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
#define AFX_DDSURFACEFILLER_H__ADE2CD7A_94E1_11D2_A3CF_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddraw.h"
class CDDSprite;
class CDDSurfaceFiller : public CObject  
  {
  DECLARE_DYNAMIC(CDDSurfaceFiller);
  public:
    CDDSurfaceFiller(void);
    virtual ~CDDSurfaceFiller(void);
    virtual bool FillSurface(CDDSprite *pSprite, CPoint pPose, CSize pSize);
    
  };

#endif // !defined(AFX_DDSURFACEFILLER_H__ADE2CD7A_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
