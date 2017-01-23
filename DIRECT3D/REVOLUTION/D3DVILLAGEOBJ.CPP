// D3DVillageObj.cpp : implementation file
//

#include "stdafx.h"
#include "d3dVillageObj.h"
#include "math.h"

 
#include "d3dGeomArsenal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DVillageObj

CD3DVillageObj::CD3DVillageObj()
  {
  }

CD3DVillageObj::~CD3DVillageObj()
  {
  }
                                  
CD3DFrame *CD3DVillageObj::CreateShapeRev() 
  {

  CD3DFrame *shape = new CD3DFrame;
  
  if (shape == NULL)
    return NULL;

  if (!shape->Create(this))
    return NULL;

  //= Objekte
  D3DVECTOR base_chess[] = {
    {D3DVAL(0), D3DVAL(0), D3DVAL(0)},
    {D3DVAL(3), D3DVAL(0), D3DVAL(0)},
    {D3DVAL(3), D3DVAL(0), D3DVAL(1)},
    {D3DVAL(1.8), D3DVAL(0), D3DVAL(2)},
    {D3DVAL(1.5), D3DVAL(0), D3DVAL(2.7)},
    {D3DVAL(1), D3DVAL(0), D3DVAL(5)},
    {D3DVAL(0.95), D3DVAL(0), D3DVAL(10)},
    {D3DVAL(2), D3DVAL(0), D3DVAL(10.3)},
    {D3DVAL(2.8), D3DVAL(0), D3DVAL(10.8)},
    {D3DVAL(3.2), D3DVAL(0), D3DVAL(11.2)},
    {D3DVAL(2.4), D3DVAL(0), D3DVAL(12)},
    {D3DVAL(0.7), D3DVAL(0), D3DVAL(12.4)},
    {D3DVAL(1), D3DVAL(0), D3DVAL(13)},
    {D3DVAL(1.1), D3DVAL(0), D3DVAL(13.5)},
    {D3DVAL(0.9), D3DVAL(0), D3DVAL(14)},
    {D3DVAL(0.6), D3DVAL(0), D3DVAL(15)},
    {D3DVAL(0), D3DVAL(0), D3DVAL(16)}
    };

  D3DVECTOR base_apple[] = {
    {D3DVAL(0), D3DVAL(0), D3DVAL(1.3)},
    {D3DVAL(1), D3DVAL(0), D3DVAL(0.5)},
    {D3DVAL(2), D3DVAL(0), D3DVAL(0.45)},
    {D3DVAL(3), D3DVAL(0), D3DVAL(0.5)},
    {D3DVAL(4), D3DVAL(0), D3DVAL(1)},
    {D3DVAL(5), D3DVAL(0), D3DVAL(1.8)},
    {D3DVAL(6), D3DVAL(0), D3DVAL(3.5)},
    {D3DVAL(6.5), D3DVAL(0), D3DVAL(6)},
    {D3DVAL(6.3), D3DVAL(0), D3DVAL(8)},
    {D3DVAL(5.8), D3DVAL(0), D3DVAL(10)},
    {D3DVAL(5), D3DVAL(0), D3DVAL(11.2)},
    {D3DVAL(4), D3DVAL(0), D3DVAL(11.8)},
    {D3DVAL(3), D3DVAL(0), D3DVAL(11.9)},
    {D3DVAL(2), D3DVAL(0), D3DVAL(11.4)},
    {D3DVAL(1), D3DVAL(0), D3DVAL(10.7)},
    {D3DVAL(0.5), D3DVAL(0), D3DVAL(10)},
    {D3DVAL(0), D3DVAL(0), D3DVAL(9)}
    };

  CD3DRevolveSmoothFrame *bishop1 = new CD3DRevolveSmoothFrame;

  if (!bishop1->Create(this, 17,  base_chess, false, true, false, 
                           0.0, 24, RGB(255, 255, 0)))
    return NULL;

  if (!bishop1->AddToFrame(shape))
    return NULL;

  bishop1->AddCombTransform(D3DVAL(4), D3DVAL(4), D3DVAL(4),
                          D3DVAL(0), D3DVAL(0), D3DVAL(0),
                          D3DVAL(-25), D3DVAL(-20), D3DVAL(70));

  if (!bishop1->SetRotation(bishop1, D3DVAL(0), D3DVAL(1), D3DVAL(1), D3DVAL(-0.2)))
    return NULL;
    
  CD3DRevolveFrame *bishop2 = new CD3DRevolveFrame;

  if (!bishop2->Create(this, 17,  base_chess, false, 
                           0.0, 24, RGB(255, 0, 255)))
    return NULL;

  if (!bishop2->AddToFrame(shape))
    return NULL;

  if (!bishop2->SetRotation(bishop2, D3DVAL(0), D3DVAL(1), D3DVAL(1), D3DVAL(-0.1)))
    return NULL;

  bishop2->AddCombTransform(D3DVAL(4), D3DVAL(4), D3DVAL(4),
                          D3DVAL(0), D3DVAL(0), D3DVAL(0),
                          D3DVAL(25), D3DVAL(-20), D3DVAL(70));

  
  //= Ohne einen kleinen Teil 
  CD3DRevolveSmoothFrame *apple1 = new CD3DRevolveSmoothFrame;

  if (!apple1->Create(this, 17,  base_apple, false, true, true, 
                            5.5, 24, RGB(200, 185, 0)))
    return NULL;

  if (!apple1->AddToFrame(shape))
    return NULL;

  apple1->AddCombTransform(D3DVAL(6), D3DVAL(6), D3DVAL(4),
                          D3DVAL(PI / 2.0 + 0.2), D3DVAL(-4), D3DVAL(0.2),
                          D3DVAL(0), D3DVAL(-10), D3DVAL(95));

  if (!apple1->SetRotation(apple1, D3DVAL(0), D3DVAL(1), D3DVAL(1), D3DVAL(-0.2)))
    return NULL;
  
  //= Oberfläche erzeugen
  CD3DRevolveFrame *apple2 = new CD3DRevolveFrame;

  if (!apple2->Create(this, 17,  base_apple, false, 
                            0.78, 24, RGB(200, 185, 0)))
    return NULL;

  if (!apple2->AddToFrame(shape))
    return NULL;

  if (!apple2->SetRotation(apple2, D3DVAL(0), D3DVAL(1), D3DVAL(1), D3DVAL(-0.1)))
    return NULL;

  apple2->AddCombTransform(D3DVAL(6), D3DVAL(6), D3DVAL(4),
                          D3DVAL(PI / 2.0 + 0.2), D3DVAL(-3), D3DVAL(0.2),
                          D3DVAL(0), D3DVAL(-10), D3DVAL(95));
    
  //= Ein Stück  vom Apfel
  CD3DRevolveFrame *apple3 = new CD3DRevolveFrame;

  if (!apple3->Create(this, 17,  base_apple, true, 
                            0.78, 24, RGB(255, 195, 0)))
    return NULL;

  if (!apple3->AddToFrame(shape))
    return NULL;

  if (!apple3->SetRotation(apple3, D3DVAL(0), D3DVAL(1), D3DVAL(1), D3DVAL(-0.1)))
    return NULL;
  if (!apple3->AddScale(D3DRMCOMBINE_AFTER, D3DVAL(6), D3DVAL(6), D3DVAL(4)))
    return NULL;
  if (!apple3->AddRotation(D3DRMCOMBINE_AFTER, D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(-PI / 2.0 + 0.2)))
    return NULL;
  if (!apple3->AddRotation(D3DRMCOMBINE_AFTER, D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(-1)))
    return NULL;
  if (!apple3->AddTranslation(D3DRMCOMBINE_AFTER, D3DVAL(0), D3DVAL(0), D3DVAL(95)))
    return NULL;
  
  return shape;
  }
                                  
  
