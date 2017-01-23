#ifndef _D3DBUMPEDPLANEFRAME_H_
#define _D3DBUMPEDPLANEFRAME_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DBumpedPlaneFrame class

class CD3DMainObj;
class CD3DBumpedPlaneFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DBumpedPlaneFrame)

  // Construction
  public:
    CD3DBumpedPlaneFrame();
    ~CD3DBumpedPlaneFrame();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, int n_cells = 10, 
                        double xBeg = 0.0, double xEnd = 1.0,
                        double zBeg = 0.0, double zEnd = 1.0,
                        double yBase = -0.1, double BumpAmp = 0.1, 
                        D3DCOLOR color = RGB (255, 255, 255));

    // Implementation
  public:
    
  protected:
    
  };

/////////////////////////////////////////////////////////////////////////////

#endif
