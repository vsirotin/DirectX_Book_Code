// d3dRevolveSmoothFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dGeomArsenal.h"
#include "d3dRevolveSmoothFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DCubeFrame

IMPLEMENT_DYNAMIC(CD3DRevolveSmoothFrame, CD3DFrame)

CD3DRevolveSmoothFrame::CD3DRevolveSmoothFrame()
  {
  pNorm = NULL;
  vert = NULL;
  }

CD3DRevolveSmoothFrame::~CD3DRevolveSmoothFrame()
  {
  if (pNorm != NULL)
    {
    delete [] pNorm;
    pNorm = NULL;
    }
  if (vert != NULL)
    {
    delete [] vert;
    vert = NULL;
    }
  }

bool CD3DRevolveSmoothFrame::Create(CD3DMainObj *pOwner, 
                                 int nbase, D3DVECTOR *pBase, 
                                 bool closed, bool average,
                                 bool border, double angle, int n_angle, 
                                 D3DCOLOR color) 
  {
  int i, j;
  CD3DPolygonFrame *pNext; 
  CD3DFaceFrame *pFace;    
  

  if (nbase < 2 || n_angle < 3)
    return false;

  //= Resultat-Objekt anlegen
  if (!CD3DFrame::Create(pOwner))
    return false;

  int iAppData = 1; //= IDs generieren
  //= Winkel abhängig von globalen Parametern korrigieren
  double ang = (angle >= 2 * PI) ? 0.0 : angle;
  bool full = ang == 0.0;
  double dang = ang / n_angle;
  if (full)
    dang = 2.0 * PI / n_angle;

  int last = nbase - 1; // index of last vertex
  //= Kurvenanfang liegt auf der Z_Achse
  bool end1 = pBase[0].x == D3DVAL(0.0);
  //= Kurvenende liegt auf der Z-Achse
  bool end2 = pBase[last].x == D3DVAL(0.0);

  //= Aproximierungselemente werden pro Schicht erzeugt
  //= Jedes Aproximierungselement hat seinen Gegenstück:
  //= Ein Aproximierungselement mit umgekehrte Orientierung

  int n_lay = 0; // Anzahl der Schichten
  int n_lays = nbase - 1; 

  //= Checken, ob nur genau ein Element liegt auf der Z-Achse liegt
  
  if ((nbase == 2 && end1 && end2) || (closed && nbase < 3))
    return false;
  
  if (end2)
    n_lays--;

  //= Normalen berechnen (in der XY Fläche)
  D3DVECTOR *pNorm = new D3DVECTOR [nbase];
  if (pNorm == NULL)
    return false;

  D3DVECTOR v1, v2;
  D3DVECTOR vert[4], norm[4];
  D3DVECTOR axisZ = {D3DVAL(0), D3DVAL(0), D3DVAL(1)};
  D3DVECTOR axisY = {D3DVAL(0), D3DVAL(1), D3DVAL(0)};
  double fi, r, r1;

  for (i = 1; i < last; i++) //= Nur Normalen von internen Ecken
    {                             //= werden berücksichtigt
    D3DRMVectorSubtract(&v1, &pBase[i], &pBase[i - 1]);
    D3DRMVectorNormalize(&v1);

    D3DRMVectorSubtract(&v2, &pBase[i + 1], &pBase[i]);
    D3DRMVectorNormalize(&v2);

    D3DRMVectorSubtract(&pNorm[i], &v1, &v2);
    D3DRMVectorNormalize(&pNorm[i]);
    }

  //= Normalen in Anfangs- und Endepunkt der Kurve definieren
  if (closed)
    {
    D3DRMVectorSubtract(&v1, &pBase[0], &pBase[last]);
    D3DRMVectorNormalize(&v1);

    D3DRMVectorSubtract(&v2, &pBase[1], &pBase[0]);
    D3DRMVectorNormalize(&v2);

    D3DRMVectorSubtract(&pNorm[0], &v1, &v2);
    D3DRMVectorNormalize(&pNorm[0]);

    D3DRMVectorSubtract(&v1, &pBase[last], &pBase[last - 1]);
    D3DRMVectorNormalize(&v1);

    D3DRMVectorSubtract(&v2, &pBase[0], &pBase[last]);
    D3DRMVectorNormalize(&v2);

    D3DRMVectorSubtract(&pNorm[last], &v1, &v2);
    D3DRMVectorNormalize(&pNorm[last]);
    }
  else
  if (average)
    { //= Gipfel-Ecke 
    pNorm[0].x = D3DVAL(0);
    pNorm[0].y = D3DVAL(0);
    pNorm[0].z = D3DVAL(-1);

    pNorm[last].x = D3DVAL(0);
    pNorm[last].y = D3DVAL(0);
    pNorm[last].z = D3DVAL(1);
    }
  else
    { //= Gipfel Eckennormale wird als gemeinseme Normale berechnet
    D3DRMVectorSubtract(&v2, &pBase[1], &pBase[0]);
    D3DRMVectorNormalize(&v2);
    D3DRMVectorRotate(&pNorm[0], &v2, &axisY, D3DVAL(-PI / 2.0));

    D3DRMVectorSubtract(&v1, &pBase[last], &pBase[last - 1]);
    D3DRMVectorNormalize(&v1);
    D3DRMVectorRotate(&pNorm[last], &v1, &axisY, D3DVAL(-PI / 2.0));
    }

  //= Erste Schicht der Aproximierungselementen
  if (end1)
    {
    //= Enthält die Dreiecke mit gemeisemem Gipfel
    vert[0].x = D3DVAL(0);
    vert[0].y = D3DVAL(0);
    norm[0]   = pNorm[0];
    vert[0].z = D3DVAL(pBase[0].z);
    vert[1].z = D3DVAL(pBase[1].z);
    vert[2].z = D3DVAL(pBase[1].z);

    for (j = 0; j < n_angle; j++)
      {
      fi = dang * j;
      r = pBase[1].x;
      vert[1].x = D3DVAL(cos(fi) * r);
      vert[1].y = D3DVAL(-sin(fi) * r);
      D3DRMVectorRotate(&norm[1], &pNorm[1], &axisZ, D3DVAL(fi));

      if (j == n_angle)
        {
        vert[2].x = pBase[1].x;
        vert[2].y = D3DVAL(0);
        norm[2] = pNorm[1];
        }
      else
        {
        fi += dang;
        vert[2].x = D3DVAL(cos(fi) * r);
        vert[2].y = D3DVAL(-sin(fi) * r);
        D3DRMVectorRotate(&norm[2], &pNorm[1], &axisZ, D3DVAL(fi));
        }

      //= Zweites Frame für das Element
      pFace = new CD3DFaceFrame;

      if (!pFace->Create(pOwner, 3, vert, norm, color))
        return false;

      if (!pFace->AddToFrame(this))
        return false;

      if (!pFace->SetAppData(iAppData++))
        return false;

      //= Andere Seite des Elementes
      pFace = new CD3DFaceFrame;

      if (!pFace->Create(pOwner, 3, vert, norm, color, false))
        return false;

      if (!pFace->AddToFrame(this))
        return false;

      if (!pFace->SetAppData(iAppData++))
        return false;

      n_lay = 1;
      }
    }    
  
  //= Forsetzung mit interner Seite

  for (i = n_lay; i < n_lays; i++)
    {
    //= Nächste Schicht
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
      D3DRMVectorRotate(&norm[0], &pNorm[i], &axisZ, D3DVAL(fi));
      vert[3].x = D3DVAL(cos(fi) * r1);
      vert[3].y = D3DVAL(-sin(fi) * r1);
      D3DRMVectorRotate(&norm[3], &pNorm[i + 1], &axisZ, D3DVAL(fi));
      fi += dang;
      vert[1].x = D3DVAL(cos(fi) * r);
      vert[1].y = D3DVAL(-sin(fi) * r);
      D3DRMVectorRotate(&norm[1], &pNorm[i], &axisZ, D3DVAL(fi));
      vert[2].x = D3DVAL(cos(fi) * r1);
      vert[2].y = D3DVAL(-sin(fi) * r1);
      D3DRMVectorRotate(&norm[2], &pNorm[i + 1], &axisZ, D3DVAL(fi));

      //= Zweites Frame für das Element
      pFace = new CD3DFaceFrame;

      if (!pFace->Create(pOwner, 4, vert, norm, color))
        return false;

      if (!pFace->AddToFrame(this))
        return false;

      if (!pFace->SetAppData(iAppData++))
        return false;

      //= Andere Seite des Elementes
      pFace = new CD3DFaceFrame;

      if (!pFace->Create(pOwner, 4, vert, norm, color, false))
        return false;

      if (!pFace->AddToFrame(this))
        return false;

      if (!pFace->SetAppData(iAppData++))
        return false;

      n_lay = 1;
      }     //= end of loop "for j"
    }       //= end of loop "for i"

  //= Letzte Schicht
  if (end2)
    {
    //= Enthält Dreiecke mit gemeinsamem Gipfel
    vert[0].x = D3DVAL(0);
    vert[0].y = D3DVAL(0);
    norm[0]   = pNorm[last];
    vert[0].z = D3DVAL(pBase[last].z);
    vert[1].z = D3DVAL(pBase[last - 1].z);
    vert[2].z = D3DVAL(pBase[last - 1].z);

    for (j = 0; j < n_angle; j++)
      {
      fi = dang * j;
      r = pBase[last].x;
      vert[1].x = D3DVAL(cos(fi) * r);
      vert[1].y = D3DVAL(-sin(fi) * r);
      D3DRMVectorRotate(&norm[1], &pNorm[last - 1], &axisZ, D3DVAL(fi));

      if (j == n_angle)
        {
        vert[2].x = pBase[last - 1].x;
        vert[2].y = D3DVAL(0);
        norm[2] = pNorm[last - 1];
        }
      else
        {
        fi += dang;
        vert[2].x = D3DVAL(cos(fi) * r);
        vert[2].y = D3DVAL(-sin(fi) * r);
        D3DRMVectorRotate(&norm[2], &pNorm[last - 1], &axisZ, D3DVAL(fi));
        }

      //= Frame für das Element reservieren
      pFace = new CD3DFaceFrame;

      if (!pFace->Create(pOwner, 3, vert, norm, color))
        return false;

      if (!pFace->AddToFrame(this))
        return false;

      if (!pFace->SetAppData(iAppData++))
        return false;

      //= Andere Seite des Elementes
      pFace = new CD3DFaceFrame;

      if (!pFace->Create(pOwner, 3, vert, norm, color, false))
        return false;

      if (!pFace->AddToFrame(this))
        return false;

      if (!pFace->SetAppData(iAppData++))
        return false;
      }
    }    

  //= Grenze-Elemente anlegen
  if (!full && border)
    {
    //= Erste Fläche mit  X = 0
    //= Frame für das Element reservieren
    pNext = new CD3DPolygonFrame;

    if (!pNext->Create(pOwner, nbase, pBase, color))
      return false;

    if (!pNext->AddToFrame(this))
      return false;

    if (!pNext->SetAppData(iAppData++))
      return false;

      //= Andere Seite des Elementes
    pNext = new CD3DPolygonFrame;

    if (!pNext->Create(pOwner, nbase, pBase, color, false))
      return false;

    if (!pNext->AddToFrame(this))
      return false;

    if (!pNext->SetAppData(iAppData++))
      return false;

    //= Zweite Grenze mit anderem Winkel
    D3DVECTOR *vert = new D3DVECTOR [nbase];
    if (vert == NULL)
      return false;
    
    for (i = 0; i < nbase; i++)
      {
      vert[i].z = pBase[i].z;
      vert[i].x = D3DVAL(cos(ang) * pBase[i].x);
      vert[i].y = D3DVAL(-sin(ang) * pBase[i].x);
      }
    //= Frame für das Element reservieren
    pNext = new CD3DPolygonFrame;

    if (!pNext->Create(pOwner, nbase, vert, color))
      return false;

    if (!pNext->AddToFrame(this))
      return false;

    if (!pNext->SetAppData(iAppData++))
      return false;

      //= Andere Seite des Elementes
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

  if (pNorm != NULL)
    {
    delete [] pNorm;
    pNorm = NULL;
    }

  return true;
  }
