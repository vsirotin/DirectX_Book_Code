// ddAquaBackground.h: interface for the CDDAquaBackground class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDAQUABACKGROUND_H__0C03E233_E6A0_11D2_873C_00A02459434F__INCLUDED_)
#define AFX_DDAQUABACKGROUND_H__0C03E233_E6A0_11D2_873C_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddSprite.h"
class CDDAquaBackground : public CDDSprite  
  {
	DECLARE_DYNAMIC(CDDAquaBackground)
  // Construction
  public:
    CDDAquaBackground(CDDMainObj *pOwner);
    virtual ~CDDAquaBackground();
    
  // Operations
  public:
    bool Create(char *fname);

  // Attributes
  public:
    bool IsChanged(void);

  private:
    int   m_curColor;
    DWORD m_dwCurTime;
    DWORD m_dwTime;
  };

#endif // !defined(AFX_DDAQUABACKGROUND_H__0C03E233_E6A0_11D2_873C_00A02459434F__INCLUDED_)
