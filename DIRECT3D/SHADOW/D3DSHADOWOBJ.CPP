// d3dShadowObj.cpp : implementation file
//

#include "stdafx.h"
#include "d3dShadowObj.h"

 
#include "d3dGeomArsenal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DShadowObj

CD3DShadowObj::CD3DShadowObj()
  {
  }

CD3DShadowObj::~CD3DShadowObj()
  {
  }
                                 
bool CD3DShadowObj::OnCreate()
  {
  //= Zwei vertikale Wände anlegen
  D3DVECTOR left_wall[] = {
    {D3DVAL(-70), D3DVAL(-22), D3DVAL(10)},
    {D3DVAL(-70), D3DVAL(48),  D3DVAL(10)}, 
    {D3DVAL(-20), D3DVAL(48),  D3DVAL(60)}, 
    {D3DVAL(-20), D3DVAL(-22), D3DVAL(60)}};
  D3DVECTOR right_wall[] = {
    {D3DVAL(-20), D3DVAL(-22), D3DVAL(60)},  
    {D3DVAL(-20), D3DVAL(48),  D3DVAL(60)}, 
    {D3DVAL(70),  D3DVAL(48),  D3DVAL(60)},        
    {D3DVAL(70),  D3DVAL(-22), D3DVAL(60)}};

  CD3DPolygonFrame *lwall = new CD3DPolygonFrame;
  if (lwall == NULL)
    return false;

  if (!lwall->Create(this, 4, left_wall, RGB(255, 255, 0)))
    return false;

  //= Wände dem Frame hinzufügen
  if (!lwall->AddToFrame(this))
    return false;

  CD3DPolygonFrame *rwall = new CD3DPolygonFrame;
  if (rwall == NULL)
    return false;

  if (!rwall->Create(this, 4, right_wall, RGB(0, 0, 255)))
    return false;

  
  if (!rwall->AddToFrame(this))
    return false;
  
  //= Würfel anlegen
  CD3DCubeFrame *cube = new CD3DCubeFrame;
  if (cube == NULL)
    return false;

  if (!cube->Create(this, RGB(255, 0, 0)))
    return false;

  //= Würfel dem Frame hinzufügen
  if (!cube->AddToFrame(this))
    return false;
  
  //= Lage festlegen
  if (!cube->AddCombTransform(D3DVAL(10), D3DVAL(10), D3DVAL(10),
                  D3DVAL(0), D3DVAL(0), D3DVAL(0),
                  D3DVAL(20), D3DVAL(-6), D3DVAL(30)))
    return false;

  //= Umgebungslicht festlegen
  if (!SetAmbientLightRGB(D3DVAL(0), D3DVAL(0), D3DVAL(0)))
    return false;

  //= Lichtquelle anlegen
  CD3DDirectionalLight *dlight = new CD3DDirectionalLight;
  if (dlight == NULL)
    return false;

  if (!dlight->Create(this))
    return false;

  //= Farbe und Intensität der gerichteten Lichtquelle
  if (!dlight->SetColorRGB(D3DVAL(4), D3DVAL(4), D3DVAL(4)))
    return false;

  //= Lichtquelle dem Frame hinzufügen
  if (!dlight->AddToFrame(this))
    return false;

  if (!dlight->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(1), D3DVAL(0), 
                                            D3DVAL(-PI / 3.0)))
    return false;

  //= Manipulationen mit der Kamera und dem Viewport
  if (!SetSceneBackgroundRGB(D3DVAL(0.3), D3DVAL(0.8), D3DVAL(0.4)))
    return false;

  if (!SetCameraFront(5.0))
    return false;
  if (!SetCameraBack(500.0))
    return false;
  if (!SetCameraField(10.0))
    return false;
  
  //= Normale zur linken Wand definieren
  D3DVECTOR norm;
  NormalFromFace(&left_wall[0], &left_wall[1], &left_wall[2], &norm);
  
  //= Schatten anlegen 
  if (!cube->AddShadow(dlight, D3DVAL(left_wall[0].x + 0.5 * norm.x), 
                          D3DVAL(left_wall[0].y + 0.5 * norm.y), 
                          D3DVAL(left_wall[0].z + 0.5 * norm.z), 
                          -norm.x, -norm.y, -norm.z))
    return false;

  //= Schatten des Wurfels auf der rechten Wand definieren
  if (!cube->AddShadow(dlight, right_wall[0].x, 
                          right_wall[0].y, 
                          right_wall[0].z, 
                          D3DVAL(0), D3DVAL(0), D3DVAL(1)))
    return false;

  //= Dieses Experiment muß man nach dem Kennenlernen der Animation durchführen
  /*
  if (!cube->SetRotation(cube, D3DVAL(0), D3DVAL(1), D3DVAL(1), 
                                            D3DVAL(0.1)))
    return false;
  
  if (!SetMoveCallback())
    return false;

  if (!SetTickEnable(true))
    return false;
  */

  return true;
  }

