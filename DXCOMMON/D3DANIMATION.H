#ifndef _D3DANIMATION_H_
#define _D3DANIMATION_H_

#include "d3drmwin.h"
#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DMaterial class

class CD3DMainObj;
class CD3DFrame;
class CD3DAnimation  : public CObject
  {
  DECLARE_DYNAMIC(CD3DAnimation)

  // Construction
  public:
    CD3DAnimation();
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, 
      D3DRMANIMATIONOPTIONS option =  D3DRMANIMATION_SCALEANDROTATION |
                                      D3DRMANIMATION_LINEARPOSITION   |
                                      D3DRMANIMATION_POSITION         |
                                      D3DRMANIMATION_CLOSED);
    virtual bool SetRotateKey(D3DVALUE rvTime, D3DVALUE rvX, D3DVALUE rvY, D3DVALUE rvZ, D3DVALUE rvAngle);
    virtual bool SetPositionKey(D3DVALUE rvTime, D3DVALUE rvX, D3DVALUE rvY, D3DVALUE rvZ);
    virtual bool SetScaleKey(D3DVALUE rvTime, D3DVALUE rvX, D3DVALUE rvY, D3DVALUE rvZ);
    virtual bool SetFrame(CD3DFrame *frm);
    virtual bool SetTime(D3DVALUE rvTime);
    // Implementation
  public:
    virtual ~CD3DAnimation();

    friend CD3DFrame;
  protected:
    LPDIRECT3DRMANIMATION2 m_lpAnimation;  //= Zeiger auf der Schnittstelle IDirect3DRMAnimation interface
    CD3DMainObj *m_pOwner;                 //= Hauptobjekt
  };

/////////////////////////////////////////////////////////////////////////////

#endif
