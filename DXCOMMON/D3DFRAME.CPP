// D3DFrame.cpp : implementation file
//

#include "stdafx.h"

#include "d3dMainObj.h"
#include "d3dFrame.h"
#include "d3dMaterial.h"
#include "d3dTexture.h"
#include "d3dLightFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

double CD3DFrame::PI = 3.1415928;

//= Callback - Funktion

static void CDECL d3dMoveCallback(LPDIRECT3DRMFRAME3 lpD3DRMFrame,
                                  LPVOID lpArg, D3DVALUE delta)
  {
  CD3DFrame *frm = (CD3DFrame *)lpArg;

  frm->ObjCallback(delta);
  }



/////////////////////////////////////////////////////////////////////////////
// CD3DFrame

IMPLEMENT_DYNAMIC(CD3DFrame, CObject)

CD3DFrame::CD3DFrame()
  {
  m_lpFrame = NULL;
  m_lpMesh = NULL;

  m_pOwner = NULL;
  m_pParent = NULL;
  m_bChanged = false; 

  m_POSITION = NULL;
  m_lpWrap = NULL;
  }

CD3DFrame::~CD3DFrame()
  {
  //= Sich vom Elternframe entfernen
  RemoveFromFrame();

  //= Sich vom Besitzerobjekt entfernen
  if (m_pOwner != NULL)
    m_pOwner->RemoveSlave(this);
  
  //= Kinderframes vernichten
  while (!m_ChildFrameList.IsEmpty())
    {
    CD3DFrame *frm = m_ChildFrameList.GetTail();
    delete frm;
    }
  
  D3DFREE(m_lpFrame);
  D3DFREE(m_lpMesh);
  D3DFREE(m_lpWrap);
  }

bool CD3DFrame::SetAppData(DWORD appdata)
  {
  D3DTRY(m_lpFrame->SetAppData(appdata));

  return true;
  }

DWORD CD3DFrame::GetAppData(void)
  {
  return (m_lpFrame->GetAppData());
  }

bool CD3DFrame::Create(CD3DMainObj* pOwner) 
  {
  if (pOwner == NULL)
    return false;

  pOwner->AddSlave(this);
  m_pOwner = pOwner;

  //= Frame anlegen
  D3DTRY(pOwner->GetMainObject()->CreateFrame(NULL, &m_lpFrame));

  //= Zeiger auf ID3DMeshBuilder2-Schnittstelle ermitteln
  D3DTRY(pOwner->GetMainObject()->CreateMeshBuilder(&m_lpMesh));

  //= Netz zum Frame einbinden
  D3DTRY(m_lpFrame->AddVisual((LPDIRECT3DRMVISUAL)m_lpMesh));

  m_bChanged = true;
  return true;
  }

bool CD3DFrame::IsChanged()
  {
  bool bChanged = m_bChanged;
    
  CD3DFrame *chld = GetFirstChild();
  while (chld != NULL)
    {
    bChanged |= chld->IsChanged();
    chld = GetNextChild();
    }

  m_bChanged = false;
  return bChanged;
  }

void CD3DFrame::AddChildFrame(CD3DFrame *pChild)
  {
  m_bChanged = true;
  m_ChildFrameList.AddTail(pChild);
  }

void CD3DFrame::RemoveChildFrame(CD3DFrame *pChild)
  {
  m_bChanged = true;
  if (!m_ChildFrameList.IsEmpty())
    {
    POSITION pos = m_ChildFrameList.Find(pChild);
    if (pos != NULL)
      m_ChildFrameList.RemoveAt(pos);
    }
  }

CD3DFrame *CD3DFrame::GetFirstChild(void)
  {
  m_POSITION = m_ChildFrameList.GetHeadPosition();
  if (m_POSITION == NULL)
    return NULL;

  return m_ChildFrameList.GetNext(m_POSITION);
  }

CD3DFrame *CD3DFrame::GetNextChild(void)
  {
  if (m_POSITION == NULL)
    return NULL;

  return m_ChildFrameList.GetNext(m_POSITION);
  }

