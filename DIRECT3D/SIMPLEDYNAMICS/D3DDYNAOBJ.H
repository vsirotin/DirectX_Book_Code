#ifndef _D3DDYNAOBJ_H_
#define _D3DDYNAOBJ_H_

#include "d3dMainObj.h"

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaObj class

class CD3DDynaObj : public CD3DMainObj
  {
  // Construction
  public:
    CD3DDynaObj();

  // Operations
  public:
    virtual void ObjCallback(D3DVALUE delta);
    
  // Implementation
  public:
    virtual ~CD3DDynaObj();
    
  protected: 
    bool OnCreate(void);

    CD3DFrame *m_pDynaObj; 
    int m_times;           //= Anzahl der Ticks
    D3DVALUE m_Vdelta;     //= Winkel - Zugabe pro Tick

  
  };

/////////////////////////////////////////////////////////////////////////////

#endif
