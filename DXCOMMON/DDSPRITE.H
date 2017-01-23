// ddSprite.h: interface for the CDDSprite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDSPRITE_H__ADE2CD79_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
#define AFX_DDSPRITE_H__ADE2CD79_94E1_11D2_A3CF_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddraw.h"


class CDDMainObj;
class CDDSurfaceFiller;
class CDDSprite : public CObject  
  {
	DECLARE_DYNAMIC(CDDSprite)        
  public:
    CDDSprite(CDDMainObj *pOwner);
    virtual ~CDDSprite(void);
    
    // Operations
  public:
    virtual bool Create(int xs, int ys, int n_of_frames = 1);
    virtual bool Clone(CDDSprite *pFather);
    virtual bool FillSurface(CDDSurfaceFiller *pFiller);

    virtual bool IsChanged(void);
    virtual void Draw(void);
    virtual CSize GetSize(void);
    virtual LPDIRECTDRAWSURFACE3 GetSurface(){return m_pSurface;};
    virtual void SetColorKey(LPDDCOLORKEY lpddck);
    virtual void NextFrame(void);
    virtual void PrevFrame(void);
    
  protected:
    LPDIRECTDRAWSURFACE3  m_pSurface;  //= Zeiger auf der aktiven Oberfläche
    LPDIRECTDRAWSURFACE3 *m_pSurfaces; //= Feld der Oberflächen
    bool m_bColorKey;

    CPoint m_ptPose;
    CSize  m_szSize;
    bool   m_bChanged;
    CDDMainObj *m_pOwner;

    int m_nOfFrames;
    int m_iCurFrame;

    bool m_bClone;
  };

#endif // !defined(AFX_DDSPRITE_H__ADE2CD79_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
