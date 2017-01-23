// D3DBasicObj.cpp : implementation file
//

#include "stdafx.h"
#include "d3dBasicObj.h"


#include "d3dPolygonFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DBasicObj

CD3DBasicObj::CD3DBasicObj()
  {
  }

CD3DBasicObj::~CD3DBasicObj()
  {
  }

bool CD3DBasicObj::OnCreate() 
  {
  //= Geometrie anlegen
  CD3DPolygonFrame *pTriangle = new CD3DPolygonFrame;
  
  //= Dreiecks-Geometrie
  D3DVECTOR vert[] = {
    {D3DVAL(20.0),  D3DVAL(-15.0),  D3DVAL(50.0)},  //= Ecke 0
    {D3DVAL(-20.0), D3DVAL(-15.0),  D3DVAL(50.0)},  //= Ecke 1
    {D3DVAL(0.0),   D3DVAL(20.0), D3DVAL(50.0)}   //= Ecke 2
  };

  if (!pTriangle->Create(this, 3, vert))
    return false;

  //= Frame zur Szene hinzufügen
  if (!pTriangle->AddToFrame(this))
    return false;

  //= Hintergrundfarbe festlegen
  if (!SetSceneBackground(RGB(64, 255, 255)))
    return false;

  //= Kamera festlegen
  if (!SetCameraFront(1.0))
    return false;

  if (!SetCameraBack(500.0))
    return false;

  if (!SetCameraField(1.0))
    return false;

  return true;
  }