// D3DMainObject.cpp : implementation file
//

#include "stdafx.h"
#include "DDMainObj.h"

#include "D3DMainObj.h"
#include "D3DFrame.h"
#include "D3DMaterial.h"
#include "D3DTexture.h"
#include "D3DAnimation.h"
#include "D3DCameraFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static DWORD BPPToDDBD(int BPP)
  {
  switch(BPP) 
    {
    case 1:
      return DDBD_1;
    case 2:
      return DDBD_2;
    case 4:
      return DDBD_4;
    case 8:
      return DDBD_8;
    case 16:
      return DDBD_16;
    case 24:
      return DDBD_24;
    case 32:
      return DDBD_32;
    }
  
  return 0;
  }

static HRESULT 
WINAPI enumDeviceFunc(LPGUID pGUID, LPSTR pDeviceDescription, 
                                     LPSTR pDeviceName, LPD3DDEVICEDESC pHWDesc, 
                                     LPD3DDEVICEDESC pHELDesc, LPVOID pContext) 
  {
  CD3DMainObj *lpD3DMainObject = (CD3DMainObj *)pContext;

  LPD3DDEVICEDESC pDesc;
  int iNewDriverCaps = 0;

  // decide which device description should be consulted.
  pDesc = pHWDesc->dcmColorModel ? pHWDesc : pHELDesc;

  //= If this driver cannot render in the current display bit-depth, 
  //= skip it and continue with the enumeration.
  if (!(pDesc->dwDeviceRenderBitDepth & BPPToDDBD(lpD3DMainObject->m_BPP)))
    return D3DENUMRET_OK;

  if (pDesc == pHWDesc) 
    iNewDriverCaps += 2;

  if ((pDesc->dwFlags & D3DDD_COLORMODEL) && (pDesc->dcmColorModel != D3DCOLOR_MONO)) 
    iNewDriverCaps += 1;

  // compare drive caps
  if (lpD3DMainObject->m_iDriverCaps < iNewDriverCaps) 
    { 
    // remember it
    lpD3DMainObject->m_iDriverCaps = iNewDriverCaps;
    memcpy(&lpD3DMainObject->m_DriverGUID, pGUID, sizeof(GUID));
    lstrcpy(lpD3DMainObject->m_DriverName, pDeviceName);
    }

  return (D3DENUMRET_OK);
  }

/////////////////////////////////////////////////////////////////////////////
// CD3DMainObj
IMPLEMENT_DYNAMIC(CD3DMainObj, CD3DFrame)

CD3DMainObj::CD3DMainObj()
  {
  m_lpD3DRM = NULL;
  m_lpDDClipper = NULL;
  
  m_lpDev = NULL;
  m_lpView = NULL;
  m_lpCameraFrame = NULL;
  m_lpAmbientLight = NULL;
  
  m_iDriverCaps = -1;
  m_BPP = 0;
  m_bChanged = false;   

  //= Festlegen der Kameraeigenschaften.
  m_fCameraFront = 1.0;
  m_fCameraBack = 10.0;
  m_fCameraField = 1.0;
  m_bFromField = true;

  m_rqQuality = D3DRMLIGHT_ON | D3DRMFILL_SOLID | D3DRMSHADE_FLAT;
  m_ptType = D3DRMPROJECT_PERSPECTIVE;
  
  //= Festlegen der Umgebungslichteeigenschaften
  m_fAmbientLightRed = D3DVAL(0.7);
  m_fAmbientLightGreen = D3DVAL(0.7);
  m_fAmbientLightBlue = D3DVAL(0.7);

  //= Hintergrund = Hintergrundfarbe
  m_bFromImage = false;
  //= Tick werden nicht erlaubt
  m_bTickEnable = false;

  //= Pick - Feld ist leer
  m_lplpFrame = NULL;
  }

bool CD3DMainObj::SetTickEnable(bool enable)
  {
  m_bTickEnable = enable;
  return true;
  }

