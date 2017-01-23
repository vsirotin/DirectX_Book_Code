// ddPuzzlesSprite.h: interface for the CDDPuzzlesSprite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDPUZZLESSPRITE_H__82CB82F6_98D9_11D2_A3D6_00A02459434F__INCLUDED_)
#define AFX_DDPUZZLESSPRITE_H__82CB82F6_98D9_11D2_A3D6_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddSprite.h"

class CDDPuzzlesSprite : public CDDSprite
  {
	DECLARE_DYNAMIC(CDDPuzzlesSprite)
  // Construction
  public:
    CDDPuzzlesSprite(CDDMainObj *pOwner);
    virtual ~CDDPuzzlesSprite();
    
    // Attributes
  public:
    
    // Operations
  public:
    bool Create(int xs, int ys, int xorg, int yorg,
                int iLugGapX, int iLugSizeX, 
                int iLugGapY, int iLugSizeY, 
                int iLugSizeH,
                bool bFirstColumn, bool bFirstRow, 
                bool bLastColumn, bool bLastRow,
                CDDPuzzlesSprite *pDupl);

    bool IsChanged(void);
    void FillSurface(void);
    bool PtInSprite(CPoint point);
    void StartMove(CPoint point);
    void Move(CPoint point);
    void EndMove(CPoint point);
    void Draw(void);
    
  protected:
    CPoint  m_ptOrg, m_ptCurrent;
    int     m_iState;
    int     m_iLugGapX, m_iLugSizeX, m_iLugRestX;
    int     m_iLugGapY, m_iLugSizeY, m_iLugRestY;
    int     m_iLugSizeH;
    bool    m_bLastColumn, m_bLastRow;

    CDDPuzzlesSprite *m_pSpriteDupl;

  private:
    void SetColor(int x0, int y0, int x1, int y1);

  };

#endif // !defined(AFX_DDPUZZLESSPRITE_H__82CB82F6_98D9_11D2_A3D6_00A02459434F__INCLUDED_)
