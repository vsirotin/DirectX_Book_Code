// d3dSweepingFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dGeomArsenal.h"
#include "d3dSweepingFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DCubeFrame

IMPLEMENT_DYNAMIC(CD3DSweepingFrame, CD3DFrame)

CD3DSweepingFrame::CD3DSweepingFrame()
  {
  base = NULL;
  top = NULL;
  norm = NULL;
  }

CD3DSweepingFrame::~CD3DSweepingFrame()
  {
  if (base != NULL)
    {
    delete [] base;
    base = NULL;
    }
  if (top != NULL)
    {
    delete [] top;
    top = NULL;
    }
  if (norm != NULL)
    {
    delete [] norm;
    norm = NULL;
    }
  }

bool CD3DSweepingFrame::Create(CD3DMainObj *pOwner, int nbase, int ntop,
                               D3DVECTOR *pBase, D3DVECTOR *pTop, 
                               bool border, bool smooth, D3DCOLOR color)
  {
  CD3DPolygonFrame *pNext;           

  
  if (nbase < 3 || 
      (nbase != ntop && ntop != 1))
    return false;

  //= Resultat-Objekt anlegen
  if (!CD3DFrame::Create(pOwner))
    return false;

  int iAppData = 1; //= IDs generieren
  
  //= Basisform. Jedes Element ist eine Fläche
  if (border)
    {
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
    
    //= Zweites Element
    if (ntop != 1)
      {
      //= Eine Seite vom Top-Element
      pNext = new CD3DPolygonFrame;
  
      if (!pNext->Create(pOwner, ntop, pTop, color))
        return false;

      if (!pNext->SetAppData(iAppData++))
        return false;
  
      if (!pNext->AddToFrame(this))
        return false;
  
    //= Andere Seite
      pNext = new CD3DPolygonFrame;
  
      if (!pNext->Create(pOwner, ntop, pTop, color, false))
        return false;

      if (!pNext->SetAppData(iAppData++))
        return false;
  
      if (!pNext->AddToFrame(this))
        return false;
      }
    }


  int i;                           
  int count = (ntop == 1) ? 3 : 4; //= Anzahl der Ecken

  if ((base = new D3DVECTOR [nbase + 2]) == NULL)
    return false;
  if ((top  = new D3DVECTOR [nbase + 2]) == NULL)
    return false;

  base[0] = pBase[nbase - 1];
  if (count == 3) 
    top[0] = pTop[0];
  else
    top[0] = pTop[nbase - 1];
  for (i = 0; i < nbase; i++)
    {
    base[i + 1] = pBase[i];
    if (count == 3)
      top[i + 1] = pTop[0];
    else
      top[i + 1] = pTop[i];
    }
  base[nbase + 1] = pBase[0];
  top[nbase + 1] = pTop[0];

 
  //= Erste Fall: smooth = false -> Resultatobjekt ist ein Polyeder

  D3DVECTOR temp[4];
  if (!smooth)
    {
    for (i = 1; i <= nbase; i++)
      {
      temp[0] = base[i];
      temp[1] = base[i + 1];
      temp[2] = top[i + 1];
      temp[3] = top[i];
      /*
      //= Zuzäzliche Experiment: 2 Ecken am Gipfel sind gleich
      int cnt;
      cnt = ((top[i].x == top[i + 1].x) && (top[i].y == top[i + 1].y)
        && (top[i].z ==top[i + 1].z)) ? 3 : 4;
        */
      //= Eine Seite vom Element
      pNext = new CD3DPolygonFrame;
  
      if (!pNext->Create(pOwner, count, temp, color))
        return false;

      if (!pNext->SetAppData(iAppData++))
        return false;
  
      if (!pNext->AddToFrame(this))
        return false;
  
    //= Andere Seite
      pNext = new CD3DPolygonFrame;
  
      if (!pNext->Create(pOwner, count, temp, color, false))
        return false;

      if (!pNext->SetAppData(iAppData++))
        return false;
  
      if (!pNext->AddToFrame(this))
        return false;
      }
    }

  else  //= Zweite Fall: smooth = true
    {
    //= Alle Normalen aller Elemente finden
    
    if ((norm = new D3DVECTOR [nbase + 2]) == NULL)
      return false;

    for (i = 0; i < nbase + 1; i++)
      {
      //= static method von CD3DFrame verwenden
      NormalFromFace(&base[i], &base[i + 1], &top[i + 1], &norm[i]);
      }

    //= Durchschnittliche Normale  mit GOURAUD-Methode berechen
    for (i = 0; i < nbase; i++)
      {
      norm[i].x = D3DVAL((norm[i].x + norm[i + 1].x) * 0.5);
      norm[i].y = D3DVAL((norm[i].y + norm[i + 1].y) * 0.5);
      norm[i].z = D3DVAL((norm[i].z + norm[i + 1].z) * 0.5);
      D3DRMVectorNormalize(&norm[i]); 
      }
    norm[nbase] = norm[0];

    D3DVECTOR tvert[4], tnorm[4];
    CD3DFaceFrame *pNext; //= fur mehrere Objekten

    for (i = 0; i < nbase; i++)
      {
      int cnt; 

      tvert[0] = base[i + 1];
      tvert[1] = base[i + 2];
      tvert[2] = top[i + 2];
      tvert[3] = top[i + 1];
      tnorm[0] = norm[i];
      tnorm[1] = norm[i + 1];
      tnorm[2] = norm[i + 1];
      tnorm[3] = norm[i];

      //= Zuzäzliche Prüfung: Wenn 2 Ecken gleich sind 
      cnt = ((tvert[2].x == tvert[3].x) && (tvert[2].y == tvert[3].y)
        && (tvert[2].z == tvert[3].z)) ? 3 : 4;
                          
      //= Eine Seite vom Element
      pNext = new CD3DFaceFrame;
  
      if (!pNext->Create(pOwner, cnt, tvert, tnorm, color))
        return false;

      if (!pNext->SetAppData(iAppData++))
        return false;
  
      if (!pNext->AddToFrame(this))
        return false;
  
    //= Andere Seite
      pNext = new CD3DFaceFrame;
  
      if (!pNext->Create(pOwner, cnt, tvert, tnorm, color, false))
        return false;

      if (!pNext->SetAppData(iAppData++))
        return false;
  
      if (!pNext->AddToFrame(this))
        return false;
      }
    }

  //= Standardfarbe definieren 
  if (!SetColor(color))
    return false;

  delete [] base;
  base = NULL;
  delete [] top;
  top = NULL;
  delete [] norm;
  norm = NULL;

  return true;
  }
