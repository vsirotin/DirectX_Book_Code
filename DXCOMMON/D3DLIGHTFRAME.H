#ifndef _D3DLIGHTFRAME_H_
#define _D3DLIGHTFRAME_H_

#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DLightFrame class

class CD3DMainObj;
class CD3DLightFrame : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DLightFrame)   


  public:
    CD3DLightFrame();
    ~CD3DLightFrame();
    
    // Attribute
  public:
    LPDIRECT3DRMLIGHT      m_lpLight;
    
    // Operationen
  public:
    
	 //= Mittellicht als Standard
    virtual bool Create(CD3DMainObj *pOwner, 
                    D3DVALUE red = 0.5, D3DVALUE green = 0.5, D3DVALUE blue = 0.5);
    bool SetColor(D3DCOLOR color);
    bool SetColorRGB(D3DVALUE red, D3DVALUE green, D3DVALUE blue);
    D3DCOLOR GetColor(void);
    bool GetColorRGB(D3DVALUE *red, D3DVALUE *green, D3DVALUE *blue);
  
  // Implementatierung
  public:
    
  protected:
    D3DRMLIGHTTYPE         m_LType;
    D3DVALUE               m_ColorRed; 
    D3DVALUE               m_ColorGreen;
    D3DVALUE               m_ColorBlue;
  };

/////////////////////////////////////////////////////////////////////////////

#endif
