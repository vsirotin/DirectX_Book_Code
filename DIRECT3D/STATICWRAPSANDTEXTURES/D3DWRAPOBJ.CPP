// d3dMaterialObj.cpp : implementation file
//

#include "stdafx.h"
#include "d3dWrapObj.h"

 
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
// CD3DWrapObj

CD3DWrapObj::CD3DWrapObj()
  {
  }

CD3DWrapObj::~CD3DWrapObj()
  {
  }

CD3DFrame *CD3DWrapObj::CreateLandscape(int x_pl, int z_pl)
  {
  
  CD3DFrame *pLand = new CD3DFrame; //= Resultat-Frame  
  if (pLand == NULL)
    return NULL;

  if (!pLand->Create(this))
    return NULL;

  //= Oberste Schicht der Landschaft
  CD3DFrame *pGrass = CD3DGeomArsenal::CreateChessBoard(this, x_pl, z_pl,
                                 RGB(255, 255, 120), RGB(255, 255, 120));
  if (pGrass == NULL)
    return NULL;

  if (!pGrass->AddToFrame(pLand))
    return NULL;

  //= Bach-Schicht
  CD3DFrame *pRiver = CD3DGeomArsenal::CreateChessBoard(this, x_pl, z_pl,
                                 RGB(0, 0, 255), RGB(0, 0, 255));
  if (pRiver == NULL)
    return NULL;

  if (!pRiver->AddToFrame(pLand))
    return NULL;

  if (!pRiver->AddCombTransform(D3DVAL(1), D3DVAL(1), D3DVAL(1),
                       D3DVAL(0), D3DVAL(0), D3DVAL(0),
                       D3DVAL(0), D3DVAL(-1), D3DVAL(0)))
    return false;


  CD3DMaterial *matRiver = new CD3DMaterial;
  if (matRiver == NULL)
    return NULL;

  if (!matRiver->Create(this, D3DVAL(1), D3DVAL(1), D3DVAL(1), D3DVAL(200)))
    return NULL;

  if (!pRiver->SetMaterial(matRiver, false))
    return NULL;

  CD3DTexture *tex = new CD3DTexture;
  if (tex == NULL)
    return NULL;

  if (!tex->Create(this, ResolveName("River.bmp")))
    return NULL;

  //= Transparentfarbe 
  if (!tex->SetTransparency(true, RGB(0, 0, 0)))
    return NULL;

  //= Texturen mit der Geometrie verbinden

  int j, k;
  CD3DFrame *frm;  
  int AppData = 1;

  for (k = 0; k < x_pl; k++)
  for (j = 0; j < z_pl; j++, AppData++)
    {
    if ((frm = pGrass->GetChildFrame((DWORD) AppData)) == NULL)
      return NULL;

    if (!frm->ApplyFlatWrap(tex, D3DVAL(0), D3DVAL(0), D3DVAL(0),
                     D3DVAL(0), D3DVAL(-1), D3DVAL(0), 
                     D3DVAL(0), D3DVAL(0), D3DVAL(1),
                     D3DVAL(0), D3DVAL(1), D3DVAL(1), D3DVAL(-1)))    
      return NULL;
    }
  
  return pLand;
  }

