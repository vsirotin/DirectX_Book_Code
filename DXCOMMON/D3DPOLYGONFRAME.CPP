// d3dPolygonFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dPolygonFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CD3DPolygonFrame

IMPLEMENT_DYNAMIC(CD3DPolygonFrame, CD3DFrame)

CD3DPolygonFrame::CD3DPolygonFrame()
  {
  }

CD3DPolygonFrame::~CD3DPolygonFrame()
  {
  }

bool CD3DPolygonFrame::Create(CD3DMainObj *pOwner,
                              int n_vert, D3DVECTOR *vert,
                              D3DCOLOR color, 
                              bool orientation)
  {
  DWORD *facedata; 

  //= Bedienungen checken
  if (n_vert <= 2)
    return false; 

  //= Speicherblock anlegen
  if ((facedata = new DWORD [2 * n_vert + 2]) == NULL)
    return false; //= no memory

  //= Berechnen der Normalen in  den Eckpunkten. 
  //= Sie sind alle gleich.
  D3DVECTOR norm;
    
  
  NormalFromFace(&vert[0], &vert[1], &vert[2], &norm);

  //= Aproximierungselement-Feld anlegen
  int i, ind = 0;

  //= Die Orientierung berücksichtigen
  if (orientation) //= Positive Orientierung 
    {
    facedata[ind++] = n_vert;
    for (i = 0; i < n_vert; i++)
      {
      facedata[ind++] = i;  //= Index des Eckpunktes
      facedata[ind++] = 0;  //= Index der Normale
      }
    }
  else
    { //= Umgekehrte Orientierung 
    norm.x = -norm.x;
    norm.y = -norm.y;
    norm.z = -norm.z;
    facedata[ind++] = n_vert;
    for (i = 0; i < n_vert; i++)
      {
      facedata[ind++] = n_vert - i - 1;  
      facedata[ind++] = 0;
      }
    }

  facedata[ind++] = 0;         

  if (!CD3DFrame::Create(pOwner))
    {
    delete [] facedata;
    return false;
    }

  //= Netz in Direct3D hinzufügen
  if (!AddFaces(n_vert, vert, 1, &norm, facedata, NULL))
    {
    delete [] facedata;
    return false;
    }

  //= Standardfarbe für das Netz definieren
  if (!SetColor(color))
    {
    delete [] facedata;
    return false;
    }

  delete [] facedata;  
  
  return true; 
  }

