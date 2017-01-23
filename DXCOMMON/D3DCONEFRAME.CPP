// d3dConeFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dConeFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DConeFrame

IMPLEMENT_DYNAMIC(CD3DConeFrame, CD3DFrame)

CD3DConeFrame::CD3DConeFrame()
  {
  }

CD3DConeFrame::~CD3DConeFrame()
  {
  }

bool CD3DConeFrame::Create(CD3DMainObj *pOwner, 
                           int vert_planes, D3DCOLOR color,
                           bool orientation)
  //= Netz für Außen-Oberfläche des Kegels
  //= vert_planes - Anzahl von vertikalen Flächen
  //= Radius = 1
  {
  int    j, ind, ind_vert, ind_norm;
  double d;
  double x, y, z;
  D3DVECTOR *cone_vert;     //= Ecken
  D3DVECTOR *cone_norm;     //= Normalen
  D3DVECTOR  temp_norm;     //= Reservierter Speicher
  DWORD     *cone_facedata; 

  //= Wert vert_planes checken
  if (vert_planes < 3)
    return false;

  //= Speicher belegen und checken
  cone_vert = new D3DVECTOR [vert_planes + 1];
  if (cone_vert == NULL)
    return false;
  cone_norm = new D3DVECTOR [vert_planes + 1];
  if (cone_norm == NULL)
    {
    delete [] cone_vert;
    return false;
    }
  cone_facedata = new DWORD [vert_planes * 9 + 1];
  if (cone_facedata == NULL)
    {
    delete [] cone_norm;
    delete [] cone_vert;
    return false;
    }                                       
    
  //= Objekt der Basisklasse anlegen
  if (!CD3DFrame::Create(pOwner))
    return false;

  ind_vert = 0;
  ind_norm = 0;
  for (j = 0; j < vert_planes; j++)
    {
    //= Ecke für Fläche i berechnen
    d = 2.0 * PI / vert_planes * j;
    //= Koordinaten der Ecke in der XY-Fläche
    x = cos(d);
    y = sin(d);
    //= Erste Ecke am unterste Grenze vom Kegel
    z = 0.0;
    //= In Ecke-Feld (array) hinzufügen
    cone_vert[ind_vert].x = D3DVAL(x);
    cone_vert[ind_vert].y = D3DVAL(y);
    cone_vert[ind_vert++].z = D3DVAL(z);
    
    //= Normalvektor berechenen
   
    temp_norm.x = D3DVAL(x);
    temp_norm.y = D3DVAL(y);
    z = 1.0; 
    temp_norm.z = D3DVAL(z);
    //= Normalisierung
    D3DRMVectorNormalize(&temp_norm);
    cone_norm[ind_norm] = temp_norm;
    ind_norm++;
    }

  //= Letzte Ecke (Gipfel vom Kegel) und seine Normale
  cone_vert[ind_vert].x = D3DVAL(0);
  cone_vert[ind_vert].y = D3DVAL(0);
  cone_vert[ind_vert++].z = D3DVAL(1);
  cone_norm[ind_norm].x = D3DVAL(0);
  cone_norm[ind_norm].y = D3DVAL(0);
  cone_norm[ind_norm++].z = D3DVAL(1);

  //= Feld von Elementen vorbereiten
  //= Orientierung beachten
  ind = 0; //= Aktueller Index
  if (orientation)
    { //= Außeroberfläche wird sichtbar
    for (j = 0; j < vert_planes - 1; j++)
      {
      cone_facedata[ind++] = 3;
      cone_facedata[ind++] = j;
      cone_facedata[ind++] = j;
      cone_facedata[ind++] = j + 1;
      cone_facedata[ind++] = j + 1;
      cone_facedata[ind++] = ind_norm - 1;
      cone_facedata[ind++] = ind_norm - 1;
      }

    //= Letztes Element
    cone_facedata[ind++] = 3; 
    cone_facedata[ind++] = vert_planes - 1;
    cone_facedata[ind++] = vert_planes - 1;
    cone_facedata[ind++] = 0;
    cone_facedata[ind++] = 0;
    cone_facedata[ind++] = ind_norm - 1;
    cone_facedata[ind++] = ind_norm - 1;
    } 

  else
    { //= Interne Oberfläche wird sichtbar
    //= Umgekehrte Orientierung
    for (j = 0; j < vert_planes - 1; j++)
      {
      cone_facedata[ind++] = 3;
      cone_facedata[ind++] = j;
      cone_facedata[ind++] = j;
      cone_facedata[ind++] = ind_norm - 1;
      cone_facedata[ind++] = ind_norm - 1;
      cone_facedata[ind++] = j + 1;
      cone_facedata[ind++] = j + 1;
      }

    //= Letztes Element
    cone_facedata[ind++] = 3; 
    cone_facedata[ind++] = vert_planes - 1;
    cone_facedata[ind++] = vert_planes - 1;
    cone_facedata[ind++] = ind_norm - 1;
    cone_facedata[ind++] = ind_norm - 1;
    cone_facedata[ind++] = 0;
    cone_facedata[ind++] = 0;
    } 
    
  
  cone_facedata[ind++] = 0;
  
  //= Netz in Direct3D hinzufügen. Farbe festlegen
  if (!AddFaces(ind_vert, cone_vert, ind_norm, cone_norm, 
                cone_facedata, NULL) || !SetColor(color))
    {
    delete [] cone_facedata;
    delete [] cone_norm;
    delete [] cone_vert;
    return false;
    }

  delete [] cone_facedata;
  delete [] cone_norm;
  delete [] cone_vert;
  return true;
  }