CD3DMainObj::~CD3DMainObj()
  {
  while (!m_SlaveList.IsEmpty())
    {
    CD3DFrame *frm = m_SlaveList.GetTail();
    delete frm;
    }
  
  while (!m_MaterialList.IsEmpty())
    {
    CD3DMaterial *mat = m_MaterialList.GetTail();
    delete mat;
    }
  
  while (!m_TextureList.IsEmpty())
    {
    CD3DTexture *tex = m_TextureList.GetTail();
    delete tex;
    }
  
  while (!m_AnimationList.IsEmpty())
    {
    CD3DAnimation *tex = m_AnimationList.GetTail();
    delete tex;
    }
  
  if (m_lplpFrame != NULL)
    {
    delete [] m_lplpFrame;
    }

  D3DFREE(m_lpView);
  D3DFREE(m_lpDev);
  D3DFREE(m_lpD3DRM);
  D3DFREE(m_lpDDClipper);
  D3DFREE(m_lpAmbientLight);
  }

bool CD3DMainObj::Create(CWnd *pParentWnd) 
  {
  
  //= Farbtiefe (bits-per-pixel) sichern
  CDC *pDC = pParentWnd->GetDC();
  m_BPP = pDC->GetDeviceCaps(BITSPIXEL);
  pParentWnd->ReleaseDC(pDC);
  
  //= Auswahl des Treibers
  if (!EnumDrivers())
    return false;
  
  //= Erzeugen des D3DRM-Objekts und des D3DRM-Fenster-Objekts 
  LPDIRECT3DRM lpD3DRM = NULL; 

  D3DTRY(Direct3DRMCreate(&lpD3DRM));
  
  HRESULT res = lpD3DRM->QueryInterface(IID_IDirect3DRM3, (void **)&m_lpD3DRM);
  
  lpD3DRM->Release();
  D3DTRY(res);

  //= Wurzelframe für die Szene erzeugen 
  D3DTRY(m_lpD3DRM->CreateFrame(NULL, &m_lpFrame));
  
  //= Kamera erzeugen
  m_lpCameraFrame = new CD3DCameraFrame;
  if (m_lpCameraFrame == NULL)
    return false;
  
  if (!m_lpCameraFrame->Create(this))
    return false;

  //= Umgebungslicht festlegen
  D3DTRY(m_lpD3DRM->CreateLightRGB(D3DRMLIGHT_AMBIENT, 
                                   m_fAmbientLightRed, 
                                   m_fAmbientLightGreen,  
                                   m_fAmbientLightBlue,
                                   &m_lpAmbientLight));
  D3DTRY(m_lpFrame->AddLight(m_lpAmbientLight));

  //= DirectDrawClipper-Objekt anlegen und mit dem Fenster verbinden 
  DDTRY(DirectDrawCreateClipper(0, &m_lpDDClipper, NULL));
  DDTRY(m_lpDDClipper->SetHWnd(0, pParentWnd->m_hWnd));
  
  //= D3DRM-Gerät anlegen
  CRect rc;
  pParentWnd->GetClientRect(&rc);
  if (!CreateDevAndView(rc.right, rc.bottom))
    return false;

  m_bChanged = true;

  //= Virtuelle Funktion aufrufen, um dem abgeleiteten Objekt    
  //= die Chance zu geben, spezifische Initialisierungen 
  //= durchzuführen 
  return OnCreate();
  }

bool CD3DMainObj::EnumDrivers()
  {
  LPDIRECTDRAW lpDD;
  LPDIRECT3D   lpD3D;
  bool ret_code;
  
  //= DirectDraw Objekt anlegen und Direct3D Schnittstelle ermitteln
  DDTRY(DirectDrawCreate(NULL, &lpDD, NULL));
  if (!DDCHECK(lpDD->QueryInterface(IID_IDirect3D, (void **)&lpD3D)))
    {
    lpDD->Release();
    return false;
    }
  
  //= Treibern aufzählen
  lpD3D->EnumDevices(enumDeviceFunc, this);
  if (m_iDriverCaps == -1)
    ret_code = false;
  else
    ret_code = true;
  
  lpD3D->Release();
  lpDD->Release();
  return ret_code;
  }                       

