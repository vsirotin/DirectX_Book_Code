#ifndef _D3DPICKOBJ_H_
#define _D3DPICKOBJ_H_

#include "d3dMainObj.h"

/////////////////////////////////////////////////////////////////////////////
// CD3DPickObj class

class CD3DPickObj : public CD3DMainObj
  {
  // Construction
  public:
    CD3DPickObj();
    
  // Implementation
  public:
    virtual ~CD3DPickObj();
    bool Pick(int x, int y);
    
  protected: 
    bool OnCreate(void);
    CD3DFrame *FindFrame(DWORD AppData);

    int m_count;
    CD3DFrame **m_FrameArray;
    D3DVALUE m_AccAngX, m_AccAngY, m_AccAngZ;
    CD3DFrame *mushroom;
  };

/////////////////////////////////////////////////////////////////////////////

#endif
