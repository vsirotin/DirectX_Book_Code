#ifndef _D3DSWEEPINGFRAME_H_
#define _D3DSWEEPINGFRAME_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DSweepingFrame class

class CD3DMainObj;
class CD3DSweepingFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DSweepingFrame)

  // Construction
  public:
    CD3DSweepingFrame();
    ~CD3DSweepingFrame();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, int nbase, int ntop,
                        D3DVECTOR *pBase, D3DVECTOR *pTop, 
                        bool border = true, bool smooth = true, 
                        D3DCOLOR color = RGB(0, 255, 0));

    // Implementation
  public:
  D3DVECTOR *base, *top, *norm; 
    
  protected:
    
  };

/////////////////////////////////////////////////////////////////////////////

#endif
