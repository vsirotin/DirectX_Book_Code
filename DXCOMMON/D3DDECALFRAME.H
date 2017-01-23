#ifndef _D3DDECALFRAME_H_
#define _D3DDECALFRAME_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DDecalFrame class

class CD3DMainObj;
class CD3DDecalFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DDecalFrame)   

  // Construction
  public:
    CD3DDecalFrame();
    ~CD3DDecalFrame();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner,  CD3DTexture *tex);

    // Implementation
  public:
    
  protected:
    
  };

/////////////////////////////////////////////////////////////////////////////

#endif
