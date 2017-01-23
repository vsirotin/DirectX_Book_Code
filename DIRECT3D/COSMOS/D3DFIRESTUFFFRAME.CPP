// d3dFireStuffFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dFireStuffFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DTorusFrame

IMPLEMENT_DYNAMIC(CD3DTorusFrame, CD3DFrame)

CD3DTorusFrame::CD3DTorusFrame()
  {
  }

CD3DTorusFrame::~CD3DTorusFrame()
  {
  }

bool CD3DTorusFrame::Create(CD3DMainObj *pOwner, int n_big, int n_small,
                                                 double r_small, D3DCOLOR color,
                                                 CD3DLightFrame *lpL)
  //= big radius of torus = 1.0
  {
  int i, j;
  D3DVECTOR *circle;
  circle = new D3DVECTOR [n_small * n_big];
  D3DVECTOR *sl = circle;
  
  //= initial cut of torus
  for (i = 0; i < n_small; i++)
    {
    sl->x = D3DVAL(cos(2.0 * PI / n_small * i) * r_small + 1.0);
    sl->y = D3DVAL(0);
    sl->z = -D3DVAL(sin(2.0 * PI / n_small * i) * r_small);
    sl++;
    }

  //= all rest cuts of torus
  for (j = 1; j < n_big; j++)
    {
    double phi = 2.0 * PI / n_big * j;
    double si = sin(phi);
    double co = cos(phi);
    D3DVECTOR *sc = circle;

    for (i = 0; i < n_small; i++)
      {
      sl->x = D3DVAL(sc->x * co - sc->y * si);
      sl->y = D3DVAL(sc->x * si + sc->y * co);
      sl->z = sc->z;
      sl++;
      sc++;
      }
    }

  DWORD nfd = n_small * n_big * 10 + 1;
  DWORD *facedata;

  facedata = new DWORD [nfd];
  DWORD ind = 0;

  for (j = 0; j < n_big - 1; j++)
    {
    for (i = 0; i < n_small - 1; i++)
      {
      facedata[ind++] = 4;
      facedata[ind++] = j * n_small + i;
      facedata[ind++] = j * n_small + i + 1;
      facedata[ind++] = j * n_small + i + 1 + n_small;
      facedata[ind++] = j * n_small + i + n_small;
      }
    
    //= last face of layer
    facedata[ind++] = 4;
    facedata[ind++] = j * n_small + n_small - 1;
    facedata[ind++] = j * n_small;
    facedata[ind++] = j * n_small + n_small;
    facedata[ind++] = j * n_small + n_small + n_small - 1;

    }
  
  //= last layer  
  for (i = 0; i < n_small - 1; i++)
    {
    facedata[ind++] = 4;
    facedata[ind++] = (n_big - 1) * n_small + i;
    facedata[ind++] = (n_big - 1) * n_small + i + 1;
    facedata[ind++] = i + 1;
    facedata[ind++] = i;
    }
    
  //= last face of layer
  facedata[ind++] = 4;
  facedata[ind++] = n_big * n_small - 1;
  facedata[ind++] = (n_big - 1) * n_small;
  facedata[ind++] = 0;
  facedata[ind++] = n_small - 1;

  facedata[ind++] = 0;
  if (!CD3DFrame::Create(pOwner))
    {
    delete [] facedata;
    delete [] circle;
    return false;
    }

  //= Pass mesh to Direct3D
  if (!AddFaces(n_small * n_big, circle, 0, NULL, facedata, NULL))
    {
    delete [] facedata;
    delete [] circle;
    return false;
    }

  delete [] facedata;
  delete [] circle;
  
  //= Define default mesh color, i.e., color of all its faces
  if (!SetColor(color))
    return false;

  if (lpL != NULL)
    {
    if (!AddShadow(lpL, D3DVAL(0), D3DVAL(0), D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(0)))
      return false;
    }

  return true;
  }


/////////////////////////////////////////////////////////////////////////////
// CD3DFireStuffFrame

IMPLEMENT_DYNAMIC(CD3DFireStuffFrame, CD3DFrame)

CD3DFireStuffFrame::CD3DFireStuffFrame()
  {
  }

CD3DFireStuffFrame::~CD3DFireStuffFrame()
  {
  }

bool CD3DFireStuffFrame::Create(CD3DMainObj *pOwner, int n_big, int n_small, 
                                double r_small, D3DCOLOR color, 
                                CD3DLightFrame *lpL)
  {
  if (!CD3DFrame::Create(pOwner))
    return false;

  CD3DTorusFrame *pT1 = new CD3DTorusFrame;
  if (pT1 == NULL)
    return false;
  if (!pT1->Create(pOwner, n_big, n_small, r_small, color, lpL))
    return false;
  if (!pT1->AddToFrame(this))
    return false;

  CD3DTorusFrame *pT2 = new CD3DTorusFrame;
  if (pT2 == NULL)
    return false;
  if (!pT2->Create(pOwner, n_big, n_small, r_small, color, lpL))
    return false;
  if (!pT2->AddToFrame(this))
    return false;
  if (!pT2->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(PI / 2)))
    return false;

  CD3DTorusFrame *pT3 = new CD3DTorusFrame;
  if (pT3 == NULL)
    return false;
  if (!pT3->Create(pOwner, n_big, n_small, r_small, color, lpL))
    return false;
  if (!pT3->AddToFrame(this))
    return false;
  if (!pT3->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(1), D3DVAL(0), D3DVAL(PI / 2)))
    return false;

  return true;
  }  

  
