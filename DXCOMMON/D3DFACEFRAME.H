#ifndef _D3DFACEFRAME_H_
#define _D3DFACEFRAME_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DFaceFrame class

class CD3DMainObj;
class CD3DCut;
class CD3DFaceFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DFaceFrame)

  // Construction
  public:
    CD3DFaceFrame();
    ~CD3DFaceFrame();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, int n_vert, D3DVECTOR *vert, D3DVECTOR *norm, 
                        D3DCOLOR color = RGB(0, 255, 0), bool orientation = true);

    // Implementation
  public:
    
  protected:
    
  };

/////////////////////////////////////////////////////////////////////////////

#endif
