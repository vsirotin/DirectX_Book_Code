// D3DVillageObj.cpp : implementation file
//

#include "stdafx.h"
#include "d3dVillageObj.h"

 
#include "d3dCameraFrame.h"
#include "d3dPyramidFrame.h"
#include "d3dCubeFrame.h"
#include "d3dPolygonFrame.h"

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
                                  
CD3DFrame *CD3DVillageObj::CreateHouse() 
  {
  //= Frame f�r ein Standardhaus
  CD3DFrame *house = new CD3DFrame;
  
  if (house == NULL)
    return NULL;

  if (!house->Create(this))
    return NULL;

  //= W�rfelobjekt
  CD3DCubeFrame *cube = new CD3DCubeFrame;
  
  if (!cube->Create(this, RGB(255, 255, 0)))
    return NULL;
  cube->AddToFrame(house);
  
  //= Verschieben entlang der Z-Achse 
  cube->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(1));

  //= Pyramide (Dach) anlegen
  CD3DPyramidFrame *pyramid = new CD3DPyramidFrame;
  pyramid->Create(this, RGB(255, 55, 55));
  pyramid->AddToFrame(house);
  
  //= Skalieren und Versetzen
  pyramid->AddScale(D3DRMCOMBINE_REPLACE, D3DVAL(1.2), D3DVAL(1.2), D3DVAL(1.5));
  pyramid->AddTranslation(D3DRMCOMBINE_AFTER, D3DVAL(0), D3DVAL(0), D3DVAL(2));

  return house;
  }
   
bool CD3DVillageObj::OnCreate() 
  {
  
  //= Geometrie erzeugen
  //= H�user 1 und 2
  CD3DFrame *house1 = CreateHouse();
  if (house1 == NULL)
    return false;

  CD3DFrame *house2 = CreateHouse();
  if (house2 == NULL)
    return false;

  if (!house1->AddToFrame(this)) //= Zur Szene hinzuf�gen
    return false;
  if (!house2->AddToFrame(this))
    return false;

	//= Kombinierte Transaktionen
  house1->AddCombTransform(D3DVAL(10), D3DVAL(10), D3DVAL(8), //= Skalieren 
                           D3DVAL(-PI / 2.0),  //= Winkel X
                           D3DVAL(+PI / 4.0),  //= Winkel Y
                           D3DVAL(0.0), //= Winkel Z - kein Drehen
                           D3DVAL(-40), D3DVAL(0), D3DVAL(70)); //= Verschiebung
  //= �hnliche Aktionen f�r das Haus 2
  house2->AddCombTransform(D3DVAL(10), D3DVAL(10), D3DVAL(8),
                           D3DVAL(-PI / 2.0),
                           D3DVAL(+PI / 8.0),
                           D3DVAL(0.0),
                           D3DVAL(20), D3DVAL(0), D3DVAL(70));

  //= Haus 3 ohne Dach. Verwenden des W�rfelbasisobjekts
  CD3DCubeFrame *house3 = new CD3DCubeFrame;
  
  if (!house3->Create(this))
    return false;
  if(!house3->AddToFrame(this))
    return false;

  house3->AddCombTransform(D3DVAL(10), D3DVAL(10), D3DVAL(8),
                           D3DVAL(-PI / 2.0),
                           D3DVAL(0.0), 
                           D3DVAL(0.0),
                           D3DVAL(70), D3DVAL(8), D3DVAL(100));
  
  //= Anlegen der Landschaftsfl�che
  D3DVECTOR vert_ground[] = {
    {D3DVAL(-1), D3DVAL(0), D3DVAL(0)},  
    {D3DVAL(-1), D3DVAL(0), D3DVAL(1)}, 
    {D3DVAL(1),  D3DVAL(0), D3DVAL(1)}, 
    {D3DVAL(1),  D3DVAL(0), D3DVAL(0)}
    };
  
  //= "Erde" festlegen
  CD3DPolygonFrame *land = new CD3DPolygonFrame;
  
  if (land == NULL)
    return false;

  if (!land->Create(this, 4, vert_ground, RGB(0, 155, 0)) ||
      !land->AddToFrame(this) ||
      !land->AddScale(D3DRMCOMBINE_REPLACE, D3DVAL(100), D3DVAL(1), D3DVAL(1000)))
    return false;
  
  //= Einstellung der Kamera
  CD3DCameraFrame *camera = GetCameraFrame();
  camera->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(5), D3DVAL(0));

  //= Kamera festlegen
  if (!SetCameraFront(1.0))
    return false;
  
  if (!SetCameraBack(3000))
    return false;

  if (!SetCameraField(3.0))
    return false;

  //= Hintergrundfarbe 
  if (!SetSceneBackground(RGB(64, 255, 255)))
    return false;

  //= Platz f�r weitere Experimente reserviert

  //= Anfang des Experimentes 1
  
  //= Rendering-Modus festlegen
  //if (!SetRenderQuality(D3DRMLIGHT_OFF | D3DRMFILL_SOLID 
  //                      | D3DRMSHADE_GOURAUD))
  //  return false;
  //= Ende des Experimentes 1

  //= Anfang des Experimentes 2
  //= Rendering-Modus festlegen
  //if (!SetRenderQuality(D3DRMLIGHT_ON | D3DRMFILL_WIREFRAME 
  //                      | D3DRMSHADE_GOURAUD))
  //  return false;
  //= Ende des Experimentes 1

  return true;
  }
