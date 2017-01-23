#ifndef _D3DCONEFRAME_H_
#define _D3DCONEFRAME_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DConeFrame class

class CD3DMainObj;
class CD3DConeFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DConeFrame)   

  // Construction
  public:
    CD3DConeFrame();
    ~CD3DConeFrame();
    
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
