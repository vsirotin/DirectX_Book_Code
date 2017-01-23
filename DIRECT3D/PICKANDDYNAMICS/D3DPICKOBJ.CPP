// d3dPickObj.cpp : implementation file
//

#include "stdafx.h"
#include "d3dPickObj.h"

 
#include "d3dGeomArsenal.h"
#include "d3dFlowerApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DPickObj

CD3DPickObj::CD3DPickObj()
  {
  m_count = 0;
  m_AccAngX = D3DVAL(0);
  m_AccAngY = D3DVAL(0);
  m_AccAngZ = D3DVAL(0);
  }

CD3DPickObj::~CD3DPickObj()
  {
  }

CD3DFrame *CD3DPickObj::FindFrame(DWORD AppData)
  {
  int i;

  for (i = 0; i < m_count; i++)
    {
    if (m_FrameArray[i] != NULL && m_FrameArray[i]->GetAppData() == AppData)
      {
      return m_FrameArray[i];
      }
    }
  return NULL;
  }

bool CD3DPickObj::Pick(int x, int y)
  {
  D3DVALUE   deltaAng = D3DVAL(PI / 10.0);
  
  if (!GetPick(x, y, &m_count, &m_FrameArray))
    return false;

  if (FindFrame((DWORD) 20) == NULL)
    { //= Notiges Objekt wurde nicht "picked"
    return false;
    }

  if (FindFrame((DWORD) 11) != NULL)
    { //= X-Ache wurde "picked"
    if (FindFrame((DWORD) 1) != NULL)
      { //= Gipfel 
      m_AccAngX += deltaAng;
      if (m_AccAngX > 2 * PI)
        m_AccAngX = D3DVAL(0);    
      }
    else
      { //= Rot festlegen   
      if (!mushroom->SetColor(RGB(255, 0, 0)))
        return false;
      }
    }

  else
  if (FindFrame((DWORD) 12) != NULL)
    { //= Y-Ache wurde "picked"
    if (FindFrame((DWORD) 1) != NULL)
      { //= Gipfel
      m_AccAngY += deltaAng;
      if (m_AccAngY > 2 * PI)
        m_AccAngY = D3DVAL(0);    
      }
    else
      { //= Grün festlegen
      if (!mushroom->SetColor(RGB(0, 255, 0)))
        return false;
      }
    }
  else
  if (FindFrame((DWORD) 13) != NULL)
    { //= Z-Ache wurde "picked"
    if (FindFrame((DWORD) 1) != NULL)
      { //= Gipfel
      m_AccAngZ += deltaAng;
      if (m_AccAngY > 2 * PI)
        m_AccAngZ = D3DVAL(0);    
      }
    else
      { //= Blau festlegen 
      if (!mushroom->SetColor(RGB(0, 0, 255)))
        return false;
      }
    }

  //= Erste Verschiebung  (0,0,0) initialisiert die Transformation
  if (!mushroom->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(0)))
    return false;
  if (!mushroom->AddCombTransform(D3DVAL(4.5), D3DVAL(4.5), D3DVAL(4.5),
                                  m_AccAngX, m_AccAngY, m_AccAngZ,
                                 D3DVAL(0), D3DVAL(0), D3DVAL(0)))
    return false;

  return true;
  }

