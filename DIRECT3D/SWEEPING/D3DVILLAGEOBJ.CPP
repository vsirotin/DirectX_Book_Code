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
                                  
CD3DFrame *CD3DVillageObj::CreateShape() 
  {

  CD3DFrame *shape = new CD3DFrame;
  
  if (shape == NULL)
    return NULL;

  if (!shape->Create(this))
    return NULL;

  D3DVECTOR base[] = {
    {D3DVAL(-6), D3DVAL(0), D3DVAL(0)},
    {D3DVAL(-5), D3DVAL(0), D3DVAL(3)},
    {D3DVAL(-3), D3DVAL(0), D3DVAL(5)},
    {D3DVAL(0), D3DVAL(0), D3DVAL(6)},
    {D3DVAL(3), D3DVAL(0), D3DVAL(5)},
    {D3DVAL(5), D3DVAL(0), D3DVAL(3)},
    {D3DVAL(6), D3DVAL(0), D3DVAL(0)},
    {D3DVAL(5), D3DVAL(0), D3DVAL(-3)},
    {D3DVAL(3), D3DVAL(0), D3DVAL(-5)},
    {D3DVAL(0), D3DVAL(0), D3DVAL(-6)},
    {D3DVAL(-3), D3DVAL(0), D3DVAL(-5)},
    {D3DVAL(-5), D3DVAL(0), D3DVAL(-3)}
    };
  D3DVECTOR top[] = {
    {D3DVAL(-4), D3DVAL(8), D3DVAL(0)},
    {D3DVAL(-3), D3DVAL(8), D3DVAL(3)},
    {D3DVAL(-3), D3DVAL(8), D3DVAL(3)},
    {D3DVAL(0), D3DVAL(8), D3DVAL(4)},
    {D3DVAL(3), D3DVAL(8), D3DVAL(3)},
    {D3DVAL(3), D3DVAL(8), D3DVAL(3)},
    {D3DVAL(4), D3DVAL(8), D3DVAL(0)},
    {D3DVAL(3), D3DVAL(8), D3DVAL(-3)},
    {D3DVAL(3), D3DVAL(8), D3DVAL(-3)},
    {D3DVAL(0), D3DVAL(8), D3DVAL(-4)},
    {D3DVAL(-3), D3DVAL(8), D3DVAL(-3)},
    {D3DVAL(-3), D3DVAL(8), D3DVAL(-3)}
    };
  D3DVECTOR top1[] = {
    {D3DVAL(-4), D3DVAL(8), D3DVAL(0)},
    {D3DVAL(-3), D3DVAL(8), D3DVAL(3)},
    {D3DVAL(0), D3DVAL(8), D3DVAL(4)},
    {D3DVAL(3), D3DVAL(8), D3DVAL(3)},
    {D3DVAL(4), D3DVAL(8), D3DVAL(0)},
    {D3DVAL(3), D3DVAL(8), D3DVAL(-3)},
    {D3DVAL(0), D3DVAL(8), D3DVAL(-4)},
    {D3DVAL(-3), D3DVAL(8), D3DVAL(-3)}
    };

  D3DVECTOR tip[] = {{D3DVAL(6), D3DVAL(16), D3DVAL(0)}};

  CD3DSweepingFrame *frag1 = new CD3DSweepingFrame;

  if (frag1 == NULL)
    return NULL;

  if (!frag1->Create(this, 12, 12, base, top, false, false))
    return NULL;
    
  if (!frag1->AddToFrame(shape))
    return NULL;
    
  if (!frag1->SetRotation(frag1, D3DVAL(0), D3DVAL(1), D3DVAL(0), D3DVAL(0.1)))
    return NULL;
                       
  CD3DSweepingFrame *frag2 = new CD3DSweepingFrame;

  if (frag2 == NULL)
    return NULL;
  
  if (!frag2->Create(this, 8, 1, top1, tip, true, false))
    return NULL;
    
  if (!frag2->AddToFrame(shape))
    return NULL;

  if (!frag2->SetRotation(frag2, D3DVAL(0), D3DVAL(1), D3DVAL(0), D3DVAL(-0.2)))
    return NULL;

  return shape;
  }
                                  
