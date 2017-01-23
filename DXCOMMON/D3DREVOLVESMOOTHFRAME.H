#ifndef _D3DREVOLVESMOOTHFRAME_H_
#define _D3DREVOLVESMOOTHFRAME_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DRevolveSmoothFrame class

class CD3DMainObj;
class CD3DRevolveSmoothFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DRevolveSmoothFrame)

  // Construction
  public:
    CD3DRevolveSmoothFrame();
    ~CD3DRevolveSmoothFrame();
    
    // Attributes
  public:
    
    // Operations
  public:
    bool Create(CD3DMainObj *pOwner, int nbase, D3DVECTOR *pBase, 
                bool closed = false, bool average = false, 
                bool border = false, double angle = 0.0, int n_angle = 24, 
                D3DCOLOR color = RGB(0, 255, 0));
      //= Erzeugt massive Drehkörper oder ihre Segmente
    // Implementation
  public:
  D3DVECTOR *vert, *pNorm; //= work area 
    
  protected:
    
  };

/////////////////////////////////////////////////////////////////////////////

#endif
