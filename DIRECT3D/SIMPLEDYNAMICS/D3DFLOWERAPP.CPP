// d3dFlowerApp.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dFlowerApp.h"
#include "d3dGeomArsenal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DPetalFrame class

IMPLEMENT_DYNAMIC(CD3DPetalFrame, CD3DFrame)

CD3DPetalFrame::CD3DPetalFrame()
  {
  }

CD3DPetalFrame::~CD3DPetalFrame()
  {
  }

bool CD3DPetalFrame::Create(CD3DMainObj *pOwner, 
                            CD3DFrame *pFarther, COLORREF color, 
                            D3DVALUE AngleY, D3DVALUE AngleZ, D3DVALUE AngleRev)
  {
  static D3DVECTOR tri[] = {
    {D3DVAL(0), D3DVAL(0), D3DVAL(0)},
    {D3DVAL(-0.2), D3DVAL(0), D3DVAL(0.2)},
    {D3DVAL(-0.4),  D3DVAL(0), D3DVAL(0.8)},
    {D3DVAL(-0.4),  D3DVAL(0), D3DVAL(0.9)},
    {D3DVAL( 0.0),  D3DVAL(0), D3DVAL(1.0)},
    {D3DVAL(+0.4),  D3DVAL(0), D3DVAL(0.9)},
    {D3DVAL(+0.35),  D3DVAL(0), D3DVAL(0.8)},
    {D3DVAL(+0.2), D3DVAL(0), D3DVAL(0.2)}
    };
  
  //= Basisobjekt anlegen
  if (!CD3DFrame::Create(pOwner))
    return false;

  CD3DPolygonFrame *pTriP = new CD3DPolygonFrame;
  if (pTriP == NULL)
    return false;

  if (!pTriP->Create(pOwner, 8, tri, color))
    return false;

  if (!pTriP->AddToFrame(this))
    return false;

  CD3DPolygonFrame *pTriN = new CD3DPolygonFrame;
  if (pTriN == NULL)
    return false;

  if (!pTriN->Create(pOwner, 8, tri, color, false))
    return false;

  if (!pTriN->AddToFrame(this))
    return false;

  if (!AddToFrame(pFarther))
    return false;

  if (!AddRotation(D3DRMCOMBINE_REPLACE, 
                   D3DVAL(0), D3DVAL(1), D3DVAL(0), AngleY))
    return false;

  if (!AddRotation(D3DRMCOMBINE_AFTER, 
                   D3DVAL(0), D3DVAL(0), D3DVAL(1), AngleZ))
    return false;

  if (!SetRotation(this, D3DVAL(0), D3DVAL(0), D3DVAL(1), AngleRev))
    return false;

  return true;
  }
   
/////////////////////////////////////////////////////////////////////////////
// CD3DFlowerFrame class

IMPLEMENT_DYNAMIC(CD3DFlowerFrame, CD3DFrame)

CD3DFlowerFrame::CD3DFlowerFrame()
  {
  }

CD3DFlowerFrame::~CD3DFlowerFrame()
  {
  }

