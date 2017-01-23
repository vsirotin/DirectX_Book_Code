// ddMainObj.cpp : implementation file
//

#include "stdafx.h"

#include "ddMainObj.h"
#include "ddSprite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDMainObj
IMPLEMENT_DYNCREATE(CDDMainObj, CObject)

CDDMainObj::CDDMainObj()
  {
  m_lpDD = NULL;
  m_lpDDPrimarySurface = NULL;
  m_lpDDBackSurface = NULL;
  m_lpDDPalette = NULL;
  m_lpDDClipper = NULL;

  m_bWindowed = false;
  m_pParent = NULL;
  m_szSize = CSize(0, 0);
  }

CDDMainObj::~CDDMainObj()
  {
  //= Alle Sprites zerstören
  POSITION pos = m_SpriteList.GetHeadPosition();
  while (pos != NULL)
    delete m_SpriteList.GetNext(pos);
  
  m_SpriteList.RemoveAll();

  if (m_bWindowed)
    {
    // Fenstermodus
    if (m_lpDDBackSurface != NULL)
      m_lpDDBackSurface->Release();

    if (m_lpDDPrimarySurface != NULL && m_lpDDClipper != NULL)
      {
      m_lpDDPrimarySurface->SetClipper(NULL);
      m_lpDDClipper->Release();
      }
    }

  if (m_lpDDPrimarySurface != NULL)
    m_lpDDPrimarySurface->Release();

  if (m_lpDDPalette != NULL)
    m_lpDDPalette->Release();

  if (m_lpDD != NULL)
    m_lpDD->Release();
  }

bool CDDMainObj::Create(CWnd *pParentWnd)
  {
  m_pParent = pParentWnd;
  if ((::GetWindowLong(pParentWnd->m_hWnd, GWL_EXSTYLE) & WS_EX_TOPMOST) != 0)
    m_bWindowed = false;
  else
    m_bWindowed = true;

  //= Ermitteln des Zeigers auf dem DirectDraw-Objekt
  LPDIRECTDRAW lpDD;
  DDTRY(DirectDrawCreate(NULL, &lpDD, NULL));

  //= Ermitteln des Zeigers auf dem IDirectDraw2 - Objekt
  bool res = DDCHECK(lpDD->QueryInterface(IID_IDirectDraw2, (void **)&m_lpDD));
  lpDD->Release(); 

  if (!res)
    return false;

  //= Kooperationsniveau festlegen 
  DDTRY(m_lpDD->SetCooperativeLevel(pParentWnd->m_hWnd, 
                                    m_bWindowed ? DDSCL_NORMAL :
                                                  DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN));

  if (!m_bWindowed)
    {
    //= Abbildungsmodus festlegen
    DDTRY(m_lpDD->SetDisplayMode(640, 480, 8, 0, 0));
    m_szSize = CSize(640, 480);
    }

  //= Struktur festlegen
  DDSURFACEDESC ddSurfDesc;

  memset(&ddSurfDesc, 0, sizeof(DDSURFACEDESC));
  ddSurfDesc.dwSize = sizeof(DDSURFACEDESC);

  if (!m_bWindowed)
    {
    ddSurfDesc.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddSurfDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | 
                                DDSCAPS_FLIP |
                                DDSCAPS_COMPLEX;
    ddSurfDesc.dwBackBufferCount = 1;
    }
  else
    {
    ddSurfDesc.dwFlags = DDSD_CAPS;
    ddSurfDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
    }

  //= Ermitteln des Zeigers auf dem IDirectDrawSurface-Objekt
  LPDIRECTDRAWSURFACE pDDSurf;
  DDTRY(m_lpDD->CreateSurface(&ddSurfDesc, &pDDSurf, NULL));

  //= Ermitteln des Zeigers auf dem DirectDrawSurface3-Objekt
  res = DDCHECK(pDDSurf->QueryInterface(IID_IDirectDrawSurface3, 
                                        (void **)&m_lpDDPrimarySurface));
  pDDSurf->Release();

  if (!res)
    return false;

  if (!m_bWindowed)
    {
    //= Ermitteln des Zeigers auf der Rückfläche
    DDSCAPS ddSurfCaps;
    ddSurfCaps.dwCaps = DDSCAPS_BACKBUFFER;

    DDTRY(m_lpDDPrimarySurface->GetAttachedSurface(&ddSurfCaps, &m_lpDDBackSurface));
    
	//= Rückfläche aufräumen
    DDSURFACEDESC  ddsd;
    BYTE          *b;

    //= Zugriffs auf den Speicher der Oberfläche verschaffen
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    DDTRY(m_lpDDBackSurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL));

    //= Oberfläche mit NULL ausfüllen
    b = (BYTE *)ddsd.lpSurface;
    for (unsigned int j = 0; j < ddsd.dwHeight; j++, b += ddsd.lPitch)
      ZeroMemory(b, ddsd.lPitch);

    DDTRY(m_lpDDBackSurface->Unlock(NULL));
    }
  else
    {
    //= Für Fenstermodus
    DDTRY(m_lpDD->CreateClipper(0, &m_lpDDClipper, NULL));

    DDTRY(m_lpDDClipper->SetHWnd(0, pParentWnd->m_hWnd));

    DDTRY(m_lpDDPrimarySurface->SetClipper(m_lpDDClipper));
    }

  //= OnCreate aufrufen, um in der Ableitungsklasse 
  //= ev. die Initialisierung fortzusetzen 

  return OnCreate();
  }