bool CD3DFrame::AddToFrame(CD3DFrame *pParent)
  {
  if (m_pParent == NULL)
    {
    m_pParent = pParent;
    pParent->AddChildFrame(this);

    //= Zum Frame hinzufügen
    LPDIRECT3DRMFRAME3 frm = m_pParent->GetFrame();
    D3DTRY(frm->AddChild(m_lpFrame));

    return true;
    }
  return false;
  }

bool CD3DFrame::AddFrame(CD3DFrame *frame)
  {
  LPDIRECT3DRMFRAME3 frm = frame->GetFrame();

  D3DTRY(m_lpMesh->AddFrame(frm));
  return true;
  }

bool CD3DFrame::RemoveFromFrame()
  {
  if (m_pParent != NULL)
    {
    m_pParent->RemoveChildFrame(this);
    m_pParent = NULL;
    return true;
    }

  return false;
  }

bool CD3DFrame::AddFaces(DWORD dwVertexCount, D3DVECTOR * lpD3DVertices,
                         DWORD normalCount, D3DVECTOR *lpNormals, DWORD *lpFaceData,
                         LPDIRECT3DRMFACEARRAY* lplpD3DRMFaceArray)
  {
  m_bChanged = true;
  D3DTRY(m_lpMesh->SetPerspective(TRUE));
  return D3DCHECK(m_lpMesh->AddFaces(dwVertexCount, lpD3DVertices, 
                                    normalCount, lpNormals, 
                                    lpFaceData, lplpD3DRMFaceArray));
  }

bool CD3DFrame::SetColor(D3DCOLOR color, bool hier)
  {
  if (m_lpMesh != NULL)
    {
    D3DTRY(m_lpMesh->SetColorRGB(D3DVAL((float)GetRValue(color) / 255.0), 
                                 D3DVAL((float)GetGValue(color) / 255.0), 
                                 D3DVAL((float)GetBValue(color) / 255.0)));
    m_bChanged = true;
    }
  if (hier)
    {
    CD3DFrame *chld = GetFirstChild();
    while (chld != NULL)
      {
      chld->SetColor(color, hier);
      chld = GetNextChild();
      }
    }

  return true;
  }

void CD3DFrame::NormalFromFace(D3DVECTOR *vert_in1, D3DVECTOR *vert_in2, D3DVECTOR *vert_in3,
                               D3DVECTOR *norm_out)
  //= Normalvektor von 3 Ecken berechnen
  //= Direct3D - Funktionalität damit verwenden
  {
  D3DVECTOR v1, v2;

 
  D3DRMVectorSubtract(&v1, vert_in2, vert_in1);   
 
  D3DRMVectorSubtract(&v2, vert_in3, vert_in1);
  D3DRMVectorCrossProduct(norm_out, &v1, &v2);
  //= Normalisierung
  D3DRMVectorNormalize(norm_out);
  }

bool CD3DFrame::AddScale(D3DRMCOMBINETYPE rctCombine,
	                       D3DVALUE rvX, D3DVALUE rvY, D3DVALUE rvZ)
  {
  m_bChanged = true;
  return D3DCHECK(m_lpFrame->AddScale(rctCombine, rvX, rvY, rvZ));
  }

bool CD3DFrame::AddTranslation(D3DRMCOMBINETYPE rctCombine,
	                       D3DVALUE rvX, D3DVALUE rvY, D3DVALUE rvZ)
  {
  m_bChanged = true;
  return D3DCHECK(m_lpFrame->AddTranslation(rctCombine, rvX, rvY, rvZ));
  }

bool CD3DFrame::AddRotation(D3DRMCOMBINETYPE rctCombine,
	                        D3DVALUE rvX,	D3DVALUE rvY,	D3DVALUE rvZ,
                          D3DVALUE rvTheta)
  {
  m_bChanged = true;
  return D3DCHECK(m_lpFrame->AddRotation(rctCombine, rvX,	rvY,	rvZ, rvTheta));
  }

