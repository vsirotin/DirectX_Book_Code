#ifndef _D3DFIRESTUFFFRAME_H_
#define _D3DFIRESTUFFFRAME_H_

#include "d3dFrame.h"

/////////////////////////////////////////////////////////////////////////////
// CD3DTorusFrame class

class CD3DMainObj;
class CD3DLightFrame;
class CD3DTorusFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DTorusFrame)

  // Construction
  public:
    CD3DTorusFrame();
    ~CD3DTorusFrame();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, int n_big = 16, int n_small = 8,
                        double r_small = 0.33, D3DCOLOR color = RGB(0, 255, 0),
                        CD3DLightFrame *lpL = NULL);

    // Implementation
  public:
    
  protected:
    
  };


/////////////////////////////////////////////////////////////////////////////
// CD3DFireStuffFrame class

class CD3DFireStuffFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DFireStuffFrame)

  // Construction
  public:
    CD3DFireStuffFrame();
    ~CD3DFireStuffFrame();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, int n_big = 16, int n_small = 8,
                        double r_small = 0.33, D3DCOLOR color = RGB(0, 255, 0),
                        CD3DLightFrame *lpL = NULL);

    // Implementation
  public:
    
  protected:
    
  };

/////////////////////////////////////////////////////////////////////////////

#endif