bool CD3DMainObj::CreateDevAndView(int width, int height)
  {
  if (width <= 0 || height <= 0)
    return false;
  
  //= D3DRM - Gerät anlegen 
  D3DTRY(m_lpD3DRM->CreateDeviceFromClipper(m_lpDDClipper, 
        &m_DriverGUID, width, height, &m_lpDev));
  
  //= D3DRM Viewport anlegen
  width = m_lpDev->GetWidth();
  height = m_lpDev->GetHeight();
  
  if (!D3DCHECK(m_lpD3DRM->CreateViewport(m_lpDev, m_lpCameraFrame->GetFrame(), 
    0, 0, width, height, &m_lpView)))
    {
    m_lpDev->Release();
    return false;
    }

  //= Kameraeigenschaften aktualisieren
  SetCameraBack(m_fCameraBack);
  SetCameraFront(m_fCameraFront);

  if (m_bFromField)
    SetCameraField(m_fCameraField);
  else
    SetCameraPlane(m_fCameraLeft, m_fCameraRight,
                   m_fCameraBottom, m_fCameraTop);
  
  //= Render-Quality festlegen
  SetRenderQuality(m_rqQuality);
  SetProjection(m_ptType);

  return true;
  }

bool CD3DMainObj::IsMatChanged()
  {
  bool temp = false;

  POSITION pos = m_MaterialList.GetHeadPosition();
  while (pos != NULL)
    {
    CD3DMaterial *mat = m_MaterialList.GetNext(pos);
    temp |= mat->IsChanged();
    }
  return temp;
  }


bool CD3DMainObj::IsTexChanged()
  {
  bool temp = false;

  POSITION pos = m_TextureList.GetHeadPosition();
  while (pos != NULL)
    {
    CD3DTexture *tex = m_TextureList.GetNext(pos);
    temp |= tex->IsChanged();
    }
  return temp;
  }

bool CD3DMainObj::Loop(bool bForced)
  {
  bool bChanged = false;

  if (!IsOK())
    return true;

  //= Bearbeitung eines Ticks
  if (m_bTickEnable)
    {
    bChanged = true;
    D3DTRY(m_lpD3DRM->Tick(D3DVAL(1.0)));
    }

  bChanged |= IsChanged() | IsMatChanged() | IsTexChanged();
  if (!bChanged && !bForced)
    return true;

  //= Viewport aufräumen
  D3DTRY(m_lpView->Clear(D3DRMCLEAR_ALL));
  
  //= Szene im Viewport darstellen (rendering)
  D3DTRY(m_lpView->Render(m_lpFrame));
  
  //= Fenster aktualisieren
  D3DTRY(m_lpDev->Update());

  m_bChanged = false;
  return true;
  }

void CD3DMainObj::Paint(CDC *dc) 
  {
  if (m_lpDev == NULL)
    return;
  
  LPDIRECT3DRMWINDEVICE lpD3DRMWinDev;
  if (!D3DCHECK(m_lpDev->QueryInterface(IID_IDirect3DRMWinDevice, (void **) &lpD3DRMWinDev)))
    return;
  
  if (!D3DCHECK(lpD3DRMWinDev->HandlePaint(dc->m_hDC)))
    return;
  
  lpD3DRMWinDev->Release();
  Loop(true);
  }

void CD3DMainObj::Activate(BOOL bActivate) 
  {
  LPDIRECT3DRMWINDEVICE lpD3DRMWinDev;
  
  if (!D3DCHECK(m_lpDev->QueryInterface(IID_IDirect3DRMWinDevice, (void **) &lpD3DRMWinDev)))
    return;
  
  if (!D3DCHECK(lpD3DRMWinDev->HandleActivate(bActivate)))
    return;
  
  lpD3DRMWinDev->Release();
  if (bActivate)
    Loop(true);
  }

void CD3DMainObj::SizeChanged(int cx, int cy)
  {
  if (!IsOK())
    return;
  
  D3DFREE(m_lpView);
  D3DFREE(m_lpDev);
  
  CreateDevAndView(cx, cy);

  Loop(true);
  }

