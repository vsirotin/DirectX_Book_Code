#ifndef _D3DREVOLVEFRAME_H_
#define _D3DREVOLVEFRAME_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DRevolveFrame class

class CD3DMainObj;
class CD3DRevolveFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DRevolveFrame)

  // Construction
  public:
    CD3DRevolveFrame();
    ~CD3DRevolveFrame();
    
    // Attributes
  public:
    
    // Operations
  public:
    bool Create(CD3DMainObj *pOwner, 
                int nbase, D3DVECTOR *pBase,
                bool border = false, double angle = 0.0, int n_angle = 24, 
                D3DCOLOR color = RGB(0, 255, 0));
      //= Erzeugt massiven Drehkörper
 
    // Implementation
  public:
  D3DVECTOR *vert; 
    
  protected:
    
  };

/////////////////////////////////////////////////////////////////////////////

#endif
