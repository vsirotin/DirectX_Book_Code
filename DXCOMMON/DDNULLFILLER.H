// ddNullFiller.h: interface for the CDDNullFiller class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDNULLFILLER_H__ADE2CD7D_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
#define AFX_DDNULLFILLER_H__ADE2CD7D_94E1_11D2_A3CF_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddSurfaceFiller.h"
class  CDDSprite;
class  CDDMainObj;
class CDDNullFiller : public CDDSurfaceFiller  
  {
  DECLARE_DYNAMIC(CDDNullFiller);
  public:
    CDDNullFiller();
    virtual ~CDDNullFiller();
    static bool FillSurface(CDDSprite *pSprite);
    static bool FillSurface(CDDMainObj *pDDObj);
    static bool FillRectangle(CDDSprite *pSprite, int x0, int y0, int x1, int y1);

  private:
    static bool FillSurface(LPDIRECTDRAWSURFACE3 pSurface);
    static bool FillRectangle(LPDIRECTDRAWSURFACE3 pSurface, int x0, int y0, int x1, int y1);
    
  };

#endif // !defined(AFX_DDNULLFILLER_H__ADE2CD7D_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
