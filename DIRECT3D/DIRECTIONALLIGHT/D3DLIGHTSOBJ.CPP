// d3dLightsObj.cpp : implementation file
//

#include "stdafx.h"
#include "d3dLightsObj.h"

 
#include "d3dGeomArsenal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DLightsObj

CD3DLightsObj::CD3DLightsObj()
  {
  }

CD3DLightsObj::~CD3DLightsObj()
  {
  }
                                 
bool CD3DLightsObj::CreateLightScene(int vert_planes, int hor_planes)
  {
  //= Landschaft-Fläche
  CD3DPolygonFrame *pPlane = new CD3DPolygonFrame;
  if (pPlane == NULL)
    return false;
  
  //= Daten für die Landschaft
  D3DVECTOR vert[] = {
    {D3DVAL(-1.0),  D3DVAL(-1.0),  D3DVAL(1.0)},
    {D3DVAL(1.0),   D3DVAL(-1.0),  D3DVAL(1.0)},
    {D3DVAL(1.0),   D3DVAL(-1.0),  D3DVAL(-1.0)},
    {D3DVAL(-1.0),  D3DVAL(-1.0),  D3DVAL(-1.0)}};

  if (!pPlane->Create(this, 4, vert, RGB(19, 211, 19)))
    return false;

  //= Frame zur Szene hinzufügen
  if (!pPlane->AddToFrame(this))
    return false;
  
  //= Lage festlegen 
  if (!pPlane->AddScale(D3DRMCOMBINE_REPLACE, D3DVAL(200), D3DVAL(15), D3DVAL(200)))
    return false;

  //= Haus erzeugen und auf der Landschaft-Fläche plazieren
  CD3DFrame *house = CD3DGeomArsenal::CreateHouse(this);
  if (house == NULL)
    return false;

  if (!house->AddToFrame(this))
    return false;

  //= Reale Größe und Lage festlegen
  if (!house->AddCombTransform(D3DVAL(10), D3DVAL(10), D3DVAL(10),
                          D3DVAL(-PI / 2.0), D3DVAL(PI / 5.0), D3DVAL(0),
                          D3DVAL(-20), D3DVAL(-15), D3DVAL(70)))
    return false;

  CD3DFrame *tree = CD3DGeomArsenal::CreateTree(this, vert_planes, hor_planes);
  if (tree == NULL)
    return false;

  if (!tree->AddToFrame(this))
    return false;
  
  //= Skalieren und in die richtige Lage versetzen
  if (!tree->AddCombTransform(D3DVAL(20), D3DVAL(20), D3DVAL(30),
                          D3DVAL(-PI / 2.0), D3DVAL(0.5), D3DVAL(0),
                          D3DVAL(20), D3DVAL(-15), D3DVAL(60)))
    return false;

  CD3DFrame *tree1 = CD3DGeomArsenal::CreateTree(this, vert_planes, hor_planes);
  if (tree1 == NULL)
    return false;

  if (!tree1->AddToFrame(this))
    return false;
  
  //= Skalieren und in die richtige Lage versetzen
  if (!tree1->AddCombTransform(D3DVAL(25), D3DVAL(25), D3DVAL(40),
                          D3DVAL(-PI / 2.0), D3DVAL(0.5), D3DVAL(0),
                          D3DVAL(-20), D3DVAL(-15), D3DVAL(120)))
    return false;

  CD3DFrame *tree2 = CD3DGeomArsenal::CreateTree(this, vert_planes, hor_planes);
  if (tree2 == NULL)
    return false;

  if (!tree2->AddToFrame(this))
    return false;
  
  //= Skalieren und in die richtige Lage versetzen
  if (!tree2->AddCombTransform(D3DVAL(30), D3DVAL(30), D3DVAL(45),
                          D3DVAL(-PI / 2.0), D3DVAL(0.5), D3DVAL(0),
                          D3DVAL(20), D3DVAL(-15), D3DVAL(130)))
    return false;

  if (!SetCameraParam(1.0, 1.0, 1500.0, RGB(128, 198, 238)))
    return false;

  return true;
  }

bool CD3DLightsObj::OnCreate()
  {
  //= Szene anlegen 
  if (!CreateLightScene(25, 9))
    return false;
/* //= Experimente:    
  //= Szene mit grober Approximierung des Baumes
  //= Experiment 1
  if (!CreateLightScene(10, 3))
    return false;
    
  //= Szene mit den Schatten
  //= Experiment 2
  if (!SetRenderQuality(D3DRMLIGHT_ON | D3DRMFILL_SOLID | D3DRMSHADE_FLAT))
    return false;
*/
  //= Farbe und Intensität des  Umgebungslichsts anlegen 
  if (!SetAmbientLightRGB(D3DVAL(0.65), D3DVAL(0.65), D3DVAL(0.65)))
    return false;

  //= Gerichtete Lichtquelle anlegen
  CD3DDirectionalLight *dlight = new CD3DDirectionalLight;
  if (dlight == NULL)
    return false;
  
  if (!dlight->Create(this)) //= Standardfarbe und Intensität
    return false;

  //= Farbe der Lichtquelle festlegen
  if (!dlight->SetColorRGB(D3DVAL(2.71), D3DVAL(4.27), D3DVAL(3.84)))
    return false;

  //= Lichtquelle dem Frame hinzufügen
  if (!dlight->AddToFrame(this))
    return false;

  //= Richtung der Lichtquelle festlegen
  if (!dlight->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(1), D3DVAL(0), 
                                           D3DVAL(-PI / 3.0)))
    return false;
  if (!dlight->AddRotation(D3DRMCOMBINE_AFTER, D3DVAL(0), D3DVAL(0), D3DVAL(1), 
                                           D3DVAL(PI / 4.0 - 0.5)))
    return false;
/*
  //= Lichtstrahlen kommen von  +Z
  //= Experiment 3
  if (!dlight->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(1), D3DVAL(0), 
                                                 D3DVAL(-PI)))
    return false;
  //= Experiment 4
  //= kein Umgebungslicht
  SetAmbientLightRGB(D3DVAL(0), D3DVAL(0), D3DVAL(0));
  //= Schwartzer Viewport
  SetSceneBackgroundRGB(D3DVAL(0), D3DVAL(0), D3DVAL(0));
*/

  return true;
  }
