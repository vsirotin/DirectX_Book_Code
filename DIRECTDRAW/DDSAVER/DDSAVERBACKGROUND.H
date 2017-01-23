// ddSaverBackground.h: interface for the CDDSaverBackground class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDSAVERBACKGROUND_H__ADE2CD7C_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
#define AFX_DDSAVERBACKGROUND_H__ADE2CD7C_94E1_11D2_A3CF_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddSprite.h"

class CDDSaverBackground : public CDDSprite  
  {
  DECLARE_DYNAMIC(CDDSaverBackground);
  public:
    CDDSaverBackground(CDDMainObj *pOwner);
    virtual ~CDDSaverBackground();
    virtual void Draw(void);
   
  };

#endif // !defined(AFX_DDSAVERBACKGROUND_H__ADE2CD7C_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
