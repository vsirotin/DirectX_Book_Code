#ifndef _D3DBASICOBJ_H_
#define _D3DBASICOBJ_H_

#include "d3dMainObj.h"

/////////////////////////////////////////////////////////////////////////////
// CD3DBasicObj class

class CD3DBasicObj : public CD3DMainObj
  {
  // Construction
  public:
    CD3DBasicObj();
    
    // Attributes
  public:
    
    // Operations
  public:
    
    // Implementation
  public:
    virtual ~CD3DBasicObj();
    
  protected: 
    bool OnCreate(void);
  };

/////////////////////////////////////////////////////////////////////////////

#endif
