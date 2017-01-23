// DDSaverObj.h: interface for the CDDSaverObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDSAVEROBJ_H__ADE2CD73_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
#define AFX_DDSAVEROBJ_H__ADE2CD73_94E1_11D2_A3CF_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddMainObj.h"
#include "SaverParameters.h"

class CDDSaverObj : public CDDMainObj  
  {
  DECLARE_DYNCREATE(CDDSaverObj);
  public:
    CDDSaverObj();
    ~CDDSaverObj();
    void Loop(void);

  protected:
    bool OnCreate(void);
    void FillSprites(void);
    
  private:
    CSaverParameters m_Param;        
    int  m_iState;
    long m_lTime;
  };

#endif // !defined(AFX_DDSAVEROBJ_H__ADE2CD73_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
