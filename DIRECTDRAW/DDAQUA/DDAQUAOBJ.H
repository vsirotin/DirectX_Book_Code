// ddAquaObj.h: interface for the CDDAquaObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDAQUAOBJ_H__43E79472_9BF4_11D2_A3DC_00A02459434F__INCLUDED_)
#define AFX_DDAQUAOBJ_H__43E79472_9BF4_11D2_A3DC_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddMainObj.h"
class CDDAquaObj : public CDDMainObj  
  {
  DECLARE_DYNCREATE(CDDAquaObj)
  public:
    CDDAquaObj();
    virtual ~CDDAquaObj();

    bool OnCreate();      
    void Capture();

  };

#endif // !defined(AFX_DDAQUAOBJ_H__43E79472_9BF4_11D2_A3DC_00A02459434F__INCLUDED_)