void CDDMainObj::SizeChanged(int cx, int cy) 
  {
  if (m_lpDD != NULL && (m_szSize.cx != cx || m_szSize.cy != cy))
    {
    //= Zusätzliche Oberfläche neu anlegen    
    m_szSize.cx = cx;
    m_szSize.cy = cy;

    if (m_lpDDBackSurface != NULL)
      m_lpDDBackSurface->Release();

    DDSURFACEDESC ddSurfDesc;
    memset(&ddSurfDesc, 0, sizeof(DDSURFACEDESC));
    ddSurfDesc.dwSize = sizeof(DDSURFACEDESC);

    ddSurfDesc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddSurfDesc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddSurfDesc.dwWidth = m_szSize.cx;
    ddSurfDesc.dwHeight = m_szSize.cy;

    LPDIRECTDRAWSURFACE pDDSurf;
    if (!DDCHECK(m_lpDD->CreateSurface(&ddSurfDesc, &pDDSurf, NULL)))
      return;

    VERIFY(DDCHECK(pDDSurf->QueryInterface(IID_IDirectDrawSurface3, (void **)&m_lpDDBackSurface)));
    pDDSurf->Release();
    }
  }

bool CDDMainObj::SetPalette(PALETTEENTRY ape[256])
  {
  //= Neue Palette erzeugen
  if (m_lpDDPalette != NULL)
    m_lpDDPalette->Release();

  DDTRY(m_lpDD->CreatePalette(DDPCAPS_8BIT, ape, &m_lpDDPalette, NULL));

  //= Einträge in der Palette festlegen 
  return DDCHECK(m_lpDDPrimarySurface->SetPalette(m_lpDDPalette));
  }

bool CDDMainObj::SetPaletteEntry(int color, int r, int g, int b)
  {
  PALETTEENTRY ape;
  ape.peRed = r;
  ape.peGreen = g;
  ape.peBlue = b;
  ape.peFlags = 0;

  ASSERT(m_lpDDPalette != NULL);

  // set specified palette entry
  DDTRY(m_lpDDPalette->SetEntries(0, color, 1, &ape));
  return true;
  }

bool CDDMainObj::OnCreate()
  {
    //= Die Methode kann in die abgeleitete Klasse implementiert werden
	//== und den Erzeugen-Vorgang fortsetzen.

  return true;
  }

void CDDMainObj::Draw()
  {
  if (m_lpDD == NULL)
    return;

  LPDIRECTDRAWSURFACE3 pBackSurf = GetBackSurface();
  if (pBackSurf == NULL)
    return;

  DDSURFACEDESC        ddsd;
  BYTE                *b;

  ZeroMemory(&ddsd, sizeof(ddsd));
  ddsd.dwSize = sizeof(ddsd);
  if (DDCHECK(pBackSurf->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL)))
    {

    b = (BYTE *)ddsd.lpSurface;
    for (int j = 0; j < m_szSize.cy; j++, b += ddsd.lPitch)
      ZeroMemory(b, ddsd.lPitch);

    DDCHECK(pBackSurf->Unlock(NULL));
    }

  POSITION pos = m_SpriteList.GetHeadPosition();
  while (pos != NULL)
    {
    CDDSprite *pSprite = m_SpriteList.GetNext(pos);

    pSprite->Draw();
    }

  Flip();
  }

