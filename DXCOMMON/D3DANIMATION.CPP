// d3dAnimation.cpp : implementation file
//

#include "stdafx.h"

#include "d3dMainObj.h"
#include "d3dAnimation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DAnimation

IMPLEMENT_DYNAMIC(CD3DAnimation, CObject)

CD3DAnimation::CD3DAnimation()
  {
  m_lpAnimation = NULL;
  m_pOwner = NULL;
  }

CD3DAnimation::~CD3DAnimation()
  {
  //= Vom Besitzerobjekt entfernen
  if (m_pOwner != NULL)
    m_pOwner->RemoveAnimation(this);
  
  D3DFREE(m_lpAnimation);
  }

bool CD3DAnimation::Create(CD3DMainObj *pOwner, D3DRMANIMATIONOPTIONS option)
  {
  if (pOwner == NULL)
    return false;

  pOwner->AddAnimation(this); //= Beim Hauptobjekt registrieren 
  m_pOwner = pOwner;

  //= Animationsschnittstelle anlegen
  D3DTRY(m_pOwner->GetMainObject()->CreateAnimation(&m_lpAnimation));

  //= Eigenschaften festlegen
  D3DTRY(m_lpAnimation->SetOptions(option));

  return true;
  }

bool CD3DAnimation::SetRotateKey(D3DVALUE rvTime, 
                            D3DVALUE rvX, D3DVALUE rvY, D3DVALUE rvZ, 
                            D3DVALUE rvAngle)
  {
  D3DRMQUATERNION quat;
  D3DVECTOR temp;

  temp.x = rvX;
  temp.y = rvY;
  temp.z = rvZ;
  
  if (D3DRMQuaternionFromRotation(&quat, &temp, rvAngle) == NULL)
    return false;
  D3DTRY(m_lpAnimation->AddRotateKey(rvTime, &quat));

  return true;
  }

bool CD3DAnimation::SetPositionKey(D3DVALUE rvTime, 
                            D3DVALUE rvX, D3DVALUE rvY, D3DVALUE rvZ)
  {
  D3DTRY(m_lpAnimation->AddPositionKey(rvTime, rvX, rvY, rvZ));

  return true;
  }

bool CD3DAnimation::SetScaleKey(D3DVALUE rvTime, 
                            D3DVALUE rvX, D3DVALUE rvY, D3DVALUE rvZ)
  {
  D3DTRY(m_lpAnimation->AddScaleKey(rvTime, rvX, rvY, rvZ));

  return true;
  }

bool CD3DAnimation::SetFrame(CD3DFrame *frm)
  {
  D3DTRY(m_lpAnimation->SetFrame(frm->m_lpFrame));

  return true;
  }

bool CD3DAnimation::SetTime(D3DVALUE rvTime)
  {
  D3DTRY(m_lpAnimation->SetTime(rvTime));

  return true;
  }
