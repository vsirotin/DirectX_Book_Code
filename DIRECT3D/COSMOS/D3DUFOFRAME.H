#ifndef _D3DUFOFRAME_H_
#define _D3DUFOFRAME_H_

#include "d3dFrame.h"

/////////////////////////////////////////////////////////////////////////////
// CD3DUFOFrame class

class CD3DMainObj;
class CD3DLightFrame;
class CD3DUFOFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DUFOFrame)

  // Construction
  public:
    CD3DUFOFrame();
    ~CD3DUFOFrame();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, int vert_planes = 32, 
                        D3DCOLOR color = RGB(0, 255, 0),
                        CD3DLightFrame *lpL = NULL);

    // Implementation
  public:
    
  protected:
    
  };

/////////////////////////////////////////////////////////////////////////////

#endif
