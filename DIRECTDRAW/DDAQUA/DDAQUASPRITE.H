// ddAquaSprite.h: interface for the CDDAquaSprite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDAQUASPRITE_H__0C03E234_E6A0_11D2_873C_00A02459434F__INCLUDED_)
#define AFX_DDAQUASPRITE_H__0C03E234_E6A0_11D2_873C_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddSprite.h"
class CDDAquaSprite : public CDDSprite  
  {
	DECLARE_DYNAMIC(CDDAquaSprite)
  // Construction
  public:
    CDDAquaSprite(CDDMainObj *pOwner);
    virtual ~CDDAquaSprite();
    
  // Attributes
  public:
    
  // Operations
  public:
    bool Create(int xorg, int yorg, char *fileName, int nOfFrames, DWORD time);
    bool Clone(CDDSprite *pFather, int xorg, int yorg, DWORD time);
    bool IsChanged(void);
    
  private:
    int   m_State;
    DWORD m_dwCurTime;
    DWORD m_dwTime;
  };

#endif // !defined(AFX_DDAQUASPRITE_H__0C03E234_E6A0_11D2_873C_00A02459434F__INCLUDED_)
