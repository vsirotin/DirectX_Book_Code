#ifndef _D3DDISKFRAME_H_
#define _D3DDISKFRAME_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DDiskFrame class

class CD3DMainObj;
class CD3DDiskFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DDiskFrame)   

  // Construction
  public:
    CD3DDiskFrame();
    ~CD3DDiskFrame();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, 
                        double rad = 0.8, int n_sectors = 8,
                        D3DCOLOR color = RGB(0, 255, 0),
                        bool orientation = true);

    // Implementation
  public:
    
  protected:
    
  };

/////////////////////////////////////////////////////////////////////////////

#endif
