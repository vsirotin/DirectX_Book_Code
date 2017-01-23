#ifndef _D3DGEOMARSENAL_H_
#define _D3DGEOMARSENAL_H_

#include "d3dFrame.h"
#include "d3dDecalFrame.h"
#include "d3dCameraFrame.h"
#include "d3dPolygonFrame.h"
#include "d3dPyramidFrame.h"
#include "d3dCubeFrame.h"
#include "d3dHalfsphereFrame.h"
#include "d3dDiskFrame.h"
#include "d3dCylinderFrame.h"
#include "d3dConeFrame.h"
#include "d3dFaceFrame.h"
#include "d3dSweepingFrame.h"
#include "d3dRevolveFrame.h"
#include "d3dRevolveSmoothFrame.h"
//= Lichtquellen
#include "d3dDirectionalLight.h"
#include "d3dParallelPointLight.h"
#include "d3dPointLight.h"
#include "d3dMaterial.h"
#include "d3dTexture.h"
#include "d3dAnimation.h"
#include "d3dSpotLight.h"

////////////////////////////////////////////////////////////////////////////
// CD3DGeomArsenal class

class CD3DMainObj;
class CD3DGeomArsenal
  {
  // Construction
  public:
    CD3DGeomArsenal(){};
    
  // Operations
  public:
    static CD3DFrame *CreateHouse(CD3DMainObj *pOwner);
    static CD3DFrame *CreateMushroom(CD3DMainObj *pOwner,
                              int vert_planes = 8, int hor_planes = 3);
    static CD3DFrame *CreateTree(CD3DMainObj *pOwner,
                              int vert_planes = 8, int hor_planes = 3);
    static CD3DFrame *CreateRadar(CD3DMainObj *pOwner,
                              int vert_planes = 16, int hor_planes = 3, 
                              D3DCOLOR color = RGB(200, 200, 200));
    static CD3DFrame *CreateAxis(CD3DMainObj *pOwner,
                              int vert_planes = 16, 
                              double ratio_rad = 0.5, 
                              double ratio_lentip = 0.2, 
                              double ratio_lenback = 0.0, 
                              D3DCOLOR color = RGB(200, 200, 200));
    static CD3DFrame *CreateChessBoard(CD3DMainObj *pOwner,
                              int x_cells = 8, int z_cells = 8,
                              D3DCOLOR black = RGB(150, 150, 150),
                              D3DCOLOR white = RGB(255, 255, 255));
  };

////////////////////////////////////////////////////////////////////////////

#endif