CD3DFrame *CD3DVillageObj::CreateShape1() 
  {

  CD3DFrame *shape = new CD3DFrame;
  
  if (shape == NULL)
    return NULL;

  if (!shape->Create(this))
    return NULL;

  //= Sweepingobjekt
  D3DVECTOR base[] = {
    {D3DVAL(-6), D3DVAL(0), D3DVAL(0)},
    {D3DVAL(-5), D3DVAL(0), D3DVAL(3)},
    {D3DVAL(-3), D3DVAL(0), D3DVAL(5)},
    {D3DVAL(0), D3DVAL(0), D3DVAL(6)},
    {D3DVAL(3), D3DVAL(0), D3DVAL(5)},
    {D3DVAL(5), D3DVAL(0), D3DVAL(3)},
    {D3DVAL(6), D3DVAL(0), D3DVAL(0)},
    {D3DVAL(5), D3DVAL(0), D3DVAL(-3)},
    {D3DVAL(3), D3DVAL(0), D3DVAL(-5)},
    {D3DVAL(0), D3DVAL(0), D3DVAL(-6)},
    {D3DVAL(-3), D3DVAL(0), D3DVAL(-5)},
    {D3DVAL(-5), D3DVAL(0), D3DVAL(-3)}
    };
  D3DVECTOR top[] = {
    {D3DVAL(-4), D3DVAL(8), D3DVAL(0)},
    {D3DVAL(-3), D3DVAL(8), D3DVAL(3)},
    {D3DVAL(-3), D3DVAL(8), D3DVAL(3)},
    {D3DVAL(0), D3DVAL(4), D3DVAL(4)},
    {D3DVAL(3), D3DVAL(4), D3DVAL(3)},
    {D3DVAL(3), D3DVAL(4), D3DVAL(3)},
    {D3DVAL(4), D3DVAL(4), D3DVAL(0)},
    {D3DVAL(3), D3DVAL(4), D3DVAL(-3)},
    {D3DVAL(3), D3DVAL(4), D3DVAL(-3)},
    {D3DVAL(0), D3DVAL(4), D3DVAL(-4)},
    {D3DVAL(-3), D3DVAL(4), D3DVAL(-3)},
    {D3DVAL(-3), D3DVAL(4), D3DVAL(-3)}
    };
  D3DVECTOR top1[] = {
    {D3DVAL(-4), D3DVAL(8), D3DVAL(0)},
    {D3DVAL(-3), D3DVAL(8), D3DVAL(3)},
    {D3DVAL(-3), D3DVAL(8), D3DVAL(3)},
    {D3DVAL(0), D3DVAL(8), D3DVAL(4)},
    {D3DVAL(3), D3DVAL(8), D3DVAL(3)},
    {D3DVAL(3), D3DVAL(8), D3DVAL(3)},
    {D3DVAL(4), D3DVAL(8), D3DVAL(0)},
    {D3DVAL(3), D3DVAL(8), D3DVAL(-3)},
    {D3DVAL(3), D3DVAL(8), D3DVAL(-3)},
    {D3DVAL(0), D3DVAL(8), D3DVAL(-4)},
    {D3DVAL(-3), D3DVAL(8), D3DVAL(-3)},
    {D3DVAL(-3), D3DVAL(8), D3DVAL(-3)}
    };
  D3DVECTOR top2[] = {
    {D3DVAL(-4), D3DVAL(12), D3DVAL(0)},
    {D3DVAL(-3), D3DVAL(12), D3DVAL(3)},
    {D3DVAL(0), D3DVAL(12), D3DVAL(4)},
    {D3DVAL(3), D3DVAL(12), D3DVAL(3)},
    {D3DVAL(4), D3DVAL(12), D3DVAL(0)},
    {D3DVAL(3), D3DVAL(12), D3DVAL(-3)},
    {D3DVAL(0), D3DVAL(12), D3DVAL(-4)},
    {D3DVAL(-3), D3DVAL(12), D3DVAL(-3)}
    };
  D3DVECTOR tip[] = {{D3DVAL(6), D3DVAL(16), D3DVAL(0)}};

  CD3DSweepingFrame *frag1 = new CD3DSweepingFrame;

  if (frag1 == NULL)
    return NULL;

  if (!frag1->Create(this, 12, 12, base, top, false))
    return NULL;
    
  if (!frag1->AddToFrame(shape))
    return NULL;
    
  if (!frag1->SetRotation(frag1, D3DVAL(0), D3DVAL(1), D3DVAL(0), D3DVAL(0.1)))
    return NULL;
                       
  CD3DSweepingFrame *frag2 = new CD3DSweepingFrame;

  if (frag2 == NULL)
    return NULL;
  
  if (!frag2->Create(this, 8, 1, top2, tip, true))
    return NULL;
    
  if (!frag2->AddToFrame(shape))
    return NULL;

  if (!frag2->SetRotation(frag2, D3DVAL(0), D3DVAL(1), D3DVAL(0), D3DVAL(-0.2)))
    return NULL;
  
  return shape;
  }
   
bool CD3DVillageObj::OnCreate() 
  {
  //= Umgebungslicht festlegen
  if (!SetAmbientLightRGB(D3DVAL(0.35), D3DVAL(0.35), D3DVAL(0.35)))
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
  plight->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(20), D3DVAL(20));

  //= Punktlichtquelle anlegen
  CD3DPointLight *plight1 = new CD3DPointLight;
  if (plight1 == NULL)
    return false;
  plight1->Create(this); //= Standardfarbe und Intensität

  //= Farbe und Intensität der Punktlichtquelle festlegen
  if (!plight1->SetColorRGB(D3DVAL(0.82), D3DVAL(0.82), D3DVAL(0.82)))
    return false;

  //= Zur Szene hinzüfugen
  if (!plight1->AddToFrame(this))
    return false;

  //= Nötige Transformation durchführen
  plight1->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(-20), D3DVAL(30));

  //= Geometrie anlegen
  CD3DFrame *scene = CreateShape();
  if (scene == NULL)
    return false;

  if (!scene->AddToFrame(this))   //= Zur Szene hinzüfugen
    return false;

  scene->AddCombTransform(D3DVAL(2), D3DVAL(2), D3DVAL(2),
                          D3DVAL(0), D3DVAL(0), D3DVAL(0),
                          D3DVAL(20), D3DVAL(-10), D3DVAL(50));

  CD3DFrame *scene1 = CreateShape1();
  if (scene1 == NULL)
    return false;

  if (!scene1->AddToFrame(this))   //= Zur Szene hinzüfugen
    return false;

  scene1->AddCombTransform(D3DVAL(2), D3DVAL(2), D3DVAL(2),
                          D3DVAL(0), D3DVAL(0), D3DVAL(0),
                          D3DVAL(-20), D3DVAL(-10), D3DVAL(50));

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
