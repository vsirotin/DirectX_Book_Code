#ifndef _D3DCOSMOSOBJ_H_
#define _D3DCOSMOSOBJ_H_

#include "d3dMainObj.h"

/////////////////////////////////////////////////////////////////////////////
// CD3DCosmosObj class

class CD3DSpotLight;
class CD3DPointLight;
class CD3DCosmosObj : public CD3DMainObj
  {
  // Construction
  public:
    CD3DCosmosObj();
    
    // Attributes
  public:
    
    // Operations
  public:
    
    void ObjCallback(D3DVALUE delta); //= adjusting of a scene because
                                      //=   of scene heartbeet

    // Implementation
  public:
    virtual ~CD3DCosmosObj();
    bool     SunObject(void);
    bool     CreateMars(void);
    bool     CreateEarth(void);
    bool     CreateRock(void);
    CD3DFrame *CreateSphere(int vert_planes = 16, int hor_planes = 15);
    CD3DFrame *CreateRocket(bool passive = true);
    bool     CreateSLight(void);
    bool     CreateUFOs(void);
    bool     BumpedTerrain(int n_cells, double xBeg, double xEnd,
                                        double zBeg, double zEnd, 
                                        double yBase, double BumpAmp);
    
  protected: 
    bool OnCreate(void);

    D3DVALUE       m_vTime;       //= current scene time
    CD3DAnimation *m_pAnimSun;    //= animation of Sun Decal
    CD3DAnimation *m_pAnimRocket; //= animation of a rocket
    CD3DFrame     *m_pSpace;      //= main frame of scene
    CD3DFrame     *m_pRocket;     //= frame of a rocket
    CD3DFrame     *m_pTerra;      //= random surface of flying landscape
    CD3DSpotLight *m_pSpotL;      //= main light source casting light for shadows
    CD3DAnimation *m_pAnim1;      //= animation of fisrt fire stuff
    CD3DAnimation *m_pAnim2;      //= animation of second fire stuff
    CD3DAnimation *m_pAnim3;      //= animation of third fire stuff
    D3DVECTOR     *sph;           //= working area of CreateSphere()
  };

/////////////////////////////////////////////////////////////////////////////

#endif
