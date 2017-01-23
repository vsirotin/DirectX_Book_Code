#ifndef _D3DMATERIALOBJ_H_
#define _D3DMATERIALOBJ_H_

#include "d3dMainObj.h"

/////////////////////////////////////////////////////////////////////////////
// CD3DMaterialObj class

class CD3DMaterialObj : public CD3DMainObj
  {
  // Construction
  public:
    CD3DMaterialObj();
    
    // Attributes
  public:
    
    // Operations
  public:
    
    // Implementation
  public:
    virtual ~CD3DMaterialObj();
    
  protected: 
    bool OnCreate(void);
  };

/////////////////////////////////////////////////////////////////////////////

#endif