CD3DFrame *CD3DWrapObj::CreateFaceHouse()
  {

  CD3DFrame *pH = new CD3DFrame; // Resultat - Frame
  if (pH == NULL)
    return NULL;

  if (!pH->Create(this))
    return NULL;

  //= Boden
  D3DVECTOR vFloor[] = {
    {D3DVAL(0), D3DVAL(0), D3DVAL(0)},
    {D3DVAL(0), D3DVAL(0), D3DVAL(1)},
    {D3DVAL(1), D3DVAL(0), D3DVAL(1)},
    {D3DVAL(1), D3DVAL(0), D3DVAL(0)}
    };

  CD3DPolygonFrame *pFloor = new CD3DPolygonFrame;
  if (pFloor == NULL)
    return NULL;

  if (!pFloor->Create(this, 4, vFloor, RGB(255, 0, 255)))
    return NULL;

  if (!pFloor->AddToFrame(pH))
    return NULL;

  CD3DPolygonFrame *pCiel = new CD3DPolygonFrame;
  if (pCiel == NULL)
    return NULL;

  if (!pCiel->Create(this, 4, vFloor, RGB(255, 255, 255), false))
    return NULL;

  if (!pCiel->AddToFrame(pH))
    return NULL;

  if (!pCiel->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(1), D3DVAL(0)))
    return NULL;

  CD3DPolygonFrame *pNear = new CD3DPolygonFrame;
  if (pNear == NULL)
    return NULL;

  if (!pNear->Create(this, 4, vFloor, RGB(255, 255, 0)))
    return NULL;

  if (!pNear->AddToFrame(pH))
    return NULL;

  if (!pNear->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(0), D3DVAL(0),
                                                D3DVAL(-PI / 2.0)))
    return NULL;

  CD3DPolygonFrame *pNearI = new CD3DPolygonFrame;
  if (pNearI == NULL)
    return NULL;

  if (!pNearI->Create(this, 4, vFloor, RGB(255, 255, 255), false))
    return NULL;

  if (!pNearI->AddToFrame(pH))
    return NULL;

  if (!pNearI->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(0), D3DVAL(0),
                                                 D3DVAL(-PI / 2.0)))
    return NULL;

  CD3DPolygonFrame *pFar = new CD3DPolygonFrame;
  if (pFar == NULL)
    return NULL;

  if (!pFar->Create(this, 4, vFloor, RGB(255, 255, 0), false))
    return NULL;

  if (!pFar->AddToFrame(pH))
    return NULL;

  if (!pFar->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(0), D3DVAL(0),
                                               D3DVAL(-PI / 2.0)))
    return NULL;

  if (!pFar->AddTranslation(D3DRMCOMBINE_AFTER, D3DVAL(0), D3DVAL(0), D3DVAL(1)))
    return NULL;

  CD3DPolygonFrame *pFarI = new CD3DPolygonFrame;
  if (pFarI == NULL)
    return NULL;

  if (!pFarI->Create(this, 4, vFloor, RGB(255, 255, 255)))
    return NULL;

  if (!pFarI->AddToFrame(pH))
    return NULL;

  if (!pFarI->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(0), D3DVAL(0),
                                                D3DVAL(-PI / 2.0)))
    return NULL;

  if (!pFarI->AddTranslation(D3DRMCOMBINE_AFTER, D3DVAL(0), D3DVAL(0), D3DVAL(1)))
    return NULL;

  CD3DPolygonFrame *pLeft = new CD3DPolygonFrame;
  if (pLeft == NULL)
    return NULL;

  if (!pLeft->Create(this, 4, vFloor, RGB(255, 255, 0)))
    return NULL;

  if (!pLeft->AddToFrame(pH))
    return NULL;

  if (!pLeft->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(1),
                                                D3DVAL(PI / 2.0)))
    return NULL;

  CD3DPolygonFrame *pLeftI = new CD3DPolygonFrame;
  if (pLeftI == NULL)
    return NULL;

  if (!pLeftI->Create(this, 4, vFloor, RGB(255, 255, 255), false))
    return NULL;

  if (!pLeftI->AddToFrame(pH))
    return NULL;

  if (!pLeftI->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(1),
                                                 D3DVAL(PI / 2.0)))
    return NULL;

  CD3DPolygonFrame *pRight = new CD3DPolygonFrame;
  if (pRight == NULL)
    return NULL;

  if (!pRight->Create(this, 4, vFloor, RGB(255, 255, 0), false))
    return NULL;

  if (!pRight->AddToFrame(pH))
    return NULL;

  if (!pRight->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(1),
                                                 D3DVAL(PI / 2.0)))
    return NULL;

  if (!pRight->AddTranslation(D3DRMCOMBINE_AFTER, D3DVAL(1), D3DVAL(0), D3DVAL(0)))
    return NULL;

  CD3DPolygonFrame *pRightI = new CD3DPolygonFrame;
  if (pRightI == NULL)
    return NULL;

  if (!pRightI->Create(this, 4, vFloor, RGB(255, 255, 255)))
    return NULL;

  if (!pRightI->AddToFrame(pH))
    return NULL;

  if (!pRightI->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(1),
                                                  D3DVAL(PI / 2.0)))
    return NULL;

  if (!pRightI->AddTranslation(D3DRMCOMBINE_AFTER, D3DVAL(1), D3DVAL(0), D3DVAL(0)))
    return NULL;

  CD3DPyramidFrame *pRoof = new CD3DPyramidFrame;
  if (pRoof == NULL)
    return NULL;

  if (!pRoof->Create(this, RGB(255, 200, 0)))
    return NULL;

  if (!pRoof->AddToFrame(pH))
    return NULL;

  if (!pRoof->AddRotation(D3DRMCOMBINE_AFTER, D3DVAL(1), D3DVAL(0), D3DVAL(0), 
                                              D3DVAL(-PI / 2.0)))
    return NULL;

  if (!pRoof->AddScale(D3DRMCOMBINE_AFTER, D3DVAL(0.65), D3DVAL(1), D3DVAL(0.65)))
    return NULL;

  if (!pRoof->AddTranslation(D3DRMCOMBINE_AFTER, D3DVAL(0.5), D3DVAL(1), D3DVAL(0.5)))
    return NULL;

  //= Farben und Texturen:
  CD3DTexture *texPoster = new CD3DTexture;
  if (texPoster == NULL)
    return NULL;

  if (!texPoster->Create(this, ResolveName("TexPoster.bmp")))
    return NULL;

  if (!pNear->ApplyFlatWrap(texPoster, D3DVAL(0), D3DVAL(0), D3DVAL(0),
                     D3DVAL(0), D3DVAL(1), D3DVAL(0), 
                     D3DVAL(0), D3DVAL(0), D3DVAL(1),
                     D3DVAL(0), D3DVAL(1), D3DVAL(1), D3DVAL(-1)))    
    return NULL;

  if (!pFar->ApplyFlatWrap(texPoster, D3DVAL(0), D3DVAL(0), D3DVAL(0),
                     D3DVAL(0), D3DVAL(1), D3DVAL(0), 
                     D3DVAL(0), D3DVAL(0), D3DVAL(1),
                     D3DVAL(0), D3DVAL(1), D3DVAL(1), D3DVAL(-1)))    
    return NULL;

  CD3DTexture *texWall = new CD3DTexture;
  if (texWall == NULL)
    return NULL;

  if (!texWall->Create(this, ResolveName("TexWall.bmp")))
    return NULL;

  if (!texWall->SetTransparency(true, RGB(0, 0, 0)))
    return NULL;

  if (!pRight->ApplyFlatWrap(texWall, D3DVAL(0), D3DVAL(0), D3DVAL(0),
                     D3DVAL(0), D3DVAL(1), D3DVAL(0), 
                     D3DVAL(1), D3DVAL(0), D3DVAL(0),
                     D3DVAL(0), D3DVAL(1), D3DVAL(1), D3DVAL(-1)))    
    return NULL;

  if (!pLeft->ApplyFlatWrap(texWall, D3DVAL(0), D3DVAL(0), D3DVAL(0),
                     D3DVAL(0), D3DVAL(1), D3DVAL(0), 
                     D3DVAL(1), D3DVAL(0), D3DVAL(0),
                     D3DVAL(0), D3DVAL(1), D3DVAL(1), D3DVAL(-1)))    
    return NULL;

  CD3DTexture *texRoof = new CD3DTexture;
  if (texRoof == NULL)
    return NULL;

  if (!texRoof->Create(this, ResolveName("TexRoof.bmp")))
    return NULL;

  if (!pRoof->ApplyCylinderWrap(texRoof, D3DVAL(0), D3DVAL(0), D3DVAL(0),
                     D3DVAL(0), D3DVAL(0), D3DVAL(1), 
                     D3DVAL(0), D3DVAL(-1), D3DVAL(0),
                     D3DVAL(0), D3DVAL(1), D3DVAL(1), D3DVAL(-1)))    
    return NULL;
  
  return pH;
  }

