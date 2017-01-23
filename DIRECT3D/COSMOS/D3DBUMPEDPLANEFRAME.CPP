// d3dBumpedPlaneFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dBumpedPlaneFrame.h"
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static double fRand(double amp1, double amp2)
  {
  double r = (double)rand() / (double)RAND_MAX;

  return (amp1 + r * (amp2 - amp1));
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DBumpedPlaneFrame

IMPLEMENT_DYNAMIC(CD3DBumpedPlaneFrame, CD3DFrame)

CD3DBumpedPlaneFrame::CD3DBumpedPlaneFrame()
  {
  }

CD3DBumpedPlaneFrame::~CD3DBumpedPlaneFrame()
  {
  }

bool CD3DBumpedPlaneFrame::Create(CD3DMainObj *pOwner, int n_cells,
                                  double xBeg, double xEnd,
                                  double zBeg, double zEnd,
                                  double yBase, double BumpAmp, D3DCOLOR color)
  //= 1. create square mesh n_cells * n_cells in XZ plane
  //= 2. disturb positions of internal nodes
  //= 3. assign random Y-value from interval [yBase, yBase + BumpAmp]
  //= 4. adjust position in scene
  {
  double dx = (xEnd - xBeg) / n_cells;
  double dz = (zEnd - zBeg) / n_cells;
  double xDeltaMax = dx / 3;
  double zDeltaMax = dz / 3;
  int    nv = (n_cells + 1) * (n_cells + 1);
  D3DVECTOR *verts;

  verts = new D3DVECTOR [nv];
  if (verts == NULL)
    return false;

  int        i, j;
  double     x, z;
  D3DVECTOR *vv = verts;

  //= assign all X values of knots
  for (i = 0; i <= n_cells; i++) //= along X
    {
    x = i * dx;

    for (j = 0; j <= n_cells; j++) //= along Z
      {
      if (i == 0 || j == 0 || i == n_cells || j == n_cells)
        {
        vv->x = D3DVAL(xBeg + x);
        }
      else
        {
        vv->x = D3DVAL(xBeg + x + fRand(-xDeltaMax, xDeltaMax));
        }
      vv++;
      }
    }

  vv = verts;  //= assign all Y values - heights in knots

  for (i = 0; i <= n_cells; i++)
    {
    for (j = 0; j <= n_cells; j++)
      {
      vv->y = D3DVAL(fRand(yBase, yBase + BumpAmp));
      vv++;
      }
    }

  vv = verts;  //= assign all Z values of knots

  for (i = 0; i <= n_cells; i++) //= along X
    {
    for (j = 0; j <= n_cells; j++) //= along Z
      {
      z = j * dz;

      if (i == 0 || j == 0 || i == n_cells || j == n_cells)
        {
        vv->z = D3DVAL(zBeg + z);
        }
      else
        {
        vv->z = D3DVAL(zBeg + z + fRand(-zDeltaMax, zDeltaMax));
        }
      vv++;
      }
    }

  //= create facedata, all will be triangles
  DWORD n_fd = 2 * 4 * n_cells * n_cells + 1;
  DWORD ind = 0;
  DWORD *fd;

  fd = new DWORD [n_fd];
  if (verts == NULL)
    return false;

  for (i = 0; i < n_cells; i++) //= along X
    {
    for (j = 0; j < n_cells; j++) //= along Z
      {
      int k = i * (n_cells + 1) + j;

      fd[ind++] = 3;
      fd[ind++] = k;
      fd[ind++] = k + 1;
      fd[ind++] = k + 1 + (n_cells + 1);
      fd[ind++] = 3;
      fd[ind++] = k;
      fd[ind++] = k + 1 + (n_cells + 1);
      fd[ind++] = k + (n_cells + 1);
      }
    }

  fd[ind++] = 0; //= finish
  
  //= Create base class object
  if (!CD3DFrame::Create(pOwner))
    return false;
      
  if (!AddFaces(nv, verts, 0, NULL, fd, NULL) || 
      !SetColor(color))
    {
    delete [] fd;
    delete [] verts;
    return false;
    }

  //= free temporary memory
  delete [] fd;
  delete [] verts;

  return true;
  }  

