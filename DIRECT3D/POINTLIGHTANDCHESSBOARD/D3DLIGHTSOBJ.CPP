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
  //= Schachtbrett von der Landschaft
  //= Sehr langsame Version
  // CD3DFrame *pPlane = CD3DGeomArsenal::CreateChessBoard(this, 100, 100,
  //                                       RGB(19, 211, 19), RGB(19, 211, 19));
  
  //= Normale Geschwindigkeit
  CD3DFrame *pPlane = CD3DGeomArsenal::CreateChessBoard(this, 30, 100,
		RGB(19, 211, 19), RGB(19, 211, 19));


  if (pPlane == NULL)
    return false;

  //= Frame zur Szene hinzufügen
  if (!pPlane->AddToFrame(this))
    return false;

  //= Lage festlegen 
  if (!pPlane->AddScale(D3DRMCOMBINE_REPLACE, D3DVAL(200), D3DVAL(1), D3DVAL(200)))
    return false;
  if (!pPlane->AddTranslation(D3DRMCOMBINE_AFTER, 
                         D3DVAL(-100), D3DVAL(-15), D3DVAL(-50)))
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
  
  //= Skalieren  und in die richtige Lage versetzen
  if (!tree->AddCombTransform(D3DVAL(20), D3DVAL(20), D3DVAL(30),
                          D3DVAL(-PI / 2.0), D3DVAL(0.5), D3DVAL(0),
                          D3DVAL(20), D3DVAL(-15), D3DVAL(60)))
    return false;

  CD3DFrame *tree1 = CD3DGeomArsenal::CreateTree(this, vert_planes, hor_planes);
  if (tree1 == NULL)
    return false;

  if (!tree1->AddToFrame(this))
    return false;
  
//= Skalieren  und in die richtige Lage versetzen
  if (!tree1->AddCombTransform(D3DVAL(25), D3DVAL(25), D3DVAL(40),
                          D3DVAL(-PI / 2.0), D3DVAL(0.5), D3DVAL(0),
                          D3DVAL(-20), D3DVAL(-15), D3DVAL(120)))
    return false;

  CD3DFrame *tree2 = CD3DGeomArsenal::CreateTree(this, vert_planes, hor_planes);
  if (tree2 == NULL)
    return false;

  if (!tree2->AddToFrame(this))
    return false;
  
//= Skalieren  und in die richtige Lage versetzen
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
  //= Experimentsszene anlegen
  if (!CreateLightScene(25, 9))
    return false;

  //= Umgebungslicht festlegen
  if (!SetAmbientLightRGB(D3DVAL(0.65), D3DVAL(0.65), D3DVAL(0.65)))
    return false;

  //= Punktlichtquelle anlegen
  CD3DPointLight *plight = new CD3DPointLight;
  if (plight == NULL)
    return false;

  if (!plight->Create(this)) //= Standardfarbe und Intensität
    return false;

  //= Farbe und Intensität der Punktlichtquelle festlegen
  if (!plight->SetColorRGB(D3DVAL(2.12), D3DVAL(2.12), D3DVAL(2.12)))
    return false;

 //= Zur Szene hinzüfugen
  if (!plight->AddToFrame(this))
    return false;

  //= Nötige Transformationen durchführen
  if (!plight->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(30), D3DVAL(60)))
    return false;

  //= Experimente  mit der Abschwächung
  //= plight->SetAttenuation(D3DVAL(5), D3DVAL(0), D3DVAL(0));
  //= plight->SetAttenuation(D3DVAL(5), D3DVAL(0), D3DVAL(5));
  //= plight->SetAttenuation(D3DVAL(5), D3DVAL(5), D3DVAL(10));

  return true;
  }
