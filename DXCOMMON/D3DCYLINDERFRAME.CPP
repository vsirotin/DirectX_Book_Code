// d3dCylinderFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dCylinderFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DCylinderFrame

IMPLEMENT_DYNAMIC(CD3DCylinderFrame, CD3DFrame)

CD3DCylinderFrame::CD3DCylinderFrame()
  {
  }

CD3DCylinderFrame::~CD3DCylinderFrame()
  {
  }

bool CD3DCylinderFrame::Create(CD3DMainObj *pOwner, 
                           int vert_planes, D3DCOLOR color,
                           bool orientation)
  //= Netz festlegen
  //= vert_planes - Anzahl der vertikallen Flächen
  //= Radius = 1.
  {
  int    j, ind, ind_vert, ind_norm;
  double d;
  double x, y, z;
  D3DVECTOR *cyl_vert;     //= Ecken
  D3DVECTOR *cyl_norm;     //= Normalen
  DWORD     *cyl_facedata; 

  if (vert_planes < 3)
    return false;

  //= Speicher belegen und checken
  cyl_vert = new D3DVECTOR [2 * vert_planes];
  if (cyl_vert == NULL)
    return false;
  cyl_norm = new D3DVECTOR [vert_planes];
  if (cyl_norm == NULL)
    {
    delete [] cyl_vert;
    return false;
    }
  cyl_facedata = new DWORD [vert_planes * 9 + 1];
  if (cyl_facedata == NULL)
    {
    delete [] cyl_norm;
    delete [] cyl_vert;
    return false;
    }                                       
    
  //= Objekt der Basisklasse anlegen
  if (!CD3DFrame::Create(pOwner))
    return false;

  ind_vert = 0;
  ind_norm = 0;
  for (j = 0; j < vert_planes; j++)
    {
    //= Berechnen von zwei Ecken auf der gleichen Schnittfläche
    d = 2.0 * PI / vert_planes * j;
    //= Koordinaten der XY - Fläche
    x = cos(d);
    y = sin(d);
    //= Erste Ecke der unteren Grenze des Zylinders
    z = -1.0;
    //= In Ecke-Feld hinzufügen
    cyl_vert[ind_vert].x = D3DVAL(x);
    cyl_vert[ind_vert].y = D3DVAL(y);
    cyl_vert[ind_vert++].z = D3DVAL(z);
    //= Zweite Ecke auf dem Dach des Zylinders
    z = 1.0;
    cyl_vert[ind_vert].x = D3DVAL(x);
    cyl_vert[ind_vert].y = D3DVAL(y);
    cyl_vert[ind_vert++].z = D3DVAL(z);
    //= Beide Ecken haben die gleiche Normale
    z = 0.0;
    cyl_norm[ind_norm].x = D3DVAL(x);
    cyl_norm[ind_norm].y = D3DVAL(y);
    cyl_norm[ind_norm++].z = D3DVAL(z);
    }

  //= Feld mit Aproximierungselementen anlegen
  //= Orientierung beachten
  ind = 0; //= current index
  if (orientation)
    { //= Außenoberfläche wird sichtbar
    for (j = 0; j < vert_planes - 1; j++)
      {
      cyl_facedata[ind++] = 4;
      cyl_facedata[ind++] = 2 * j;
      cyl_facedata[ind++] = j;
      cyl_facedata[ind++] = 2 * j + 2;
      cyl_facedata[ind++] = j + 1;
      cyl_facedata[ind++] = 2 * j + 3;
      cyl_facedata[ind++] = j + 1;
      cyl_facedata[ind++] = 2 * j + 1;
      cyl_facedata[ind++] = j;
      }

    //= Daten über letztes Aproximierungselement hinzufügen
    cyl_facedata[ind++] = 4; 
    cyl_facedata[ind++] = 2 * vert_planes - 2;
    cyl_facedata[ind++] = vert_planes - 1;
    cyl_facedata[ind++] = 0;
    cyl_facedata[ind++] = 0;
    cyl_facedata[ind++] = 1;
    cyl_facedata[ind++] = 0;
    cyl_facedata[ind++] = 2 * vert_planes - 1;
    cyl_facedata[ind++] = vert_planes - 1;
    } 

  else
    { //= Innere Oberfläche wird sichtbar
    //= Umgekehrte Orientierung
    for (j = 0; j < vert_planes - 1; j++)
      {
      cyl_facedata[ind++] = 4;
      cyl_facedata[ind++] = 2 * j;
      cyl_facedata[ind++] = j;
      cyl_facedata[ind++] = 2 * j + 1;
      cyl_facedata[ind++] = j;
      cyl_facedata[ind++] = 2 * j + 3;
      cyl_facedata[ind++] = j + 1;
      cyl_facedata[ind++] = 2 * j + 2;
      cyl_facedata[ind++] = j + 1;
      }

    //= Daten über letztes Aproximierungselement hinzufügen
    cyl_facedata[ind++] = 4; 
    cyl_facedata[ind++] = 2 * vert_planes - 2;
    cyl_facedata[ind++] = vert_planes - 1;
    cyl_facedata[ind++] = 2 * vert_planes - 1;
    cyl_facedata[ind++] = vert_planes - 1;
    cyl_facedata[ind++] = 1;
    cyl_facedata[ind++] = 0;
    cyl_facedata[ind++] = 0;
    cyl_facedata[ind++] = 0;
    } 
    

  cyl_facedata[ind++] = 0;
  
  //= Netz zu Direct3D hinzufügen. Farbe festlegen
  if (!AddFaces(ind_vert, cyl_vert, ind_norm, cyl_norm, 
                cyl_facedata, NULL) || !SetColor(color))
    {
    delete [] cyl_facedata;
    delete [] cyl_norm;
    delete [] cyl_vert;
    return false;
    }

  delete [] cyl_facedata;
  delete [] cyl_norm;
  delete [] cyl_vert;
  return true;
  }
