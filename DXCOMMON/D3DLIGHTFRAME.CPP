// d3dLightFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dLightFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DLightFrame

IMPLEMENT_DYNAMIC(CD3DLightFrame, CD3DFrame)

CD3DLightFrame::CD3DLightFrame()
  {
  m_lpLight = NULL; 
  }

CD3DLightFrame::~CD3DLightFrame()
  {
  D3DFREE(m_lpLight); 
  }

bool CD3DLightFrame::SetColor(D3DCOLOR color)
  
  {
  m_bChanged = true;
  D3DVALUE red, green, blue;

  red = D3DVAL((float)GetRValue(color) / 255.0); 
  green = D3DVAL((float)GetGValue(color) / 255.0);
  blue = D3DVAL((float)GetBValue(color) / 255.0);

  return SetColorRGB(red, green, blue);
  }

bool CD3DLightFrame::SetColorRGB(D3DVALUE red, D3DVALUE green, 
                                    D3DVALUE blue)
  //= DirectX - Farbendefinition
  {
  m_bChanged = true;

  m_ColorRed = red; 
  m_ColorGreen = green;
  m_ColorBlue = blue;
  return D3DCHECK(m_lpLight->SetColorRGB(red, green, blue));
  }


bool CD3DLightFrame::Create(CD3DMainObj *pOwner, 
                           D3DVALUE red, D3DVALUE green, D3DVALUE blue)
  {
  LPDIRECT3DRM3 main_obj = pOwner->GetMainObject();
  
  //= Zuerst erzeugen wir den assoziierten Frame
  if (!CD3DFrame::Create(pOwner))
    return NULL;

  m_ColorRed = red; 
  m_ColorGreen = green;
  m_ColorBlue = blue;
  
  //=Jetzt legen wir die Lichtquellenparameter fest
  D3DTRY(main_obj->CreateLightRGB(m_LType, 
                                  red, green, blue, &m_lpLight));
  
  D3DTRY(m_lpFrame->AddLight(m_lpLight));
  return true;
  }

D3DCOLOR CD3DLightFrame::GetColor(void)
  {
  D3DCOLOR col = m_lpLight->GetColor();
  return RGB(RGB_GETRED(col), RGB_GETGREEN(col), RGB_GETBLUE(col));
  }

bool CD3DLightFrame::GetColorRGB(D3DVALUE *red, D3DVALUE *green, 
                                       D3DVALUE *blue)
  {
  *red = m_ColorRed; 
  *green = m_ColorGreen;
  *blue = m_ColorBlue;

  return true;
  }