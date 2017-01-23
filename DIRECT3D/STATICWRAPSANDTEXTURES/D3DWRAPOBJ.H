#ifndef _D3DWRAPOBJ_H_
#define _D3DWRAPOBJ_H_

#include "d3dMainObj.h"

/////////////////////////////////////////////////////////////////////////////
// CD3DWrapObj class

class CD3Dtexture;
class CD3DWrapObj : public CD3DMainObj
  {
  // Construction
  public:
    CD3DWrapObj();
    
    // Attributes
  public:
    
    // Operations
  public:
    
    // Implementation
  public:
    virtual ~CD3DWrapObj();
    
  protected: 
    bool OnCreate(void);
    bool PutCylTexture(CD3DFrame *tree, CD3DTexture *tex);
    CD3DFrame *CreateLandscape(int x_pl = 10, int z_pl = 10);
    CD3DFrame *CreateFaceHouse(void);
  };

/////////////////////////////////////////////////////////////////////////////

#endif
