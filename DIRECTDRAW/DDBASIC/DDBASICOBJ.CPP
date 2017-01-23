// DDBasicObj.cpp: implementation of the CDDBasicObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ddbasic.h"
#include "ddBasicObj.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CDDBasicObj, CDDMainObj);
CDDBasicObj::CDDBasicObj()
  {
  m_dAngle[0] = 0.0;
  m_dAngle[1] = 0.025;
  m_nSurface = 0;

  m_iCounter = 0;
  }

CDDBasicObj::~CDDBasicObj()
  {
  }

bool CDDBasicObj::OnCreate()
  {
  HDC hdc;
  if (m_lpDDPrimarySurface->GetDC(&hdc) == DD_OK)
    {
    char *msg = "Primary Surface. Press ESC to exit";

    SetBkColor(hdc, RGB(0, 0, 255));
    SetTextColor(hdc, RGB(255, 255, 0));
    TextOut(hdc, 0, 0, msg, strlen(msg));
    m_lpDDPrimarySurface->ReleaseDC(hdc);
    }

  if (m_lpDDBackSurface->GetDC(&hdc) == DD_OK)
    {
    char *msg = "Back Surface";

    SetBkColor(hdc, RGB(0, 0, 255));
    SetTextColor(hdc, RGB(255, 255, 0));
    TextOut(hdc, 0, 0, msg, strlen(msg));
    m_lpDDBackSurface->ReleaseDC(hdc);
    } 

  return true;
  }

void CDDBasicObj::Loop()
  {
  if (m_iCounter++ < 1000)
    return;

  m_iCounter = 0;
  double PI2 = 3.1415926535 * 2.0;
  int x1, y1, x2, y2;

  double xc = 320, yc = 240; //= Zentrum des Orbits
  double xr = 150, yr = 150; //= Radius des Orbits
  double xr1 = 50, yr1 = 50; //= Radius des Kreises

  HDC hdc;
  if (m_lpDDBackSurface->GetDC(&hdc) == DD_OK)
    {
    CDC dc;
    dc.Attach(hdc);

    CBrush brush, *pOldBrush;

    brush.CreateSolidBrush(RGB(0, 0, 0));
    pOldBrush = dc.SelectObject(&brush);

    //= Alte Grenze des Kreises
    x1 = (int)((xc + xr * cos(m_dAngle[m_nSurface])) - xr1);
    y1 = (int)((yc + yr * sin(m_dAngle[m_nSurface])) - yr1);
    x2 = (int)((xc + xr * cos(m_dAngle[m_nSurface])) + xr1);
    y2 = (int)((yc + yr * sin(m_dAngle[m_nSurface])) + yr1);

    dc.Ellipse(x1, y1, x2, y2);
    dc.SelectObject(pOldBrush);
    brush.DeleteObject();

    if ((m_dAngle[m_nSurface] += 0.05) >= PI2)
      m_dAngle[m_nSurface] -= PI2;

    brush.CreateSolidBrush(RGB(255, 0, 0));
    pOldBrush = dc.SelectObject(&brush);

    //= Neue Position des Kreises
    x1 = (int)((xc + xr * cos(m_dAngle[m_nSurface])) - xr1);
    y1 = (int)((yc + yr * sin(m_dAngle[m_nSurface])) - yr1);
    x2 = (int)((xc + xr * cos(m_dAngle[m_nSurface])) + xr1);
    y2 = (int)((yc + yr * sin(m_dAngle[m_nSurface])) + yr1);

    dc.Ellipse(x1, y1, x2, y2);
    dc.SelectObject(pOldBrush);
    brush.DeleteObject();

    dc.Detach();
    m_lpDDBackSurface->ReleaseDC(hdc);
    m_nSurface = 1 - m_nSurface;
    }

  Flip();
  }

