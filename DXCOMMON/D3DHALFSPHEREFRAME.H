#ifndef _D3DHALFSPHEREFRAME_H_
#define _D3DHALFSPHEREFRAME_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DHalfsphereFrame class

class CD3DMainObj;
class CD3DHalfsphereFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DHalfsphereFrame)   

  // Construction
  public:
    CD3DHalfsphereFrame();
    ~CD3DHalfsphereFrame();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner,
                        int vert_planes, int hor_planes, 
                        D3DCOLOR color = RGB(0, 255, 0), 
                        bool orientation = true);
    // Implementation
  public:
    
  protected:
    
  };

/////////////////////////////////////////////////////////////////////////////

#endif