bool CD3DMainObj::D3DCheckHRESULT(HRESULT hr, int line, char *file)
  {
  if (hr == D3DRM_OK)
    return true;
  
  CString strErr;    
  switch (hr)
    {
    case D3DRMERR_BADALLOC:
      strErr = CString("Out of memory. ");
      break;
      
    case D3DRMERR_BADDEVICE:
      strErr = CString("Device is not compatible with renderer. ");
      break;
      
    case D3DRMERR_BADFILE:
      strErr = CString("Data file is corrupt. ");
      break;
      
    case D3DRMERR_BADMAJORVERSION:
      strErr = CString("Bad DLL major version. ");
      break;
      
    case D3DRMERR_BADMINORVERSION:
      strErr = CString("Bad DLL minor version. ");
      break;
      
    case D3DRMERR_BADOBJECT:
      strErr = CString("Object expected in argument. ");
      break;
      
    case D3DRMERR_BADPMDATA:
      strErr = CString("The data in the .x file is corrupted. The conversion to a progressive mesh succeeded but produced an invalid progressive mesh in the .x file. ");
      break;
      
    case D3DRMERR_BADTYPE:
      strErr = CString("Bad argument type passed. ");
      break;
      
    case D3DRMERR_BADVALUE:
      strErr = CString("Bad argument value passed. ");
      break;
      
    case D3DRMERR_BOXNOTSET:
      strErr = CString("An attempt was made to access a bounding box (for example, with IDirect3DRMFrame3::GetBox) when no bounding box was set on the frame. ");
      break;
      
    case D3DRMERR_CONNECTIONLOST:
      strErr = CString("Data connection was lost during a load, clone, or duplicate. ");
      break;
      
    case D3DRMERR_FACEUSED:
      strErr = CString("Face already used in a mesh. ");
      break;
      
    case D3DRMERR_FILENOTFOUND:
      strErr = CString("File cannot be opened. ");
      break;
      
    case D3DRMERR_INVALIDLIBRARY:
      strErr = CString("Specified libary is invalid. ");
      break;
      
    case D3DRMERR_LIBRARYNOTFOUND:
      strErr = CString("Specified libary not found. ");
      break;
      
    case D3DRMERR_LOADABORTED:
      strErr = CString("Load aborted by user. ");
      break;
      
    case D3DRMERR_NOTDONEYET:
      strErr = CString("Unimplemented. ");
      break;
      
    case D3DRMERR_NOTENOUGHDATA:
      strErr = CString("Not enough data has been loaded to perform the requested operation. ");
      break;
      
    case D3DRMERR_NOTFOUND:
      strErr = CString("Object not found in specified place. ");
      break;
      
    case D3DRMERR_PENDING:
      strErr = CString("Data required to supply the requested information has not finished loading. ");
      break;
      
    case D3DRMERR_REQUESTTOOLARGE:
      strErr = CString("Attempt was made to set a level of detail in a progressive mesh greater than the maximum available. ");
      break;
      
    case D3DRMERR_REQUESTTOOSMALL:
      strErr = CString("Attempt was made to set the minimum rendering detail of a progressive mesh smaller than the detail in the base mesh (the minimum for rendering). ");
      break;
      
    case D3DRMERR_UNABLETOEXECUTE:
      strErr = CString("Unable to carry out procedure. ");
      break;
      
    case DDERR_INVALIDOBJECT:
      strErr = CString("Received pointer that was an invalid object. ");
      break;
      
    case DDERR_INVALIDPARAMS:
      strErr = CString("One or more of the parameters passed to the method are incorrect. ");
      break;
      
    case DDERR_NOTFOUND:
      strErr = CString("The requested item was not found. ");
      break;
      
    case DDERR_NOTINITIALIZED:
      strErr = CString("An attempt was made to call an interface method of an object created by CoCreateInstance before the object was initialized. ");
      break;
      
    case DDERR_OUTOFMEMORY:
      strErr = CString("DirectDraw does not have enough memory to perform the operation. ");
      break;

// version 6
    case D3DRMERR_CLIENTNOTREGISTERED:
    strErr = CString("Client has not been registered. Call IDirect3DRM3::RegisterClient. ");
    break;
    
    case D3DRMERR_ELEMENTINUSE:
    strErr = CString("Element can't be modified or deleted while in use. To empty a submesh, call Empty() against its parent. ");
    break;
      
/*    case D3DRMERR_ENTRYINUSE:
    strErr = CString("Vertex or normal entries are currently in use by a face and cannot be deleted. ");
    break;
    
    case D3DRMERR_INCOMPATIBLEKEY:
    strErr = CString("Specified animation key is incompatible. The key cannot be modified. ");
    break;
  
    case 3DRMERR_INVALIDOBJECT:
    strErr = CString("Method received a pointer to an object that is invalid. ");
    break;
  
    case 3DRMERR_INVALIDPARAMS:
    strErr = CString("One of the parameters passed to the method is invalid. ");
    break;
  
    case 3DRMERR_NOSUCHKEY:
    strErr = CString("Specified animation key does not exist. ");
    break;
  
    case 3DRMERR_NOTCREATEDFROMDDS:
    strErr = CString("Specified texture was not created from a DirectDraw Surface. ");
    break;
  
    case 3DRMERR_OUTOFRANGE:
    strErr = CString("Specified value is out of range. ");
    break;
  
    case 3DRMERR_TEXTUREFORMATNOTFOUND:
    strErr = CString("Texture format could not be found that meets the specified criteria and that the underlying Immediate Mode device supports. ");
    break;

*/
    default:
      strErr = CString("UNKNOWN. ");
    }
    
  D3DError(strErr, hr, line, file);  
  return false;    
  }
  
