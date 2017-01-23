// d3dHalfsphereFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dHalfsphereFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DHalfsphereFrame

IMPLEMENT_DYNAMIC(CD3DHalfsphereFrame, CD3DFrame)

CD3DHalfsphereFrame::CD3DHalfsphereFrame()
  {
  }

CD3DHalfsphereFrame::~CD3DHalfsphereFrame()
  {
  }

bool CD3DHalfsphereFrame::Create(CD3DMainObj *pOwner,
                              int vert_planes, int hor_planes, 
                              D3DCOLOR color,
                              bool orientation)
  //= Netz für die Halbsphäre anlegen
  //= vert_planes - Anzahl der vertikalen Flächen
  //= hor_planes  - Anzahl der horizontalen Flächen
  //= Radius =  1.
  {
  int        i, j, ind, ind_vert, ind_norm;
  double     d, p;         //= Aktueller Winkel
  double     x, y, z;      //= Aktuelle Koordinaten
  D3DVECTOR *hat_vert;     //= Ecken
  D3DVECTOR *hat_norm;     //= Normallen
  DWORD     *hat_facedata; 

 
  if (vert_planes < 3 || hor_planes < 1)
    return false;

  //= Speicher belegen
  hat_vert = new D3DVECTOR [vert_planes * (hor_planes + 1) + 1];
  if (hat_vert == NULL)
    return false;
  hat_norm = new D3DVECTOR [vert_planes * (hor_planes + 1) + 1];
  if (hat_norm == NULL)
    {
    delete [] hat_vert;
    return false;
    }
  hat_facedata = new DWORD [vert_planes * hor_planes * 9 + vert_planes * 7 + 1];
  if (hat_facedata == NULL)
    {
    delete [] hat_norm;
    delete [] hat_vert;
    return false;
    }                                       
  
  //= Objekt der Basisklasse anlegen
  if (!CD3DFrame::Create(pOwner))
    return false;

  //= Feld mit Ecken und Normalen anlegen
  ind_vert = 0; //= Index der aktuellen Ecke
  ind_norm = 0; //= Index der aktuelen Normale
  for (i = 0; i <= hor_planes; i++) 
    //= Horizontale Flächen

    {
    //= p - Winkel für das Berechnen des Z-Wertes
    p = PI / 2.0 / (hor_planes + 1) * i; 
    
    for (j = 0; j < vert_planes; j++)
      //= Vertikalle Flächen
      {
      //= d - Winkel für das Berechnen des Z-Wertes
      d = 2.0 * PI / vert_planes * j;      
      //= Koordinaten der (i,j) Ecke berechnen
      //= Radius = 1 (wird nicht benutzt)
      y = cos(p) * sin(d);
      x = cos(p) * cos(d);
      z = sin(p);
      //= In Feld hinzufügen
      hat_vert[ind_vert].x = D3DVAL(x);
      hat_vert[ind_vert].y = D3DVAL(y);
      hat_vert[ind_vert++].z = D3DVAL(z);
    
      hat_norm[ind_norm].x = D3DVAL(x);
      hat_norm[ind_norm].y = D3DVAL(y);
      hat_norm[ind_norm++].z = D3DVAL(z);
      } //= end loop for j
    }   //= end loop for i
  
  //= Letzte Ecke hinzufügen
  hat_vert[ind_vert].x = D3DVAL(0.0);
  hat_vert[ind_vert].y = D3DVAL(0.0);
  hat_vert[ind_vert++].z = D3DVAL(1.0);
  
  hat_norm[ind_norm].x = D3DVAL(0);
  hat_norm[ind_norm].y = D3DVAL(0);
  hat_norm[ind_norm++].z = D3DVAL(1);
  
  //= Feld mit Aproximierungselementen-Daten anlegen
  ind = 0; //= current index

  //= Orientierung beachten
  if (orientation)
    { //= Außenoberfläche wird sichtbar
    //= Liste der Quadrate
	  for (i = 0; i < hor_planes; i++)
       {
      for (j = 0; j < vert_planes; j++)
        {
        //= Für jedes Aproximierungselement fangen die Daten mit der Anzahl der Ecken an
        hat_facedata[ind++] = 4; 
        //= Danach die Liste der Ecken im Uhrsinn  
        hat_facedata[ind++] = j + (i + 1) * vert_planes; //= Ecke 1
        hat_facedata[ind++] = j + (i + 1) * vert_planes; //= Normal 1
        hat_facedata[ind++] = j + i * vert_planes; //= Ecke 2
        hat_facedata[ind++] = j + i * vert_planes; //= Normal 2
        
        //= ist das das letzte Aproximierungselement in der Schicht?
        if (j != vert_planes - 1)
          { //= nein
          //= Dann werden die Indexe der Ecken 3 und 4 berechnen:
          hat_facedata[ind++] = j + i * vert_planes + 1;       //= Ecke 3
          hat_facedata[ind++] = j + i * vert_planes + 1; 
          hat_facedata[ind++] = j + (i + 1) * vert_planes + 1; //= Ecke 4
          hat_facedata[ind++] = j + (i + 1) * vert_planes + 1; 
          }
        else
          { //= Letztes Aproximierungselement
          hat_facedata[ind++] = i * vert_planes;       //= Ecke  3
          hat_facedata[ind++] = i * vert_planes; 
          hat_facedata[ind++] = (i + 1) * vert_planes; //= Ecke 4
          hat_facedata[ind++] = (i + 1) * vert_planes; 
          }                                     
        }
      }

    //= Information über Dreieck-Elemente auf dem Gipfel der Sphäre
    for (i = 0; i < vert_planes - 1; i++)
      {
      hat_facedata[ind++] = 3;
      //= Erste Ecke auf dem Gipfel der Sphäre
      hat_facedata[ind++] = vert_planes * (hor_planes + 1); 
      hat_facedata[ind++] = vert_planes * (hor_planes + 1);
      hat_facedata[ind++] = vert_planes * hor_planes + i;
      hat_facedata[ind++] = vert_planes * hor_planes + i;
      hat_facedata[ind++] = vert_planes * hor_planes + i + 1;
      hat_facedata[ind++] = vert_planes * hor_planes + i + 1; 
      }
  
    //= Letzte Dreiecke 
    hat_facedata[ind++] = 3;
    hat_facedata[ind++] = vert_planes * (hor_planes + 1); 
    hat_facedata[ind++] = vert_planes * (hor_planes + 1);
    hat_facedata[ind++] = vert_planes * (hor_planes + 1) - 1;
    hat_facedata[ind++] = vert_planes * (hor_planes + 1) - 1; 
    hat_facedata[ind++] = vert_planes * hor_planes;
    hat_facedata[ind++] = vert_planes * hor_planes;
    }
  
  else
    { //= Interne Oberfläche wird sichtbaran
    //= Alle Aktionen wiederholen
    for (i = 0; i < hor_planes; i++)
      {
      for (j = 0; j < vert_planes; j++)
        {
        hat_facedata[ind++] = 4; 
        hat_facedata[ind++] = j + i * vert_planes;
        hat_facedata[ind++] = j + i * vert_planes;
        hat_facedata[ind++] = j + (i + 1) * vert_planes;
        hat_facedata[ind++] = j + (i + 1) * vert_planes;

        if (j != vert_planes - 1)
          {
          hat_facedata[ind++] = j + (i + 1) * vert_planes + 1;
          hat_facedata[ind++] = j + (i + 1) * vert_planes + 1;
          hat_facedata[ind++] = j + i * vert_planes + 1;
          hat_facedata[ind++] = j + i * vert_planes + 1;
          }
        else
          {
          hat_facedata[ind++] = (i + 1) * vert_planes;
          hat_facedata[ind++] = (i + 1) * vert_planes;
          hat_facedata[ind++] = i * vert_planes;
          hat_facedata[ind++] = i * vert_planes;
          }                                     
        }
      }

    for (i = 0; i < vert_planes - 1; i++)
      {
      hat_facedata[ind++] = 3;
      hat_facedata[ind++] = vert_planes * (hor_planes + 1); 
      hat_facedata[ind++] = vert_planes * (hor_planes + 1);
      hat_facedata[ind++] = vert_planes * hor_planes + i + 1;
      hat_facedata[ind++] = vert_planes * hor_planes + i + 1; 
      hat_facedata[ind++] = vert_planes * hor_planes + i;
      hat_facedata[ind++] = vert_planes * hor_planes + i;
      }
  
    hat_facedata[ind++] = 3;
    hat_facedata[ind++] = vert_planes * (hor_planes + 1); 
    hat_facedata[ind++] = vert_planes * (hor_planes + 1);
    hat_facedata[ind++] = vert_planes * hor_planes;
    hat_facedata[ind++] = vert_planes * hor_planes;
    hat_facedata[ind++] = vert_planes * (hor_planes + 1) - 1;
    hat_facedata[ind++] = vert_planes * (hor_planes + 1) - 1; 
    }

  //= Alle Aproximierungselemente zeigen
  hat_facedata[ind++] = 0;    
  
  //= Daten in Direct3D hinzufügen
  //= Standardfarbe definieren
  if (!AddFaces(ind_vert, hat_vert, ind_norm, hat_norm, 
                hat_facedata, NULL) || !SetColor(color))
    {
    delete [] hat_facedata;
    delete [] hat_norm;
    delete [] hat_vert;
    return false;
    }

  //= Speicher freigegeben
  delete [] hat_facedata;
  delete [] hat_norm;
  delete [] hat_vert;
  return true;
  }
