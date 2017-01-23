// d3dSpotLight.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dSpotLight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DSpotLight

IMPLEMENT_DYNAMIC(CD3DSpotLight, CD3DLightFrame)

CD3DSpotLight::CD3DSpotLight()
  {
  m_LType = D3DRMLIGHT_SPOT;
  }

CD3DSpotLight::~CD3DSpotLight()
  {
  }

bool CD3DSpotLight::Create(CD3DMainObj *pOwner, 
                           D3DVALUE red, D3DVALUE green, D3DVALUE blue,
                           D3DVALUE umbra, D3DVALUE penumbra, 
                           D3DVALUE attn_c, D3DVALUE attn_l, D3DVALUE attn_q,
                           D3DVALUE range)
  {
  
  //= Anlegen des Frame-Objekts
  if (!CD3DLightFrame::Create(pOwner, red, green, blue))
    return false;

  if (!SetAttenuation(attn_c, attn_l, attn_q))
    return false;

  if (!SetSpotLightCone(umbra, penumbra, range))
    return false;

  return true;
  }

bool CD3DSpotLight::SetSpotLightCone(D3DVALUE umbra, D3DVALUE penumbra, 
                                D3DVALUE range)
  {
  D3DTRY(m_lpLight->SetUmbra(umbra));
  D3DTRY(m_lpLight->SetPenumbra(penumbra));
  D3DTRY(m_lpLight->SetRange(range));
  m_Umbra = umbra;
  m_Penumbra = penumbra;
  m_Range = range;

  return true;
  }

bool CD3DSpotLight::GetSpotLightCone(D3DVALUE *umbra, D3DVALUE *penumbra, 
                                D3DVALUE *range)
  {
  *umbra = m_Umbra;
  *penumbra = m_Penumbra;
  *range = m_Range;

  return true;
  }

bool CD3DSpotLight::SetAttenuation(D3DVALUE attn_c, 
                                   D3DVALUE attn_l, D3DVALUE attn_q)
  {
  D3DTRY(m_lpLight->SetConstantAttenuation(attn_c));
  D3DTRY(m_lpLight->SetLinearAttenuation(attn_l));
  D3DTRY(m_lpLight->SetQuadraticAttenuation(attn_q));
  m_AttnC = attn_c;
  m_AttnL = attn_l;
  m_AttnQ = attn_q;

  return true;
  }

bool CD3DSpotLight::GetAttenuation(D3DVALUE *attn_c, 
                                    D3DVALUE *attn_l, D3DVALUE *attn_q)
  {
  *attn_c = m_AttnC;
  *attn_l = m_AttnL;
  *attn_q = m_AttnQ;

  return true;
  }

