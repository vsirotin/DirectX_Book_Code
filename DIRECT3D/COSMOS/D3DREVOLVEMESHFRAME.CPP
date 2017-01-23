// d3dRevolveMeshFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dRevolveMeshFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DRevolveMeshFrame

IMPLEMENT_DYNAMIC(CD3DRevolveMeshFrame, CD3DFrame)

CD3DRevolveMeshFrame::CD3DRevolveMeshFrame()
  {
  }

CD3DRevolveMeshFrame::~CD3DRevolveMeshFrame()
  {
  }

bool CD3DRevolveMeshFrame::Create(CD3DMainObj *pOwner, 
                           int nCur, D3DVECTOR *curve,
                           int vert_planes, D3DCOLOR color)
  //= Bild the mesh for a side surface of a rotating curve (2*PI).
  //= nCur > 2 is a number of curve points.
  //= vert_planes > 2 is a number of vertical planes (sectors, pies).
  //= Radii of a model is assumed as X values.
  //= Only vertices of a mesh are computed, 
  //= normals are assigned by Direct3D automatically.
  //= !!! First and Last points of a curve must have zero X-coordinate
  {
  int    i, j, ind, ind_vert;
  double d;
  double x, y;
  D3DVECTOR *vert;
  DWORD     *facedata; 

  //= check values of vert_planes and nCur
  //= and coordinates of extreme points of a curve
  if (vert_planes < 3 || nCur < 3 ||
      curve[0].x != D3DVAL(0)     ||
      curve[nCur - 1].x != D3DVAL(0))
    return false;

  //= count a number of mesh vertices
  int vert_number = vert_planes * (nCur - 2) + 2;

  //= allocate memory and check 
  vert = new D3DVECTOR [vert_number];
  if (vert == NULL)
    return false;

  facedata = new DWORD [vert_planes * (8 + (nCur - 3) * 5) + 1];
  if (facedata == NULL)
    {
    delete [] vert;
    return false;
    }                                       
    
  //= Create base class object
  if (!CD3DFrame::Create(pOwner))
    return false;

  ind_vert = 0;
  //= first tip of a body
  vert[ind_vert].x = D3DVAL(0);
  vert[ind_vert].y = D3DVAL(0);
  vert[ind_vert++].z = curve[0].z;

  //= Create intermediate layers of vertices
  for (i = 1; i < nCur - 1; i++)
    for (j = 0; j < vert_planes; j++)
      {
      //= Let's compute vertex that lies on the j-th cutting plane
      d = 2.0 * PI / vert_planes * j;
      //= Coordinates of vertex on XY plane
      x = cos(d) * curve[i].x;
      y = sin(d) * curve[i].x;
      vert[ind_vert].x = D3DVAL(x);
      vert[ind_vert].y = D3DVAL(y);
      vert[ind_vert++].z = curve[i].z;
      }

  //= add next tip of a body
  vert[ind_vert].x = D3DVAL(0);
  vert[ind_vert].y = D3DVAL(0);
  vert[ind_vert++].z = curve[nCur - 1].z;

  //= -------- create triangles data
  ind = 0;

  //= Create top layer of trg
  for (j = 0; j < vert_planes - 1; j++)
    {
    facedata[ind++] = 3; //= triangle data without vertices' normals
    facedata[ind++] = 0; //= always first tip
    facedata[ind++] = j + 1;
    facedata[ind++] = j + 2;
    }
  //= last trg
  facedata[ind++] = 3;
  facedata[ind++] = 0;
  facedata[ind++] = vert_planes;
  facedata[ind++] = 1;

  //= Create intermediate layers of rectangles but trgs
  //= nCur - 3 layers
  for (i = 0; i < nCur - 3; i++)
    { 
    for (j = 0; j < vert_planes - 1; j++)
      {
      facedata[ind++] = 4;
      facedata[ind++] = vert_planes * i + j + 1;
      facedata[ind++] = vert_planes * (i + 1) + j + 1;
      facedata[ind++] = vert_planes * (i + 1) + j + 2;
      facedata[ind++] = vert_planes * i + j + 2;
      }
    //= last rect of a layer
    facedata[ind++] = 4;
    facedata[ind++] = vert_planes * (i + 1);
    facedata[ind++] = vert_planes * (i + 2);
    facedata[ind++] = vert_planes * (i + 1) + 1;
    facedata[ind++] = vert_planes * i + 1;
    }

  //= last layer of trgs near the bottom tip of a body
  i = nCur - 3;
  for (j = 0; j < vert_planes - 1; j++)
    {
    facedata[ind++] = 3;
    facedata[ind++] = vert_planes * i + j + 1;
    facedata[ind++] = vert_number - 1;
    facedata[ind++] = vert_planes * i + j + 2;
    }
  //= last rect of a layer
  facedata[ind++] = 3;
  facedata[ind++] = vert_planes * (i + 1);
  facedata[ind++] = vert_number - 1;
  facedata[ind++] = vert_planes * i + 1;
    
  //= The end of array
  facedata[ind++] = 0;
  
  //= Pass mesh to Direct3D + set mesh color
  if (!AddFaces(ind_vert, vert, 0, NULL, 
                facedata, NULL) || !SetColor(color))
    {
    delete [] facedata;
    delete [] vert;
    return false;
    }

  delete [] facedata;
  delete [] vert;
  return true;
  }
