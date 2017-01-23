#ifndef _D3DANIMOBJ_H_
#define _D3DANIMOBJ_H_

#include "d3dMainObj.h"

/////////////////////////////////////////////////////////////////////////////
// CD3DAnimObj class

class CD3DAnimObj : public CD3DMainObj
  {

  public:
    CD3DAnimObj();


  public:
    virtual void ObjCallback(D3DVALUE delta);
    

  public:
    virtual ~CD3DAnimObj();
    
  protected: 
    bool OnCreate(void);

    CD3DAnimation *m_pAnim;   //= Animationsobjekt
    D3DVALUE       m_vTime;   //= Aktuelle Zeit
  
  };

/////////////////////////////////////////////////////////////////////////////

#endif
