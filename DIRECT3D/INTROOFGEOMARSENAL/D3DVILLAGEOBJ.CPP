// D3DVillageObj.cpp : implementation file
//

#include "stdafx.h"
#include "d3dVillageObj.h"

 
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
                                  
bool CD3DVillageObj::OnCreate() 
  {
  
  //= Geometrie erzeugen
  //= Häuser 1 und 2
  CD3DFrame *house1 = CD3DGeomArsenal::CreateHouse(this);
  if (house1 == NULL)
    return false;

  CD3DFrame *house2 = CD3DGeomArsenal::CreateHouse(this);
  if (house2 == NULL)
    return false;

  if (!house1->AddToFrame(this)) //= Zur Szene hinzüfugen
    return false;
  if (!house2->AddToFrame(this))
    return false;

  house1->AddCombTransform(D3DVAL(10), D3DVAL(10), D3DVAL(8), //= Skalieren 
                           D3DVAL(-PI / 2.0),  //= Winkel X
                           D3DVAL(+PI / 4.0),  //= Winkel Y
                           D3DVAL(0.0), //= Winkel Z - kein Drehen
                           D3DVAL(-40), D3DVAL(0), D3DVAL(70)); //= Verschiebung
  //= Ähnliche Aktionen für das Haus 2
  house2->AddCombTransform(D3DVAL(10), D3DVAL(10), D3DVAL(8),
                           D3DVAL(-PI / 2.0),
                           D3DVAL(+PI / 8.0),
                           D3DVAL(0.0),
                           D3DVAL(20), D3DVAL(0), D3DVAL(70));

  //= Haus 3 ohne Dach
  CD3DCubeFrame *house3 = new CD3DCubeFrame;
  
  if (!house3->Create(this))
    return false;
  if(!house3->AddToFrame(this))
    return false;

  house3->AddCombTransform(D3DVAL(10), D3DVAL(10), D3DVAL(8),
                           D3DVAL(-PI / 2.0),
                           D3DVAL(0.0), //= kein Y-Winkel
                           D3DVAL(0.0),
                           D3DVAL(70), D3DVAL(8), D3DVAL(100));
  //= Daten für Landschaft-Fläche
  D3DVECTOR vert_ground[] = {
    {D3DVAL(-1), D3DVAL(0), D3DVAL(0)},  
    {D3DVAL(-1), D3DVAL(0), D3DVAL(1)}, 
    {D3DVAL(1),  D3DVAL(0), D3DVAL(1)}, 
    {D3DVAL(1),  D3DVAL(0), D3DVAL(0)}
    };
  
  //= "Erde"
  CD3DPolygonFrame *land = new CD3DPolygonFrame;
  
  if (land == NULL)
    return false;

  if (!land->Create(this, 4, vert_ground, RGB(0, 155, 0)) ||
      !land->AddToFrame(this) ||
      !land->AddScale(D3DRMCOMBINE_REPLACE, D3DVAL(100), D3DVAL(1), D3DVAL(1000)))
    return false;
  
  //= Kamera festlegen
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
  
  //= Platz für weitere Experimente reserviert

  //= Experiment 1
   //if (!SetRenderQuality(D3DRMLIGHT_OFF | D3DRMFILL_SOLID 
  //                      | D3DRMSHADE_GOURAUD))
  //  return false;
 

  //= Experiment 2
  
   //if (!SetRenderQuality(D3DRMLIGHT_ON | D3DRMFILL_WIREFRAME 
  //                      | D3DRMSHADE_GOURAUD))
  //  return false;
 

  //= Experiment mit Parallelprojektion
  //if (!SetProjection(D3DRMPROJECT_ORTHOGRAPHIC))
  //  return false;
  //if (!SetCameraField(100.0))
  //  return false;
  // Kamera um X-Achse drehen
  //camera->AddRotation(D3DRMCOMBINE_AFTER, 
  //               D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(PI / 10.0));
 

  return true;
  }
