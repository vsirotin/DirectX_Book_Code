// ddPuzzles2Obj.h: interface for the CDDPuzzles2Obj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDPUZZLES2OBJ_H__9FA2EB6C_E8C2_11D2_8741_00A02459434F__INCLUDED_)
#define AFX_DDPUZZLES2OBJ_H__9FA2EB6C_E8C2_11D2_8741_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddPuzzlesObj.h"

class CDDPuzzles2Obj : public CDDPuzzlesObj  
  {
  public:
    CDDPuzzles2Obj(void);
    virtual ~CDDPuzzles2Obj(void);
    virtual bool OnCreate(void);
    virtual void Start(void);
    
  };

#endif // !defined(AFX_DDPUZZLES2OBJ_H__9FA2EB6C_E8C2_11D2_8741_00A02459434F__INCLUDED_)
