// ddPuzzlesBackground.h: interface for the CDDPuzzlesBackground class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDPUZZLESBACKGROUND_H__7DF6D348_989B_11D2_A3D6_00A02459434F__INCLUDED_)
#define AFX_DDPUZZLESBACKGROUND_H__7DF6D348_989B_11D2_A3D6_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddSprite.h"
class CDDPuzzlesBackground : public CDDSprite  
  {
	DECLARE_DYNAMIC(CDDPuzzlesBackground)
  // Construction
  public:
    CDDPuzzlesBackground(CDDMainObj *pOwner);
    virtual ~CDDPuzzlesBackground();
    
    // Attributes
  public:
    
    // Operations
  public:
    bool Create(int xs, int ys, int iCellsX, int iCellsY,
                int iCellsSizeX, int iCellsSizeY,
                int iLugGapX, int iLugSizeX, 
                int iLugGapY, int iLugSizeY, int iLugSizeH);

    void Draw(void);
    void FillSurface(void);
    void DrawCells(COLORREF color);

  private:
    int m_iCellsX, m_iCellsY;
    int m_iCellsSizeX, m_iCellsSizeY;
    int m_iLugGapX, m_iLugSizeX;
    int m_iLugGapY, m_iLugSizeY;
    int m_iLugSizeH;
    
  };

#endif // !defined(AFX_DDPUZZLESBACKGROUND_H__7DF6D348_989B_11D2_A3D6_00A02459434F__INCLUDED_)
