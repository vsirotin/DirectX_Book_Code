// d3dMaterialObj.cpp : implementation file
//

#include "stdafx.h"
#include "d3dMaterialObj.h"

 
#include "d3dGeomArsenal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DMaterialObj

CD3DMaterialObj::CD3DMaterialObj()
  {
  }

CD3DMaterialObj::~CD3DMaterialObj()
  {
  }

bool CD3DMaterialObj::OnCreate()
  {
  
  //= Kachel-Landschaft. Die Kacheln haben verschiedene Farben.
  CD3DFrame *pPlane = CD3DGeomArsenal::CreateChessBoard(this, 10, 10,
                                         RGB(255, 255, 100), RGB(0, 255, 0));
  if (pPlane == NULL)
    return false;

  if (!pPlane->AddToFrame(this))
    return false;

  pPlane->AddCombTransform(D3DVAL(100), D3DVAL(1), D3DVAL(100),
                       D3DVAL(0), D3DVAL(0), D3DVAL(0),
                       D3DVAL(-50), D3DVAL(-15), D3DVAL(0));
  //= Materialparameter festlegen
  CD3DMaterial *matPlane = new CD3DMaterial;

  if (!matPlane->Create(this, D3DVAL(1), D3DVAL(1), D3DVAL(1), D3DVAL(5)))
    return false;

  if (!pPlane->SetMaterial(matPlane, false))
    return false;

  //=  Frame pH:  Haus mit Fenster
  CD3DFrame *pH = new CD3DFrame;
  
  if (pH == NULL)
    return NULL;

  if (!pH->Create(this))
    return NULL;
  
  if (!pH->AddToFrame(this))
    return false;

  CD3DFrame *house = CD3DGeomArsenal::CreateHouse(this);

  if (house == NULL)
    return false;

  if (!house->AddToFrame(pH))
    return false;

  CD3DFrame *wind = CD3DGeomArsenal::CreateChessBoard(this, 4, 4,
                              RGB(150, 150, 150), RGB(150, 150, 150));
  if (wind == NULL)
    return false;

  if (!wind->AddToFrame(pH))
    return false;

  //= Fenster an der Wand "befestigen"
  wind->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(-0.5), D3DVAL(1.1), D3DVAL(0.5));
  pH->AddCombTransform(D3DVAL(10), D3DVAL(10), D3DVAL(10),
                       D3DVAL(-PI / 2.0), D3DVAL(PI / 5.0), D3DVAL(0),
                       D3DVAL(-20), D3DVAL(-15), D3DVAL(70));

  //= Material des Fensters festlegen
  CD3DMaterial *matwind = new CD3DMaterial;
  if (!matwind->Create(this, D3DVAL(1), D3DVAL(1), D3DVAL(1), D3DVAL(120),
                             D3DVAL(0.9), D3DVAL(0.9), D3DVAL(0)))
    return false;

  if (!wind->SetMaterial(matwind))
    return false;

  //= Pilz
  CD3DFrame *mushroom = CD3DGeomArsenal::CreateMushroom(this, 32, 10);

  if (mushroom == NULL)
    return false;

  if (!mushroom->AddToFrame(this))
    return false;

  mushroom->AddCombTransform(D3DVAL(10), D3DVAL(10), D3DVAL(10),
                          D3DVAL(-PI / 2.0), D3DVAL(0), D3DVAL(0),
                          D3DVAL(20), D3DVAL(-10), D3DVAL(50));
  
  //= Material für den ganzen Pilz
  CD3DMaterial *matMashr = new CD3DMaterial;
  if (!matMashr->Create(this, D3DVAL(1), D3DVAL(1), D3DVAL(1), D3DVAL(60)))
    return false;
  
  if (!mushroom->SetMaterial(matMashr))
    return false;

  //= Sphäre mit Index 4 finden
  CD3DFrame *pHsphere = mushroom->GetChildFrame((DWORD) 4);
              
  //= Material: keine Wiederspiegelung
  CD3DMaterial *matRoot = new CD3DMaterial;
  if (!matRoot->Create(this, D3DVAL(0), D3DVAL(0), D3DVAL(0), D3DVAL(60)))
    return false;
  
  if (!pHsphere->SetMaterial(matRoot))
    return false;

  //= Lichtquellen
  
  if (!SetAmbientLightRGB(D3DVAL(0), D3DVAL(0), D3DVAL(0)))
    return false;

  //= Punktlichtquelle anlegen
  CD3DPointLight *plight = new CD3DPointLight;
  if (plight == NULL)
    return false;
  plight->Create(this); //= Standardfarbe und Intensität

  //= Farbe und Intensität der Punktlichtquelle festlegen
  if (!plight->SetColorRGB(D3DVAL(1.12), D3DVAL(1.12), D3DVAL(1.12)))
    return false;

 //= Zur Szene hinzüfugen
  if (!plight->AddToFrame(this))
    return false;

  //= Nötige Transformationen durchführen
  plight->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(-5), D3DVAL(30));

  //= Gerichtete Lichtquelle anlegen
  CD3DDirectionalLight *dlight = new CD3DDirectionalLight;
  
  if (dlight == NULL)
    return false;
  
  dlight->Create(this); //= Standardfarbe und Intensität

  //= Farbe und Intensität der gerichteten Lichtquelle festlegen
  if (!dlight->SetColorRGB(D3DVAL(1.45), D3DVAL(1.45), D3DVAL(1.45)))
    return false;

 //= Zur Szene hinzüfugen
  if (!dlight->AddToFrame(this))
    return false;

  //= Restliche Transformationen durchführen
  
  dlight->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(PI / 3.0 * 2.0));

  //= Kamera festlegen
  CD3DCameraFrame *camera = GetCameraFrame();
  
  camera->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(0), D3DVAL(0), 
                                            D3DVAL(PI / 9.0));
  camera->AddTranslation(D3DRMCOMBINE_AFTER, D3DVAL(0), D3DVAL(15), D3DVAL(0));

  //= Manipulationen mit der Kamera und dem Viewport
  if (!SetSceneBackground(RGB(140, 140, 140)))
    return false;
  if (!SetCameraFront(1.0))
    return false;
  if (!SetCameraBack(500.0))
    return false;
  if (!SetCameraField(2.0))
    return false;
  if (!SetRenderQuality(D3DRMLIGHT_ON | D3DRMFILL_SOLID | D3DRMSHADE_GOURAUD))
    return false;                                       

  return true;
  }