void CD3DMainObj::D3DError(const CString& strErr, HRESULT hr, int line, char *file)
  {
  CString str = strErr;
  
  if(hr != 0)
    {
    CString strTmp;
    strTmp.Format(" \nFehlercode: %X ", hr);
    str += strTmp;
    if (line != -1 && file != NULL)
      {
      strTmp.Format(" \nLine : %d \nFile: %s", line, file);
      str += strTmp;
      }
    }
  
  ::MessageBox(NULL, str, "Fehhler in Direct3D", MB_OK);
  }
  
bool CD3DMainObj::SetCameraFront(D3DVALUE fFront)
  { 
	//= Festlegen der Distanz bis zur Frontfläche
  m_bChanged = true;
  m_fCameraFront = fFront;
  return D3DCHECK(m_lpView->SetFront(D3DVAL(fFront)));
  }
  
bool CD3DMainObj::SetCameraBack(D3DVALUE fBack)
  { 
	//= Festlegen der Distanz bis zur Rückfläche
  m_bChanged = true;
  m_fCameraBack = fBack;
  return D3DCHECK(m_lpView->SetBack(D3DVAL(fBack)));
  }
  
bool CD3DMainObj::SetCameraField(D3DVALUE fField)
  { 
	//= Festlegen der Distanz bis zur Rückfläche
  m_bChanged = true;
  m_bFromField = true;
  m_fCameraField = fField;
  return D3DCHECK(m_lpView->SetField(D3DVAL(fField)));
  }
   
bool CD3DMainObj::SetCameraPlane(D3DVALUE fLeft, D3DVALUE fRight, D3DVALUE fBottom, D3DVALUE fTop)
  { 
	//= Attribute von Fronfläche festlegen
  m_bChanged = true;
  m_bFromField = false;
  m_fCameraLeft = fLeft;
  m_fCameraRight = fRight;
  m_fCameraBottom = fBottom;
  m_fCameraTop = fTop;

  return D3DCHECK(m_lpView->SetPlane(D3DVAL(fLeft), D3DVAL(fRight), 
                                     D3DVAL(fBottom), D3DVAL(fTop)));
  }

bool CD3DMainObj::SetSceneBackground(D3DCOLOR color)
  {
  m_bChanged = true;
  m_bFromImage = false;
  return D3DCHECK(m_lpFrame->SetSceneBackgroundRGB(D3DVAL((float)GetRValue(color) / 255.0), 
                                                   D3DVAL((float)GetGValue(color) / 255.0), 
                                                   D3DVAL((float)GetBValue(color) / 255.0)));
  }

bool CD3DMainObj::SetSceneBackgroundRGB(D3DVALUE red, D3DVALUE green, D3DVALUE blue)
  {
  m_bChanged = true;
  m_bFromImage = false;
  return D3DCHECK(m_lpFrame->SetSceneBackgroundRGB(red, green, blue)); 
  }

D3DCOLOR CD3DMainObj::GetSceneBackground()
  {
  D3DCOLOR col = m_lpFrame->GetSceneBackground();
  return RGB(RGB_GETRED(col), RGB_GETGREEN(col), RGB_GETBLUE(col));
  }

