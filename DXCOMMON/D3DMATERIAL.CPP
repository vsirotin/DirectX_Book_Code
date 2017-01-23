// d3dMaterial.cpp : implementation file
//

#include "stdafx.h"

#include "d3dMainObj.h"
#include "d3dMaterial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DMaterial

IMPLEMENT_DYNAMIC(CD3DMaterial, CObject)

CD3DMaterial::CD3DMaterial()
  {
  m_lpMaterial = NULL;
  m_pOwner = NULL;
  m_bChanged = false; 
  }

CD3DMaterial::~CD3DMaterial()
  {
//= Vom Besitzerobjekt entfernen
  if (m_pOwner != NULL)
    m_pOwner->RemoveMaterial(this);
  
  D3DFREE(m_lpMaterial);
  }

bool CD3DMaterial::SetAppData(DWORD appdata)
  {
  D3DTRY(m_lpMaterial->SetAppData(appdata));

  return true;
  }

DWORD CD3DMaterial::GetAppData(void)
  {
  return (m_lpMaterial->GetAppData());
  }

bool CD3DMaterial::IsChanged()
  {
  bool bChanged = m_bChanged;
    
  m_bChanged = false;
  return bChanged;
  }

bool CD3DMaterial::Create(CD3DMainObj *pOwner,
                          D3DVALUE rvspRed, D3DVALUE rvspGreen, 
                          D3DVALUE rvspBlue, D3DVALUE rvspPower,
                          D3DVALUE rvemRed, D3DVALUE rvemGreen, 
                          D3DVALUE rvemBlue)
  {
  if (pOwner == NULL)
    return false;

  pOwner->AddMaterial(this); //= Beim Besitzerobjekt registrieren
  m_pOwner = pOwner;
  
  //= Materialschnittstelle ermitteln
  D3DTRY(m_pOwner->GetMainObject()->CreateMaterial(rvspPower, &m_lpMaterial));

  //= Eigenschaften festlegen
  D3DTRY(m_lpMaterial->SetEmissive(rvemRed, rvemGreen, rvemBlue));
  D3DTRY(m_lpMaterial->SetSpecular(rvspRed, rvspGreen, rvspBlue));

  m_bChanged = true; 
  return true;
  }

bool CD3DMaterial::SetEmissive(D3DVALUE rvemRed, D3DVALUE rvemGreen, 
                               D3DVALUE rvemBlue)
  {
  D3DTRY(m_lpMaterial->SetEmissive(rvemRed, rvemGreen, rvemBlue));
  
  m_bChanged = true; 
  return true;
  }

bool CD3DMaterial::SetSpecular(D3DVALUE rvspRed, D3DVALUE rvspGreen, 
                               D3DVALUE rvspBlue, D3DVALUE rvspPower)
  {
  D3DTRY(m_lpMaterial->SetSpecular(rvspRed, rvspGreen, rvspBlue));
  D3DTRY(m_lpMaterial->SetPower(rvspPower));
  
  m_bChanged = true; 
  return true;
  }

bool CD3DMaterial::GetEmissive(D3DVALUE *rvemRed, D3DVALUE *rvemGreen, 
                               D3DVALUE *rvemBlue)
  {
  D3DTRY(m_lpMaterial->GetEmissive(rvemRed, rvemGreen, rvemBlue));
  
  return true;
  }

bool CD3DMaterial::GetSpecular(D3DVALUE *rvspRed, D3DVALUE *rvspGreen, 
                               D3DVALUE *rvspBlue, D3DVALUE *rvspPower)
  {
  D3DTRY(m_lpMaterial->GetSpecular(rvspRed, rvspGreen, rvspBlue));
  *rvspPower = m_lpMaterial->GetPower();
  
  return true;
  }

bool CD3DMaterial::SetAmbient(D3DVALUE rvamRed, D3DVALUE rvamGreen, 
                              D3DVALUE rvamBlue)
  {
  D3DTRY(m_lpMaterial->SetAmbient(rvamRed, rvamGreen, rvamBlue));
  
  m_bChanged = true; 
  return true;
  }

bool CD3DMaterial::GetAmbient(D3DVALUE *rvamRed, D3DVALUE *rvamGreen, 
                              D3DVALUE *rvamBlue)
  {
  D3DTRY(m_lpMaterial->GetAmbient(rvamRed, rvamGreen, rvamBlue));
  
  return true;
  }

