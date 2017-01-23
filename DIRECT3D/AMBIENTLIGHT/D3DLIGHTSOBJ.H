#ifndef _D3DLIGHTSOBJ_H_
#define _D3DLIGHTSOBJ_H_

#include "d3dMainObj.h"

/////////////////////////////////////////////////////////////////////////////
// CD3DLightsObj class

class CD3DLightsObj : public CD3DMainObj
  {
  // Construction
  public:
    CD3DLightsObj();
    
    // Attributes
  public:
    
    // Operations
  public:
    
    // Implementation
  public:
    virtual ~CD3DLightsObj();
    bool     CreateLightScene(int vert_planes, int hor_planes);
    
  protected: 
    bool OnCreate(void);
  };

/////////////////////////////////////////////////////////////////////////////

#endif