bool CD3DMainObj::SetImageFile(LPCSTR filename)
  {
  LPDIRECT3DRMTEXTURE3 lpTexture;
  D3DTRY(m_lpD3DRM->LoadTexture((const char *)filename, &lpTexture));

  D3DTRY(m_lpFrame->SetSceneBackgroundImage(lpTexture));
  D3DFREE(lpTexture);
  m_bFromImage = true;
  m_bChanged = true;
  return true;
  }

bool CD3DMainObj::GetFogEnable()
  {
  return (m_lpFrame->GetSceneFogEnable()) ? true : false;
  }

D3DCOLOR CD3DMainObj::GetFogColor(void)
  {
  D3DCOLOR col = m_lpFrame->GetSceneFogColor();
  return RGB(RGB_GETRED(col), RGB_GETGREEN(col), RGB_GETBLUE(col));
  }

bool CD3DMainObj::GetFogParams(D3DVALUE *rvStart, D3DVALUE *rvEnd)
  {
  D3DVALUE lprvDensity;                                  
  D3DTRY(m_lpFrame->GetSceneFogParams(rvStart, rvEnd, &lprvDensity));
  return true;
  }

bool CD3DMainObj::SetFogEnable(bool Flag)
  {
  D3DTRY(m_lpFrame->SetSceneFogEnable(Flag));
  m_bChanged = true;
  return true;
  }

bool CD3DMainObj::SetFogColor(D3DCOLOR color)
  {
  return D3DCHECK(m_lpFrame->SetSceneFogColor((D3DCOLOR)color));
  m_bChanged = true;
  }

bool CD3DMainObj::SetFogParams(D3DVALUE rvStart, D3DVALUE rvEnd)
  {
  D3DVALUE rvDensity = 1.0;
  D3DTRY(m_lpFrame->SetSceneFogParams(rvStart, rvEnd, rvDensity));
  m_bChanged = true;
  return true;
  }
   
bool CD3DMainObj::SetRenderQuality(D3DRMRENDERQUALITY rqQuality)
  {
  m_bChanged = true;
  m_rqQuality = rqQuality;
  D3DTRY(m_lpDev->SetQuality(rqQuality));
  D3DTRY(m_lpDev->SetDither(FALSE));
  D3DTRY(m_lpDev->SetRenderMode(D3DRMRENDERMODE_BLENDEDTRANSPARENCY
                              | D3DRMRENDERMODE_SORTEDTRANSPARENCY
                              | D3DRMRENDERMODE_VIEWDEPENDENTSPECULAR));

  return true;
  }

bool CD3DMainObj::SetProjection(D3DRMPROJECTIONTYPE rptType)
  {
  m_bChanged = true;
  m_ptType = rptType;
  return D3DCHECK(m_lpView->SetProjection(rptType));
  }

bool CD3DMainObj::SetCameraParam(double Field, double Front, double Back, 
                        D3DCOLOR BkgColor, D3DCOLOR AmbColor,
                        D3DRMRENDERQUALITY rqQuality,
                        D3DRMPROJECTIONTYPE rptType)
  {
  if (!SetCameraBack(D3DVAL(Back)))
    return false;
  if (!SetCameraFront(D3DVAL(Front)))
    return false;
  if (!SetCameraField(D3DVAL(Field)))
    return false;
  if (!SetSceneBackground(BkgColor))
    return false;
  if (!SetAmbientLight(AmbColor))
    return false;
  if (!SetRenderQuality(rqQuality))
    return false;
  if (!SetProjection(rptType))
    return false;

  return true;
  }

bool CD3DMainObj::SetAmbientLight(D3DCOLOR color)
  {
  D3DVALUE red, green, blue;

  red = D3DVAL((float)GetRValue(color) / 255.0); 
  green = D3DVAL((float)GetGValue(color) / 255.0);
  blue = D3DVAL((float)GetBValue(color) / 255.0);

  return SetAmbientLightRGB(red, green, blue);
  }

bool CD3DMainObj::SetAmbientLightRGB(D3DVALUE red, D3DVALUE green, D3DVALUE blue)
  {
  m_bChanged = true;

  D3DTRY(m_lpAmbientLight->SetColorRGB(red, green, blue));
  m_fAmbientLightRed = red;
  m_fAmbientLightGreen = green;
  m_fAmbientLightBlue = blue;

  return true;
  }

