// ddImageFiller.h: interface for the CDDImageFiller class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDIMAGEFILLER_H__9FA2EB54_E8C2_11D2_8741_00A02459434F__INCLUDED_)
#define AFX_DDIMAGEFILLER_H__9FA2EB54_E8C2_11D2_8741_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddSurfaceFiller.h"

class CDDSprite;
class CDDMainObj;
class CImageFile;
class CDDImageFiller : public CDDSurfaceFiller  
  {
  DECLARE_DYNAMIC(CDDImageFiller);
  public:
    CDDImageFiller(){m_ImageFile = NULL;}
    virtual ~CDDImageFiller(){}

    virtual bool GetSize(int *w, int *h);
    virtual void GetDirectDrawPalette(PALETTEENTRY *ape);

    virtual bool Create(LPTSTR name);
    virtual bool FillSurface(CDDSprite *pSprite, int x = 0, int y = 0);
    virtual bool FillSurface(CDDMainObj *pDDObj, int x = 0, int y = 0);

  private:
    bool FillSurface(LPDIRECTDRAWSURFACE3 pSurface, int x = 0, int y = 0);

  protected:
    CImageFile *m_ImageFile;
  };

#endif // !defined(AFX_DDIMAGEFILLER_H__9FA2EB54_E8C2_11D2_8741_00A02459434F__INCLUDED_)
