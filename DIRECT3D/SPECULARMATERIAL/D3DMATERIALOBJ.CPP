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

  if (!pPlane->AddCombTransform(D3DVAL(100), D3DVAL(1), D3DVAL(100),
                       D3DVAL(0), D3DVAL(0), D3DVAL(0),
                       D3DVAL(-50), D3DVAL(-15), D3DVAL(0)))
    return false;

  //= Materialparameter festlegen
  CD3DMaterial *matPlane = new CD3DMaterial;
  if (matPlane == NULL)
    return false;

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
  if (!wind->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(-0.5), D3DVAL(1.1), D3DVAL(0.5)))
    return false;

  if (!pH->AddCombTransform(D3DVAL(10), D3DVAL(10), D3DVAL(10),
                       D3DVAL(-PI / 2.0), D3DVAL(PI / 5.0), D3DVAL(0),
                       D3DVAL(-20), D3DVAL(-15), D3DVAL(50)))
    return false;

  //= Material des Fensters festlegen
  CD3DMaterial *matwind = new CD3DMaterial;
  if (matwind == NULL)
    return false;

  if (!matwind->Create(this, D3DVAL(1), D3DVAL(1), D3DVAL(1), D3DVAL(120),
                             D3DVAL(0.9), D3DVAL(0.9), D3DVAL(0)))
    return false;

  if (!wind->SetMaterial(matwind))
    return false;

  //= Bäume
  int vert_planes = 24;
  int hor_planes = 6;

  CD3DFrame *tree = CD3DGeomArsenal::CreateTree(this, vert_planes, hor_planes);
  if (tree == NULL)
    return false;

  if (!tree->AddToFrame(this))
    return false;
  
  //= Transformationen
  if (!tree->AddCombTransform(D3DVAL(20), D3DVAL(20), D3DVAL(30),
                          D3DVAL(-PI / 2.0), D3DVAL(0.5), D3DVAL(0),
                          D3DVAL(20), D3DVAL(-15), D3DVAL(30)))
    return false;

  CD3DFrame *tree1 = CD3DGeomArsenal::CreateTree(this, vert_planes, hor_planes);
  if (tree1 == NULL)
    return false;

  if (!tree1->AddToFrame(this))
    return false;
  
   if (!tree1->AddCombTransform(D3DVAL(25), D3DVAL(25), D3DVAL(40),
                          D3DVAL(-PI / 2.0), D3DVAL(0.5), D3DVAL(0),
                          D3DVAL(-20), D3DVAL(-15), D3DVAL(95)))
    return false;

  CD3DFrame *tree2 = CD3DGeomArsenal::CreateTree(this, vert_planes, hor_planes);
  if (tree2 == NULL)
    return false;

  if (!tree2->AddToFrame(this))
    return false;
  
   if (!tree2->AddCombTransform(D3DVAL(30), D3DVAL(30), D3DVAL(45),
                          D3DVAL(-PI / 2.0), D3DVAL(0.5), D3DVAL(0),
                          D3DVAL(20), D3DVAL(-15), D3DVAL(90)))
    return false;

  //= Material der Bäume
  CD3DMaterial *matTree = new CD3DMaterial;
  if (matTree == NULL)
    return false;

  if (!matTree->Create(this, D3DVAL(1), D3DVAL(1), D3DVAL(1), D3DVAL(60)))
    return false;
  
  if (!tree->SetMaterial(matTree))
    return false;

  if (!tree1->SetMaterial(matTree))
    return false;

  //= Lichtquellen
  //= Punktlichtquelle

  CD3DPointLight *plight = new CD3DPointLight;
  if (plight == NULL)
    return false;

  if (!plight->Create(this))
    return false;

  if (!plight->SetColorRGB(D3DVAL(1.12), D3DVAL(1.12), D3DVAL(1.12)))
    return false;

  if (!plight->AddToFrame(this))
    return false;

  if (!plight->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(-5), D3DVAL(30)))
    return false;

  //= Gerichtetes Licht (Sonne)
  CD3DDirectionalLight *dlight = new CD3DDirectionalLight;
  if (dlight == NULL)
    return false;
  
  if (!dlight->Create(this))
    return false;

   if (!dlight->SetColorRGB(D3DVAL(1.45), D3DVAL(1.45), D3DVAL(1.45)))
    return false;

   if (!dlight->AddToFrame(this))
    return false;

   
  if (!dlight->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(PI / 3.0 * 2.0)))
    return false;

  //= Kameraparameter festlegen
  CD3DCameraFrame *camera = GetCameraFrame();
  if (camera == NULL)
    return false;
  
  if (!camera->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(0), D3DVAL(0), 
                                            D3DVAL(PI / 9.0)))
    return false;

  if (!camera->AddTranslation(D3DRMCOMBINE_AFTER, D3DVAL(0), D3DVAL(15), D3DVAL(-10)))
    return false;

  if (!SetCameraParam(2.0, 1.0, 1500.0, RGB(128, 198, 238), RGB(0, 0, 0)))
    return false;

  return true;
  }