D3DCOLOR CD3DMainObj::GetAmbientLight()
  {
  return RGB(m_fAmbientLightRed, m_fAmbientLightGreen, m_fAmbientLightBlue);
  }

bool CD3DMainObj::GetAmbientLightRGB(D3DVALUE *red, D3DVALUE *green, D3DVALUE *blue)
  {
  *red = m_fAmbientLightRed;
  *green = m_fAmbientLightGreen;
  *blue = m_fAmbientLightBlue;

  return true;
  }

void CD3DMainObj::AddSlave(CD3DFrame *pSlave)
  {
  m_SlaveList.AddTail(pSlave);
  }

void CD3DMainObj::RemoveSlave(CD3DFrame *pSlave)
  {
  if (!m_SlaveList.IsEmpty())
    {
    POSITION pos = m_SlaveList.Find(pSlave);
    if (pos != NULL)
      m_SlaveList.RemoveAt(pos);
    }
  }

void CD3DMainObj::AddMaterial(CD3DMaterial *pSlave)
  {
  m_MaterialList.AddTail(pSlave);
  }

void CD3DMainObj::RemoveMaterial(CD3DMaterial *pSlave)
  {
  if (!m_MaterialList.IsEmpty())
    {
    POSITION pos = m_MaterialList.Find(pSlave);
    if (pos != NULL)
      m_MaterialList.RemoveAt(pos);
    }
  }

void CD3DMainObj::AddTexture(CD3DTexture *pSlave)
  {
  m_TextureList.AddTail(pSlave);
  }

void CD3DMainObj::RemoveTexture(CD3DTexture *pSlave)
  {
  if (!m_TextureList.IsEmpty())
    {
    POSITION pos = m_TextureList.Find(pSlave);
    if (pos != NULL)
      m_TextureList.RemoveAt(pos);
    }
  }

void CD3DMainObj::AddAnimation(CD3DAnimation *pSlave)
  {
  m_AnimationList.AddTail(pSlave);
  }

void CD3DMainObj::RemoveAnimation(CD3DAnimation *pSlave)
  {
  if (!m_AnimationList.IsEmpty())
    {
    POSITION pos = m_AnimationList.Find(pSlave);
    if (pos != NULL)
      m_AnimationList.RemoveAt(pos);
    }
  }

bool CD3DMainObj::GetPick(int iX, int iY, int *count, CD3DFrame ***FrameArray)
  {
  int cnt;
  LPDIRECT3DRMPICKEDARRAY Picked;
  LPDIRECT3DRMFRAMEARRAY  lpFrameArray;
  LPDIRECT3DRMFRAME       frm;
  LPDIRECT3DRMVISUAL      lpVisual;
  D3DRMPICKDESC           D3DRMPickDesc;

  D3DTRY(m_lpView->Pick(iX, iY, &Picked));

  if (Picked == NULL || (Picked->GetSize() == 0))
    return false;

  D3DTRY(Picked->GetPick(0, &lpVisual, &lpFrameArray, &D3DRMPickDesc));
  D3DFREE(Picked);
  D3DFREE(lpVisual);
  
  cnt = lpFrameArray->GetSize();

  if (m_lplpFrame != NULL)
    {
    delete [] m_lplpFrame;
    }

  m_lplpFrame = new CD3DFrame *[cnt];
  int i;

  for (i = 0; i < cnt; i++)
    {
    m_lplpFrame[i] = NULL;
    D3DTRY(lpFrameArray->GetElement(i, &frm));
    POSITION pos = m_SlaveList.GetHeadPosition();

    while (pos != NULL)
      {
      CD3DFrame *chld = m_SlaveList.GetNext(pos);

      LPDIRECT3DRMFRAME lpFrame;
      D3DTRY(chld->m_lpFrame->QueryInterface(IID_IDirect3DRMFrame, (void **)&lpFrame));
      if (lpFrame == frm)
        {
        m_lplpFrame[i] = chld;
        D3DFREE(lpFrame);
        break;
        }

      D3DFREE(lpFrame);
      }
    }
  
  *count = cnt;
  *FrameArray = m_lplpFrame;
  
  return true;
  }

