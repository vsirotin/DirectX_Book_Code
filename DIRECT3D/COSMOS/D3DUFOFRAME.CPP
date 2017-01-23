// d3dUFOFrame.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>

#include "d3dMainObj.h"
#include "d3dUFOFrame.h"
#include "d3dRevolveMeshFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DUFOFrame

IMPLEMENT_DYNAMIC(CD3DUFOFrame, CD3DFrame)

CD3DUFOFrame::CD3DUFOFrame()
  {
  }

CD3DUFOFrame::~CD3DUFOFrame()
  {
  }

bool CD3DUFOFrame::Create(CD3DMainObj *pOwner, int vert_planes,
                                D3DCOLOR color, CD3DLightFrame *lpL)
  {
  if (!CD3DFrame::Create(pOwner))
    return false;
  
  D3DVECTOR UFO[] = {
   {D3DVAL(0),    D3DVAL(0), D3DVAL(6)},
   {D3DVAL(1),    D3DVAL(0), D3DVAL(6)},
   {D3DVAL(2),    D3DVAL(0), D3DVAL(5.8)},
   {D3DVAL(3),    D3DVAL(0), D3DVAL(5.5)},
   {D3DVAL(4),    D3DVAL(0), D3DVAL(5)},
   {D3DVAL(5.2),  D3DVAL(0), D3DVAL(4)},
   {D3DVAL(6),    D3DVAL(0), D3DVAL(3)},
   {D3DVAL(6.5),  D3DVAL(0), D3DVAL(2)},
   {D3DVAL(6.7),  D3DVAL(0), D3DVAL(1.8)},
   {D3DVAL(7.7),  D3DVAL(0), D3DVAL(1.1)},
   {D3DVAL(8),    D3DVAL(0), D3DVAL(1)},
   {D3DVAL(10),   D3DVAL(0), D3DVAL(1)},
   {D3DVAL(10.7), D3DVAL(0), D3DVAL(0.85)},
   {D3DVAL(11),   D3DVAL(0), D3DVAL(0.6)},
   {D3DVAL(11),   D3DVAL(0), D3DVAL(0.3)},
   {D3DVAL(10),   D3DVAL(0), D3DVAL(-0.1)},
   {D3DVAL(9),    D3DVAL(0), D3DVAL(-0.5)},
   {D3DVAL(8),    D3DVAL(0), D3DVAL(-0.8)},
   {D3DVAL(7),    D3DVAL(0), D3DVAL(-0.9)},
   {D3DVAL(6),    D3DVAL(0), D3DVAL(-1)},
   {D3DVAL(5),    D3DVAL(0), D3DVAL(-2)},
   {D3DVAL(0),    D3DVAL(0), D3DVAL(-2.1)}
   };

  CD3DRevolveMeshFrame *pUFO = new CD3DRevolveMeshFrame;
  if (pUFO == NULL)
    return false;

  if (!pUFO->Create(pOwner, 22, UFO, vert_planes, color)) 
    return false;

  if (!pUFO->AddToFrame(this))
    return false;

  if (lpL != NULL)
    {
    if (!pUFO->AddShadow(lpL, D3DVAL(0), D3DVAL(0), D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(0)))
      return false;
    }

  return true;
  }  

  
