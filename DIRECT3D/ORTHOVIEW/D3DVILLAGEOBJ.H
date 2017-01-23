#ifndef _D3DVILLAGEOBJ_H_
#define _D3DVILLAGEOBJ_H_

#include "d3dMainObj.h"

/////////////////////////////////////////////////////////////////////////////
// CD3DVillageObj class

class CD3DVillageObj : public CD3DMainObj
  {
  // Construction
  public:
    CD3DVillageObj();
    
    // Attributes
  public:
    
    // Operations
  public:
    
    // Implementation
  public:
    virtual ~CD3DVillageObj();
    
  protected: 
    bool OnCreate(void);
    CD3DFrame *CreateHouse(void); 
  };

/////////////////////////////////////////////////////////////////////////////

#endif
