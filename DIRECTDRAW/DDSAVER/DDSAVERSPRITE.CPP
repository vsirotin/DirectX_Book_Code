// ddSaverSprite.cpp: implementation of the CDDSaverSprite class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ddSaver.h"
#include "ddSaverSprite.h"

#include "ddMainObj.h"
#include "ddSurfaceFiller.h"

#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CDDSaverSprite, CDDSprite)
CDDSaverSprite::CDDSaverSprite(CDDMainObj *pOwner) : CDDSprite(pOwner)
  {

  m_dAlpha = 0.0;
  m_dSpeed = 3.0;
  }

CDDSaverSprite::~CDDSaverSprite()
  {
  while (!m_poseList.IsEmpty())
    {
    CPoint *p = m_poseList.RemoveTail();
    delete p;
    }
  }

bool CDDSaverSprite::Create(int xs, int ys, int xorg, int yorg, int speed)
  {
  if (!CDDSprite::Create(xs, ys))
    return false;


  m_ptOrg = CPoint(xorg, yorg);
  m_ptPose = m_ptOrg;
  m_dSpeed = speed;

  return true;
  }

bool CDDSaverSprite::IsChanged()
  {
  if (m_iState == 1)
    {
    int x = (int)(m_dSpeed * cos(m_dAlpha));
    int y = (int)(m_dSpeed * sin(m_dAlpha));
    m_ptPose.Offset(x, y);

    CPoint *p = new CPoint(m_ptPose);
    m_poseList.AddTail(p);
    if (p->x > m_pOwner->m_szSize.cx || 
        p->y > m_pOwner->m_szSize.cy ||
        p->x + m_szSize.cx < 0 || 
        p->y + m_szSize.cy < 0)
      {
      //= Wenn sich das Sprite außerhalb des Bildschierms befindet
      m_iState = 2;
      }

    return true;
    }
  else if (m_iState == 3)
    {
    if (!m_poseList.IsEmpty())
      {
      CPoint *p = m_poseList.RemoveTail();
      m_ptPose = *p;

      delete p;
      return true;
      }

    m_iState = 0;
    }

  return false;
  }

bool CDDSaverSprite::FillSurface(CDDSurfaceFiller *pFiller)
  {
  m_dAlpha = ((double)rand() / RAND_MAX) * 3.1415926535 * 2.0;
  m_iState = 0;
  m_ptPose = m_ptOrg;
  m_poseList.AddTail(new CPoint(m_ptPose));

  return CDDSprite::FillSurface(pFiller);
  }

void CDDSaverSprite::SetState(int state)
  {
  m_iState = state;
  }

int CDDSaverSprite::GetState()
  {
  return m_iState;
  }