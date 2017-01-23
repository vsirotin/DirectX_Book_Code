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
  //= Erste Pilz mit sehr grober Approximierung
  CD3DFrame *mushroom1 = CD3DGeomArsenal::CreateMushroom(this, 4, 2);
  if (mushroom1 == NULL)
    return false;

  //= Zur Szene hinzufügen
  if (!mushroom1->AddToFrame(this))
    return false;
  
  //= Drehen und verschieben
  mushroom1->AddCombTransform(D3DVAL(1), D3DVAL(1), D3DVAL(1), //= Kein Skalieren 
                           D3DVAL(-PI / 2.0),  //= Winkel X
                           D3DVAL(0.0),        //= 
                           D3DVAL(0.0),        //= 
                           D3DVAL(-3), D3DVAL(0), D3DVAL(10)); //= Verschiebung
  
  //= Zweiter Pilz mit mittlerer Aproximierung
  CD3DFrame *mushroom2 = CD3DGeomArsenal::CreateMushroom(this, 12, 5);
  if (mushroom2 == NULL)
    return false;

 //= Zur Szene hinzüfugen
  if (!mushroom2->AddToFrame(this))
    return false;
  
  //= Skalieren , Drehen und Verschiebenung
  mushroom2->AddCombTransform(D3DVAL(2), D3DVAL(2), D3DVAL(2),
                           D3DVAL(-PI / 3.0), D3DVAL(0.0), D3DVAL(0.0),
                           D3DVAL(0), D3DVAL(-3), D3DVAL(20));
  //= Dritter Pilz mit guter Approximierung
  CD3DFrame *mushroom3 = CD3DGeomArsenal::CreateMushroom(this, 32, 7);
  if (mushroom3 == NULL)
    return false;

 //= Zur Szene hinzüfugen
  if (!mushroom3->AddToFrame(this))
    return false;
  
  //= Skalieren , Drehen und Verschieben
  mushroom3->AddCombTransform(D3DVAL(3), D3DVAL(3), D3DVAL(3),
                           D3DVAL(-(PI / 2.0 + PI / 8.0)), 
                           D3DVAL(0.0), D3DVAL(0.0),
                           D3DVAL(5), D3DVAL(-4), D3DVAL(20));
  if (!SetSceneBackground(RGB(64, 255, 255)))
    return false;

  if (!SetCameraFront(1.5))
    return false;

  if (!SetCameraBack(500.0))
    return false;

  if (!SetCameraField(1.0))
    return false;
  
  return true;
  }