bool CD3DFlowerFrame::Create(CD3DMainObj *pOwner, CD3DFrame *pFarther,
                             D3DVALUE AngleY, D3DVALUE AngleRev)
  {
  if (!CD3DFrame::Create(pOwner))
    return false;

  //= Zentrum der Blüte festlegen 
  CD3DDiskFrame *pHeartP = new CD3DDiskFrame;
  if (pHeartP == NULL)
    return false;

  if (!pHeartP->Create(pOwner, 0.4, 8, RGB(255, 255, 0)))
    return false;

  if (!pHeartP->AddToFrame(this))
    return false;

  if (!pHeartP->AddScale(D3DRMCOMBINE_REPLACE, 
                        D3DVAL(0.5), D3DVAL(0.5), D3DVAL(0.5)))
    return false;

  if (!pHeartP->AddRotation(D3DRMCOMBINE_AFTER, 
                        D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(-PI / 2.0)))
    return false;

  CD3DDiskFrame *pHeartN = new CD3DDiskFrame;
  if (pHeartN == NULL)
    return false;

  if (!pHeartN->Create(pOwner, 0.4, 8, RGB(255, 255, 0), false))
    return false;

  if (!pHeartN->AddToFrame(this))
    return false;

  if (!pHeartN->AddScale(D3DRMCOMBINE_REPLACE, 
                        D3DVAL(0.5), D3DVAL(0.5), D3DVAL(0.5)))
    return false;

  if (!pHeartN->AddRotation(D3DRMCOMBINE_AFTER, 
                        D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(-PI / 2.0)))
    return false;

  //= Erstes Blütenblatt festlegen 
  CD3DPetalFrame *pTri1 = new CD3DPetalFrame;
  if (pTri1 == NULL)
    return false;

  if (!pTri1->Create(pOwner, this, RGB(255, 0, 0))) 
    return false;

  //= Andere Blütenblätter festlegen...
  CD3DPetalFrame *pTri2 = new CD3DPetalFrame;
  if (pTri2 == NULL)
    return false;

  if (!pTri2->Create(pOwner, this, RGB(0, 255, 0), 
                     D3DVAL(PI / 2.0), D3DVAL(0.3)))
    return false;

  CD3DPetalFrame *pTri3 = new CD3DPetalFrame;
  if (pTri3 == NULL)
    return false;

  if (!pTri3->Create(pOwner, this, RGB(0, 0, 255), 
                     D3DVAL(PI), D3DVAL(0.4)))
    return false;

  CD3DPetalFrame *pTri4 = new CD3DPetalFrame;
  if (pTri4 == NULL)
    return false;

  if (!pTri4->Create(pOwner, this, RGB(255, 255, 255), 
                     D3DVAL(-PI / 2.0), D3DVAL(0.5)))
    return false;

  if (!AddToFrame(pFarther))
    return false;

  if (!AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(2)))
    return false;

  if (!AddRotation(D3DRMCOMBINE_AFTER, 
                   D3DVAL(0), D3DVAL(1), D3DVAL(0), AngleY))
    return false;

  if (!SetRotation(pFarther, D3DVAL(0), D3DVAL(1), D3DVAL(0), AngleRev))
    return false;

  return true;
  }
   
/////////////////////////////////////////////////////////////////////////////
// CD3DFlowerLeft class

IMPLEMENT_DYNAMIC(CD3DFlowerLeft, CD3DFlowerFrame)

CD3DFlowerLeft::CD3DFlowerLeft()
  {
  m_times = 0;
  m_delta = D3DVAL(-0.1);
  }

CD3DFlowerLeft::~CD3DFlowerLeft()
  {
  }

bool CD3DFlowerLeft::Create(CD3DMainObj *pOwner, CD3DFrame *pFarther,
                            D3DVALUE AngleY, D3DVALUE AngleRev)
  {
  if (!CD3DFlowerFrame::Create(pOwner, pFarther, AngleY, AngleRev))
    return false;

  if (!SetVelocity(pFarther, D3DVAL(m_delta),	D3DVAL(0),	D3DVAL(0), false))
    return false;

  if (!SetMoveCallback())
    return false;

  m_pFarther = pFarther;

  return true;
  }

void CD3DFlowerLeft::ObjCallback(D3DVALUE delta)
  {
  if (++m_times == 35)
    {
    m_delta = -m_delta;
    SetVelocity(m_pFarther, D3DVAL(m_delta), D3DVAL(0), D3DVAL(0), false);
    m_times = 0;
    }
  }
   
/////////////////////////////////////////////////////////////////////////////
// CD3DFlowerRight class

IMPLEMENT_DYNAMIC(CD3DFlowerRight, CD3DFlowerFrame)

CD3DFlowerRight::CD3DFlowerRight()
  {
  m_times = 0;
  m_delta = D3DVAL(0.1);
  }

CD3DFlowerRight::~CD3DFlowerRight()
  {
  }                

bool CD3DFlowerRight::Create(CD3DMainObj *pOwner, CD3DFrame *pFarther,
                             D3DVALUE AngleY, D3DVALUE AngleRev)
  {
  if (!CD3DFlowerFrame::Create(pOwner, pFarther, AngleY, AngleRev))
    return false;

  if (!SetVelocity(pFarther, D3DVAL(m_delta),	D3DVAL(0),	D3DVAL(0), true))
    return false;

  if (!SetMoveCallback())
    return false;

  m_pFarther = pFarther;

  return true;
  }

void CD3DFlowerRight::ObjCallback(D3DVALUE delta)
  {
  if (++m_times == 5)
    {
    m_delta = -m_delta;
    SetVelocity(m_pFarther, D3DVAL(m_delta),	D3DVAL(0),	D3DVAL(0), true);
    m_times = 0;
    }
  }
