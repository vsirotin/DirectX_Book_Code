// d3dDynaChromeObj.cpp : implementation file
//

#include "stdafx.h"
#include "d3dDynaChromeObj.h"

 
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
// CD3DDynaObj

CD3DDynaChromeObj::CD3DDynaChromeObj()
  {
  }

CD3DDynaChromeObj::~CD3DDynaChromeObj()
  {
  }

void CD3DDynaChromeObj::ObjCallback(D3DVALUE delta)
  {
  pSphere->ApplyChrome(tex1, camera, pSphere);
  pCyl->ApplyChrome(tex1, camera, pCyl);
  pDisk->ApplyChrome(tex1, camera, pDisk);
  pSphere2->ApplyChrome(tex1, camera, pSphere2);
  }

bool CD3DDynaChromeObj::OnCreate()
  {
  CD3DFrame *mushroom = CD3DGeomArsenal::CreateMushroom(this, 32, 10);

  if (mushroom == NULL)
    return false;

  if (!mushroom->AddToFrame(this))
    return false;

  mushroom->AddCombTransform(D3DVAL(10), D3DVAL(10), D3DVAL(10),
                          D3DVAL(-PI / 2.0), D3DVAL(PI / 3.0), D3DVAL(PI / 3.0),
                          D3DVAL(0), D3DVAL(-15), D3DVAL(50));

  CD3DMaterial *matMashr = new CD3DMaterial;
  if (!matMashr->Create(this, D3DVAL(1), D3DVAL(1), D3DVAL(1), D3DVAL(200)))
    return false;
  
  if (!mushroom->SetMaterial(matMashr))
    return false;
  
  if (!mushroom->SetColor(RGB(255, 255, 255)))
    return false;

  CD3DDirectionalLight *dlight = new CD3DDirectionalLight;
  
  if (dlight == NULL)
    return false;
  
  dlight->Create(this);

  if (!dlight->SetColorRGB(D3DVAL(1.45), D3DVAL(1.45), D3DVAL(1.45)))
    return false;

  if (!dlight->AddToFrame(this))
    return false;

  dlight->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(PI / 3.0 * 2.0));

  if (!SetAmbientLightRGB(D3DVAL(0.8), D3DVAL(0.8), D3DVAL(0.8)))
    return false;

  camera = GetCameraFrame();
  
  camera->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(0), D3DVAL(0), 
                                            D3DVAL(PI / 9.0));
  camera->AddTranslation(D3DRMCOMBINE_AFTER, D3DVAL(0), D3DVAL(15), D3DVAL(0));

  if (!SetImageFile(ResolveName("Chrome.bmp")))
    return false;
  if (!SetCameraFront(1.0))
    return false;
  if (!SetCameraBack(500.0))
    return false;
  if (!SetCameraField(1.0))
    return false;
  if (!SetRenderQuality(D3DRMLIGHT_ON | D3DRMFILL_SOLID | D3DRMSHADE_GOURAUD))
    return false;                                       

  tex1 = new CD3DTexture;
  if (tex1 == NULL)
    return false;

  if (!tex1->Create(this, ResolveName("Chrome.bmp")))
    return false;

  pSphere = mushroom->GetChildFrame((DWORD) 1);
  pSphere2 = mushroom->GetChildFrame((DWORD) 4);
  pDisk = mushroom->GetChildFrame((DWORD) 2);
  pCyl = mushroom->GetChildFrame((DWORD) 3);

  if (!camera->CreateChromeWrap())
    return false;
  if (!pSphere->ApplyChrome(tex1, camera, pSphere))
    return false;
  if (!pCyl->ApplyChrome(tex1, camera, pCyl))
    return false;
  if (!pDisk->ApplyChrome(tex1, camera, pDisk))
    return false;
  if (!pSphere2->ApplyChrome(tex1, camera, pSphere2))
    return false;

  //= Drehgeschwindigkeeit festlegen.
  if (!mushroom->SetRotation(mushroom, D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(0.3)))
    return false;

  if (!SetMoveCallback())
    return false;

  //= Direct3D informieren, daß die Szene Ticks benötigt
  if (!SetTickEnable(true))
    return false;

  return true;
  }
