#ifndef _D3DFRAME_H_
#define _D3DFRAME_H_

#include "d3drmwin.h"

/////////////////////////////////////////////////////////////////////////////
// CD3DFrame class

class CD3DMaterial;
class CD3DTexture;
class CD3DAnimation;
class CD3DMainObj;
class CD3DLightFrame;
class CD3DFrame : public CObject
  {
	DECLARE_DYNAMIC(CD3DFrame)   

  // Construction
  public:
    CD3DFrame();
    
    // Attributes
  public:
    static double PI;
    
    // Operations
  public:
    virtual bool SetAppData(DWORD appdata); 
    virtual DWORD GetAppData(void); 
    virtual DWORD GetChildNumber(void);
    virtual CD3DFrame *GetChildFrame(DWORD AppData);
    virtual bool Create(CD3DMainObj *pOwner);
    virtual bool AddToFrame(CD3DFrame *pParent);
    virtual bool AddFrame(CD3DFrame *frame);
    virtual bool AddDecalVisual(CD3DTexture *tex);
    virtual bool RemoveFromFrame(void);
    virtual bool SetColor(D3DCOLOR color, bool hierarchy = true);
    virtual bool SetMaterial(CD3DMaterial *mat, bool hierarchy = true);
    virtual bool AddScale(D3DRMCOMBINETYPE rctCombine,
	                        D3DVALUE rvX,	D3DVALUE rvY,	D3DVALUE rvZ);
    virtual bool AddTranslation(D3DRMCOMBINETYPE rctCombine,
	                        D3DVALUE rvX,	D3DVALUE rvY,	D3DVALUE rvZ);
    virtual bool AddRotation(D3DRMCOMBINETYPE rctCombine,
	                        D3DVALUE rvX,	D3DVALUE rvY,	D3DVALUE rvZ, D3DVALUE rvTheta);
    virtual bool SetPosition(CD3DFrame *lpRef, D3DVALUE rvX,	D3DVALUE rvY,	D3DVALUE rvZ);
    virtual bool SetRotation(CD3DFrame *lpRef, D3DVALUE rvX,	D3DVALUE rvY,	D3DVALUE rvZ,
                          D3DVALUE rvTheta);
    virtual bool SetVelocity(CD3DFrame *lpRef, D3DVALUE rvX,	D3DVALUE rvY,	D3DVALUE rvZ,
                          bool frotvel = false);
    virtual bool SetMoveCallback(bool set = true, bool before = true);
    virtual void ObjCallback(D3DVALUE delta) {};

    virtual bool AddCombTransform(D3DVALUE rvsX,	D3DVALUE rvsY,	D3DVALUE rvsZ,
                          D3DVALUE rvThetaX, D3DVALUE rvThetaY, D3DVALUE rvThetaZ,
	                        D3DVALUE rvX,	D3DVALUE rvY,	D3DVALUE rvZ);
    virtual bool AddShadow(CD3DLightFrame *who_cast,
                  D3DVALUE rvsX, D3DVALUE rvsY, D3DVALUE rvsZ,
                  D3DVALUE rvX, D3DVALUE rvY, D3DVALUE rvZ);
    virtual bool TransformToWorld(D3DVALUE rvFX, D3DVALUE rvFY, D3DVALUE rvFZ,
                  D3DVALUE *rvWX, D3DVALUE *rvWY, D3DVALUE *rvWZ);
    virtual CD3DFrame *GetFirstChild(void);
    virtual CD3DFrame *GetNextChild(void);

    virtual bool ApplyFlatWrap(CD3DTexture *tex,
		            D3DVALUE ox = D3DVAL(0),	D3DVALUE oy = D3DVAL(0),	D3DVALUE oz = D3DVAL(0),
		            D3DVALUE dx = D3DVAL(0),	D3DVALUE dy = D3DVAL(0),	D3DVALUE dz = D3DVAL(1),
		            D3DVALUE ux = D3DVAL(0),	D3DVALUE uy = D3DVAL(1),	D3DVALUE uz = D3DVAL(0),
		            D3DVALUE ou = D3DVAL(0),	D3DVALUE ov = D3DVAL(0),  
                D3DVALUE su = D3DVAL(1),	D3DVALUE sv = D3DVAL(1));
    virtual bool ApplyCylinderWrap(CD3DTexture *tex,
		            D3DVALUE ox = D3DVAL(0),	D3DVALUE oy = D3DVAL(0),	D3DVALUE oz = D3DVAL(0),
		            D3DVALUE dx = D3DVAL(0),	D3DVALUE dy = D3DVAL(0),	D3DVALUE dz = D3DVAL(1),
		            D3DVALUE ux = D3DVAL(0),	D3DVALUE uy = D3DVAL(1),	D3DVALUE uz = D3DVAL(0),
		            D3DVALUE ou = D3DVAL(0),	D3DVALUE ov = D3DVAL(0),  
                D3DVALUE su = D3DVAL(1),	D3DVALUE sv = D3DVAL(1));
    virtual bool ApplySphereWrap(CD3DTexture *tex,
		            D3DVALUE ox = D3DVAL(0),	D3DVALUE oy = D3DVAL(0),	D3DVALUE oz = D3DVAL(0),
		            D3DVALUE dx = D3DVAL(0),	D3DVALUE dy = D3DVAL(0),	D3DVALUE dz = D3DVAL(1),
		            D3DVALUE ux = D3DVAL(0),	D3DVALUE uy = D3DVAL(1),	D3DVALUE uz = D3DVAL(0),
		            D3DVALUE ou = D3DVAL(0),	D3DVALUE ov = D3DVAL(0),  
                D3DVALUE su = D3DVAL(1),	D3DVALUE sv = D3DVAL(1));
    virtual bool ApplyChromeWrap(CD3DTexture *tex, CD3DFrame *lpRef, CD3DFrame *lpObj,
		            D3DVALUE ox = D3DVAL(0),	D3DVALUE oy = D3DVAL(0),	D3DVALUE oz = D3DVAL(0),
		            D3DVALUE dx = D3DVAL(0),	D3DVALUE dy = D3DVAL(0),	D3DVALUE dz = D3DVAL(-1),
		            D3DVALUE ux = D3DVAL(0),	D3DVALUE uy = D3DVAL(1),	D3DVALUE uz = D3DVAL(0),
		            D3DVALUE ou = D3DVAL(0),	D3DVALUE ov = D3DVAL(0),  
                D3DVALUE su = D3DVAL(1),	D3DVALUE sv = D3DVAL(-1));
    virtual bool CreateChromeWrap(D3DVALUE ox = D3DVAL(0),	D3DVALUE oy = D3DVAL(0),	D3DVALUE oz = D3DVAL(0),
		            D3DVALUE dx = D3DVAL(0),	D3DVALUE dy = D3DVAL(0),	D3DVALUE dz = D3DVAL(-1),
		            D3DVALUE ux = D3DVAL(0),	D3DVALUE uy = D3DVAL(1),	D3DVALUE uz = D3DVAL(0),
		            D3DVALUE ou = D3DVAL(0),	D3DVALUE ov = D3DVAL(0),  
                D3DVALUE su = D3DVAL(1),	D3DVALUE sv = D3DVAL(-1));
    virtual bool ApplyChrome(CD3DTexture *tex, CD3DFrame *lpRef, CD3DFrame *lpObj);
    // Implementation
  public:
    virtual ~CD3DFrame();

  friend CD3DMainObj;
  protected:
    bool IsChanged(void);
    LPDIRECT3DRMFRAME3 GetFrame(void){return m_lpFrame;}
    bool AddFaces(DWORD dwVertexCount, D3DVECTOR * lpD3DVertices,
                  DWORD normalCount, D3DVECTOR *lpNormals, DWORD *lpFaceData,
                  LPDIRECT3DRMFACEARRAY* lplpD3DRMFaceArray = NULL);
    void AddChildFrame(CD3DFrame *pChild);
    void RemoveChildFrame(CD3DFrame *pChild);
    static void NormalFromFace(D3DVECTOR *vert_in1, D3DVECTOR *vert_in2, D3DVECTOR *vert_in3,
                               D3DVECTOR *norm_out);
    
  friend CD3DAnimation;
  protected:
    LPDIRECT3DRMMESHBUILDER3 m_lpMesh;     //= Netzgeometrie
    LPDIRECT3DRMFRAME3       m_lpFrame;    //= Wurzelframe 
    LPDIRECT3DRMWRAP         m_lpWrap;     //= wrap interface if this frame 
                                           //= is used as reference frame
    bool m_bChanged;

    CD3DMainObj *m_pOwner;
    CD3DFrame   *m_pParent;
    POSITION     m_POSITION;
    
    CTypedPtrList<CPtrList, CD3DFrame *> m_ChildFrameList;
  };

/////////////////////////////////////////////////////////////////////////////

#endif
