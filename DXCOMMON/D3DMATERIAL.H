#ifndef _D3DMATERIAL_H_
#define _D3DMATERIAL_H_

#include "d3drmwin.h"
#include "d3dFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CD3DMaterial class

class CD3DMainObj;
class CD3DFrame;
class CD3DMaterial : public CObject
  {
  DECLARE_DYNAMIC(CD3DMaterial)

  // Construction
  public:
    CD3DMaterial();
    
    // Attributes
  public:
    
    // Operations
  public:
    virtual bool SetAppData(DWORD appdata); 
    virtual DWORD GetAppData(void); 
    virtual bool Create(CD3DMainObj *pOwner, 
                                D3DVALUE rvspRed = D3DVAL(1), 
                                D3DVALUE rvspGreen = D3DVAL(1), 
                                D3DVALUE rvspBlue = D3DVAL(1),
                                D3DVALUE rvspPower = D3DVAL(60),
                                D3DVALUE rvemRed = D3DVAL(0), 
                                D3DVALUE rvemGreen = D3DVAL(0), 
                                D3DVALUE rvemBlue = D3DVAL(0));
    virtual bool SetEmissive(D3DVALUE rvemRed = D3DVAL(0), 
                                D3DVALUE rvemGreen = D3DVAL(0), 
                                D3DVALUE rvemBlue = D3DVAL(0));
    virtual bool GetEmissive(D3DVALUE *rvemRed, D3DVALUE *rvemGreen, 
                                D3DVALUE *rvemBlue);
    virtual bool SetSpecular(D3DVALUE rvspRed = D3DVAL(1), 
                                D3DVALUE rvspGreen = D3DVAL(1), 
                                D3DVALUE rvspBlue = D3DVAL(1),
                                D3DVALUE rvspPower = D3DVAL(60));
    virtual bool GetSpecular(D3DVALUE *rvspRed, D3DVALUE *rvspGreen, 
                                D3DVALUE *rvspBlue, D3DVALUE *rvspPower);
    virtual bool SetAmbient(D3DVALUE rvamRed = D3DVAL(0.5), 
                                D3DVALUE rvamGreen = D3DVAL(0.5), 
                                D3DVALUE rvamBlue = D3DVAL(0.5));
    virtual bool GetAmbient(D3DVALUE *rvamRed, D3DVALUE *rvamGreen, 
                                D3DVALUE *rvamBlue);

    // Implementation
  public:
    virtual ~CD3DMaterial();

    friend CD3DMainObj;
  protected:
    bool IsChanged(void);

    friend CD3DFrame;
  protected:
    LPDIRECT3DRMMATERIAL2 m_lpMaterial; //= Zeiger auf der Schnittstelle IDirect3DRMMaterial

    bool m_bChanged;                    //= true wenn geändert

    CD3DMainObj *m_pOwner;              //= Hauptobjekt
  };

/////////////////////////////////////////////////////////////////////////////

#endif
