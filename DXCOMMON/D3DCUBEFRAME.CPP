// d3dCubeFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dCubeFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DCubeFrame

IMPLEMENT_DYNAMIC(CD3DCubeFrame, CD3DFrame)

CD3DCubeFrame::CD3DCubeFrame()
  {
  }

CD3DCubeFrame::~CD3DCubeFrame()
  {
  }

bool CD3DCubeFrame::Create(CD3DMainObj *pOwner, 
                           D3DCOLOR color)
  {
  //= Standardform des Würfels definieren
  static D3DVECTOR cube_vert[] = { //= Körperecke
    {D3DVAL(-1), D3DVAL(-1), D3DVAL(-1)},  
    {D3DVAL(-1), D3DVAL(-1), D3DVAL(1)}, 
    {D3DVAL(-1), D3DVAL(1),  D3DVAL(-1)}, 
    {D3DVAL(-1), D3DVAL(1),  D3DVAL(1)}, 
    {D3DVAL(1),  D3DVAL(-1), D3DVAL(-1)}, 
    {D3DVAL(1),  D3DVAL(-1), D3DVAL(1)}, 
    {D3DVAL(1),  D3DVAL(1),  D3DVAL(-1)}, 
    {D3DVAL(1),  D3DVAL(1),  D3DVAL(1)}};
  static D3DVECTOR cube_norm[] = { //= Normale
    {D3DVAL(1),  D3DVAL(0),  D3DVAL(0)}, 
    {D3DVAL(-1), D3DVAL(0),  D3DVAL(0)}, 
    {D3DVAL(0),  D3DVAL(1),  D3DVAL(0)}, 
    {D3DVAL(0),  D3DVAL(-1), D3DVAL(0)}, 
    {D3DVAL(0),  D3DVAL(0),  D3DVAL(1)}, 
    {D3DVAL(0),  D3DVAL(0),  D3DVAL(-1)}};
  static DWORD cube_facedata[] = { //= Elementen
    4, 0, 5, 2, 5, 6, 5, 4, 5,
    4, 0, 1, 1, 1, 3, 1, 2, 1,
    4, 2, 2, 3, 2, 7, 2, 6, 2,
    4, 4, 0, 6, 0, 7, 0, 5, 0,
    4, 0, 3, 4, 3, 5, 3, 1, 3,
    4, 7, 4, 3, 4, 1, 4, 5, 4,
    0};

  if (!CD3DFrame::Create(pOwner))
    return false;

  //= Würfel zu Direct3D hinzufügen
  if (!AddFaces(8, cube_vert, 6, cube_norm, cube_facedata, NULL))
    return false;

  //= Standardfarbe definieren
  if (!SetColor(color))
    return false;

  return true;
  }

