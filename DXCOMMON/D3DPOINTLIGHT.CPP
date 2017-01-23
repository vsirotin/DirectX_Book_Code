// d3dPointLight.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dPointLight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DPointLight

IMPLEMENT_DYNAMIC(CD3DPointLight, CD3DLightFrame)

CD3DPointLight::CD3DPointLight()
  {
  m_LType = D3DRMLIGHT_POINT;
  }

CD3DPointLight::~CD3DPointLight()
  {
  }


bool CD3DPointLight::Create(CD3DMainObj *pOwner, 
                            D3DVALUE red, D3DVALUE green, D3DVALUE blue,
                            D3DVALUE attn_c, D3DVALUE attn_l, D3DVALUE attn_q)
  {
  //= creation of LightFrameobject
  if (!CD3DLightFrame::Create(pOwner, red, green, blue))
    return false;

  if (!SetAttenuation(attn_c, attn_l, attn_q))
    return false;

  return true;
  }

bool CD3DPointLight::SetAttenuation(D3DVALUE attn_c, 
                                    D3DVALUE attn_l, D3DVALUE attn_q)
  {
  D3DTRY(m_lpLight->SetConstantAttenuation(attn_c));
  D3DTRY(m_lpLight->SetLinearAttenuation(attn_l));
  D3DTRY(m_lpLight->SetQuadraticAttenuation(attn_q));
  //  1 / [constant_attenuation_factor + 
  //       distance * linear_attenuation_factor + 
  //      (distance**2) * quadratic_attenuation_factor] 
  m_AttnC = attn_c;
  m_AttnL = attn_l;
  m_AttnQ = attn_q;

  return true;
  }

bool CD3DPointLight::GetAttenuation(D3DVALUE *attn_c, 
                                    D3DVALUE *attn_l, D3DVALUE *attn_q)
  {
  *attn_c = m_AttnC;
  *attn_l = m_AttnL;
  *attn_q = m_AttnQ;

  return true;
  }