bool CD3DFrame::SetPosition(CD3DFrame *lpRef,
	                       D3DVALUE rvX, D3DVALUE rvY, D3DVALUE rvZ)
  {
  m_bChanged = true;
  return D3DCHECK(m_lpFrame->SetPosition(lpRef->m_lpFrame, rvX, rvY, rvZ));
  }

bool CD3DFrame::SetRotation(CD3DFrame *lpRef,
	                        D3DVALUE rvX,	D3DVALUE rvY,	D3DVALUE rvZ,
                          D3DVALUE rvTheta)
  {
  m_bChanged = true;
  return D3DCHECK(m_lpFrame->SetRotation(lpRef->m_lpFrame, rvX,	rvY,	rvZ, rvTheta));
  }

bool CD3DFrame::SetVelocity(CD3DFrame *lpRef,
	                        D3DVALUE rvX,	D3DVALUE rvY,	D3DVALUE rvZ,
                          bool frotvel)
  {
  m_bChanged = true;
  return D3DCHECK(m_lpFrame->SetVelocity(lpRef->m_lpFrame, rvX,	rvY,	rvZ, frotvel));
  }

bool CD3DFrame::SetMoveCallback(bool SetDelete, bool before)
  {
  if (SetDelete)
    {
    D3DTRY(m_lpFrame->AddMoveCallback(&d3dMoveCallback, this, 
           before ? D3DRMCALLBACK_PREORDER : D3DRMCALLBACK_POSTORDER));
    }
  else
    {
    D3DTRY(m_lpFrame->DeleteMoveCallback(&d3dMoveCallback, this));
    }
  return true;
  }

bool CD3DFrame::AddCombTransform(D3DVALUE rvsX,	D3DVALUE rvsY,	D3DVALUE rvsZ,
                          D3DVALUE rvThetaX, D3DVALUE rvThetaY, D3DVALUE rvThetaZ,
	                        D3DVALUE rvX,	D3DVALUE rvY,	D3DVALUE rvZ)
  {
  //= Änderungen beachten
  m_bChanged = true;

  //= Mit dem Skalieren anfangen
  D3DCHECK(m_lpFrame->AddScale(D3DRMCOMBINE_AFTER, rvsX, rvsY, rvsZ));

  //= Nur Nicht-Null Drehen berücksichtigen
  //= Drehen um den X-Koordinatenpfeil
  if (rvThetaX != D3DVAL(0.0))
    D3DCHECK(m_lpFrame->AddRotation(D3DRMCOMBINE_AFTER, D3DVAL(1), 
                                    D3DVAL(0), D3DVAL(0), rvThetaX));
  //= Drehen um den Y-Koordinatenpfeil
  if (rvThetaY != D3DVAL(0.0))
    D3DCHECK(m_lpFrame->AddRotation(D3DRMCOMBINE_AFTER, D3DVAL(0), 
                                    D3DVAL(1), D3DVAL(0), rvThetaY));
  //= Drehen um den Y-Koordinatenpfeil
  if (rvThetaZ != D3DVAL(0.0))
    D3DCHECK(m_lpFrame->AddRotation(D3DRMCOMBINE_AFTER, D3DVAL(0), 
                                    D3DVAL(0), D3DVAL(1), rvThetaZ));
  //= Verschiebung
  return D3DCHECK(m_lpFrame->AddTranslation(D3DRMCOMBINE_AFTER, rvX, rvY, rvZ));
  }

bool CD3DFrame::TransformToWorld(D3DVALUE rvFX, D3DVALUE rvFY, D3DVALUE rvFZ,
                          D3DVALUE *rvWX, D3DVALUE *rvWY, D3DVALUE *rvWZ)
  {
  return true;   
  }