void CDDMainObj::Flip()
  {
  if (!m_bWindowed)
    {
    //= Vollbildschirm-Modus
    DDCHECK(m_lpDDPrimarySurface->Flip(NULL, DDFLIP_WAIT));
    }
  else
    {
    //= Fenstermodus
    DDBLTFX unused;
    memset(&unused, 0, sizeof(DDBLTFX));
    unused.dwSize = sizeof(DDBLTFX);

    if (m_pParent != NULL)
      {
      CRect rect(0, 0, 0, 0);
      CRect rectSrc(0, 0, m_szSize.cx, m_szSize.cy);

      m_pParent->GetClientRect(&rect);
      m_pParent->ClientToScreen(&rect);

      rect.right = rect.left + m_szSize.cx;
      rect.bottom = rect.top + m_szSize.cy;
      if (m_szSize.cx != 0 && m_szSize.cy != 0)
        VERIFY(DDCHECK(m_lpDDPrimarySurface->Blt(rect, m_lpDDBackSurface, rectSrc, DDBLT_WAIT, &unused)));
      }
    }
  }

void CDDMainObj::Loop()
  {
  bool res = false;

  //= Alle Sprites auf Änderungen checken
  POSITION pos = m_SpriteList.GetHeadPosition();
  while (pos != NULL)
    {
    CDDSprite *pSprite = m_SpriteList.GetNext(pos);

    if (pSprite->IsChanged())
      res = true;
    }

  //= Wenn ein Sprite sich geändert hat, alle Sprites neu zeichnen
  if (res)
    Draw();
  }

void CDDMainObj::AddSprite(CDDSprite *pSprite)
  {
  m_SpriteList.AddTail(pSprite);
  }

void CDDMainObj::MoveSpriteToEnd(CDDSprite *pSprite)
  {
  //= Position des Sprites in der Liste finden
  POSITION pos = m_SpriteList.Find(pSprite);

  //= Aus der Liste entfernen
  m_SpriteList.RemoveAt(pos);

  //= Am Ende der Liste hinzufügen
  m_SpriteList.AddTail(pSprite);
  }

bool CDDMainObj::GetDC(CDC &dc)
  {
  HDC hdc;
  if (DDCHECK(m_lpDDBackSurface->GetDC(&hdc)))
    {
    if (dc.Attach(hdc))
      {
      return true;
      }

    return false;
    }

  return false;
  }

void CDDMainObj::ReleaseDC(CDC &dc)
  {
  HDC hdc = dc.m_hDC;

  dc.Detach();
  m_lpDDBackSurface->ReleaseDC(hdc);
  }

LPDIRECTDRAWSURFACE3 CDDMainObj::GetBackSurface()
  {
  return m_lpDDBackSurface;
  }

