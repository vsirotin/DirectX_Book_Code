#ifndef _D3DDYNACHROMEOBJ_H_
#define _D3DDYNACHROMEOBJ_H_

#include "d3dMainObj.h"

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaChromeObj class

class CD3DDynaChromeObj : public CD3DMainObj
  {
  // Construction
  public:
    CD3DDynaChromeObj();

  // Operations
  public:
    virtual void ObjCallback(D3DVALUE delta);
    
  // Implementation
  public:
    virtual ~CD3DDynaChromeObj();
    
  protected: 
    bool OnCreate(void);

  CD3DFrame * pSphere;
  CD3DFrame *pSphere2;
  CD3DFrame *pDisk;
  CD3DFrame *pCyl;  
  CD3DCameraFrame *camera;
  CD3DTexture *tex1;
  };

/////////////////////////////////////////////////////////////////////////////

#endif
