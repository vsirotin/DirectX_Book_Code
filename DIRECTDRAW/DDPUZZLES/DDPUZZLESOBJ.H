// ddPuzzlesObj.h: interface for the CDDPuzzlesObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDPUZZLESOBJ_H__7DF6D342_989B_11D2_A3D6_00A02459434F__INCLUDED_)
#define AFX_DDPUZZLESOBJ_H__7DF6D342_989B_11D2_A3D6_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddMainObj.h"
class CDDPuzzlesSprite;
class CDDPuzzlesObj : public CDDMainObj  
  {
  DECLARE_DYNCREATE(CDDPuzzlesObj);
  public:
    CDDPuzzlesObj();
    virtual ~CDDPuzzlesObj();
    
  public:
    bool OnCreate();      
    void Start(void);     
    void Capture(void);

	//= Bearbeitung der Mausbewegungen
    int OnMouseMove(UINT nFlags, CPoint point);      
    int OnLButtonDown(UINT nFlags, CPoint point); 
    int OnLButtonUp(UINT nFlags, CPoint point);

  protected:
    bool m_bStarted;                 //= Beim true ist das Spiel gestartet game is started
    CDDPuzzlesSprite *m_pDraggedSprite;

  };

char *ResolveName(char *name);

#endif // !defined(AFX_DDPUZZLESOBJ_H__7DF6D342_989B_11D2_A3D6_00A02459434F__INCLUDED_)
