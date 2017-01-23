// d3dCosmosObj.cpp : implementation file
// Idea of scenario : Aleksandr P. Stasenko, (1999) student
//                    Math. and Mech. Faculty of 
//                    Novosibirsk State University, Russia
//                    Scene and behavior are compiled as a fantasy
//                    after looking at SDK's samples and
//                    many interesting stuffs from Internet
//  E.g., Earth texture was built on the base of image file 
//	      http://maps.jpl.nasa.gov/textures/ear0xuu2.jpg
//
//

#include "stdafx.h"
#include "d3dCosmosObj.h"
#include "d3dBumpedPlaneFrame.h"
#include "d3dUFOFrame.h"
#include "d3dRevolveMeshFrame.h"
#include "math.h"
//= references to used objects:
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

static double fRand(double amp1, double amp2)
  {
  double r = (double)rand() / (double)RAND_MAX;
  
  return (amp1 + r * (amp2 - amp1));
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DCosmosObj

CD3DCosmosObj::CD3DCosmosObj()
  {
  m_vTime = D3DVAL(0);
  sph = NULL;
  }

CD3DCosmosObj::~CD3DCosmosObj()
  {
  if (sph != NULL)
    {
    delete [] sph;
    }
  }

void CD3DCosmosObj::ObjCallback(D3DVALUE delta)
  {
  static a = 0;
  m_vTime += D3DVAL(0.1);

  //= Sun animation
  m_pAnimSun->SetTime(m_vTime);

  //= Rocket animation
  m_pAnimRocket->SetTime(m_vTime);

  //= fire stuffs animations
  m_pAnim1->SetTime(m_vTime);
  m_pAnim2->SetTime(m_vTime);
  m_pAnim3->SetTime(m_vTime);
  }

bool CD3DCosmosObj::SunObject()
  {
  //= Sun decal

  CD3DTexture *texSun = new CD3DTexture;
  if (texSun == NULL)
    return false;
  if (!texSun->Create(this, ResolveName("SunDecal.bmp")))
    return false;
  if (!texSun->SetSize(D3DVAL(30), D3DVAL(30)))
    return false;
  if (!texSun->SetScale(true))
    return false;
  if (!texSun->SetTransparency(true, RGB(0, 0, 0)))
    return false;
  if (!texSun->SetOrigin(31, 31))
    return false;

  CD3DDecalFrame *decalSun = new CD3DDecalFrame;
  if (decalSun == NULL)
    return false;
  
  if (!decalSun->Create(this, texSun))
    return false;

  //= put decal's frame into space
  if (!decalSun->AddToFrame(m_pSpace))
    return false;

  //= create light object - type = ParallelPoint
  CD3DParallelPointLight *pplight = new CD3DParallelPointLight;
  if (pplight == NULL)
    return false;

  if (!pplight->Create(this)) //= default color and intensity
    return false;

  //= Assign color and intensity of point light
  if (!pplight->SetColorRGB(D3DVAL(1), D3DVAL(1), D3DVAL(1)))
    return false;

  //= attach light frame to the scene frame
  if (!pplight->AddToFrame(decalSun))
    return false;

  //= create its animation
  D3DVALUE tTime[] = {D3DVAL(0), D3DVAL(1), D3DVAL(2)};
  D3DVECTOR tPos[]  = {
    {D3DVAL(10), D3DVAL(-30), D3DVAL(100)},
    {D3DVAL(10), D3DVAL(-30), D3DVAL(120)},
    {D3DVAL(10), D3DVAL(-30), D3DVAL(100)}
    };

  m_pAnimSun = new CD3DAnimation;
  if (m_pAnimSun == NULL)
    return false;

  if (!m_pAnimSun->Create(this)) 
    return false;

  int i;
  for (i = 0; i < 3; i++)
    {
    if (!m_pAnimSun->SetPositionKey(D3DVAL(tTime[i]), 
                      tPos[i].x, tPos[i].y, tPos[i].z))
      return false;
    }

  if (!m_pAnimSun->SetFrame(decalSun))
    return false;

  return true;
  }

bool CD3DCosmosObj::CreateUFOs()
  {
  //= first flying light object
  CD3DFrame *pFirst = new CD3DFrame;
  if (pFirst == NULL)
    return false;

  if (!pFirst->Create(this)) 
    return false;

  if (!pFirst->AddToFrame(m_pTerra))
    return false;

  CD3DUFOFrame *pFS1 = new CD3DUFOFrame;
  if (pFS1 == NULL)
    return false;

  if (!pFS1->Create(this, 32, RGB(255, 0, 0), m_pSpotL)) 
    return false;

  if (!pFS1->AddToFrame(pFirst))
    return false;

  if (!pFS1->AddScale(D3DRMCOMBINE_REPLACE, D3DVAL(0.0125), D3DVAL(0.0125), D3DVAL(0.0125)))
    return false;

  CD3DMaterial *mat1 = new CD3DMaterial;
  if (mat1 == NULL)
    return false;
  if (!mat1->Create(this, D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(1),
                          D3DVAL(1), D3DVAL(0), D3DVAL(0)))
    return false;

  if (!pFS1->SetMaterial(mat1, true))
    return false;
  
  if (!pFS1->SetRotation(pFS1, D3DVAL(1), D3DVAL(1), D3DVAL(1), D3DVAL(PI / 100)))
    return false;

  CD3DPointLight *pPL1 = new CD3DPointLight;
  if (pPL1 == NULL)
    return false;
  if (!pPL1->Create(this, D3DVAL(1), D3DVAL(0), D3DVAL(0),
                          D3DVAL(1), D3DVAL(0), D3DVAL(0)))
    return false;

  if (!pPL1->AddToFrame(pFirst))
    return false;

  //= create animation of fire stuff
  m_pAnim1 = new CD3DAnimation;
  if (m_pAnim1 == NULL)
    return false;

  if (!m_pAnim1->Create(this, D3DRMANIMATION_CLOSED | D3DRMANIMATION_POSITION | D3DRMANIMATION_SPLINEPOSITION)) 
    return false;

  int i;
  double xR = 1.0;
  double zR = -0.5;
  double y_val;
  
  for (i = 0; i < 9; i++)
    {
    double r = fRand(0.0, 1.0);
    
    if (i== 0)
      y_val = r;

    if (i == 8)
      r = y_val;

    if (!m_pAnim1->SetPositionKey(D3DVAL(i / 2.0), 
                                  D3DVAL(xR * cos((2 * PI / 8.0) * i)),
                                  D3DVAL(r),
                                  D3DVAL(zR * sin((2 * PI / 8.0) * i))))
      return false;
    }

  if (!m_pAnim1->SetFrame(pFirst))
    return false;

  //= second flying light object
  CD3DFrame *pSecond = new CD3DFrame;
  if (pSecond == NULL)
    return false;

  if (!pSecond->Create(this)) 
    return false;

  if (!pSecond->AddToFrame(m_pTerra))
    return false;

  CD3DUFOFrame *pFS2 = new CD3DUFOFrame;
  if (pFS2 == NULL)
    return false;

  if (!pFS2->Create(this, 32, RGB(0, 255, 0), m_pSpotL)) 
    return false;

  if (!pFS2->AddToFrame(pSecond))
    return false;

  if (!pFS2->AddScale(D3DRMCOMBINE_REPLACE, D3DVAL(0.0125), D3DVAL(0.0125), D3DVAL(0.0125)))
    return false;

  CD3DMaterial *mat2 = new CD3DMaterial;
  if (mat2 == NULL)
    return false;
  if (!mat2->Create(this, D3DVAL(0), D3DVAL(1), D3DVAL(0), D3DVAL(1),
                          D3DVAL(0), D3DVAL(1), D3DVAL(0)))
    return false;

  if (!pFS2->SetMaterial(mat2, true))
    return false;
  
  if (!pFS2->SetRotation(pFS1, D3DVAL(1), D3DVAL(1), D3DVAL(0), D3DVAL(PI / 20)))
    return false;

  CD3DPointLight *pPL2 = new CD3DPointLight;
  if (pPL2 == NULL)
    return false;
  if (!pPL2->Create(this, D3DVAL(0), D3DVAL(1), D3DVAL(0),
                          D3DVAL(0), D3DVAL(1), D3DVAL(0)))
    return false;

  if (!pPL2->AddToFrame(pSecond))
    return false;

  //= create animation of fire stuff
  m_pAnim2 = new CD3DAnimation;
  if (m_pAnim2 == NULL)
    return false;

  if (!m_pAnim2->Create(this, D3DRMANIMATION_CLOSED | D3DRMANIMATION_POSITION | D3DRMANIMATION_SPLINEPOSITION)) 
    return false;

  xR = -0.5;
  zR = 1.0;
  
  for (i = 0; i < 9; i++)
    {
    double r = fRand(0.0, 1.0);
    
    if (i== 0)
      y_val = r;

    if (i == 8)
      r = y_val;

    if (!m_pAnim2->SetPositionKey(D3DVAL(i / 2.0), 
                                  D3DVAL(xR * cos((2 * PI / 8.0) * i)),
                                  D3DVAL(r),
                                  D3DVAL(zR * sin((2 * PI / 8.0) * i))))
      return false;
    }

  if (!m_pAnim2->SetFrame(pSecond))
    return false;

  //= third flying light object
  CD3DFrame *pThird = new CD3DFrame;
  if (pThird == NULL)
    return false;

  if (!pThird->Create(this)) 
    return false;

  if (!pThird->AddToFrame(m_pTerra))
    return false;

  CD3DUFOFrame *pFS3 = new CD3DUFOFrame;
  if (pFS3 == NULL)
    return false;

  if (!pFS3->Create(this, 32, RGB(0, 0, 255), m_pSpotL)) 
    return false;

  if (!pFS3->AddToFrame(pThird))
    return false;

  if (!pFS3->AddScale(D3DRMCOMBINE_REPLACE, D3DVAL(0.0125), D3DVAL(0.0125), D3DVAL(0.0125)))
    return false;

  CD3DMaterial *mat3 = new CD3DMaterial;
  if (mat3 == NULL)
    return false;
  if (!mat3->Create(this, D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(1),
                          D3DVAL(0), D3DVAL(0), D3DVAL(1)))
    return false;

  if (!pFS3->SetMaterial(mat3, true))
    return false;

  if (!pFS3->SetRotation(pFS1, D3DVAL(1), D3DVAL(1), D3DVAL(0), D3DVAL(PI / 20)))
    return false;

  CD3DPointLight *pPL3 = new CD3DPointLight;
  if (pPL3 == NULL)
    return false;
  if (!pPL3->Create(this, D3DVAL(0), D3DVAL(0), D3DVAL(1),
                          D3DVAL(0), D3DVAL(0), D3DVAL(1)))
    return false;

  if (!pPL3->AddToFrame(pThird))
    return false;

  //= create animation of fire stuff
  m_pAnim3 = new CD3DAnimation;
  if (m_pAnim3 == NULL)
    return false;

  if (!m_pAnim3->Create(this, D3DRMANIMATION_CLOSED | D3DRMANIMATION_POSITION | D3DRMANIMATION_SPLINEPOSITION)) 
    return false;

  xR = 0.7;
  zR = 0.7;
  
  for (i = 0; i < 9; i++)
    {
    double r = fRand(0.1, 1.0);
    
    if (i== 0)
      y_val = r;

    if (i == 8)
      r = y_val;

    if (!m_pAnim3->SetPositionKey(D3DVAL(i / 2.0), 
                                  D3DVAL(xR * cos((2 * PI / 8.0) * i)),
                                  D3DVAL(r),
                                  D3DVAL(zR * sin((2 * PI / 8.0) * i))))
      return false;
    }

  if (!m_pAnim3->SetFrame(pThird))
    return false;  

  return true;
  }

bool CD3DCosmosObj::CreateRock()
  {
  D3DVECTOR hanoi[] = {   //= 27 points
   {D3DVAL(0),  D3DVAL(0), D3DVAL(25)},
   {D3DVAL(3),  D3DVAL(0), D3DVAL(25)},
   {D3DVAL(4),  D3DVAL(0), D3DVAL(24)},
   {D3DVAL(4),  D3DVAL(0), D3DVAL(22)},
   {D3DVAL(5),  D3DVAL(0), D3DVAL(22)},
   {D3DVAL(5),  D3DVAL(0), D3DVAL(20)},
   {D3DVAL(6),  D3DVAL(0), D3DVAL(20)},
   {D3DVAL(6),  D3DVAL(0), D3DVAL(18)},
   {D3DVAL(7),  D3DVAL(0), D3DVAL(18)},
   {D3DVAL(7),  D3DVAL(0), D3DVAL(16)},
   {D3DVAL(8),  D3DVAL(0), D3DVAL(16)},
   {D3DVAL(8),  D3DVAL(0), D3DVAL(14)},
   {D3DVAL(9),  D3DVAL(0), D3DVAL(14)},
   {D3DVAL(9),  D3DVAL(0), D3DVAL(12)},
   {D3DVAL(10), D3DVAL(0), D3DVAL(12)},
   {D3DVAL(10), D3DVAL(0), D3DVAL(10)},
   {D3DVAL(11), D3DVAL(0), D3DVAL(10)},
   {D3DVAL(11), D3DVAL(0), D3DVAL(8)},
   {D3DVAL(12), D3DVAL(0), D3DVAL(8)},
   {D3DVAL(12), D3DVAL(0), D3DVAL(6)},
   {D3DVAL(13), D3DVAL(0), D3DVAL(6)},
   {D3DVAL(13), D3DVAL(0), D3DVAL(4)},
   {D3DVAL(14), D3DVAL(0), D3DVAL(4)},
   {D3DVAL(14), D3DVAL(0), D3DVAL(2)},
   {D3DVAL(15), D3DVAL(0), D3DVAL(2)},
   {D3DVAL(15), D3DVAL(0), D3DVAL(0)},
   {D3DVAL(0),  D3DVAL(0), D3DVAL(0)}
   };

  D3DVECTOR flag1[] = {   //= 4 points
   {D3DVAL(0),   D3DVAL(0), D3DVAL(25)},
   {D3DVAL(0),   D3DVAL(0), D3DVAL(28)},
   {D3DVAL(0.2), D3DVAL(0), D3DVAL(28)},
   {D3DVAL(0.2), D3DVAL(0), D3DVAL(25)}
   };

  D3DVECTOR flag2[] = {   //= 4 points
   {D3DVAL(0), D3DVAL(0), D3DVAL(29)},
   {D3DVAL(0), D3DVAL(0), D3DVAL(32)},
   {D3DVAL(4), D3DVAL(0), D3DVAL(32)},
   {D3DVAL(4), D3DVAL(0), D3DVAL(29)}
   };

  CD3DFrame *pTower = new CD3DFrame;
  if (pTower == NULL)
    return false;

  if (!pTower->Create(this)) 
    return false;

  if (!pTower->AddToFrame(m_pTerra))
    return false;

  CD3DFrame *pFlags = new CD3DFrame;
  if (pFlags == NULL)
    return false;

  if (!pFlags->Create(this)) 
    return false;

  if (!pFlags->AddToFrame(pTower))
    return false;

  CD3DPolygonFrame *pFlag1 = new CD3DPolygonFrame;
  if (pFlag1 == NULL)
    return false;

  if (!pFlag1->Create(this, 4, flag1, RGB(255, 0, 0))) 
    return false;

  if (!pFlag1->AddToFrame(pFlags))
    return false;

  if (!pFlag1->AddShadow(m_pSpotL, D3DVAL(0), D3DVAL(0.), D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(0)))
    return false;

  CD3DPolygonFrame *pFlag1B = new CD3DPolygonFrame;
  if (pFlag1B == NULL)
    return false;

  if (!pFlag1B->Create(this, 4, flag1, RGB(255, 0, 0), false)) 
    return false;

  if (!pFlag1B->AddToFrame(pFlags))
    return false;

  if (!pFlag1B->AddShadow(m_pSpotL, D3DVAL(0), D3DVAL(0.), D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(0)))
    return false;

  CD3DPolygonFrame *pFlag2 = new CD3DPolygonFrame;
  if (pFlag2 == NULL)
    return false;

  if (!pFlag2->Create(this, 4, flag2, RGB(0, 255, 0))) 
    return false;

  if (!pFlag2->AddToFrame(pFlags))
    return false;

  if (!pFlag2->AddShadow(m_pSpotL, D3DVAL(0), D3DVAL(0.), D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(0)))
    return false;

  CD3DPolygonFrame *pFlag2B = new CD3DPolygonFrame;
  if (pFlag2B == NULL)
    return false;

  if (!pFlag2B->Create(this, 4, flag2, RGB(0, 255, 0), false)) 
    return false;

  if (!pFlag2B->AddToFrame(pFlags))
    return false;

  if (!pFlag2B->AddShadow(m_pSpotL, D3DVAL(0), D3DVAL(0.), D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(0)))
    return false;
  
  if (!pFlags->SetRotation(pFlags, D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(PI / 10)))
    return false;

  CD3DRevolveMeshFrame *pRock = new CD3DRevolveMeshFrame;
  if (pRock == NULL)
    return false;

  if (!pRock->Create(this, 27, hanoi, 5)) 
    return false;

  if (!pRock->AddToFrame(pTower))
    return false;

  if (!pTower->AddScale(D3DRMCOMBINE_REPLACE, D3DVAL(0.03), D3DVAL(0.03), D3DVAL(0.03)))
    return false;

  if (!pTower->AddRotation(D3DRMCOMBINE_AFTER, D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(-PI / 2)))
    return false;
  
  CD3DTexture *tex = new CD3DTexture;
  if (tex == NULL)
    return false;
  if (!tex->Create(this, ResolveName("Pyramid.bmp")))
    return false;

  if (!pRock->ApplyCylinderWrap(tex, D3DVAL(0), D3DVAL(0), D3DVAL(0),    
                                D3DVAL(0), D3DVAL(0), D3DVAL(1),
                                D3DVAL(0), D3DVAL(1), D3DVAL(0),
                                D3DVAL(0), D3DVAL(0), 
                                D3DVAL(0.06), D3DVAL(0.03)))
    return false;

  CD3DMaterial *mat = new CD3DMaterial;
  if (mat == NULL)
    return false;
  if (!mat->Create(this, D3DVAL(1), D3DVAL(1), D3DVAL(1), D3DVAL(100)))
    return false;

  if (!pRock->SetMaterial(mat, true))
    return false;

  if (!pRock->AddShadow(m_pSpotL, D3DVAL(0), D3DVAL(0.), D3DVAL(0), 
                                  D3DVAL(0), D3DVAL(1), D3DVAL(0)))
    return false;

  CD3DMaterial *mat1 = new CD3DMaterial;
  if (mat1 == NULL)
    return false;
  if (!mat1->Create(this, D3DVAL(0), D3DVAL(1), D3DVAL(1), D3DVAL(5),
                          D3DVAL(1), D3DVAL(1), D3DVAL(0.25)))
    return false;

  if (!pFlags->SetMaterial(mat1, true))
    return false;

  return true;
  }

CD3DFrame *CD3DCosmosObj::CreateRocket(bool passive)
  {
  D3DVECTOR rocket[] = {   //= 14 points
   {D3DVAL(0),   D3DVAL(0), D3DVAL(35)},
   {D3DVAL(0.5), D3DVAL(0), D3DVAL(33.8)},
   {D3DVAL(2.1), D3DVAL(0), D3DVAL(33.2)},
   {D3DVAL(3),   D3DVAL(0), D3DVAL(32)},
   {D3DVAL(4),   D3DVAL(0), D3DVAL(30)},
   {D3DVAL(5),   D3DVAL(0), D3DVAL(27)},
   {D3DVAL(5.4), D3DVAL(0), D3DVAL(25)},
   {D3DVAL(5.7), D3DVAL(0), D3DVAL(22.6)},
   {D3DVAL(6),   D3DVAL(0), D3DVAL(20)},
   {D3DVAL(6),   D3DVAL(0), D3DVAL(15)},
   {D3DVAL(5),   D3DVAL(0), D3DVAL(10)},
   {D3DVAL(3),   D3DVAL(0), D3DVAL(2)},
   {D3DVAL(3),   D3DVAL(0), D3DVAL(0)},
   {D3DVAL(0),   D3DVAL(0), D3DVAL(0)}
   };

  CD3DFrame *pRocket = new CD3DFrame;
  if (pRocket == NULL)
    return NULL;

  if (!pRocket->Create(this)) 
    return NULL;

  if (!pRocket->AddToFrame(m_pSpace))
    return NULL;

  CD3DRevolveMeshFrame *pRev = new CD3DRevolveMeshFrame;
  if (pRev == NULL)
    return NULL;

  if (!pRev->Create(this, 14, rocket, 16)) 
    return NULL;

  if (!pRev->AddToFrame(pRocket))
    return NULL;

  D3DVECTOR wing[] = {   //= 4 points
   {D3DVAL(5), D3DVAL(0), D3DVAL(10)},
   {D3DVAL(9), D3DVAL(0), D3DVAL(-5)},
   {D3DVAL(3), D3DVAL(0), D3DVAL(0)},
   {D3DVAL(3), D3DVAL(0), D3DVAL(2)}
   };

  CD3DPolygonFrame *pWing1 = new CD3DPolygonFrame;
  if (pWing1 == NULL)
    return NULL;

  if (!pWing1->Create(this, 4, wing)) 
    return NULL;

  if (!pWing1->AddToFrame(pRocket))
    return NULL;

  if (!pWing1->AddRotation(D3DRMCOMBINE_AFTER, 
                           D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(0.5)))
    return NULL;

  CD3DPolygonFrame *pWing1B = new CD3DPolygonFrame;
  if (pWing1B == NULL)
    return NULL;

  if (!pWing1B->Create(this, 4, wing, RGB(0, 255, 0), false)) 
    return NULL;

  if (!pWing1B->AddToFrame(pRocket))
    return NULL;

  if (!pWing1B->AddRotation(D3DRMCOMBINE_AFTER, 
                            D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(0.5)))
    return NULL;

  CD3DPolygonFrame *pWing2 = new CD3DPolygonFrame;
  if (pWing2 == NULL)
    return NULL;

  if (!pWing2->Create(this, 4, wing, RGB(0, 255, 0))) 
    return NULL;

  if (!pWing2->AddToFrame(pRocket))
    return NULL;

  if (!pWing2->AddRotation(D3DRMCOMBINE_AFTER, 
                           D3DVAL(0), D3DVAL(0), D3DVAL(1), 
                           D3DVAL(2 * PI / 3.0 + 0.5)))
    return NULL;

  CD3DPolygonFrame *pWing2B = new CD3DPolygonFrame;
  if (pWing2B == NULL)
    return NULL;

  if (!pWing2B->Create(this, 4, wing, RGB(0, 255, 0), false)) 
    return NULL;

  if (!pWing2B->AddToFrame(pRocket))
    return NULL;

  if (!pWing2B->AddRotation(D3DRMCOMBINE_AFTER, 
                            D3DVAL(0), D3DVAL(0), D3DVAL(1), 
                            D3DVAL(2 * PI / 3.0 + 0.5)))
    return NULL;

  CD3DPolygonFrame *pWing3 = new CD3DPolygonFrame;
  if (pWing3 == NULL)
    return NULL;

  if (!pWing3->Create(this, 4, wing, RGB(0, 255, 0))) 
    return NULL;

  if (!pWing3->AddToFrame(pRocket))
    return NULL;

  if (!pWing3->AddRotation(D3DRMCOMBINE_AFTER, 
                           D3DVAL(0), D3DVAL(0), D3DVAL(1), 
                           D3DVAL(2 * PI / 3 * 2.0 + 0.5)))
    return NULL;

  CD3DPolygonFrame *pWing3B = new CD3DPolygonFrame;
  if (pWing3B == NULL)
    return NULL;

  if (!pWing3B->Create(this, 4, wing, RGB(0, 255, 0), false)) 
    return NULL;

  if (!pWing3B->AddToFrame(pRocket))
    return NULL;

  if (!pWing3B->AddRotation(D3DRMCOMBINE_AFTER, 
                            D3DVAL(0), D3DVAL(0), D3DVAL(1), 
                            D3DVAL(2 * PI / 3 * 2.0 + 0.5)))
    return NULL;

  if (!pRocket->SetColor(RGB(0, 255, 255)))
    return NULL;

  CD3DMaterial *mat = new CD3DMaterial;
  if (mat == NULL)
    return NULL;
  if (!mat->Create(this, D3DVAL(0), D3DVAL(1), D3DVAL(1), D3DVAL(5),
                         D3DVAL(0.3), D3DVAL(0.3), D3DVAL(0.25)))
    return NULL;

  if (!pRocket->SetMaterial(mat, true))
    return NULL;

  m_pAnimRocket = new CD3DAnimation;
  if (m_pAnimRocket == NULL)
    return NULL;

  if (!m_pAnimRocket->Create(this)) 
    return NULL;

  if (passive)
    return pRocket;

  int anim_count = 3;
  int rvTime[] = {0, 1, 2};
  
  D3DVECTOR rvPos[] = {
    {D3DVAL(10), D3DVAL(-3), D3DVAL(7)},
    {D3DVAL(0), D3DVAL(-3), D3DVAL(7)},
    {D3DVAL(-10), D3DVAL(-3), D3DVAL(7)}
    };
  D3DVECTOR rvSca[] = {
    {D3DVAL(0.1), D3DVAL(0.1), D3DVAL(0.1)},
    {D3DVAL(0.1), D3DVAL(0.1), D3DVAL(0.1)},
    {D3DVAL(0.1), D3DVAL(0.1), D3DVAL(0.1)}
    };
  D3DVECTOR rvRot[] = {
    {D3DVAL(0), D3DVAL(1), D3DVAL(0)},
    {D3DVAL(0), D3DVAL(1), D3DVAL(0)},
    {D3DVAL(0), D3DVAL(1), D3DVAL(0)}
    };
  D3DVALUE rvAng[] = {D3DVAL(PI / 2), D3DVAL(PI / 2), D3DVAL(PI / 2)};

  int i;
  for (i = 0; i < anim_count; i++)
    {
    if (!m_pAnimRocket->SetPositionKey(D3DVAL(rvTime[i]), 
                      rvPos[i].x, rvPos[i].y, rvPos[i].z))
      return NULL;
    if (!m_pAnimRocket->SetRotateKey(D3DVAL(rvTime[i]), 
                      rvRot[i].x, rvRot[i].y, rvRot[i].z, rvAng[i]))
      return NULL;
    if (!m_pAnimRocket->SetScaleKey(D3DVAL(rvTime[i]), 
                      rvSca[i].x, rvSca[i].y, rvSca[i].z))
      return NULL;
    }

  if (!m_pAnimRocket->SetFrame(pRocket))
    return NULL;

  return pRocket;
  }

CD3DFrame *CD3DCosmosObj::CreateSphere(int vert_planes, int hor_planes)
  {
  if (sph != NULL)
    {
    delete [] sph;
    }

  if (vert_planes < 3 || hor_planes < 3)
    return NULL;

  sph = new D3DVECTOR [hor_planes];
  if (sph == NULL)
    return NULL;

  //= fill both ends of a curve
  sph[0].x = D3DVAL(0);
  sph[0].y = D3DVAL(0);
  sph[0].z = D3DVAL(1);
  sph[hor_planes - 1].x = D3DVAL(0);
  sph[hor_planes - 1].y = D3DVAL(0);
  sph[hor_planes - 1].z = D3DVAL(-1);
  
  double dPhi = PI / (hor_planes - 1);
  int i;

  for (i = 1; i < hor_planes - 1; i++)
    {
    double phi = dPhi * i;

    sph[i].x = D3DVAL(sin(phi));
    sph[i].y = D3DVAL(0);
    sph[i].z = D3DVAL(cos(phi));
    }

  CD3DRevolveMeshFrame *pSph = new CD3DRevolveMeshFrame;
  if (pSph == NULL)
    return NULL;

  if (!pSph->Create(this, hor_planes, sph, vert_planes, RGB(255, 255, 255))) 
    return NULL;

  return pSph;
  }

bool CD3DCosmosObj::CreateEarth()
  {
  int n_vert = 64, n_hor = 64;

  CD3DFrame *pFrame = new CD3DFrame;
  if (pFrame == NULL)
    return false;

  if (!pFrame->Create(this))
    return false;

  if (!pFrame->AddToFrame(m_pSpace))
    return false;

  if (!pFrame->AddScale(D3DRMCOMBINE_REPLACE, 
                        D3DVAL(40), D3DVAL(40), D3DVAL(38)))
    return false;

  if (!pFrame->AddRotation(D3DRMCOMBINE_AFTER, 
                        D3DVAL(1), D3DVAL(0), D3DVAL(0), 
                        D3DVAL(-PI / 12.0 * 7.0)))
    return false;

  if (!pFrame->AddTranslation(D3DRMCOMBINE_AFTER, 
                        D3DVAL(100), D3DVAL(-50), D3DVAL(250)))
    return false;

  CD3DFrame *phs = CreateSphere(n_vert, n_hor);
  if (phs == NULL)
    return false;

  if (!phs->AddToFrame(pFrame))
    return false;

  if (!phs->AddRotation(D3DRMCOMBINE_REPLACE, 
                        D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(0)))
    return false;
  
  if (!phs->SetRotation(phs, D3DVAL(0), D3DVAL(0), D3DVAL(1), 
                             D3DVAL(PI / 10)))
    return false;

  //= create and apply wrap function
  CD3DTexture *tex = new CD3DTexture;
  if (tex == NULL)
    return false;
  if (!tex->Create(this, ResolveName("Earth.bmp")))
    return false;

  if (!phs->ApplySphereWrap(tex, 
                            D3DVAL(0), D3DVAL(0), D3DVAL(0),    
                            D3DVAL(0), D3DVAL(0), D3DVAL(1),
                            D3DVAL(0), D3DVAL(1), D3DVAL(0),
                            D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(1)))
    return false;

  return true;
  }

bool CD3DCosmosObj::CreateMars()
  {
  int n_vert = 64, n_hor = 32;

  CD3DFrame *pFrame = new CD3DFrame;
  if (pFrame == NULL)
    return false;

  if (!pFrame->Create(this))
    return false;

  if (!pFrame->AddToFrame(m_pSpace))
    return false;

  if (!pFrame->AddRotation(D3DRMCOMBINE_AFTER, 
                           D3DVAL(1), D3DVAL(0), D3DVAL(0), 
                           D3DVAL(-PI / 12.0 * 7.0)))
    return false;

  if (!pFrame->AddTranslation(D3DRMCOMBINE_AFTER, 
                           D3DVAL(-20), D3DVAL(-50), D3DVAL(100)))
    return false;
  
  if (!pFrame->SetRotation(pFrame, 
                           D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(PI / 100)))
    return false;

  CD3DHalfsphereFrame *phsTop = new CD3DHalfsphereFrame;
  if (phsTop == NULL)
    return false;

  if (!phsTop->Create(this, n_vert, n_hor, RGB(255, 255, 255)))
    return false;

  if (!phsTop->AddToFrame(pFrame))
    return false;

  if (!phsTop->AddScale(D3DRMCOMBINE_REPLACE, 
                        D3DVAL(45), D3DVAL(45), D3DVAL(40)))
    return false;

  if (!phsTop->AddRotation(D3DRMCOMBINE_AFTER, 
                        D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(0)))
    return false;

  CD3DHalfsphereFrame *phsBottom = new CD3DHalfsphereFrame;
  if (phsBottom == NULL)
    return false;

  if (!phsBottom->Create(this, n_vert, n_hor, RGB(255, 255, 255), false))
    return false;

  if (!phsBottom->AddToFrame(pFrame))
    return false;
  
  if (!phsBottom->AddScale(D3DRMCOMBINE_REPLACE, 
                           D3DVAL(45), D3DVAL(45), D3DVAL(40)))
    return false;

  //= invert its Z
  if (!phsBottom->AddScale(D3DRMCOMBINE_AFTER, 
                           D3DVAL(1), D3DVAL(1), D3DVAL(-1)))
    return false;

  //= create and apply wrap function
  CD3DTexture *tex = new CD3DTexture;
  if (tex == NULL)
    return false;
  if (!tex->Create(this, ResolveName("Mars.bmp")))
    return false;

  if (!phsTop->ApplySphereWrap(tex, 
                               D3DVAL(0), D3DVAL(0), D3DVAL(0),    
                               D3DVAL(0), D3DVAL(0), D3DVAL(1),
                               D3DVAL(0), D3DVAL(1), D3DVAL(0),
                               D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(1)))
    return false;

  if (!phsBottom->ApplySphereWrap(tex, 
                               D3DVAL(0), D3DVAL(0), D3DVAL(0),    
                               D3DVAL(0), D3DVAL(0), D3DVAL(1),
                               D3DVAL(0), D3DVAL(1), D3DVAL(0),
                               D3DVAL(0), D3DVAL(1), D3DVAL(1), D3DVAL(-1)))
    return false;
 
  return true;
  }
  
bool CD3DCosmosObj::BumpedTerrain(int n_cells, 
                                  double xBeg, double xEnd,
                                  double zBeg, double zEnd,
                                  double yBase, double BumpAmp)
  {
  CD3DBumpedPlaneFrame *terra = new CD3DBumpedPlaneFrame;
  if (terra == NULL)
    return false;

  if (!terra->Create(this, n_cells, xBeg, xEnd, zBeg, zEnd, yBase, BumpAmp))
    return false;

  if (!terra->AddToFrame(m_pTerra))
    return false;

  CD3DTexture *tex = new CD3DTexture;
  if (tex == NULL)
    return false;
  if (!tex->Create(this, ResolveName("Surface.bmp")))
    return false;

  if (!terra->ApplyFlatWrap(tex, D3DVAL(0), D3DVAL(1), D3DVAL(0),    
                                 D3DVAL(0), D3DVAL(-1), D3DVAL(0),
                                 D3DVAL(0), D3DVAL(0), D3DVAL(1),
                                 D3DVAL(0), D3DVAL(0), 
                                 D3DVAL(1.0 / 3.0), D3DVAL(1.0 / 3.0)))
    return false;

  CD3DMaterial *mat = new CD3DMaterial;
  if (mat == NULL)
    return false;
  if (!mat->Create(this, D3DVAL(1), D3DVAL(1), D3DVAL(1), D3DVAL(5)))
    return false;

  if (!terra->SetMaterial(mat))
    return false;

  CD3DFrame *pR1;
  if ((pR1 = CreateRocket()) == NULL)
    return false;

  if (!pR1->AddCombTransform(D3DVAL(0.02), D3DVAL(0.02), D3DVAL(0.02), 
                  D3DVAL(-PI / 2), D3DVAL(0), D3DVAL(0),           
                  D3DVAL(-1.8), D3DVAL(0.2), D3DVAL(0.3)))
    return false;

  CD3DFrame *pR2;
  if ((pR2 = CreateRocket()) == NULL)
    return false;

  if (!pR2->AddCombTransform(D3DVAL(0.02), D3DVAL(0.02), D3DVAL(0.02), 
                  D3DVAL(-PI / 2), D3DVAL(0), D3DVAL(0),           
                  D3DVAL(-2.1), D3DVAL(1), D3DVAL(0.5)))
    return false;

  return true;
  }  

bool CD3DCosmosObj::CreateSLight()
  {
  m_pSpotL = new CD3DSpotLight;
  if (m_pSpotL == NULL)
    return false;

  if (!m_pSpotL->Create(this))
    return false;

  if (!m_pSpotL->SetColorRGB(D3DVAL(0.5), D3DVAL(0.5), D3DVAL(0.5)))
    return false;

  if (!m_pSpotL->SetSpotLightCone(D3DVAL(PI / 3), D3DVAL(PI / 2)))
    return false;

  if (!m_pSpotL->AddToFrame(m_pSpace))
    return false;

  if (!m_pSpotL->AddRotation(D3DRMCOMBINE_AFTER, 
                       D3DVAL(0), D3DVAL(1), D3DVAL(0), D3DVAL(PI / 2)))
    return false;

  double alpha = atan2(-0.4, -1.0);
  if (!m_pSpotL->AddRotation(D3DRMCOMBINE_AFTER, 
                       D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(alpha)))
    return false;

  if (!m_pSpotL->AddTranslation(D3DRMCOMBINE_AFTER, 
                       D3DVAL(1), D3DVAL(1.5), D3DVAL(-1.3)))
    return false;

  return true;
  }

bool CD3DCosmosObj::OnCreate()
  {
  m_pSpace = new CD3DFrame;
  if (m_pSpace == NULL)
    return false;

  if (!m_pSpace->Create(this))
    return false;

  if (!m_pSpace->AddToFrame(this))
    return false;

  if (!CreateSLight())
    return false;

  if (!SunObject())
    return false;
    
  //= adjust camera frame parameters
  D3DVALUE ang = D3DVAL(PI / 6.0);

  CD3DCameraFrame *camera = GetCameraFrame();

  if (!camera->AddRotation(D3DRMCOMBINE_AFTER, 
                           D3DVAL(1), D3DVAL(0), D3DVAL(0), ang))
    return false;
  if (!camera->AddTranslation(D3DRMCOMBINE_AFTER, 
                           D3DVAL(0), D3DVAL(2), D3DVAL(-4)))
    return false;

  if (!CreateMars())
    return false;

  if (!CreateEarth())
    return false;

  m_pTerra = new CD3DFrame;
  if (m_pTerra == NULL)
    return false;

  if (!m_pTerra->Create(this))
    return false;

  if (!m_pTerra->AddToFrame(m_pSpace))
    return false;

  if (!BumpedTerrain(33, -2.0, 2.0, -2.0, 2.0, -0.15, 0.15))
    return false;  

  if (!CreateRock())
    return false;

  if ((m_pRocket = CreateRocket(false)) == NULL)
    return false;

  if (!m_pTerra->AddTranslation(D3DRMCOMBINE_AFTER, 
                                D3DVAL(0), D3DVAL(0), D3DVAL(-1.5)))
    return false;

  if (!m_pTerra->SetRotation(m_pSpace, 
                             D3DVAL(0), D3DVAL(1), D3DVAL(0), 
                             D3DVAL(PI / 100)))
    return false;

  if (!CreateUFOs())
    return false;

  if (!SetCameraParam(1.0, 1.0, FLT_MAX, RGB(63, 63, 63), RGB(63, 63, 63)))
    return false;

  //= "Create" Universe as back curtain of objects images
  if (!SetImageFile(ResolveName("Stars.bmp")))
    return false;

  if (!SetMoveCallback())
    return false;

  if (!SetTickEnable(true))
    return false;

  return true;
  }
