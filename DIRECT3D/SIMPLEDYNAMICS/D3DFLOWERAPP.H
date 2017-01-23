#ifndef _D3DFLOWERAPP_H_
#define _D3DFLOWERAPP_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DPetalFrame class

class CD3DMainObj;
class CD3DPetalFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DPetalFrame)

  // Construction
  public:
    CD3DPetalFrame();
    ~CD3DPetalFrame();
  // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, 
                    CD3DFrame *pFarther,            
                    COLORREF color = RGB(0, 255, 0), 
                    D3DVALUE AngleY = D3DVAL(0.0), 
                    D3DVALUE AngleZ = D3DVAL(0.2), 
                    D3DVALUE AngleRev = D3DVAL(0.05));
  };

/////////////////////////////////////////////////////////////////////////////
// CD3DFlowerFrame class

class CD3DFlowerFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DFlowerFrame)

  // Construction
  public:
    CD3DFlowerFrame();
    ~CD3DFlowerFrame();
    
  // Attributes
  public:
    int        m_times;
    D3DVALUE   m_delta;
    CD3DFrame *m_pFarther;

  // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, 
                    CD3DFrame *pFarther, 
                    D3DVALUE AngleY = D3DVAL(0.0), 
                    D3DVALUE AngleRev = D3DVAL(0.1));
  };



/////////////////////////////////////////////////////////////////////////////
// CD3DFlowerLeft class

class CD3DFlowerLeft : public CD3DFlowerFrame
  {
	DECLARE_DYNAMIC(CD3DFlowerLeft)

  // Construction
  public:
    CD3DFlowerLeft();
    ~CD3DFlowerLeft();
  // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, 
                    CD3DFrame *pFarther, 
                    D3DVALUE AngleY = D3DVAL(-PI / 2.0), 
                    D3DVALUE AngleRev = D3DVAL(0.1));
    virtual void ObjCallback(D3DVALUE delta);
  };

/////////////////////////////////////////////////////////////////////////////
// CD3DFlowerRight class

class CD3DFlowerRight : public CD3DFlowerFrame
  {
	DECLARE_DYNAMIC(CD3DFlowerRight)

  // Construction
  public:
    CD3DFlowerRight();
    ~CD3DFlowerRight();
  // Operations
  public:
    virtual bool Create(CD3DMainObj *pOwner, 
                    CD3DFrame *pFarther, 
                    D3DVALUE AngleY = D3DVAL(PI / 2.0), 
                    D3DVALUE AngleRev = D3DVAL(0.1));
    virtual void ObjCallback(D3DVALUE delta);
  };

/////////////////////////////////////////////////////////////////////////////
#endif
