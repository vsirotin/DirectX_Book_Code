#ifndef _D3DCUBEFRAME_H_
#define _D3DCUBEFRAME_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DCubeFrame class

class CD3DMainObj;
class CD3DCubeFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DCubeFrame)   

  // Construction
  public:
    CD3DCubeFrame();
    ~CD3DCubeFrame();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, 
                        D3DCOLOR color = RGB(0, 255, 0));

    // Implementation
  public:
    
  protected:
    
  };

/////////////////////////////////////////////////////////////////////////////

#endif
