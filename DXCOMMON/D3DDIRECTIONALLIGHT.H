#ifndef _D3DDIRECTIONALLIGHT_H_
#define _D3DDIRECTIONALLIGHT_H_

#include "d3dLightFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DDirectionalLight class

class CD3DMainObj;
class CD3DDirectionalLight : public CD3DLightFrame
  {
	DECLARE_DYNAMIC(CD3DDirectionalLight)

  // Construction
  public:
    CD3DDirectionalLight();
    ~CD3DDirectionalLight();
  };
/////////////////////////////////////////////////////////////////////////////

#endif
