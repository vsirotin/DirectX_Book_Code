// d3dMaterialObj.cpp : implementation file
//

#include "stdafx.h"
#include "d3dDecalObj.h"

 
#include "d3dGeomArsenal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static char *ResolveName(char *name)
  {
  static char newname[_MAX_PATH];
  static char *path[] = {"", "data\\", 
                         "..\\", "..\\data\\", 
                         "..\\..\\", "..\\..\\data\\",
                         "..\\..\\..\\", "..\\..\\..\\data\\",
                         "..\\..\\..\\..\\", "..\\..\\..\\..\\data\\"
                        };

  CFileStatus status;

  for (int i = 0; i < sizeof(path) / sizeof(path[0]); i++)
    {
    strcpy(newname, path[i]);
    strcat(newname, name);

    if (CFile::GetStatus(newname, status))
      return newname;
    }

  sprintf(newname, "FILE: %s not found", name);
  AfxMessageBox(newname);

  return name;
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DDecalObj

CD3DDecalObj::CD3DDecalObj()
  {
  }

CD3DDecalObj::~CD3DDecalObj()
  {
  }

bool CD3DDecalObj::OnCreate()
  {
  //= Schachbrett von der Landschaft
  CD3DFrame *pPlane = CD3DGeomArsenal::CreateChessBoard(this, 10, 10,
                                         RGB(255, 255, 120), RGB(255, 255, 120));
  if (pPlane == NULL)
    return false;

  if (!pPlane->AddToFrame(this))
    return false;

  if (!pPlane->AddCombTransform(D3DVAL(100), D3DVAL(1), D3DVAL(100),
                       D3DVAL(0), D3DVAL(0), D3DVAL(0),
                       D3DVAL(-50), D3DVAL(-15), D3DVAL(0)))
    return false;

  //= Material der Fläche vorbereiten
  CD3DMaterial *matPlane = new CD3DMaterial;
  if (matPlane == NULL)
    return false;

  if (!matPlane->Create(this, D3DVAL(1), D3DVAL(1), D3DVAL(1), D3DVAL(5)))
    return false;

  if (!pPlane->SetMaterial(matPlane, false))
    return false;

  //= Frame für ein Haus mit einem Fenster
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

  //= Fenster auf die Wand kleben
  if (!wind->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(-0.5), D3DVAL(1.1), D3DVAL(0.5)))
    return false;

  if (!pH->AddCombTransform(D3DVAL(10), D3DVAL(10), D3DVAL(10),
                       D3DVAL(-PI / 2.0), D3DVAL(PI / 5.0), D3DVAL(0),
                       D3DVAL(-20), D3DVAL(-15), D3DVAL(50)))
    return false;

  //= Material des Fensters vorbereiten
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
  
//= Skalieren  und in die richtige Lage versetzen
  if (!tree->AddCombTransform(D3DVAL(20), D3DVAL(20), D3DVAL(30),
                          D3DVAL(-PI / 2.0), D3DVAL(0.5), D3DVAL(0),
                          D3DVAL(20), D3DVAL(-15), D3DVAL(30)))
    return false;

  CD3DFrame *tree1 = CD3DGeomArsenal::CreateTree(this, vert_planes, hor_planes);
  if (tree1 == NULL)
    return false;

  if (!tree1->AddToFrame(this))
    return false;
  
//= Skalieren  und in die richtige Lage versetzen
  if (!tree1->AddCombTransform(D3DVAL(25), D3DVAL(25), D3DVAL(40),
                          D3DVAL(-PI / 2.0), D3DVAL(0.5), D3DVAL(0),
                          D3DVAL(-20), D3DVAL(-15), D3DVAL(95)))
    return false;

  CD3DFrame *tree2 = CD3DGeomArsenal::CreateTree(this, vert_planes, hor_planes);
  if (tree2 == NULL)
    return false;

  if (!tree2->AddToFrame(this))
    return false;
  
//= Skalieren  und in die richtige Lage versetzen
  if (!tree2->AddCombTransform(D3DVAL(30), D3DVAL(30), D3DVAL(45),
                          D3DVAL(-PI / 2.0), D3DVAL(0.5), D3DVAL(0),
                          D3DVAL(20), D3DVAL(-15), D3DVAL(90)))
    return false;

  //= Material von Bäumen
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
  //= Punktlichtquelle anlegen
  CD3DPointLight *plight = new CD3DPointLight;
  if (plight == NULL)
    return false;

  if (!plight->Create(this))
    return false;

  //= Farbe und Intensität der Punktlichtquelle festlegen
  if (!plight->SetColorRGB(D3DVAL(1.12), D3DVAL(1.12), D3DVAL(1.12)))
    return false;

 //= Zur Szene hinzüfugen
  if (!plight->AddToFrame(this))
    return false;

  //= Nötige Transformation durchführen
  if (!plight->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(-5), D3DVAL(30)))
    return false;

  //= Gerichtete Lichtquelle anlegen
  CD3DDirectionalLight *dlight = new CD3DDirectionalLight;
  if (dlight == NULL)
    return false;
  
  if (!dlight->Create(this))
    return false;

  //= Farbe und Intensität der gerichtete Lichtquelle festlegen
  if (!dlight->SetColorRGB(D3DVAL(1.45), D3DVAL(1.45), D3DVAL(1.45)))
    return false;

 //= Zur Szene hinzüfugen
  if (!dlight->AddToFrame(this))
    return false;

  //= Restliche Transformationen durchführen
  
  if (!dlight->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(PI / 3.0 * 2.0)))
    return false;

  //= Kamera festlegen
  CD3DCameraFrame *camera = GetCameraFrame();
  if (camera == NULL)
    return false;
  
  if (!camera->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(0), D3DVAL(0), 
                                            D3DVAL(PI / 9.0)))
    return false;

  if (!camera->AddTranslation(D3DRMCOMBINE_AFTER, D3DVAL(0), D3DVAL(15), D3DVAL(-10)))
    return false;

  if (!SetCameraParam(2.0, 1.0, 1500.0, RGB(128, 198, 238), RGB(200, 200, 200)))
    return false;
  
  //=Texturen:
  //= Verwendung von Poster (Decal) als visuelles Element der Szene
  CD3DTexture *tex1 = new CD3DTexture;
  if (tex1 == NULL)
    return false;
  if (!tex1->Create(this, ResolveName("Decal.bmp")))
    return false;
  if (!tex1->SetSize(D3DVAL(30), D3DVAL(15)))
    return false;
  if (!tex1->SetScale(true))
    return false;
  if (!tex1->SetTransparency(true, RGB(255, 255, 255)))
    return false;
  if (!tex1->SetOrigin(0, 127))
    return false;

  CD3DTexture *tex2 = new CD3DTexture;
  if (tex2 == NULL)
    return false;
  if (!tex2->Create(this, ResolveName("Decal.bmp")))
    return false;
  if (!tex2->SetSize(D3DVAL(3), D3DVAL(1.5)))
    return false;
  if (!tex2->SetScale(false))
    return false;
  if (!tex2->SetOrigin(0, 127))
    return false;

  CD3DDecalFrame *decal1 = new CD3DDecalFrame;
  if (decal1 == NULL)
    return false;
  
  if (!decal1->Create(this, tex1))
    return false;

  //= Einfügen des Posters in die Szene
  if (!decal1->AddToFrame(this))
    return false;

  if (!decal1->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(-30), D3DVAL(-15), D3DVAL(30)))
    return false;

  CD3DDecalFrame *decal2 = new CD3DDecalFrame;
  if (decal2 == NULL)
    return false;
  
  if (!decal2->Create(this, tex2))
    return false;

  if (!decal2->AddToFrame(this))
    return false;

  if (!decal2->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(-25), D3DVAL(-15), D3DVAL(60)))
    return false;

  return true;
  }