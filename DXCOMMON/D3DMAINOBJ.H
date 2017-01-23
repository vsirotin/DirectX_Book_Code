#ifndef _D3DMAINOBJ_H_
#define _D3DMAINOBJ_H_

#include "d3drmwin.h"

/////////////////////////////////////////////////////////////////////////////
// Macros

#define D3DCHECK(func)  CD3DMainObj::D3DCheckHRESULT(func, __LINE__, __FILE__)
#define D3DTRY(func)    if (!D3DCHECK(func)) return false
#define D3DFREE(obj)    if (obj != NULL) {obj->Release(); obj = NULL;}

/////////////////////////////////////////////////////////////////////////////
// CD3DMainObj class

#include "d3dFrame.h"

class CD3DCameraFrame;
class CD3DLightFrame;
class CD3DMaterial;
class CD3DTexture;
class CD3DAnimation;
class CD3DFrameExplorerCamera;
class CD3DFrameExplorerMainObjRendering;
class CD3DMainObj : public CD3DFrame
  {
	DECLARE_DYNAMIC(CD3DMainObj) 
  // Construction
  public:
    CD3DMainObj();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool Create(CWnd* pParent);
    virtual bool IsOK(void) {return (m_lpD3DRM != NULL && m_lpDev != NULL && m_lpView != NULL);}
    virtual bool Loop(bool bForced = false);
    virtual void Paint(CDC *dc);
    virtual void Activate(BOOL bActivate);
    virtual void SizeChanged(int cx, int cy);

    //= Kamera-Operationen
    CD3DCameraFrame *GetCameraFrame(void){return m_lpCameraFrame;}
    bool SetCameraFront(D3DVALUE fFront);
    bool SetCameraBack(D3DVALUE fBack);
    bool SetCameraField(D3DVALUE fField);
    bool SetCameraPlane(D3DVALUE fLeft, D3DVALUE fRight, D3DVALUE fBottom, D3DVALUE fTop);
    
    bool SetCameraParam(double Field = 1.0, 
                        double Front = 1.0, double Back = 1500.0, 
                        D3DCOLOR BkgColor = RGB(64, 255, 255), 
                        D3DCOLOR AmbColor = RGB(170, 170, 170),
                        D3DRMRENDERQUALITY rqQuality = D3DRMLIGHT_ON | 
                                   D3DRMFILL_SOLID | D3DRMSHADE_GOURAUD,
                        D3DRMPROJECTIONTYPE rptType = D3DRMPROJECT_PERSPECTIVE);
    //= Operationen mit der Szene 
    bool SetSceneBackground(D3DCOLOR color);
    D3DCOLOR GetSceneBackground(void);
    bool SetSceneBackgroundRGB(D3DVALUE red, D3DVALUE green, D3DVALUE blue);
    bool SetAmbientLight(D3DCOLOR color);
    bool SetAmbientLightRGB(D3DVALUE red, D3DVALUE green, D3DVALUE blue);
    D3DCOLOR GetAmbientLight(void);
    bool GetAmbientLightRGB(D3DVALUE *red, D3DVALUE *green, D3DVALUE *blue);
    bool GetFogEnable(void);
    D3DCOLOR GetFogColor(void);
    bool GetFogParams(D3DVALUE *rvStart, D3DVALUE *rvEnd);
    bool SetFogEnable(bool Flag);
    bool SetFogColor(D3DCOLOR color);
    bool SetFogParams(D3DVALUE rvStart, D3DVALUE rvEnd);
    bool SetImageFile(LPCSTR FileName);

    bool SetTickEnable(bool enable);
    bool GetPick(int iX, int iY, int *count, CD3DFrame ***FrameArray);

    //= Rendering-Operationen
    bool SetRenderQuality(D3DRMRENDERQUALITY rqQuality);

    bool SetProjection(D3DRMPROJECTIONTYPE rptType);
    
    //= Fehlerbearbeitung
    static  void D3DError(const CString &str, HRESULT hr = 0, int line = -1, char *file = NULL);
    static  bool D3DCheckHRESULT(HRESULT res, int line = -1, char *file = NULL);
    
    // Implementation
  public:
    virtual ~CD3DMainObj();
    
  protected: 
    virtual bool EnumDrivers(void);
    virtual bool CreateDevAndView(int width, int height);
  
    virtual bool       OnCreate(void){return true;}
    LPDIRECT3DRM3      GetMainObject(void){return m_lpD3DRM;}
    void               AddSlave(CD3DFrame *pSlave);
    void               RemoveSlave(CD3DFrame *pSlave);
    virtual bool       IsMatChanged(void);
    void               AddMaterial(CD3DMaterial *pSlave);
    void               RemoveMaterial(CD3DMaterial *pSlave);
    virtual bool       IsTexChanged(void);
    void               AddTexture(CD3DTexture *pSlave);
    void               RemoveTexture(CD3DTexture *pSlave);
    void               AddAnimation(CD3DAnimation *pSlave);
    void               RemoveAnimation(CD3DAnimation *pSlave);

    //= Freund-Funktionen
    friend HRESULT WINAPI enumDeviceFunc(LPGUID lpGuid, LPSTR lpDeviceDescription, 
                                         LPSTR lpDeviceName, LPD3DDEVICEDESC lpHWDesc, 
                                         LPD3DDEVICEDESC lpHELDesc, LPVOID lpContext);
    //= Freund-Klassen
    friend CD3DFrame;
    friend CD3DLightFrame;
    friend CD3DMaterial;
    friend CD3DTexture;
    friend CD3DAnimation;
    friend CD3DFrameExplorerCamera;
    friend CD3DFrameExplorerMainObjRendering;

  protected:
    GUID m_DriverGUID;     //= GUIDs der Treiber 
    char m_DriverName[50]; //= Namen der Treiber 
    int  m_iDriverCaps;    
    
    LPDIRECT3DRM3          m_lpD3DRM;          //= Direct3DRM-Objekt
    LPDIRECTDRAWCLIPPER    m_lpDDClipper;      //= DirectDrawClipper-Objekt
    
    LPDIRECT3DRMDEVICE3    m_lpDev;      //= Direct3DRM-Gerät 
    LPDIRECT3DRMVIEWPORT2  m_lpView;     //= Direct3DRM-Viewport 

    LPDIRECT3DRMLIGHT      m_lpAmbientLight;  //= Umgebungslicht
    CD3DCameraFrame       *m_lpCameraFrame;   //= Frame (POV )

    int  m_BPP;                   //= Farbtiefe des aktuellen Bildschirmmodusses

    //= Liste der Frames
    CTypedPtrList<CPtrList, CD3DFrame *> m_SlaveList;
    //= Liste der Materials
    CTypedPtrList<CPtrList, CD3DMaterial *> m_MaterialList;
    //= Texturliste
    CTypedPtrList<CPtrList, CD3DTexture *> m_TextureList;
    //= Liste der Animationen
    CTypedPtrList<CPtrList, CD3DAnimation *> m_AnimationList;

    //= Kamera-Parameter
    bool  m_bFromField;      //= Typ der Kamera-Fläche
    D3DVALUE m_fCameraFront, m_fCameraBack, m_fCameraField;
    D3DVALUE m_fCameraLeft, m_fCameraRight, m_fCameraBottom, m_fCameraTop;

    //= Rendering-Qualität
    D3DRMRENDERQUALITY  m_rqQuality;

    D3DRMPROJECTIONTYPE m_ptType;
    
    //= Farbe des Umgebungslichts
    D3DVALUE m_fAmbientLightRed;
    D3DVALUE m_fAmbientLightGreen;
    D3DVALUE m_fAmbientLightBlue;

    //= Hintergrundimage oder Hintergrundfarbe?
    bool m_bFromImage;

    //= Sind Ticks sind erlaubt?
    bool m_bTickEnable;

    //= Feld mit "picked" Frames
    CD3DFrame **m_lplpFrame;
  };

/////////////////////////////////////////////////////////////////////////////

#endif
