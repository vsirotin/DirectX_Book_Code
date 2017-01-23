#ifndef _D3DREVOLVEMESHFRAME_H_
#define _D3DREVOLVEMESHFRAME_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// Cd3dRevolveMeshFrame class

class CD3DMainObj;
class CD3DRevolveMeshFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DRevolveMeshFrame)

  // Construction
  public:
    CD3DRevolveMeshFrame();
    ~CD3DRevolveMeshFrame();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, 
                        int nZ, D3DVECTOR *curve,
                        int vert_planes = 8,
                        D3DCOLOR color = RGB(255, 255, 255));
    // Implementation
  public:
    
  protected:
    
  };

/////////////////////////////////////////////////////////////////////////////

#endif
