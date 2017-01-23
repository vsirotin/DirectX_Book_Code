// DDBasicObj.h: interface for the CDDBasicObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDBASICOBJ_H__A1510B01_9311_11D2_A3CB_00A02459434F__INCLUDED_)
#define AFX_DDBASICOBJ_H__A1510B01_9311_11D2_A3CB_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddMainObj.h"

class CDDBasicObj : public CDDMainObj  
  {
  DECLARE_DYNCREATE(CDDBasicObj);
  public:
    CDDBasicObj();
    virtual ~CDDBasicObj();
    virtual void Loop(void);

  protected:
    virtual bool OnCreate(void);
    double m_dAngle[2];
    int    m_iCounter;
    int    m_nSurface;

  };

#endif // !defined(AFX_DDBASICOBJ_H__A1510B01_9311_11D2_A3CB_00A02459434F__INCLUDED_)
