#ifndef _D3DPYRAMIDFRAME_H_
#define _D3DPYRAMIDFRAME_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DPyramidFrame class

class CD3DMainObj;
class CD3DPyramidFrame : public CD3DFrame  
  {
  DECLARE_DYNAMIC(CD3DPyramidFrame)   

  public:
	  CD3DPyramidFrame();
	  ~CD3DPyramidFrame();
    
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

