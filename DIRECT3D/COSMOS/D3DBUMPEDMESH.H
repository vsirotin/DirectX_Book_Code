#ifndef _D3DBUMPEDVESH_H_
#define _D3DBUMPEDVESH_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DCubeFrame class

class CD3DMainObj;
class CD3DBumpedMesh : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DBumpedMesh)

  // Construction
  public:
    CD3DBumpedMesh();
    ~CD3DBumpedMesh();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, D3DVALUE aX, D3DVALUE aY, D3DVALUE aZ, 
                         D3DVALUE bX, D3DVALUE bY, D3DVALUE bZ, 
                         D3DVALUE cX, D3DVALUE cY, D3DVALUE cZ, 
                         D3DVALUE dX, D3DVALUE dY, D3DVALUE dZ,
                         double dPerimeter = 0.5, double dBumpMapAmplitude = 0.1,
                         D3DCOLOR color = RGB(0, 255, 0));

    // Implementation
  public:
    
  protected:
    
  };

/////////////////////////////////////////////////////////////////////////////

#endif
