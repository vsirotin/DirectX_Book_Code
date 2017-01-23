#ifndef _DDMAINOBJ_H_
#define _DDMAINOBJ_H_

// CDDMainObj.h : header file
//

// DirectDraw functions and constants declaration
#include "ddraw.h"

#define DDCHECK(func)  CDDMainObj::DDCheckHRESULT(func, __LINE__, __FILE__)
#define DDTRY(func)    if (!DDCHECK(func)) return false

/////////////////////////////////////////////////////////////////////////////
// CCDDMainObj class

class CDDSprite;
class CDDMainObj : public CObject
  {
  // Construction
  DECLARE_DYNCREATE(CDDMainObj)
  public:
    CDDMainObj();
    
    // Attributes
  public:
    CSize  m_szSize;
    
    // Operations
  public:
	  virtual bool Create(CWnd *hWnd);
    virtual void SizeChanged(int cx, int cy);
    virtual void Draw(void);
    virtual void Flip(void);
    virtual void Loop(void);
    virtual void AddSprite(CDDSprite *pSprite);
    virtual bool GetDC(CDC &dc);
    virtual void ReleaseDC(CDC &dc);
    virtual LPDIRECTDRAWSURFACE3 GetBackSurface(void);
    virtual bool SetPalette(PALETTEENTRY ape[256]);
    virtual bool SetPaletteEntry(int color, int r, int g, int b);
    virtual void MoveSpriteToEnd(CDDSprite *pSprite);

  protected:
    virtual bool OnCreate(void);

    // Implementation
  public:
    virtual ~CDDMainObj(void);
    
    static bool DDCheckHRESULT(HRESULT res, int line = -1, char *filename = NULL);
    static void DDError(const CString &str, HRESULT hr = 0, int line = -1, char *file = NULL);

    friend CDDSprite;
  protected:
    bool                 m_bWindowed;
    CWnd                *m_pParent;

    LPDIRECTDRAWCLIPPER  m_lpDDClipper;
    LPDIRECTDRAWPALETTE  m_lpDDPalette;
	  LPDIRECTDRAWSURFACE3 m_lpDDBackSurface;
	  LPDIRECTDRAWSURFACE3 m_lpDDPrimarySurface;
	  LPDIRECTDRAW2        m_lpDD;
    CTypedPtrList<CPtrList, CDDSprite *> m_SpriteList;
  };

#endif // _DDMAINOBJ_H_
