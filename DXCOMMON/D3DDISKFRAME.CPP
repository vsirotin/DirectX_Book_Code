// d3dDiskFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dDiskFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DDiskFrame

IMPLEMENT_DYNAMIC(CD3DDiskFrame, CD3DFrame)

CD3DDiskFrame::CD3DDiskFrame()
  {
  }

CD3DDiskFrame::~CD3DDiskFrame()
  {
  }

bool CD3DDiskFrame::Create(CD3DMainObj *pOwner, 
                           double rad,
                           int n_sectors, D3DCOLOR color,
                           bool orientation)
  //= Netz für einen Kreis mit einem Loch festlegen
  //= n_sectors - Anzahl der Sektoren
  //= rad - Radius des Loches
  //= Außer-Radius = 1
  {
  int    j, ind, ind_vert;
  double d;       //= Winkel des Sektors
  double x, y, z;

  //= Normalen der Ecken. Alle sind gleich
  int    ind_norm = 1; //= Anzahl der verschiedenen Normalen
  static D3DVECTOR disk_norm[] = {D3DVAL(0.0), D3DVAL(0.0), D3DVAL(-1.0)}; 
  D3DVECTOR *disk_vert;     //= Ecken von Disk-Aproximierungselementen
  DWORD     *disk_facedata;

  int face_numb_vert; 

 
  if (rad < 0.0 || rad >= 1.0)
    return false;

   if (n_sectors < 3)
    return false;

  //= Speicher belegen
  disk_vert = new D3DVECTOR [2 * n_sectors];
  if (disk_vert == NULL)
    return false;
  disk_facedata = new DWORD [n_sectors * 9 + 1];
  if (disk_facedata == NULL)
    {
    delete [] disk_vert;
    return false;
    }                                       
    
  //= Objekt der Basisklasse anlegen
  if (!CD3DFrame::Create(pOwner))
    return false;

  ind_vert = 0;
  //= Zuerst die Ecken der Außengrenze berechnen
  for (j = 0; j < n_sectors; j++)
    
    {
    d = 2.0 * PI / n_sectors * j;
    x = cos(d); //= Koordinaten der j - Ecke berechnen
    y = sin(d);
    z = 0.0;    //= Fläche z = 0
 
    disk_vert[ind_vert].x = D3DVAL(x);
    disk_vert[ind_vert].y = D3DVAL(y);
    disk_vert[ind_vert++].z = D3DVAL(z);
    }
  
  if (rad != 0.0)
    {
    //= Loch bearbeiten
    face_numb_vert = 4; 
    //= Koordinaten der internen Grenze berechnen
    for (j = 0; j < n_sectors; j++)
      {
      d = 2.0 * PI / n_sectors * j;
      x = rad * cos(d);
      y = rad * sin(d);
      z = 0.0;
      disk_vert[ind_vert].x = D3DVAL(x);
      disk_vert[ind_vert].y = D3DVAL(y);
      disk_vert[ind_vert++].z = D3DVAL(z);
      }
    } //= End of if (...)
  else
    {
    face_numb_vert = 3;
    //= Letzte Ecke: Zentrum des Kreises
    disk_vert[ind_vert].x = D3DVAL(0);
    disk_vert[ind_vert].y = D3DVAL(0);
    disk_vert[ind_vert++].z = D3DVAL(0);
    }

  //= Aproximierungselementen-Daten generieren
  ind = 0; //= Aktueller Index

  if (!orientation)
    { //= Fall von falscher Orientierung
    for (j = 0; j < n_sectors - 1; j++)
      {
      disk_facedata[ind++] = face_numb_vert; //= 3 oder 4
      //= Ecke 1 liegt auf Außengrenze
      disk_facedata[ind++] = j;   //= Index
      disk_facedata[ind++] = 0;   //= Normale
      if (face_numb_vert == 4)
        { //= 4 Ecken
        //= Ecke 2 liegt auf interne Grenze
        disk_facedata[ind++] = j + n_sectors;
        disk_facedata[ind++] = 0;
        
        disk_facedata[ind++] = j + n_sectors + 1;
        disk_facedata[ind++] = 0;
        }
      else
        { //= 3 Ecken
        //= Ecke 2 liegt im Zentrum
        disk_facedata[ind++] = ind_vert - 1;
        disk_facedata[ind++] = 0;
        }

      //= Letzte Ecke auf der Außengrenze
      disk_facedata[ind++] = j + 1;
      disk_facedata[ind++] = 0;
      }
  
    //= Daten über letztes Aproximierungselement hinzufügen
    disk_facedata[ind++] = face_numb_vert; 
    disk_facedata[ind++] = n_sectors - 1;
    disk_facedata[ind++] = 0;
  
    if (face_numb_vert == 4)
      { //= 4 Ecke
      disk_facedata[ind++] = n_sectors + n_sectors - 1;
      disk_facedata[ind++] = 0;
      disk_facedata[ind++] = n_sectors;
      disk_facedata[ind++] = 0;
      }
    else
      {
      disk_facedata[ind++] = ind_vert - 1;
      disk_facedata[ind++] = 0;
      }
    disk_facedata[ind++] = 0;
    disk_facedata[ind++] = 0;
    } 
  
  else
    { //= Richtige Orientierung
    for (j = 0; j < n_sectors - 1; j++)
      {
      disk_facedata[ind++] = face_numb_vert;
      disk_facedata[ind++] = j + 1;
      disk_facedata[ind++] = 0;
      if (face_numb_vert == 4)
        { //= 4 Ecken
        disk_facedata[ind++] = j + n_sectors + 1;
        disk_facedata[ind++] = 0;
        disk_facedata[ind++] = j + n_sectors;
        disk_facedata[ind++] = 0;
        }
      else
        { //= 3 Ecken
        disk_facedata[ind++] = ind_vert - 1;
        disk_facedata[ind++] = 0;
        }

      //= Letzte Ecke auf der Außengrenze
      disk_facedata[ind++] = j;
      disk_facedata[ind++] = 0;
      }
  
    //= Daten über letzten Aproximierungselement hinzufügen
    disk_facedata[ind++] = face_numb_vert; 
    disk_facedata[ind++] = 0;
    disk_facedata[ind++] = 0;
  
    if (face_numb_vert == 4)
      { //= 4 Ecken
      disk_facedata[ind++] = n_sectors;
      disk_facedata[ind++] = 0;
      disk_facedata[ind++] = n_sectors + n_sectors - 1;
      disk_facedata[ind++] = 0;
      }
    else
      {
      disk_facedata[ind++] = ind_vert - 1;
      disk_facedata[ind++] = 0;
      }
    disk_facedata[ind++] = n_sectors - 1;
    disk_facedata[ind++] = 0;
    } 

  //= Ende der Daten
  disk_facedata[ind++] = 0;
  
  //= Netz zu Direct3D hinzufügen. Farbe festlegen
  if (!AddFaces(ind_vert, disk_vert, ind_norm, disk_norm, 
                disk_facedata, NULL) || !SetColor(color))
    {
    delete [] disk_facedata;
    delete [] disk_vert;
    return false;
    }
  delete [] disk_facedata;
  delete [] disk_vert;
  return true;
  }