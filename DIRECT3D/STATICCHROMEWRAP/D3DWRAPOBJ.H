#ifndef _D3DWRAPOBJ_H_
#define _D3DWRAPOBJ_H_

#include "d3dMainObj.h"

/////////////////////////////////////////////////////////////////////////////
// CD3DWrapObj class

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
  };

/////////////////////////////////////////////////////////////////////////////

#endif
