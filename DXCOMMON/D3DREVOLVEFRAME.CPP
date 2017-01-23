// d3dRevolveFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dGeomArsenal.h"
#include "d3dRevolveFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DCubeFrame

IMPLEMENT_DYNAMIC(CD3DRevolveFrame, CD3DFrame)

CD3DRevolveFrame::CD3DRevolveFrame()
  {
  vert = NULL;
  }

CD3DRevolveFrame::~CD3DRevolveFrame()
  {
  if (vert != NULL)
    {
    delete [] vert;
    vert = NULL;
    }
  }

bool CD3DRevolveFrame::Create(CD3DMainObj *pOwner, 
                              int nbase, D3DVECTOR *pBase,
                              bool border, double angle, int n_angle, 
                              D3DCOLOR color)
  {
  int i, j;
  CD3DPolygonFrame *pNext; 

  if (nbase < 2 || n_angle < 3)
    return false;

  //= Resultat-Objekt anlegen
  if (!CD3DFrame::Create(pOwner))
    return false;

  int iAppData = 1; //= IDs generieren
  //= Winkel abhängig von globalen Paramern korrigieren
  double ang = (angle >= 2 * PI) ? 0.0 : angle;
  bool full = ang == 0.0;
  double dang = ang / n_angle;
  if (full)
    dang = 2.0 * PI / n_angle;
  //= Kurve liegt in der Z-Achse
  bool end1 = pBase[0].x == D3DVAL(0.0);
  //= Ende der Kurve
  bool end2 = pBase[nbase - 1].x == D3DVAL(0.0);

  //= Aproximierungselemente werden pro Schicht angelegt
  //= Jedes Aproximierungselement hat sein Gegenstück:
  //= Aproximierungselement mit umgekerter Orientierung

  int n_lay = 0; // Anzahl der Schichten
  int n_lays = nbase - 1; // all layers

  //= Segment der Z-Ache checken
  
  if (nbase == 2 && end1 && end2)
    return false;
  
  if (end2)
    n_lays--;

  //= Erste Schicht
  if (end1)
    {
    //= Enthält Dreiecke
    D3DVECTOR vert[3];
    double fi, r;

    vert[0].x = D3DVAL(0);
    vert[0].y = D3DVAL(0);
    vert[0].z = D3DVAL(pBase[0].z);
    vert[1].z = D3DVAL(pBase[1].z);
    vert[2].z = D3DVAL(pBase[1].z);

    for (j = 0; j < n_angle; j++)
      {
      fi = dang * j;
      r = pBase[1].x;
      vert[1].x = D3DVAL(cos(fi) * r);
      vert[1].y = D3DVAL(-sin(fi) * r);

      if (j == n_angle)
        {
        vert[2].x = pBase[1].x;
        vert[2].y = D3DVAL(0);
        }
      else
        {
        fi += dang;
        vert[2].x = D3DVAL(cos(fi) * r);
        vert[2].y = D3DVAL(-sin(fi) * r);
        }

      //= Frame reservieren
      pNext = new CD3DPolygonFrame;

      if (!pNext->Create(pOwner, 3, vert, color))
        return false;

      if (!pNext->AddToFrame(this))
        return false;

      if (!pNext->SetAppData(iAppData++))
        return false;

      //= Andere Seite 
      pNext = new CD3DPolygonFrame;

      if (!pNext->Create(pOwner, 3, vert, color, false))
        return false;

      if (!pNext->AddToFrame(this))
        return false;

      if (!pNext->SetAppData(iAppData++))
        return false;

      n_lay = 1;
      }
    }    
  
  //= Mit interner Seite fortsetzen

  for (i = n_lay; i < n_lays; i++)
    {
    //= Nächste Schicht der Quadrant - Elementen
    D3DVECTOR vert[4];
    double fi, r, r1;

    r = pBase[i].x;
    r1 = pBase[i + 1].x;
    vert[0].z = D3DVAL(pBase[i].z);
    vert[1].z = D3DVAL(pBase[i].z);
    vert[2].z = D3DVAL(pBase[i + 1].z);
    vert[3].z = D3DVAL(pBase[i + 1].z);

    for (j = 0; j < n_angle; j++)
      {
      fi = dang * j;
      vert[0].x = D3DVAL(cos(fi) * r);
      vert[0].y = D3DVAL(-sin(fi) * r);
      vert[3].x = D3DVAL(cos(fi) * r1);
      vert[3].y = D3DVAL(-sin(fi) * r1);
      fi += dang;
      vert[1].x = D3DVAL(cos(fi) * r);
      vert[1].y = D3DVAL(-sin(fi) * r);
      vert[2].x = D3DVAL(cos(fi) * r1);
      vert[2].y = D3DVAL(-sin(fi) * r1);

      //= Frame reservieren
      pNext = new CD3DPolygonFrame;

      if (!pNext->Create(pOwner, 4, vert, color))
        return false;

      if (!pNext->AddToFrame(this))
        return false;

      if (!pNext->SetAppData(iAppData++))
        return false;

      //= Andere Seite
      pNext = new CD3DPolygonFrame;

      if (!pNext->Create(pOwner, 4, vert, color, false))
        return false;

      if (!pNext->AddToFrame(this))
        return false;

      if (!pNext->SetAppData(iAppData++))
        return false;

      n_lay = 1;
      }     //= end of loop "for j"
    }       //= end of loop "for i"

  //= Letzte Schicht
  if (end2)
    {
    //= Enthält  Dreiecke mit gemeinsamem Gipfel
    D3DVECTOR vert[3];
    double fi, r;

    vert[0].x = D3DVAL(0);
    vert[0].y = D3DVAL(0);
    vert[0].z = D3DVAL(pBase[nbase - 1].z);
    vert[1].z = D3DVAL(pBase[nbase - 2].z);
    vert[2].z = D3DVAL(pBase[nbase - 2].z);

    for (j = 0; j < n_angle; j++)
      {
      fi = dang * j;
      r = pBase[nbase - 2].x;
      vert[1].x = D3DVAL(cos(fi) * r);
      vert[1].y = D3DVAL(-sin(fi) * r);

      if (j == n_angle)
        {
        vert[2].x = pBase[nbase - 2].x;
        vert[2].y = D3DVAL(0);
        }
      else
        {
        fi += dang;
        vert[2].x = D3DVAL(cos(fi) * r);
        vert[2].y = D3DVAL(-sin(fi) * r);
        }

      //= Frame reservieren
      pNext = new CD3DPolygonFrame;

      if (!pNext->Create(pOwner, 3, vert, color))
        return false;

      if (!pNext->AddToFrame(this))
        return false;

      if (!pNext->SetAppData(iAppData++))
        return false;

      //= Andere Seite
      pNext = new CD3DPolygonFrame;

      if (!pNext->Create(pOwner, 3, vert, color, false))
        return false;

      if (!pNext->AddToFrame(this))
        return false;

      if (!pNext->SetAppData(iAppData++))
        return false;
      }
    }    

  //= Grenzelemente, wenn es nötig und erlaubt ist
  if (!full && border)
    {
    //= Fläche X = 0
    //= Frame reservieren
    pNext = new CD3DPolygonFrame;

    if (!pNext->Create(pOwner, nbase, pBase, color))
      return false;

    if (!pNext->AddToFrame(this))
      return false;

    if (!pNext->SetAppData(iAppData++))
      return false;

    //= Andere Seite
    pNext = new CD3DPolygonFrame;

    if (!pNext->Create(pOwner, nbase, pBase, color, false))
      return false;

    if (!pNext->AddToFrame(this))
      return false;

    if (!pNext->SetAppData(iAppData++))
      return false;

    //= Zweite Grenze 
    D3DVECTOR *vert = new D3DVECTOR [nbase];

    if (vert == NULL)
      return false;
    
    for (i = 0; i < nbase; i++)
      {
      vert[i].z = pBase[i].z;
      vert[i].x = D3DVAL(cos(ang) * pBase[i].x);
      vert[i].y = D3DVAL(-sin(ang) * pBase[i].x);
      }
    //= Frame reservieren
    pNext = new CD3DPolygonFrame;

    if (!pNext->Create(pOwner, nbase, vert, color))
      return false;

    if (!pNext->AddToFrame(this))
      return false;

    if (!pNext->SetAppData(iAppData++))
      return false;

    //= Andere Seite
    pNext = new CD3DPolygonFrame;

    if (!pNext->Create(pOwner, nbase, vert, color, false))
      return false;

    if (!pNext->AddToFrame(this))
      return false;

    if (!pNext->SetAppData(iAppData++))
      return false;                       

    if (vert != NULL)
      {
      delete [] vert;
      vert = NULL;
      }
    }

  return true;
  }
