#ifndef _D3DCAMERAFRAME_H_
#define _D3DCAMERAFRAME_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DCameraFrame class

class CD3DMainObj;
class CD3DCameraFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DCameraFrame)   

  // Construction
  public:
    CD3DCameraFrame();
    ~CD3DCameraFrame();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner);

    // Implementation
  public:
    
  protected:
    
  };

/////////////////////////////////////////////////////////////////////////////

#endif