bool CD3DFrame::AddShadow(CD3DLightFrame *who_cast,
                          D3DVALUE rvsX, D3DVALUE rvsY, D3DVALUE rvsZ,
                          D3DVALUE rvX, D3DVALUE rvY, D3DVALUE rvZ)
  {
  LPDIRECT3DRMSHADOW2 lpShadow; 

	
  D3DTRY(m_pOwner->GetMainObject()->CreateShadow((LPDIRECT3DRMVISUAL)m_lpMesh,
               who_cast->m_lpLight, 
               rvsX, rvsY, rvsZ,    
               rvX, rvY, rvZ,       
              &lpShadow));          

  D3DTRY(m_lpFrame->AddVisual(lpShadow));
  D3DTRY(lpShadow->SetOptions(D3DRMSHADOW_TRUEALPHA)); 

  D3DFREE(lpShadow);  

  return true;
  }

bool CD3DFrame::SetMaterial(CD3DMaterial *mat, bool hier)
  {
  if (m_lpMesh != NULL)
    {
    D3DTRY(m_lpMesh->SetMaterial(mat->m_lpMaterial));
    m_bChanged = true;
    }

  if (hier)
    {
    CD3DFrame *chld = GetFirstChild();
    while (chld != NULL)
      {
      chld->SetMaterial(mat, hier);
      chld = GetNextChild();
      }
    }

  return true;
  }

DWORD CD3DFrame::GetChildNumber()
  {
  DWORD n  = 0;
  CD3DFrame *chld = GetFirstChild();

  while (chld != NULL)
    {
    n++;
    chld = GetNextChild();
    }

  return n;
  }

CD3DFrame *CD3DFrame::GetChildFrame(DWORD AppData)
  {
  CD3DFrame *chld = GetFirstChild();

  while (chld != NULL)
    {
    if (chld->GetAppData() == AppData)
      return chld;
    chld = GetNextChild();
    }

  return NULL;
  }

bool CD3DFrame::AddDecalVisual(CD3DTexture *tex)
  {
  D3DTRY(m_lpFrame->AddVisual((LPDIRECT3DRMVISUAL)tex->m_lpTexture));
  return true;
  }

bool CD3DFrame::ApplyFlatWrap(CD3DTexture *tex,
                            D3DVALUE ox, D3DVALUE oy, D3DVALUE oz,
                            D3DVALUE dx, D3DVALUE dy, D3DVALUE dz,
                            D3DVALUE ux, D3DVALUE uy, D3DVALUE uz,
                            D3DVALUE ou, D3DVALUE ov, D3DVALUE su, D3DVALUE sv)
  {
  LPDIRECT3DRMWRAP lpWrap;  //= Verweis auf die Wrap-Schnittstelle

  if (m_lpMesh == NULL)
    return false;           

  D3DTRY(m_pOwner->GetMainObject()->CreateWrap(D3DRMWRAP_FLAT, NULL,
                 ox, oy, oz, dx, dy, dz, ux, uy, uz, ou, ov, su, sv, &lpWrap));
  D3DTRY(lpWrap->Apply((LPDIRECT3DRMOBJECT)m_lpMesh));
  D3DTRY(m_lpMesh->SetTexture(tex->m_lpTexture));
  D3DFREE(lpWrap);

  return true;
  }

bool CD3DFrame::ApplyCylinderWrap(CD3DTexture *tex,
                            D3DVALUE ox, D3DVALUE oy, D3DVALUE oz,
                            D3DVALUE dx, D3DVALUE dy, D3DVALUE dz,
                            D3DVALUE ux, D3DVALUE uy, D3DVALUE uz,
                            D3DVALUE ou, D3DVALUE ov, D3DVALUE su, D3DVALUE sv)
  {
  LPDIRECT3DRMWRAP lpWrap;  //= Verweis auf die Wrap-Schnittstelle

  if (m_lpMesh == NULL)
    return false;           

  D3DTRY(m_pOwner->GetMainObject()->CreateWrap(D3DRMWRAP_CYLINDER, NULL,
                 ox, oy, oz, dx, dy, dz, ux, uy, uz, ou, ov, su, sv, &lpWrap));
  D3DTRY(lpWrap->Apply((LPDIRECT3DRMOBJECT)m_lpMesh));
  D3DTRY(m_lpMesh->SetTexture(tex->m_lpTexture));
  D3DFREE(lpWrap);

  return true;
  }

