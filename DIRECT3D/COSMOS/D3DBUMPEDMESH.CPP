// d3dBumpedMesh.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dBumpedMesh.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DBumpedMesh

IMPLEMENT_DYNAMIC(CD3DBumpedMesh, CD3DFrame)

CD3DBumpedMesh::CD3DBumpedMesh()
  {
  }

CD3DBumpedMesh::~CD3DBumpedMesh()
  {
  }

bool CD3DBumpedMesh::Create(CD3DMainObj *pOwner, D3DVALUE aX, D3DVALUE aY, D3DVALUE aZ, 
                         D3DVALUE bX, D3DVALUE bY, D3DVALUE bZ, 
                         D3DVALUE cX, D3DVALUE cY, D3DVALUE cZ, 
                         D3DVALUE dX, D3DVALUE dY, D3DVALUE dZ,
                         D3DVALUE dPerimeter, D3DVALUE dBumpMapAmplitude, D3DCOLOR color) 
  {
  BumpedTrian(aX, aY, aZ, bX, bY, bZ, dX, dY, dZ, dPerimeter, dBumpMapAmplitude, color);
  BumpedTrian(bX, bY, bZ, cX, cY, cZ, dX, dY, dZ, dPerimeter, dBumpMapAmplitude, color);
  }

  {
  //= define basic shape of generic CUBE
  static D3DVECTOR cube_vert[] = { //= all 8 vertices
    {D3DVAL(-1), D3DVAL(-1), D3DVAL(-1)},  
    {D3DVAL(-1), D3DVAL(-1), D3DVAL(1)}, 
    {D3DVAL(-1), D3DVAL(1),  D3DVAL(-1)}, 
    {D3DVAL(-1), D3DVAL(1),  D3DVAL(1)}, 
    {D3DVAL(1),  D3DVAL(-1), D3DVAL(-1)}, 
    {D3DVAL(1),  D3DVAL(-1), D3DVAL(1)}, 
    {D3DVAL(1),  D3DVAL(1),  D3DVAL(-1)}, 
    {D3DVAL(1),  D3DVAL(1),  D3DVAL(1)}};
  static D3DVECTOR cube_norm[] = { //= all 6 different normals
    {D3DVAL(1),  D3DVAL(0),  D3DVAL(0)}, 
    {D3DVAL(-1), D3DVAL(0),  D3DVAL(0)}, 
    {D3DVAL(0),  D3DVAL(1),  D3DVAL(0)}, 
    {D3DVAL(0),  D3DVAL(-1), D3DVAL(0)}, 
    {D3DVAL(0),  D3DVAL(0),  D3DVAL(1)}, 
    {D3DVAL(0),  D3DVAL(0),  D3DVAL(-1)}};
  static DWORD cube_facedata[] = { //= all 6 faces
    4, 0, 5, 2, 5, 6, 5, 4, 5,
    4, 0, 1, 1, 1, 3, 1, 2, 1,
    4, 2, 2, 3, 2, 7, 2, 6, 2,
    4, 4, 0, 6, 0, 7, 0, 5, 0,
    4, 0, 3, 4, 3, 5, 3, 1, 3,
    4, 7, 4, 3, 4, 1, 4, 5, 4,
    0};

  if (!CD3DFrame::Create(pOwner))
    return false;

  //= finally: pass a cube to Direct3D
  if (!AddFaces(8, cube_vert, 6, cube_norm, cube_facedata, NULL))
    return false;

  //= Define default mesh color, i.e., color of all its faces
  if (!SetColor(color))
    return false;

  return true;
  }

