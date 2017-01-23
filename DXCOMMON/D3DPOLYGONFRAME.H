#ifndef _D3DPOLYGONFRAME_H_
#define _D3DPOLYGONFRAME_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DPolygonFrame class

class CD3DMainObj;
class CD3DPolygonFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DPolygonFrame)   

  // Construction
  public:
    CD3DPolygonFrame();
    ~CD3DPolygonFrame();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, int n_vert, D3DVECTOR *vert,                     
                        D3DCOLOR color = RGB(0, 255, 0), bool orientation = true);

    // Implementation
  public:
    
  protected:
    
  };

/////////////////////////////////////////////////////////////////////////////

#endif