bool CD3DPickObj::OnCreate()
  {
  CD3DFrame *pPickObj = new CD3DFrame;
  if (pPickObj == NULL)
    return false;

  if (!pPickObj->Create(this))
    return false;

  if (!pPickObj->AddToFrame(this))
    return false;
  
  //= Hauptobjekt anlegen
  CD3DFrame *pMidObj = new CD3DFrame;
  if (pMidObj == NULL)
    return false;

  if (!pMidObj->Create(this))
    return false;

  if (!pMidObj->AddToFrame(pPickObj))
    return false;

  if (!pMidObj->SetAppData((DWORD) 20))
    return false;

  mushroom = CD3DGeomArsenal::CreateMushroom(this, 32, 10);

  if (mushroom == NULL)
    return false;

  if (!mushroom->AddToFrame(pMidObj))
    return false;

  if (!mushroom->AddCombTransform(D3DVAL(4.5), D3DVAL(4.5), D3DVAL(4.5),
                          D3DVAL(0), D3DVAL(0), D3DVAL(0),
                          D3DVAL(0), D3DVAL(0), D3DVAL(0)))
    return false;

  CD3DMaterial *mat = new CD3DMaterial;
  if (!mat->Create(this, D3DVAL(1), D3DVAL(1), D3DVAL(1), D3DVAL(200)))
    return false;
  
  if (!mushroom->SetColor(RGB(155, 200, 255)))
    return false;

  CD3DDirectionalLight *dlight = new CD3DDirectionalLight;
  
  if (dlight == NULL)
    return false;
  
  dlight->Create(this);

  if (!dlight->SetColorRGB(D3DVAL(1.45), D3DVAL(1.45), D3DVAL(1.45)))
    return false;

  if (!dlight->AddToFrame(this))
    return false;

//  dlight->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(PI / 3.0 * 2.0));

  CD3DFrame *pAxisX = CD3DGeomArsenal::CreateAxis(this, 16, 0.5, 0.5, 0.0, 
                              RGB(255, 0, 0));
  if (pAxisX == NULL)
    return false;

  if (!pAxisX->AddToFrame(pMidObj))
    return false;

  if (!pAxisX->SetAppData((DWORD) 11))
    return false;

  if (!pAxisX->AddCombTransform(D3DVAL(3), D3DVAL(3), D3DVAL(15),
                                D3DVAL(0), D3DVAL(PI / 2.0), D3DVAL(0),
                                D3DVAL(0), D3DVAL(0), D3DVAL(0)))
    return false;

  CD3DFlowerFrame *pFlowerX = new CD3DFlowerFrame;
  if (pFlowerX == NULL)
    return false;

  if (!pFlowerX->Create(this, pMidObj))
    return false;

  if (!pFlowerX->AddCombTransform(D3DVAL(5), D3DVAL(5), D3DVAL(5),
                              D3DVAL(0), D3DVAL(0), D3DVAL(PI / 2.0), 
                              D3DVAL(20), D3DVAL(0), D3DVAL(0)))
    return false;

  if (!pFlowerX->SetRotation(pMidObj, D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(0.2)))
    return false;

  CD3DFrame *pAxisY = CD3DGeomArsenal::CreateAxis(this, 16, 0.5, 0.5, 0.0, 
                              RGB(0, 255, 0));
  if (pAxisY == NULL)
    return false;

  if (!pAxisY->AddToFrame(pMidObj))
    return false;

  if (!pAxisY->SetAppData((DWORD) 12))
    return false;

  if (!pAxisY->AddCombTransform(D3DVAL(3), D3DVAL(3), D3DVAL(15),
                                D3DVAL(-PI / 2.0), D3DVAL(0), D3DVAL(0),
                                D3DVAL(0), D3DVAL(0), D3DVAL(0)))
    return false;

  CD3DFlowerFrame *pFlowerY = new CD3DFlowerFrame;
  if (pFlowerY == NULL)
    return false;

  if (!pFlowerY->Create(this, pMidObj))
    return false;

  if (!pFlowerY->AddCombTransform(D3DVAL(5), D3DVAL(5), D3DVAL(5),
                              D3DVAL(0), D3DVAL(PI / 2.0), D3DVAL(0), 
                              D3DVAL(0), D3DVAL(20), D3DVAL(0)))
    return false;

  if (!pFlowerY->SetRotation(pMidObj, D3DVAL(0), D3DVAL(1), D3DVAL(0), D3DVAL(0.2)))
    return false;

  CD3DFrame *pAxisZ = CD3DGeomArsenal::CreateAxis(this, 16, 0.5, 0.5, 0.0, 
                              RGB(0, 0, 255));
  if (pAxisZ == NULL)
    return false;

  if (!pAxisZ->SetAppData((DWORD) 13))
    return false;

  if (!pAxisZ->AddToFrame(pMidObj))
    return false;

  if (!pAxisZ->AddCombTransform(D3DVAL(3), D3DVAL(3), D3DVAL(15),
                                D3DVAL(0), D3DVAL(0), D3DVAL(0),
                                D3DVAL(0), D3DVAL(0), D3DVAL(0)))
    return false;

  CD3DFlowerFrame *pFlowerZ = new CD3DFlowerFrame;
  if (pFlowerZ == NULL)
    return false;

  if (!pFlowerZ->Create(this, pMidObj))
    return false;

  if (!pFlowerZ->AddCombTransform(D3DVAL(5), D3DVAL(5), D3DVAL(5),
                              D3DVAL(-PI / 2.0), D3DVAL(0), D3DVAL(0), 
                              D3DVAL(0), D3DVAL(0), D3DVAL(20)))
    return false;

  if (!pFlowerZ->SetRotation(pMidObj, D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(0.2)))
    return false;
  
  if (!pPickObj->SetMaterial(mat))
    return false;

  if (!pPickObj->AddCombTransform(D3DVAL(2), D3DVAL(2), D3DVAL(2),
            D3DVAL(-PI / 2.0), D3DVAL(PI / 4.0), D3DVAL(0),
            D3DVAL(0), D3DVAL(0), D3DVAL(90)))
    return false;

  //= Punktlichtquelle anlegen
  CD3DPointLight *plight = new CD3DPointLight;
  
  if (plight == NULL)
    return false;
  
  if (!plight->Create(this))
    return false;

  //= Farbe und Intensität festlegen
  if (!plight->SetColorRGB(D3DVAL(1.45), D3DVAL(1.45), D3DVAL(1.45)))
    return false;

 //= Zur Szene hinzüfugen
  if (!plight->AddToFrame(pPickObj))
    return false;

  //= Zur Kamera verschieben
  if (!plight->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(-1)))
    return false;

  //= Direct3D informieren, daß die Szene Ticks benötigt
  if (!SetTickEnable(true))
    return false;

  if (!SetAmbientLightRGB(D3DVAL(0.4), D3DVAL(0.4), D3DVAL(0.4)))
    return false;
  if (!SetSceneBackground(RGB(155, 155, 200)))
    return false;
  if (!SetCameraFront(1.0))
    return false;
  if (!SetCameraBack(1500.0))
    return false;
  if (!SetCameraField(1.0))
    return false;
  if (!SetRenderQuality(D3DRMLIGHT_ON | D3DRMFILL_SOLID | D3DRMSHADE_GOURAUD))
    return false;                                       
  
  return true;
  }
