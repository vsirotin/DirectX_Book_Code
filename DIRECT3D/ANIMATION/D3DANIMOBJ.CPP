// d3dAnimObj.cpp : implementation file
//

#include "stdafx.h"
#include "d3dAnimObj.h"
#include "d3dGeomArsenal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DAnimObj

CD3DAnimObj::CD3DAnimObj()
  {
  m_vTime = D3DVAL(0);   
  }

CD3DAnimObj::~CD3DAnimObj()
  {
  }

void CD3DAnimObj::ObjCallback(D3DVALUE delta)
  {
  m_vTime += D3DVAL(0.5);

  m_pAnim->SetTime(m_vTime);
  }

bool CD3DAnimObj::OnCreate()
  {
  CD3DFrame *pAnimObj = new CD3DFrame;
  if (pAnimObj == NULL)
    return false;

  if (!pAnimObj->Create(this))
    return false;

  if (!pAnimObj->AddToFrame(this))
    return false;
  
  //= Animationsobjekt anlegen
  CD3DFrame *m_pMidObj = new CD3DFrame;
  if (m_pMidObj == NULL)
    return false;

  if (!m_pMidObj->Create(this))
    return false;

  if (!m_pMidObj->AddToFrame(pAnimObj))
    return false;

  CD3DFrame *pAxisX = CD3DGeomArsenal::CreateAxis(this, 16, 0.5, 0.5, 0.0, 
                              RGB(255, 0, 0));
  if (pAxisX == NULL)
    return false;

  if (!pAxisX->AddToFrame(m_pMidObj))
    return false;

  if (!pAxisX->AddCombTransform(D3DVAL(3), D3DVAL(3), D3DVAL(10),
    D3DVAL(0), D3DVAL(PI / 2.0), D3DVAL(0),
    D3DVAL(0), D3DVAL(0), D3DVAL(0)))
    return false;

  CD3DFrame *pAxisY = CD3DGeomArsenal::CreateAxis(this, 16, 0.5, 0.5, 0.0, 
                              RGB(0, 255, 0));
  if (pAxisY == NULL)
    return false;

  if (!pAxisY->AddToFrame(m_pMidObj))
    return false;

  if (!pAxisY->AddCombTransform(D3DVAL(3), D3DVAL(3), D3DVAL(10),
    D3DVAL(-PI / 2.0), D3DVAL(0), D3DVAL(0),
    D3DVAL(0), D3DVAL(0), D3DVAL(0)))
    return false;

  CD3DFrame *pAxisZ = CD3DGeomArsenal::CreateAxis(this, 16, 0.5, 0.5, 0.0, 
                              RGB(0, 0, 255));
  if (pAxisZ == NULL)
    return false;

  if (!pAxisZ->AddToFrame(m_pMidObj))
    return false;

  if (!pAxisZ->AddCombTransform(D3DVAL(3), D3DVAL(3), D3DVAL(10),
    D3DVAL(0), D3DVAL(0), D3DVAL(0),
    D3DVAL(0), D3DVAL(0), D3DVAL(0)))
    return false;

  if (!pAnimObj->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(130)))
    return false;
  
  if (!SetMoveCallback())
    return false;

  if (!SetTickEnable(true))
    return false;

  //= Animationssektion:
  m_pAnim = new CD3DAnimation;
  if (m_pAnim == NULL)
    return false;

  if (!m_pAnim->Create(this)) 
    return false;

  int anim_count = 10;
  static int rvTime[] = {0, 20, 40, 60, 80, 100, 120, 140, 160, 180};
  
  static D3DVECTOR rvPos[] = {
    {D3DVAL(-180), D3DVAL(50), D3DVAL(70)},
    {D3DVAL(-100), D3DVAL(60), D3DVAL(70)},
    {D3DVAL(0), D3DVAL(80), D3DVAL(70)},
    {D3DVAL(20),  D3DVAL(70), D3DVAL(70)},
    {D3DVAL(100),  D3DVAL(40), D3DVAL(70)},
    {D3DVAL(180),  D3DVAL(50), D3DVAL(70)},
    {D3DVAL(100), D3DVAL(30), D3DVAL(70)},
    {D3DVAL(0),  D3DVAL(20), D3DVAL(70)},
    {D3DVAL(-100),  D3DVAL(40), D3DVAL(70)},
    {D3DVAL(-180),  D3DVAL(50), D3DVAL(70)}
    };
  static D3DVECTOR rvSca[] = {
    {D3DVAL(5), D3DVAL(5), D3DVAL(5)},
    {D3DVAL(10), D3DVAL(10), D3DVAL(5)},
    {D3DVAL(10), D3DVAL(10), D3DVAL(15)},
    {D3DVAL(15), D3DVAL(15), D3DVAL(15)},
    {D3DVAL(10), D3DVAL(10), D3DVAL(10)},
    {D3DVAL(8), D3DVAL(8), D3DVAL(8)},
    {D3DVAL(10), D3DVAL(10), D3DVAL(10)},
    {D3DVAL(8), D3DVAL(8), D3DVAL(8)},
    {D3DVAL(10), D3DVAL(10), D3DVAL(10)},
    {D3DVAL(5), D3DVAL(5), D3DVAL(5)}
    };
  static D3DVECTOR rvRot[] = {
    {D3DVAL(0.1), D3DVAL(0), D3DVAL(1)},
    {D3DVAL(0.1), D3DVAL(0), D3DVAL(1)},
    {D3DVAL(0.1), D3DVAL(0), D3DVAL(1)},
    {D3DVAL(0.1), D3DVAL(0), D3DVAL(1)},
    {D3DVAL(1), D3DVAL(0), D3DVAL(1)},
    {D3DVAL(1), D3DVAL(0), D3DVAL(1)},
    {D3DVAL(1), D3DVAL(0), D3DVAL(1)},
    {D3DVAL(1), D3DVAL(0), D3DVAL(1)},
    {D3DVAL(1), D3DVAL(0), D3DVAL(1)},
    {D3DVAL(1), D3DVAL(0), D3DVAL(1)}
    };
  static D3DVALUE rvAng[] = {D3DVAL(0.5), D3DVAL(0.8), D3DVAL(1),
                             D3DVAL(1.5), D3DVAL(1.8), D3DVAL(2.2),
                             D3DVAL(2.8), D3DVAL(3.2), D3DVAL(3.8),
                             D3DVAL(4.2)};

  int i;
  for (i = 0; i < anim_count; i++)
    {
    if (!m_pAnim->SetPositionKey(D3DVAL(rvTime[i]), 
                      rvPos[i].x, rvPos[i].y, rvPos[i].z))
      return false;
    if (!m_pAnim->SetRotateKey(D3DVAL(rvTime[i]), 
                      rvRot[i].x, rvRot[i].y, rvRot[i].z, rvAng[i]))
      return false;
    if (!m_pAnim->SetScaleKey(D3DVAL(rvTime[i]), 
                      rvSca[i].x, rvSca[i].y, rvSca[i].z))
      return false;
    }

  if (!m_pAnim->SetFrame(m_pMidObj))
    return false;

  if (!SetCameraParam(2.0, 1.0, 1500.0, RGB(255, 255, 255), RGB(255, 255, 255)))
    return false;

  return true;
  }
