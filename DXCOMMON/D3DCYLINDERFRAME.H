#ifndef _D3DCYLINDERFRAME_H_
#define _D3DCYLINDERFRAME_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DCylinderFrame class

class CD3DMainObj;
class CD3DCylinderFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DCylinderFrame)   

  // Construction
  public:
    CD3DCylinderFrame();
    ~CD3DCylinderFrame();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, 
                        int vert_planes = 8,
                        D3DCOLOR color = RGB(0, 255, 0),
                        bool orientation = true);

    // Implementation
  public:
    
  protected:
    
  };

/////////////////////////////////////////////////////////////////////////////

#endif
