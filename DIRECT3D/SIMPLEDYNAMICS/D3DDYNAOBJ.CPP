// d3dDynaObj.cpp : implementation file
//

#include "stdafx.h"
#include "d3dDynaObj.h"

 
#include "d3dGeomArsenal.h"
#include "d3dFlowerApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DDynaObj

CD3DDynaObj::CD3DDynaObj()
  {
  m_Vdelta = D3DVAL(0.1);   
  m_times = 0;
  }

CD3DDynaObj::~CD3DDynaObj()
  {
  }

void CD3DDynaObj::ObjCallback(D3DVALUE delta)
  {
  if (++m_times == 55)
    {
    m_Vdelta = -m_Vdelta;
    m_pDynaObj->SetRotation(this, D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(m_Vdelta));
    m_times = 0;
    }
  }

bool CD3DDynaObj::OnCreate()
  {
  
  //= Hauptframe anlegen 
  m_pDynaObj = new CD3DFrame;
  if (m_pDynaObj == NULL)
    return false;

  if (!m_pDynaObj->Create(this))
    return false;
 
  //= Zentrum festlegen
  CD3DDiskFrame *pHeart = new CD3DDiskFrame;
  if (pHeart == NULL)
    return false;

  if (!pHeart->Create(this, 0.0, 16, RGB(255, 255, 0)))
    return false;

  if (!pHeart->SetColor(RGB(255, 255, 0)))
    return false;

  if (!pHeart->AddToFrame(m_pDynaObj))
    return false;

  if (!pHeart->AddScale(D3DRMCOMBINE_REPLACE, D3DVAL(0.3), D3DVAL(0.3), D3DVAL(0.3)))
    return false;

  if (!pHeart->AddRotation(D3DRMCOMBINE_AFTER, 
                        D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(-PI / 2.0)))
    return false;

  //= Obere Blüte
  CD3DFlowerFrame *pFlowerTop = new CD3DFlowerFrame;
  if (pFlowerTop == NULL)
    return false;

  if (!pFlowerTop->Create(this, m_pDynaObj))
    return false;

  //= Weitere Blüten... 
  CD3DFlowerFrame *pFlowerBot = new CD3DFlowerFrame;
  if (pFlowerBot == NULL)
    return false;

  if (!pFlowerBot->Create(this, m_pDynaObj, D3DVAL(PI)))
    return false;

  
  CD3DFlowerLeft *pFlowerLeft = new CD3DFlowerLeft;
  if (pFlowerLeft == NULL)
    return false;

  if (!pFlowerLeft->Create(this, m_pDynaObj))
    return false;

  
  CD3DFlowerRight *pFlowerRight = new CD3DFlowerRight;
  if (pFlowerRight == NULL)
    return false;

  if (!pFlowerRight->Create(this, m_pDynaObj))
    return false;

  //= Objekt zum Frame hinzufügen
  if (!m_pDynaObj->AddToFrame(this))
    return false;

  //= Transformationen festlegen
  if (!m_pDynaObj->AddCombTransform(D3DVAL(15), D3DVAL(15), D3DVAL(15),
                              D3DVAL(-PI / 2.0), D3DVAL(0), D3DVAL(0), 
                              D3DVAL(0), D3DVAL(0), D3DVAL(100)))
    return false;

  if (!m_pDynaObj->SetRotation(this, D3DVAL(0), D3DVAL(0), D3DVAL(1), m_Vdelta))
    return false;

  //= Rückmeldung einschalten
  if (!SetMoveCallback())
    return false;

  //= Material des Objektes vorbereiten
  CD3DMaterial *mat = new CD3DMaterial;

  if (!mat->Create(this, D3DVAL(1), D3DVAL(1), D3DVAL(1), D3DVAL(5)))
    return false;

  if (!m_pDynaObj->SetMaterial(mat, true))
    return false;

  //= Direct3D über den Bedarf von Ticks informieren
  if (!SetTickEnable(true))
    return false;

  //= Punktlichtquelle anlegen
  CD3DPointLight *plight = new CD3DPointLight;
  
  if (plight == NULL)
    return false;
  
  if (!plight->Create(this))
    return false;

   if (!plight->SetColorRGB(D3DVAL(1.45), D3DVAL(1.45), D3DVAL(1.45)))
    return false;

 
  if (!plight->AddToFrame(pHeart))
    return false;

  //= Kameratransformationen
  if (!plight->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(-1)))
    return false;

  if (!SetCameraParam(2.5, 1.0, 1500.0, RGB(140, 140, 140), RGB(102, 102, 153)))
    return false;
  
  return true;
  }