bool CD3DVillageObj::OnCreate() 
  {
  //= Umgebungslicht festlegen
  if (!SetAmbientLightRGB(D3DVAL(0.65), D3DVAL(0.65), D3DVAL(0.65)))
    return false;

  //= Punktlichtquelle anlegen
  CD3DPointLight *plight = new CD3DPointLight;
  if (plight == NULL)
    return false;
  plight->Create(this); //= Standardfarbe und Intensität

  //= Farbe und Intensität der Punktlichtquelle festlegen
  if (!plight->SetColorRGB(D3DVAL(0.82), D3DVAL(0.82), D3DVAL(0.82)))
    return false;

 //= Zur Szene hinzüfugen
  if (!plight->AddToFrame(this))
    return false;

  //= Nötige Transformation durchführen
  plight->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(-10), D3DVAL(0), D3DVAL(75));

  //= Punktlichtquelle anlegen
  CD3DPointLight *plight1 = new CD3DPointLight;
  if (plight1 == NULL)
    return false;
  plight1->Create(this); //= Standardfarbe und Intensität

  //= Farbe und Intensität der Punktlichtquelle festlegen
  if (!plight1->SetColorRGB(D3DVAL(1.82), D3DVAL(1.82), D3DVAL(1.82)))
    return false;

 //= Zur Szene hinzüfugen
  if (!plight1->AddToFrame(this))
    return false;

  //= Nötige Transformationen durchführen
  plight1->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(65), D3DVAL(0), D3DVAL(75));

  //= Geometrie anlegen
  CD3DFrame *scene = CreateShapeRev();
  if (scene == NULL)
    return false;

  if (!scene->AddToFrame(this))   //= Zur Szene hinzüfugen
    return false;

  CD3DMaterial *mat = new CD3DMaterial;

  if (!mat->Create(this, D3DVAL(1), D3DVAL(1), D3DVAL(1), D3DVAL(50)))
    return false;
  
  if (!SetMaterial(mat))
    return false;
  
  if (!SetSceneBackground(RGB(64, 255, 255)))
    return false;

  if (!SetTickEnable(true))
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
