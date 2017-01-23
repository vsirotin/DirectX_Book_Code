// d3dFaceFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dFaceFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CD3DFaceFrame

IMPLEMENT_DYNAMIC(CD3DFaceFrame, CD3DFrame)

CD3DFaceFrame::CD3DFaceFrame()
  {
  }

CD3DFaceFrame::~CD3DFaceFrame()
  {
  }

bool CD3DFaceFrame::Create(CD3DMainObj *pOwner,
                           int n_vert, D3DVECTOR *vert, D3DVECTOR *norm, 
                           D3DCOLOR color, bool orientation)
  {
  DWORD *facedata; //= Daten über Aproximierungselementen


  if (n_vert <= 2)
    return false; 

  //= Speicher für Aproximierungselementen belegen
  if ((facedata = new DWORD [2 * n_vert + 2]) == NULL)
    return false; //= no memory

  //= Speicher für Normalen belegen
  D3DVECTOR *anorm;
  if ((anorm = new D3DVECTOR [n_vert]) == NULL)
    {
    delete [] facedata;
    return false; 
    }

  int i;
  for (i = 0; i < n_vert; i++)
    {
    //= Normale für Ecke 1 berechnen
    //= Methode von Direct3D verwenden
    anorm[i] = norm[i];
    if (D3DRMVectorNormalize(&anorm[i]) == NULL)
      {
      delete [] facedata;
      delete [] anorm;
      return false; 
      }
    }

  int ind = 0; 
  facedata[ind++] = n_vert;  //= Feld mit Aproximierungselementen anlegen

  //= Orientierung berücksichtigen
  if (orientation) //= Positive Orientierung
    {
    for (i = 0; i < n_vert; i++)
      {
      facedata[ind++] = i;  //= Index der Ecke
      facedata[ind++] = i;  //= Index der Normale
      }
    }
  else
    { //= Umgekehrte Orientierung
    for (i = 0; i < n_vert; i++)
      {
      anorm[i].x = -anorm[i].x;
      anorm[i].y = -anorm[i].y;
      anorm[i].z = -anorm[i].z;
      facedata[ind++] = n_vert - i - 1;  //= Index der Ecke
      facedata[ind++] = n_vert - i - 1;
      }
    }

  facedata[ind++] = 0;         //= Ende der Aproximierungselementen-Daten

  if (!CD3DFrame::Create(pOwner))
    {
    delete [] facedata;
    delete [] anorm;
    return false;
    }

  //= Netz in Direct3D hinzufügen
  if (!AddFaces(n_vert, vert, n_vert, anorm, facedata, NULL))
    {
    delete [] facedata;
    delete [] anorm;
    return false;
    }

  //= Standardfarbe für das Netz definieren
  if (!SetColor(color))
    {
    delete [] facedata;
    delete [] anorm;
    return false;
    }

  delete [] facedata;  
  delete [] anorm;
  
  return true; 
  }

