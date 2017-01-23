// d3dWrapObj.cpp : implementation file
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

bool CD3DWrapObj::OnCreate()
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

  CD3DCameraFrame *camera = GetCameraFrame();
  
  camera->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(0), D3DVAL(0), 
                                            D3DVAL(PI / 9.0));
  camera->AddTranslation(D3DRMCOMBINE_AFTER, D3DVAL(0), D3DVAL(15), D3DVAL(0));

  if (!SetCameraParam(1.0, 1.0, 1500.0, RGB(102, 102, 153), RGB(200, 200, 200)))
    return false;

  if (!SetImageFile(ResolveName("Chrome.bmp")))
    return false;

  CD3DTexture *tex1 = new CD3DTexture;
  if (tex1 == NULL)
    return false;

  if (!tex1->Create(this, ResolveName("Chrome.bmp")))
    return false;

  CD3DFrame *pSphere  = mushroom->GetChildFrame((DWORD) 1);
  CD3DFrame *pSphere2 = mushroom->GetChildFrame((DWORD) 4);
  CD3DFrame *pDisk    = mushroom->GetChildFrame((DWORD) 2);
  CD3DFrame *pCyl     = mushroom->GetChildFrame((DWORD) 3);

  //= Experiment 1

  if (!pSphere->ApplyChromeWrap(tex1, camera, pSphere,
		            D3DVAL(0),	D3DVAL(0),	D3DVAL(0),
		            D3DVAL(0),	D3DVAL(0),	D3DVAL(-1),
		            D3DVAL(0),	D3DVAL(1),	D3DVAL(0),
		            D3DVAL(0),	D3DVAL(0),  
                D3DVAL(1),	D3DVAL(-1)))
    return false;

  if (!pCyl->ApplyChromeWrap(tex1, camera, pCyl,
		            D3DVAL(0),	D3DVAL(0),	D3DVAL(0),
		            D3DVAL(0),	D3DVAL(0),	D3DVAL(-1),
		            D3DVAL(0),	D3DVAL(1),	D3DVAL(0),
		            D3DVAL(0),	D3DVAL(1),  
                D3DVAL(1),	D3DVAL(-1)))
    return false;
  
  if (!pDisk->ApplyChromeWrap(tex1, camera, pDisk,
		            D3DVAL(0),	D3DVAL(0),	D3DVAL(0),
		            D3DVAL(0),	D3DVAL(0),	D3DVAL(-1),
		            D3DVAL(0),	D3DVAL(1),	D3DVAL(0),
		            D3DVAL(0),	D3DVAL(1),  
                D3DVAL(1),	D3DVAL(-1)))
    return false;

  if (!pSphere2->ApplyChromeWrap(tex1, camera, pSphere2,
		            D3DVAL(0),	D3DVAL(0),	D3DVAL(0),
		            D3DVAL(0),	D3DVAL(0),	D3DVAL(-1),
		            D3DVAL(0),	D3DVAL(1),	D3DVAL(0),
		            D3DVAL(0),	D3DVAL(1),  
                D3DVAL(1),	D3DVAL(-1)))
    return false;


  //= Experiment 2
  //= Parameter lpObj = Frame der ganzen Szene
/*
  if (!pSphere->ApplyChromeWrap(tex1, camera, this))
    return false;
  if (!pCyl->ApplyChromeWrap(tex1, camera, this))
    return false;
  if (!pDisk->ApplyChromeWrap(tex1, camera, this))
    return false;
  if (!pSphere2->ApplyChromeWrap(tex1, camera, this))
    return false;
*/


  return true;
  }

