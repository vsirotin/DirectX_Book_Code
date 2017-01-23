#ifndef _D3DPOINTLIGHT_H_
#define _D3DPOINTLIGHT_H_

#include "d3dLightFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DPointLight class

class CD3DMainObj;
class CD3DPointLight : public CD3DLightFrame
  {
	DECLARE_DYNAMIC(CD3DPointLight)

  // Construction
  public:
    CD3DPointLight();
    ~CD3DPointLight();
    
    // Attributes
  public:
    
    // Operations
  public:
    //= Mittleres Licht als Standardeinstellung

    bool Create(CD3DMainObj *pOwner, 
                 D3DVALUE red = 0.5, D3DVALUE green = 0.5, D3DVALUE blue = 0.5,
                 D3DVALUE attn_c = 1.0, D3DVALUE attn_l = 0.0, D3DVALUE attn_q = 0.0);
    bool SetAttenuation(D3DVALUE attn_c = 1.0, D3DVALUE attn_l = 0.0, 
                        D3DVALUE attn_q = 0.0);
    bool GetAttenuation(D3DVALUE *attn_c, D3DVALUE *attn_l, D3DVALUE *attn_q);
  // Implementation
  public:
    
  protected:
    D3DVALUE               m_AttnC; //= Ständige Abschwächung
    D3DVALUE               m_AttnL; //= Lineare Abschwächung
    D3DVALUE               m_AttnQ; //= Quadratische Abschwächung
  };

/////////////////////////////////////////////////////////////////////////////

#endif
