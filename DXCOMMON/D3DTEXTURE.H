#ifndef _D3DTEXTURE_H_
#define _D3DTEXTURE_H_

#include "d3drmwin.h"
#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DTexture class

class CD3DMainObj;
class CD3DFrame;
class CD3DTexture  : public CObject
  {
  DECLARE_DYNAMIC(CD3DTexture)

  // Construction
  public:
    CD3DTexture();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, LPCSTR filename,
                                int iX = 0, int iY = 0,
                                D3DVALUE rvSizeX = D3DVAL(1), 
                                D3DVALUE rvSizeY = D3DVAL(1), 
                                bool transparency = false,
                                D3DCOLOR transp_color = RGB(0, 0, 0));
    virtual bool SetSize(D3DVALUE rvSizeX = D3DVAL(1), D3DVALUE rvSizeY = D3DVAL(1));
    virtual bool SetOrigin(int iX = 0, int iY = 0);
    virtual bool SetScale(bool scale = true);
    virtual bool SetTransparency(bool transparency = false,
                                 D3DCOLOR transp_color = RGB(0, 0, 0));
    // Implementation
  public:
    virtual ~CD3DTexture();

    friend CD3DMainObj;
  protected:
    bool IsChanged(void);

    friend CD3DFrame;
  protected:
    LPDIRECT3DRMTEXTURE3 m_lpTexture;  //= Zeiger auf der Schnittstelle IDirect3DRMTexture
    bool m_bChanged;                   //= true wenn geändert

    CD3DMainObj *m_pOwner;             //= //= Hauptobjekt
  };

/////////////////////////////////////////////////////////////////////////////

#endif