bool CD3DFrame::ApplySphereWrap(CD3DTexture *tex,
                            D3DVALUE ox, D3DVALUE oy, D3DVALUE oz,
                            D3DVALUE dx, D3DVALUE dy, D3DVALUE dz,
                            D3DVALUE ux, D3DVALUE uy, D3DVALUE uz,
                            D3DVALUE ou, D3DVALUE ov, D3DVALUE su, D3DVALUE sv)
  {
  LPDIRECT3DRMWRAP lpWrap;  //= Verweis auf die Wrap-Schnittstelle

  if (m_lpMesh == NULL)
    return false;           

  D3DTRY(m_pOwner->GetMainObject()->CreateWrap(D3DRMWRAP_SPHERE, NULL,
                 ox, oy, oz, dx, dy, dz, ux, uy, uz, ou, ov, su, sv, &lpWrap));
  D3DTRY(lpWrap->Apply((LPDIRECT3DRMOBJECT)m_lpMesh));
  D3DTRY(m_lpMesh->SetTexture(tex->m_lpTexture));
  D3DFREE(lpWrap);

  return true;
  }

bool CD3DFrame::CreateChromeWrap(D3DVALUE ox, D3DVALUE oy, D3DVALUE oz,
                            D3DVALUE dx, D3DVALUE dy, D3DVALUE dz,
                            D3DVALUE ux, D3DVALUE uy, D3DVALUE uz,
                            D3DVALUE ou, D3DVALUE ov, D3DVALUE su, D3DVALUE sv)
  {

  if (m_lpWrap != NULL)
    D3DFREE(m_lpWrap);

  D3DTRY(m_pOwner->GetMainObject()->CreateWrap(D3DRMWRAP_CHROME, 
                 m_lpFrame,
                 ox, oy, oz, dx, dy, dz, ux, uy, uz, ou, ov, su, sv, &m_lpWrap));
  return true;
  }


bool CD3DFrame::ApplyChromeWrap(CD3DTexture *tex, CD3DFrame *lpRef, CD3DFrame *lpObj,
                            D3DVALUE ox, D3DVALUE oy, D3DVALUE oz,
                            D3DVALUE dx, D3DVALUE dy, D3DVALUE dz,
                            D3DVALUE ux, D3DVALUE uy, D3DVALUE uz,
                            D3DVALUE ou, D3DVALUE ov, D3DVALUE su, D3DVALUE sv)
  {
  LPDIRECT3DRMWRAP lpWrap;  //= Verweis auf die Wrap-Schnittstelle

  if (m_lpMesh == NULL)
    return false;           

  D3DTRY(m_pOwner->GetMainObject()->CreateWrap(D3DRMWRAP_CHROME, 
                 lpRef->m_lpFrame,
                 ox, oy, oz, dx, dy, dz, ux, uy, uz, ou, ov, su, sv, &lpWrap));
  D3DTRY(m_lpMesh->SetTexture(tex->m_lpTexture));
  
  LPDIRECT3DRMFRAME lpFrame;
  D3DTRY(lpObj->m_lpFrame->QueryInterface(IID_IDirect3DRMFrame, (void **)&lpFrame));

  D3DTRY(lpWrap->ApplyRelative(lpFrame, (LPDIRECT3DRMOBJECT)m_lpMesh));
  D3DFREE(lpWrap);

  return true;
  }

bool CD3DFrame::ApplyChrome(CD3DTexture *tex, CD3DFrame *lpRef, CD3DFrame *lpObj)
  {
  D3DTRY(m_lpMesh->SetTexture(tex->m_lpTexture));
  
  LPDIRECT3DRMFRAME lpFrame;
  D3DTRY(lpObj->m_lpFrame->QueryInterface(IID_IDirect3DRMFrame, (void **)&lpFrame));

  D3DTRY(lpRef->m_lpWrap->ApplyRelative(lpFrame, (LPDIRECT3DRMOBJECT)m_lpMesh));

  return true;
  }

