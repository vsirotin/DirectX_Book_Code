// d3dPyramidFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dPyramidFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DPyramidFrame

IMPLEMENT_DYNAMIC(CD3DPyramidFrame, CD3DFrame)

CD3DPyramidFrame::CD3DPyramidFrame()
  {
  }

CD3DPyramidFrame::~CD3DPyramidFrame()
  {
  }

bool CD3DPyramidFrame::Create(CD3DMainObj *pOwner, D3DCOLOR color)
  {
  
  //= Basisform der Pyramide festlegen
  static D3DVECTOR vert[] = { 
    {D3DVAL(-1), D3DVAL(-1), D3DVAL(0)},   //= Quadratische Grundfläche
    {D3DVAL(-1), D3DVAL(1),  D3DVAL(0)}, 
    {D3DVAL(1),  D3DVAL(1),  D3DVAL(0)}, 
    {D3DVAL(1),  D3DVAL(-1), D3DVAL(0)}, 
    {D3DVAL(0),  D3DVAL(0),  D3DVAL(1)}};  //= Gipfel
  static DWORD facedata[] = { //= 5 Aproximierungselementen
    4, 0, 0, 1, 0, 2, 0, 3, 0,  
    3, 4, 1, 0, 1, 3, 1,        
    3, 4, 2, 1, 2, 0, 2,
    3, 4, 3, 2, 3, 1, 3,
    3, 4, 4, 3, 4, 2, 4,
    0};

  
  int i, j, k, n1, n2, n3;
  
  if (!CD3DFrame::Create(pOwner))
    return false;
  
  //= Normalenvektor der Pyramide berechnen
  D3DVECTOR norm[5];


  for (i = 0, j = 0; j < 5; j++)
    {
    k = 2 * facedata[i] + 1;
    n1 = facedata[i + 1];
    n2 = facedata[i + 3];
    n3 = facedata[i + 5];

    NormalFromFace(&vert[n1], &vert[n2], &vert[n3], &norm[j]);
    i += k;
    }

  //= Pyramide zu Direct3D hinzufügen
  if (!AddFaces(5, vert, 5, norm, facedata, NULL))
    return false;
  
  //= Standardfarbe definieren
  if (!SetColor(color))
    return false;
  
  return true;
  }

