#ifndef _D3DPARALLELPOINTLIGHT_H_
#define _D3DPARALLELPOINTLIGHT_H_

#include "d3dLightFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DParallelPointLight class

class CD3DMainObj;
class CD3DParallelPointLight : public CD3DLightFrame
  {
	DECLARE_DYNAMIC(CD3DParallelPointLight)

  // Construction
  public:
    CD3DParallelPointLight();
    ~CD3DParallelPointLight();
  };

/////////////////////////////////////////////////////////////////////////////

#endif
