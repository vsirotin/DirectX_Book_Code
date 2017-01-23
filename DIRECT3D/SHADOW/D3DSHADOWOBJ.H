#ifndef _D3DSHADOWOBJ_H_
#define _D3DSHADOWOBJ_H_

#include "d3dMainObj.h"

/////////////////////////////////////////////////////////////////////////////
// CD3DShadowObj class

class CD3DShadowObj : public CD3DMainObj
  {
  // Construction
  public:
    CD3DShadowObj();
    
    // Attributes
  public:
    
    // Operations
  public:
    
    // Implementation
  public:
    virtual ~CD3DShadowObj();
    
  protected: 
    bool OnCreate(void);
  };

/////////////////////////////////////////////////////////////////////////////

#endif
