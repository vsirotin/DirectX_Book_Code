// d3dMushroomObj.cpp : implementation file
//

#include "stdafx.h"
#include "d3dMushroomObj.h"

 
#include "d3dGeomArsenal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DMushroomObj

CD3DMushroomObj::CD3DMushroomObj()
  {
  }

CD3DMushroomObj::~CD3DMushroomObj()
  {
  }
                                  
bool CD3DMushroomObj::OnCreate() 
  {
  //= Radar erzeugen
  CD3DFrame *radar= CD3DGeomArsenal::CreateRadar(this, 48, 8, RGB(255, 200, 200));
  if (radar == NULL)
    return false;

 //= Zur Szene hinzüfugen
  if (!radar->AddToFrame(this))
    return false;
  
  //= Größe und Position anpassen
  radar->AddCombTransform(D3DVAL(20), D3DVAL(20), D3DVAL(20),
                          D3DVAL(-PI / 2.0), D3DVAL(0.3), D3DVAL(0.0),
                          D3DVAL(-40), D3DVAL(-20), D3DVAL(120));
  //= Achse mit einem Disk dahinter
  CD3DFrame *axis1 = CD3DGeomArsenal::CreateAxis(this, 18,
                           0.5, 0.3, 0.0, RGB(170, 170, 170));
  if (axis1 == NULL)
    return false;

  if (!axis1->AddToFrame(this))
    return false;
  
  axis1->AddCombTransform(D3DVAL(10), D3DVAL(10), D3DVAL(35),
                          D3DVAL(0.0), D3DVAL(-PI / 7.0 * 3.0), D3DVAL(0.0),
                          D3DVAL(40), D3DVAL(40), D3DVAL(160));
  //= Achse mit einer Sphäre dahinter
  CD3DFrame *axis2 = CD3DGeomArsenal::CreateAxis(this, 24,
                           0.5, 0.3, 0.1, RGB(170, 255, 170));
  if (axis2 == NULL)
    return false;

  if (!axis2->AddToFrame(this))
    return false;
  
  axis2->AddCombTransform(D3DVAL(10), D3DVAL(10), D3DVAL(45),
                          D3DVAL(0.0), D3DVAL(-PI / 7.0 * 3.0), D3DVAL(0.0),
                          D3DVAL(40), D3DVAL(20), D3DVAL(160));
  //= Achse ohne Kegeldisk
  CD3DFrame *axis3 = CD3DGeomArsenal::CreateAxis(this, 32,
                           1.0, 0.3, 0.1, RGB(255, 170, 170));
  if (axis3 == NULL)
    return false;

  if (!axis3->AddToFrame(this))
    return false;
  
  axis3->AddCombTransform(D3DVAL(10), D3DVAL(10), D3DVAL(40),
                          D3DVAL(0.0), D3DVAL(-PI / 7.0 * 3.0), D3DVAL(0.0),
                          D3DVAL(40), D3DVAL(0), D3DVAL(160));

  if (!SetSceneBackground(RGB(64, 255, 255)))
    return false;

  //= Umgebungslicht festlegen
  if (!SetAmbientLightRGB(D3DVAL(0.65), D3DVAL(0.65), D3DVAL(0.65)))
    return false;

  //= Punktlichtquelle anlegen
  CD3DPointLight *plight = new CD3DPointLight;
  if (plight == NULL)
    return false;
  plight->Create(this); //= Standardfarbe und Intensität

  //= Farbe und Intensität der Punktlichtquelle festlegen
  if (!plight->SetColorRGB(D3DVAL(2.12), D3DVAL(2.12), D3DVAL(2.12)))
    return false;

 //= Zur Szene hinzüfugen
  if (!plight->AddToFrame(this))
    return false;

//= Nötige Transformationen durchführen
  plight->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(80), D3DVAL(160));

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

  //= Material der Fläche vorbereiten
  CD3DMaterial *matPlane = new CD3DMaterial;

  if (!matPlane->Create(this, D3DVAL(1), D3DVAL(1), D3DVAL(1), D3DVAL(120)))
    return false;

  if (!this->SetMaterial(matPlane, false))
    return false;

  //= Restliche Transformationen durchführen

  if (!SetCameraFront(1.0))
    return false;

  if (!SetCameraBack(1500.0))
    return false;

  if (!SetCameraField(D3DVAL(0.8)))
    return false;

  if (!SetRenderQuality(D3DRMLIGHT_ON | D3DRMFILL_SOLID | D3DRMSHADE_GOURAUD))
    return false;                                       
  
  return true;
  }
