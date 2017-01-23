// ddSaverSprite.h: interface for the CDDSaverSprite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDSAVERSPRITE_H__ADE2CD7B_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
#define AFX_DDSAVERSPRITE_H__ADE2CD7B_94E1_11D2_A3CF_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddSprite.h"
class CDDSaverSprite : public CDDSprite  
  {
  DECLARE_DYNAMIC(CDDSaverSprite)
  public:
    CDDSaverSprite(CDDMainObj *pOwner);
    virtual ~CDDSaverSprite();

    bool Create(int xs, int ys, int xorg, int yorg, int speed);
    bool IsChanged(void);
    bool FillSurface(CDDSurfaceFiller *pFiller);
    void SetState(int state);
    int  GetState(void);

  protected:
    CPoint  m_ptOrg;
    double  m_dAlpha;
    double  m_dSpeed;
    int     m_iState;
    CTypedPtrList<CPtrList, CPoint*> m_poseList;
  };

#endif // !defined(AFX_DDSAVERSPRITE_H__ADE2CD7B_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