bool CDDMainObj::DDCheckHRESULT(HRESULT hr, int line, char *file)
  {
  if (hr == DD_OK)
    return true;
  
  CString strErr;    
  switch (hr)
    {
    case DDERR_ALREADYINITIALIZED:
      strErr = CString("The object has already been initialized. ");
      break;

    case DDERR_BLTFASTCANTCLIP:
      strErr = CString("A DirectDrawClipper object is attached to a source surface that has passed into a call to the IDirectDrawSurface2::BltFast method. ");
      break;

    case DDERR_CANNOTATTACHSURFACE:
      strErr = CString("A surface cannot be attached to another requested surface. ");
      break;

    case DDERR_CANNOTDETACHSURFACE: 
      strErr = CString("A surface cannot be detached from another requested surface. ");
      break;

    case DDERR_CANTCREATEDC:
      strErr = CString("Windows cannot create any more device contexts (DCs). ");
      break;

    case DDERR_CANTDUPLICATE:
      strErr = CString("Primary and 3D surfaces, or surfaces that are implicitly created, cannot be duplicated. ");
      break;

    case DDERR_CANTLOCKSURFACE: 
      strErr = CString("Access to this surface is refused because an attempt was made to lock the primary surface without DCI support. ");
      break;

    case DDERR_CANTPAGELOCK:
      strErr = CString("An attempt to page lock a surface failed. Page lock will not work on a display-memory surface or an emulated primary surface. ");
      break;

    case DDERR_CANTPAGEUNLOCK:
      strErr = CString("An attempt to page unlock a surface failed. Page unlock will not work on a display-memory surface or an emulated primary surface. ");
      break;

    case DDERR_CLIPPERISUSINGHWND:
      strErr = CString("An attempt was made to set a clip list for a DirectDrawClipper object that is already monitoring a window handle. ");
      break;

    case DDERR_COLORKEYNOTSET:
      strErr = CString("No source color key is specified for this operation. ");
      break;

    case DDERR_CURRENTLYNOTAVAIL:
      strErr = CString("No support is currently available. ");
      break;

    case DDERR_DCALREADYCREATED:
      strErr = CString("A device context (DC) has already been returned for this surface. Only one DC can be retrieved for each surface. ");
      break;

    case DDERR_DIRECTDRAWALREADYCREATED:
      strErr = CString("A DirectDraw object representing this driver has already been created for this process. ");
      break;

    case DDERR_EXCEPTION:
      strErr = CString("An exception was encountered while performing the requested operation. ");
      break;

    case DDERR_EXCLUSIVEMODEALREADYSET:
      strErr = CString("An attempt was made to set the cooperative level when it was already set to exclusive. ");
      break;

    case DDERR_GENERIC:
      strErr = CString("There is an undefined error condition. ");
      break;

    case DDERR_HEIGHTALIGN:
      strErr = CString("The height of the provided rectangle is not a multiple of the required alignment. ");
      break;

    case DDERR_HWNDALREADYSET:
      strErr = CString("The DirectDraw cooperative level window handle has already been set. It cannot be reset while the process has surfaces or palettes created. ");
      break;

    case DDERR_HWNDSUBCLASSED:
      strErr = CString("DirectDraw is prevented from restoring state because the DirectDraw cooperative level window handle has been subclassed. ");
      break;

    case DDERR_IMPLICITLYCREATED:
      strErr = CString("The surface cannot be restored because it is an implicitly created surface. ");
      break;

    case DDERR_INCOMPATIBLEPRIMARY:
      strErr = CString("The primary surface creation request does not match with the existing primary surface. ");
      break;

    case DDERR_INVALIDCAPS:
      strErr = CString("One or more of the capability bits passed to the callback function are incorrect. ");
      break;

    case DDERR_INVALIDCLIPLIST:
      strErr = CString("DirectDraw does not support the provided clip list. ");
      break;

    case DDERR_INVALIDDIRECTDRAWGUID:
      strErr = CString("The globally unique identifier (GUID) passed to the DirectDrawCreate function is not a valid DirectDraw driver identifier. ");
      break;

    case DDERR_INVALIDMODE:
      strErr = CString("DirectDraw does not support the requested mode. ");
      break;

    case DDERR_INVALIDOBJECT:
      strErr = CString("DirectDraw received a pointer that was an invalid DirectDraw object. ");
      break;

    case DDERR_INVALIDPARAMS:
      strErr = CString("One or more of the parameters passed to the method are incorrect. ");
      break;

    case DDERR_INVALIDPIXELFORMAT:
      strErr = CString("The pixel format was invalid as specified. ");
      break;

    case DDERR_INVALIDPOSITION:
      strErr = CString("The position of the overlay on the destination is no longer legal. ");
      break;

    case DDERR_INVALIDRECT:
      strErr = CString("The provided rectangle was invalid. ");
      break;

    case DDERR_INVALIDSURFACETYPE:
      strErr = CString("The requested operation could not be performed because the surface was of the wrong type. ");
      break;

    case DDERR_LOCKEDSURFACES:
      strErr = CString("One or more surfaces are locked, causing the failure of the requested operation. ");
      break;

    case DDERR_NO3D:
      strErr = CString("No 3D hardware or emulation is present. ");
      break;

    case DDERR_NOALPHAHW:
      strErr = CString("No alpha acceleration hardware is present or available, causing the failure of the requested operation. ");
      break;

    case DDERR_NOBLTHW:
      strErr = CString("No blitter hardware is present. ");
      break;

    case DDERR_NOCLIPLIST:
      strErr = CString("No clip list is available. ");
      break;

    case DDERR_NOCLIPPERATTACHED:
      strErr = CString("No DirectDrawClipper object is attached to the surface object. ");
      break;

    case DDERR_NOCOLORCONVHW:
      strErr = CString("The operation cannot be carried out because no color-conversion hardware is present or available. ");
      break;

    case DDERR_NOCOLORKEY:
      strErr = CString("The surface does not currently have a color key. ");
      break;

    case DDERR_NOCOLORKEYHW:
      strErr = CString("The operation cannot be carried out because there is no hardware support for the destination color key. ");
      break;

    case DDERR_NOCOOPERATIVELEVELSET:
      strErr = CString("A create function is called without the IDirectDraw2::SetCooperativeLevel method being called. ");
      break;

    case DDERR_NODC:
      strErr = CString("No DC has ever been created for this surface. ");
      break;

    case DDERR_NODDROPSHW:
      strErr = CString("No DirectDraw raster operation (ROP) hardware is available. ");
      break;

    case DDERR_NODIRECTDRAWHW:
      strErr = CString("Hardware-only DirectDraw object creation is not possible; the driver does not support any hardware. ");
      break;

    case DDERR_NODIRECTDRAWSUPPORT:
      strErr = CString("DirectDraw support is not possible with the current display driver. ");
      break;

    case DDERR_NOEMULATION:
      strErr = CString("Software emulation is not available. ");
      break;

    case DDERR_NOEXCLUSIVEMODE:
      strErr = CString("The operation requires the application to have exclusive mode, but the application does not have exclusive mode. ");
      break;

    case DDERR_NOFLIPHW:
      strErr = CString("Flipping visible surfaces is not supported. ");
      break;

    case DDERR_NOGDI:
      strErr = CString("No GDI is present. ");
      break;

    case DDERR_NOHWND:
      strErr = CString("Clipper notification requires a window handle, or no window handle has been previously set as the cooperative level window handle. ");
      break;

    case DDERR_NOMIPMAPHW:
      strErr = CString("The operation cannot be carried out because no mipmap texture mapping hardware is present or available. ");
      break;

    case DDERR_NOMIRRORHW:
      strErr = CString("The operation cannot be carried out because no mirroring hardware is present or available. ");
      break;

    case DDERR_NOOVERLAYDEST:
      strErr = CString("The IDirectDrawSurface2::GetOverlayPosition method is called on an overlay that the IDirectDrawSurface2::UpdateOverlay method has not been called on to establish a destination. ");
      break;

    case DDERR_NOOVERLAYHW:
      strErr = CString("The operation cannot be carried out because no overlay hardware is present or available. ");
      break;

    case DDERR_NOPALETTEATTACHED:
      strErr = CString("No palette object is attached to this surface. ");
      break;

    case DDERR_NOPALETTEHW:
      strErr = CString("There is no hardware support for 16- or 256-color palettes. ");
      break;

    case DDERR_NORASTEROPHW:
      strErr = CString("The operation cannot be carried out because no appropriate raster operation hardware is present or available. ");
      break;

    case DDERR_NOROTATIONHW:
      strErr = CString("The operation cannot be carried out because no rotation hardware is present or available. ");
      break;

    case DDERR_NOSTRETCHHW:
      strErr = CString("The operation cannot be carried out because there is no hardware support for stretching. ");
      break;

    case DDERR_NOT4BITCOLOR:
      strErr = CString("The DirectDrawSurface object is not using a 4-bit color palette and the requested operation requires a 4-bit color palette. ");
      break;

    case DDERR_NOT4BITCOLORINDEX:
      strErr = CString("The DirectDrawSurface object is not using a 4-bit color index palette and the requested operation requires a 4-bit color index palette. ");
      break;

    case DDERR_NOT8BITCOLOR:
      strErr = CString("The DirectDrawSurface object is not using an 8-bit color palette and the requested operation requires an 8-bit color palette. ");
      break;

    case DDERR_NOTAOVERLAYSURFACE:
      strErr = CString("An overlay component is called for a non-overlay surface. ");
      break;

    case DDERR_NOTEXTUREHW:
      strErr = CString("The operation cannot be carried out because no texture-mapping hardware is present or available. ");
      break;

    case DDERR_NOTFLIPPABLE:
      strErr = CString("An attempt has been made to flip a surface that cannot be flipped. ");
      break;

    case DDERR_NOTFOUND:
      strErr = CString("The requested item was not found. ");
      break;

    case DDERR_NOTINITIALIZED:
      strErr = CString("An attempt was made to call an interface method of a DirectDraw object created by CoCreateInstance before the object was initialized. ");
      break;

    case DDERR_NOTLOCKED:
      strErr = CString("An attempt is made to unlock a surface that was not locked. ");
      break;

    case DDERR_NOTPAGELOCKED:
      strErr = CString("An attempt is made to page unlock a surface with no outstanding page locks. ");
      break;

    case DDERR_NOTPALETTIZED:
      strErr = CString("The surface being used is not a palette-based surface. ");
      break;

    case DDERR_NOVSYNCHW:
      strErr = CString("The operation cannot be carried out because there is no hardware support for vertical blank synchronized operations. ");
      break;

    case DDERR_NOZBUFFERHW:
      strErr = CString("The operation to create a z-buffer in display memory or to perform a blit using a z-buffer cannot be carried out because there is no hardware support for z-buffers. ");
      break;

    case DDERR_NOZOVERLAYHW:
      strErr = CString("The overlay surfaces cannot be z-layered based on the z-order because the hardware does not support z-ordering of overlays. ");
      break;

    case DDERR_OUTOFCAPS:
      strErr = CString("The hardware needed for the requested operation has already been allocated. ");
      break;

    case DDERR_OUTOFMEMORY:
      strErr = CString("DirectDraw does not have enough memory to perform the operation. ");
      break;

    case DDERR_OUTOFVIDEOMEMORY:
      strErr = CString("DirectDraw does not have enough display memory to perform the operation. ");
      break;

    case DDERR_OVERLAYCANTCLIP:
      strErr = CString("The hardware does not support clipped overlays. ");
      break;

    case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
      strErr = CString("An attempt was made to have more than one color key active on an overlay. ");
      break;

    case DDERR_OVERLAYNOTVISIBLE:
      strErr = CString("The IDirectDrawSurface2::GetOverlayPosition method is called on a hidden overlay. ");
      break;

    case DDERR_PALETTEBUSY:
      strErr = CString("Access to this palette is refused because the palette is locked by another thread. ");
      break;

    case DDERR_PRIMARYSURFACEALREADYEXISTS:
      strErr = CString("This process has already created a primary surface. ");
      break;

    case DDERR_REGIONTOOSMALL:
      strErr = CString("The region passed to the IDirectDrawClipper::GetClipList method is too small. ");
      break;

    case DDERR_SURFACEALREADYATTACHED:
      strErr = CString("An attempt was made to attach a surface to another surface to which it is already attached. ");
      break;

    case DDERR_SURFACEALREADYDEPENDENT:
      strErr = CString("An attempt was made to make a surface a dependency of another surface to which it is already dependent. ");
      break;

    case DDERR_SURFACEBUSY:
      strErr = CString("Access to the surface is refused because the surface is locked by another thread. ");
      break;

    case DDERR_SURFACEISOBSCURED:
      strErr = CString("Access to the surface is refused because the surface is obscured. ");
      break;

    case DDERR_SURFACELOST:
      strErr = CString("Access to the surface is refused because the surface memory is gone. The DirectDrawSurface object representing this surface should have the IDirectDrawSurface2::Restore method called on it. ");
      break;

    case DDERR_SURFACENOTATTACHED:
      strErr = CString("The requested surface is not attached. ");
      break;

    case DDERR_TOOBIGHEIGHT:
      strErr = CString("The height requested by DirectDraw is too large. ");
      break;

    case DDERR_TOOBIGSIZE:
      strErr = CString("The size requested by DirectDraw is too large. However, the individual height and width are OK. ");
      break;

    case DDERR_TOOBIGWIDTH:
      strErr = CString("The width requested by DirectDraw is too large. ");
      break;

    case DDERR_UNSUPPORTED:
      strErr = CString("The operation is not supported. ");
      break;

    case DDERR_UNSUPPORTEDFORMAT:
      strErr = CString("The FourCC format requested is not supported by DirectDraw. ");
      break;

    case DDERR_UNSUPPORTEDMASK:
      strErr = CString("The bitmask in the pixel format requested is not supported by DirectDraw. ");
      break;

    case DDERR_UNSUPPORTEDMODE:
      strErr = CString("The display is currently in an unsupported mode. ");
      break;

    case DDERR_VERTICALBLANKINPROGRESS:
      strErr = CString("A vertical blank is in progress. ");
      break;

    case DDERR_WASSTILLDRAWING:
      strErr = CString("The previous blit operation that is transferring information to or from this surface is incomplete. ");
      break;

    case DDERR_WRONGMODE:
      strErr = CString("This surface cannot be restored because it was created in a different mode. ");
      break;

    case DDERR_XALIGN:
      strErr = CString("The provided rectangle was not horizontally aligned on a required boundary.");
      break;

    default:
      strErr = CString("UNKNOWN. ");
      break;
    }

  DDError(strErr, hr, line, file);  
  return false;    
  }

void CDDMainObj::DDError(const CString& strErr, HRESULT hr, int line, char *file)
  {
  CString str = strErr;
  
  if (hr != DD_OK)
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
  
  TRACE1("Fehhler in DirectDraw: %s\n", str);
  ::MessageBox(NULL, str, "Fehhler in DirectDraw", MB_OK);
  }
  