bool CD3DWrapObj::OnCreate()
  {
  CD3DFrame *pH = CreateFaceHouse();
  if (pH == NULL)
    return false;

  if (!pH->AddToFrame(this))
    return NULL;

  if (!pH->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(-0.5), D3DVAL(0), D3DVAL(-0.5)))
    return NULL;

  if (!pH->AddCombTransform(D3DVAL(20), D3DVAL(20), D3DVAL(30),
                       D3DVAL(0), D3DVAL(PI / 5.0), D3DVAL(0),
                       D3DVAL(-30), D3DVAL(-14), D3DVAL(50)))
    return false;

  CD3DFrame *pL = CreateLandscape(10, 10);

  if (!pL->AddToFrame(this))
    return NULL;

  if (!pL->AddCombTransform(D3DVAL(100), D3DVAL(1), D3DVAL(100),
                       D3DVAL(0), D3DVAL(0), D3DVAL(0),
                       D3DVAL(-50), D3DVAL(-15), D3DVAL(0)))
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

  //= Nötige Transformationen durchführen
  if (!plight->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(-5), D3DVAL(30)))
    return false;

  //= Gerichtete Lichtquelle anlegen
  CD3DDirectionalLight *dlight = new CD3DDirectionalLight;
  if (dlight == NULL)
    return false;
  
  if (!dlight->Create(this))
    return false;

  //= Farbe und Intensität der gerichteten Lichtquelle festlegen
  if (!dlight->SetColorRGB(D3DVAL(1.45), D3DVAL(1.45), D3DVAL(1.45)))
    return false;

 //= Zur Szene hinzüfugen
  if (!dlight->AddToFrame(this))
    return false;
  
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
  
  //= Texturen und Wraps
  CD3DTexture *tex1 = new CD3DTexture;
  if (tex1 == NULL)
    return false;
  if (!tex1->Create(this, ResolveName("TexTree.bmp")))
    return false;
  
  if (!PutCylTexture(tree, tex1))
    return false;

  CD3DTexture *tex2 = new CD3DTexture;
  if (tex2 == NULL)
    return false;
  if (!tex2->Create(this, ResolveName("TexTree1.bmp")))
    return false;
  
  if (!PutCylTexture(tree2, tex2))
    return false;

  if (!PutCylTexture(tree1, tex2))
    return false;

  return true;
  }

bool CD3DWrapObj::PutCylTexture(CD3DFrame *tree, CD3DTexture *tex)
  {
  CD3DFrame *pSphere1 = tree->GetChildFrame((DWORD) 1);
  if (pSphere1 == NULL)
    return false;

  if (!pSphere1->ApplyCylinderWrap(tex, D3DVAL(0), D3DVAL(0), D3DVAL(0),
                     D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(1), D3DVAL(-1), D3DVAL(0),
                     D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(2)))
    return false;

  CD3DFrame *pSphere2 = tree->GetChildFrame((DWORD) 2);
  if (pSphere2 == NULL)
    return false;

  if (!pSphere2->ApplyCylinderWrap(tex, D3DVAL(0), D3DVAL(0), D3DVAL(0),
                     D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(1), D3DVAL(-1), D3DVAL(0),
                     D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(2)))
    return false;

  return true;
  }

