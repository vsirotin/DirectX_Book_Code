#ifndef _D3DSPOTLIGHT_H_
#define _D3DSPOTLIGHT_H_

#include "d3dLightFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DSpotLight class

class CD3DMainObj;
class CD3DSpotLight : public CD3DLightFrame
  {
	DECLARE_DYNAMIC(CD3DSpotLight)

  // Construction
  public:
    CD3DSpotLight();
    ~CD3DSpotLight();
    
    // Attributes
  public:
    
    // Operations
  public:
    
	//= Mittleres Licht als Standardeinstellung
    virtual bool Create(CD3DMainObj *pOwner, 
              D3DVALUE red = 0.5, D3DVALUE green = 0.5, D3DVALUE blue = 0.5,
              D3DVALUE umbra = 0.5, D3DVALUE penumbra = 0.75, 
              D3DVALUE attn_c = 1.0, D3DVALUE attn_l = 0.0, D3DVALUE attn_q = 0.0,
              D3DVALUE range = 1000.0);
    bool SetSpotLightCone(D3DVALUE umbra = 0.5, D3DVALUE penumbra = 0.75, D3DVALUE range = 1000.0);
    bool GetSpotLightCone(D3DVALUE *umbra, D3DVALUE *penumbra, D3DVALUE *range);
    bool SetAttenuation(D3DVALUE attn_c = 1.0, D3DVALUE attn_l = 0.0, 
                        D3DVALUE attn_q = 0.0);
    bool GetAttenuation(D3DVALUE *attn_c, D3DVALUE *attn_l, D3DVALUE *attn_q);
  // Implementation
  public:
    
  protected:
    D3DVALUE               m_AttnC; //= Ständige Abschwächung
    D3DVALUE               m_AttnL; //= Lineare Abschwächung
    D3DVALUE               m_AttnQ; //= Quadratische Abschwächung
    D3DVALUE               m_Range; //= Maximaler Abstand 
    D3DVALUE               m_Umbra; //= Kegel mit maximaler Intensität
    D3DVALUE               m_Penumbra; //= Beleuchtungskegel 
  };

/////////////////////////////////////////////////////////////////////////////

#endif
