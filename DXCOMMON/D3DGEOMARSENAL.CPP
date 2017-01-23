// CD3DGeomArsenal.cpp : implementation file
//

#include "stdafx.h"
#include "d3dGeomArsenal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD3DGeomArsenal
                                 
CD3DFrame *CD3DGeomArsenal::CreateHouse(CD3DMainObj *pOwner) 
  {
  //= Frame vom Basis-Haus
  CD3DFrame *house = new CD3DFrame;
  
  if (house == NULL)
    return NULL;

  if (!house->Create(pOwner))
    return NULL;

  //= Würfel
  CD3DCubeFrame *cube = new CD3DCubeFrame;
  
  if (!cube->Create(pOwner, RGB(255, 255, 0)))
    return NULL;

  cube->AddToFrame(house);
  //= An der z-Achse entlang verschieben
  cube->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(1));
  //= Index festlegen
  cube->SetAppData(1);

  //= Pyramide
  CD3DPyramidFrame *pyramid = new CD3DPyramidFrame;
  
  if (!pyramid->Create(pOwner, RGB(255, 55, 55)))
    return NULL;

  pyramid->AddToFrame(house);
  //= Verschiebung an der z-Achse entlang. Über dem Wurfel anlegen
  pyramid->AddScale(D3DRMCOMBINE_REPLACE, D3DVAL(1.2), D3DVAL(1.2), D3DVAL(1.5));
  pyramid->AddTranslation(D3DRMCOMBINE_AFTER, D3DVAL(0), D3DVAL(0), D3DVAL(2));
  //= Index festlegen
  pyramid->SetAppData(2);

  //= Haus ist fertig: Größe: 2*2*3.5 Einheiten
  return house;
  }
   
CD3DFrame *CD3DGeomArsenal::CreateMushroom(CD3DMainObj *pOwner,
                                  int vert_planes, int hor_planes) 
  {
  //= Frame des Pilzes
  CD3DFrame *mushroom = new CD3DFrame;
  
  if (mushroom == NULL)
    return NULL;

  if (!mushroom->Create(pOwner))
    return NULL;

  //= Halbsphäre anlegen
  CD3DHalfsphereFrame *hat_sphere = new CD3DHalfsphereFrame;
  
  if (!hat_sphere->Create(pOwner, vert_planes, hor_planes, 
                                RGB(255, 0, 0)))
    return NULL;
  
  //= Halbsphäre zum Pilz hinzufügen
  if (!hat_sphere->AddToFrame(mushroom))
    return NULL;
  
  //= An der Z-Achse entlang verschieben
  hat_sphere->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(2));
  //= Index festlegen
  hat_sphere->SetAppData(1);

  //= Disk erzeugen
  CD3DDiskFrame *hat_disk = new CD3DDiskFrame;
  
  //= "-Z" Disk erzeugen
  if (!hat_disk->Create(pOwner, 0.45, vert_planes, 
                        RGB(255, 255, 0), false))
    return NULL;
  
  //= Disk zum Pilz hinzufügen
  if(!hat_disk->AddToFrame(mushroom))
    return NULL;

  //= Verschiebung entlang der Z-Achse
  hat_disk->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(2));
  //= Index festlegen
  hat_disk->SetAppData(2);

  //= Zylinder erzeugen
  CD3DCylinderFrame *cylinder = new CD3DCylinderFrame;
  
  if (!cylinder->Create(pOwner, vert_planes, RGB(0, 0, 255)))
    return NULL;
  
  //= Zylinder zum Pilz hinzufügen
  if (!cylinder->AddToFrame(mushroom))
    return NULL;

  //= Zylinder für X- und Y-Achsen kalieren.
  //= Verschiebung an der Z-Achse entlang
  cylinder->AddCombTransform(D3DVAL(0.45), D3DVAL(0.45), D3DVAL(1),
    D3DVAL(0), D3DVAL(0), D3DVAL(0), 
    D3DVAL(0), D3DVAL(0), D3DVAL(1));
  //= Index festlegen
  cylinder->SetAppData(3);

  //= Halbsphäre (unten) anlegen
  CD3DHalfsphereFrame *root_sphere = new CD3DHalfsphereFrame;
  
  if (!root_sphere->Create(pOwner, vert_planes, hor_planes, RGB(170, 170, 170)))
    return NULL;
  
  //= Halbsphäre zum Pilz hinzufügen
  if (!root_sphere->AddToFrame(mushroom))
    return NULL;

  //= Halbsphäre transformieren
  root_sphere->AddCombTransform(D3DVAL(0.45), D3DVAL(0.45), D3DVAL(0.45),
                D3DVAL(CD3DFrame::PI), D3DVAL(0), D3DVAL(0), //= Drehen
                D3DVAL(0), D3DVAL(0), D3DVAL(0)); //= Keine Verschiebung
  //= Index festlegen
  root_sphere->SetAppData(4);

  //= Pilz ist fertig: Größe 2*2 in XY; 
  //= In Z: von  -0.45 bis 3 
  return mushroom;
  }

CD3DFrame *CD3DGeomArsenal::CreateAxis(CD3DMainObj *pOwner,
                                       int vert_planes, 
                                       double ratio_rad,
                                       double ratio_lentip,
                                       double ratio_lenback,
                                       D3DCOLOR color) 
  {
  //= Allgemeine Achse

  CD3DFrame *axis = new CD3DFrame;
  
  if (axis == NULL)
    return NULL;

  if (!axis->Create(pOwner))
    return NULL;

  //= Gipfel anlegen
  CD3DConeFrame *cone = new CD3DConeFrame;
  
  if (!cone->Create(pOwner, vert_planes, color))
    return NULL;
  
  cone->AddToFrame(axis);
  cone->AddScale(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(1), D3DVAL(ratio_lentip));
  cone->AddTranslation(D3DRMCOMBINE_AFTER, D3DVAL(0), D3DVAL(0), D3DVAL(1));
//= Index festlegen
  cone->SetAppData(1);

  //= Disk von Gipfel festlegen
  CD3DDiskFrame *tip_disk = new CD3DDiskFrame;
  
  if (!tip_disk->Create(pOwner, 0.0, vert_planes, color, false))
    return NULL;
  
  //= Disk zum Frame hinzufügen
  tip_disk->AddToFrame(axis);
  //= Verschiebung an der Z-Achse entlang
  tip_disk->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(1));
//= Index festlegen
  tip_disk->SetAppData(2);

  //= Zylinder anlegen
  CD3DCylinderFrame *cylinder = new CD3DCylinderFrame;
  
  if (!cylinder->Create(pOwner, vert_planes, color))
    return NULL;
  
  //= Zylinder zum Frame hinzufügen
  cylinder->AddToFrame(axis);
  //= Zylinder transformieren
  cylinder->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(1));
  cylinder->AddScale(D3DRMCOMBINE_AFTER, D3DVAL(ratio_rad), D3DVAL(ratio_rad), D3DVAL(0.5));
//= Index festlegen
  tip_disk->SetAppData(3);

  if (ratio_lenback == 0.0)
    {
    //= Disk vom Gipfel anlegen
    CD3DDiskFrame *back_disk = new CD3DDiskFrame;
  
    if (!back_disk->Create(pOwner, 0.0, vert_planes, color, false))
      return NULL;
  
    back_disk->AddToFrame(axis);
    back_disk->AddScale(D3DRMCOMBINE_REPLACE, D3DVAL(ratio_rad), D3DVAL(ratio_rad), D3DVAL(1));
//= Index festlegen
    back_disk->SetAppData(4);

    return axis;
    }

  //= Halbsphäre der Hinterseite anlegen
  CD3DHalfsphereFrame *back_sphere = new CD3DHalfsphereFrame;
  
  if (!back_sphere->Create(pOwner, vert_planes, 3, color))
    return NULL;
  
  back_sphere->AddToFrame(axis);
  back_sphere->AddRotation(D3DRMCOMBINE_REPLACE, D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(CD3DFrame::PI));
  back_sphere->AddScale(D3DRMCOMBINE_AFTER, D3DVAL(ratio_rad), D3DVAL(ratio_rad), D3DVAL(ratio_lenback));
//= Index festlegen
  back_sphere->SetAppData(4);

  //= Die Achse ist fertig: Größe: in XY 1*1 (ratio_rad*ratio_rad); 
  //= In Z von -ratio_lenback bis  1+ratio_lentip  Einheiten
  return axis;
  }

CD3DFrame *CD3DGeomArsenal::CreateRadar(CD3DMainObj *pOwner,
                                        int vert_planes, int hor_planes, 
                                        D3DCOLOR color)
  {
  // Allgemeine Radar
  CD3DFrame *Radar = new CD3DFrame;
  
  if (Radar == NULL)
    return NULL;

  if (!Radar->Create(pOwner))
    return NULL;

  //= Pyramide
  CD3DPyramidFrame *pyramid = new CD3DPyramidFrame;

  pyramid->Create(pOwner, color);
  pyramid->AddToFrame(Radar);
  pyramid->AddScale(D3DRMCOMBINE_REPLACE, D3DVAL(0.3), D3DVAL(0.3), D3DVAL(1.5));
//= Index festlegen
  pyramid->SetAppData(1);
  
  //=  1/2 der Sphäre
  CD3DHalfsphereFrame *half_sphere = new CD3DHalfsphereFrame;
  
  if (!half_sphere->Create(pOwner, vert_planes, hor_planes, color))
    return NULL;
  
  half_sphere->AddToFrame(Radar);
  half_sphere->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(-1));
  half_sphere->AddCombTransform(D3DVAL(1), D3DVAL(1), D3DVAL(0.45),
                    D3DVAL(0), D3DVAL(-CD3DFrame::PI / 3.0 * 2.0), D3DVAL(0), 
                    D3DVAL(0), D3DVAL(0), D3DVAL(1.5));
//= Index festlegen
  half_sphere->SetAppData(2);

  //= Anedre  1/2 von Sphäre
  CD3DHalfsphereFrame *ihalf_sphere = new CD3DHalfsphereFrame;
  
  if (!ihalf_sphere->Create(pOwner, vert_planes, hor_planes, color, false))
    return NULL;
  

  ihalf_sphere->AddToFrame(Radar);
  ihalf_sphere->AddTranslation(D3DRMCOMBINE_REPLACE, D3DVAL(0), D3DVAL(0), D3DVAL(-1));
  ihalf_sphere->AddCombTransform(D3DVAL(1), D3DVAL(1), D3DVAL(0.45),
                     D3DVAL(0), D3DVAL(-CD3DFrame::PI / 3.0 * 2.0), D3DVAL(0), 
                     D3DVAL(0), D3DVAL(0), D3DVAL(1.5));
//= Index festlegen
  ihalf_sphere->SetAppData(3);
  
  //= Pyramide - Pfeil
  CD3DPyramidFrame *pyramid1 = new CD3DPyramidFrame;
  pyramid1->Create(pOwner, color);
  pyramid1->AddToFrame(Radar);
  pyramid1->AddCombTransform(D3DVAL(0.05), D3DVAL(0.05), D3DVAL(2),
                     D3DVAL(0), D3DVAL(CD3DFrame::PI / 3.0), D3DVAL(0), 
                     D3DVAL(0), D3DVAL(0), D3DVAL(1.5));
//= Index festlegen
  pyramid1->SetAppData(4);
  
  return Radar;
  }

CD3DFrame *CD3DGeomArsenal::CreateChessBoard(CD3DMainObj *pOwner,
                              int x_cells, int z_cells,
                              D3DCOLOR black, D3DCOLOR white)
  {
  D3DVECTOR cell[4];        //= Aktuelle Zelle-Polygon
  D3DCOLOR  color[2];       //= Farbe des aktuellen Polygons
  DWORD     index = 0;      //= Aktuelle Index des Zelle-Frame
  CD3DPolygonFrame *fcell;  //= Aktuelle Zelle-Frame

  if (x_cells < 2 || z_cells < 2)
    return NULL;
  
  //= Schachbrett-Frame
  CD3DFrame *chess = new CD3DFrame;
  
  if (chess == NULL)
    return NULL;

  if (!chess->Create(pOwner))
    return NULL;

  int    i, j, i_col = 0, j_col;
  double x, z;

  color[0] = black;
  color[1] = white;
  
  double dx = 1.0 / (double)x_cells;
  double dz = 1.0 / (double)z_cells;

  // cells
  for (i = 0; i < x_cells; i++)
    {
    x = i * dx;
    j_col = i_col;

    for (j = 0; j < z_cells; j++)
      {
      z = j * dz;
      cell[0].x = D3DVAL(x);
      cell[0].y = D3DVAL(0);
      cell[0].z = D3DVAL(z);
      cell[1].x = D3DVAL(x);
      cell[1].y = D3DVAL(0);
      cell[1].z = D3DVAL(z + dz);
      cell[2].x = D3DVAL(x + dx);
      cell[2].y = D3DVAL(0);
      cell[2].z = D3DVAL(z + dz);
      cell[3].x = D3DVAL(x + dx);
      cell[3].y = D3DVAL(0);
      cell[3].z = D3DVAL(z);

      fcell = new CD3DPolygonFrame;

      if (fcell == NULL)
        return NULL;
      
      if (!fcell->Create(pOwner, 4, cell, color[j_col]))
        return NULL;
      
      j_col = 1 - j_col; //= Alternative-Farber

      if (!fcell->AddToFrame(chess))
        return NULL;
		//= Index festlegen
      fcell->SetAppData(++index);
      }
    i_col = 1 - i_col;   //= Farbe in erste Zelle der nächsten Zeile ändern
    }         
  
  return chess;
  }

CD3DFrame *CD3DGeomArsenal::CreateTree(CD3DMainObj *pOwner,
                                  int vert_planes, int hor_planes) 
  {
  //= Frame des Baums
  CD3DFrame *tree = new CD3DFrame;
  
  if (tree == NULL)
    return NULL;

  if (!tree->Create(pOwner))
    return NULL;

  CD3DHalfsphereFrame *hs1 = new CD3DHalfsphereFrame;
  if (hs1 == NULL)
    return NULL;
  
  if (!hs1->Create(pOwner, vert_planes, hor_planes))
    return NULL;

  //= Baum-Frame zur Szene hinzufügen
  if (!hs1->AddToFrame(tree))
    return NULL;

  if (!hs1->AddCombTransform(D3DVAL(0.4), D3DVAL(0.4), D3DVAL(0.5),
                             D3DVAL(0), D3DVAL(0), D3DVAL(0),
                             D3DVAL(0), D3DVAL(0), D3DVAL(1)))
    return NULL;
  
	//= Index festlegen
  if (!hs1->SetAppData(1))
    return NULL;

  CD3DHalfsphereFrame *hs2 = new CD3DHalfsphereFrame;
  if (hs2 == NULL)
    return NULL;
  
  if (!hs2->Create(pOwner, vert_planes, hor_planes))
    return NULL;

  if (!hs2->AddToFrame(tree))
    return NULL;

  if (!hs2->AddCombTransform(D3DVAL(0.4), D3DVAL(0.4), D3DVAL(0.5),
                             D3DVAL(CD3DFrame::PI), D3DVAL(0), D3DVAL(0),
                             D3DVAL(0), D3DVAL(0), D3DVAL(1)))
    return NULL;

  if (!hs2->SetAppData(2))
    return NULL;

  CD3DHalfsphereFrame *hs3 = new CD3DHalfsphereFrame;
  if (hs3 == NULL)
    return NULL;

  if (!hs3->Create(pOwner, vert_planes, hor_planes))
    return NULL;

  if (!hs3->AddToFrame(tree))
    return NULL;

  if (!hs3->AddCombTransform(D3DVAL(0.3), D3DVAL(0.3), D3DVAL(0.2),
                            D3DVAL(CD3DFrame::PI / 2.0), 
                            D3DVAL(0), D3DVAL(0),
                            D3DVAL(0), D3DVAL(0), D3DVAL(0.7)))
    return NULL;

  if (!hs3->SetAppData(3))
    return NULL;

  CD3DHalfsphereFrame *hs4 = new CD3DHalfsphereFrame;
  if (hs4 == NULL)
    return NULL;

  if (!hs4->Create(pOwner, vert_planes, hor_planes))
    return NULL;

  if (!hs4->AddToFrame(tree))
    return NULL;

  if (!hs4->AddCombTransform(D3DVAL(0.3), D3DVAL(0.3), D3DVAL(0.2),
                       D3DVAL(CD3DFrame::PI / 2.0), D3DVAL(0), 
                       D3DVAL(2.0 * CD3DFrame::PI / 3.0),
                       D3DVAL(0), D3DVAL(0), D3DVAL(0.7)))
    return NULL;

  if (!hs4->SetAppData(4))
    return NULL;

  CD3DHalfsphereFrame *hs5 = new CD3DHalfsphereFrame;
  if (hs5 == NULL)
    return NULL;

  if (!hs5->Create(pOwner, vert_planes, hor_planes))
    return NULL;

  if (!hs5->AddToFrame(tree))
    return NULL;

  if (!hs5->AddCombTransform(D3DVAL(0.3), D3DVAL(0.3), D3DVAL(0.2),
                       D3DVAL(CD3DFrame::PI / 2.0), D3DVAL(0), 
                       D3DVAL(4.0 * CD3DFrame::PI / 3.0),
                       D3DVAL(0), D3DVAL(0), D3DVAL(0.7)))
    return NULL;

  if (!hs5->SetAppData(5))
    return NULL;

  CD3DConeFrame *cn = new CD3DConeFrame;
  if (cn == NULL)
    return NULL;

  if (!cn->Create(pOwner, vert_planes))
    return NULL;

  if (!cn->AddToFrame(tree))
    return NULL;

  if (!cn->AddCombTransform(D3DVAL(0.05), D3DVAL(0.05), D3DVAL(1),
                            D3DVAL(0), D3DVAL(0), D3DVAL(0),
                            D3DVAL(0), D3DVAL(0), D3DVAL(0)))
    return NULL;

  if (!cn->SetAppData(6))
    return NULL;

  if (!tree->SetColor(RGB(32, 155, 0)))
    return NULL;

  if (!cn->SetColor(RGB(127, 72, 7)))
    return NULL;

  //= Der Baum ist fertig. Größe:XY: 0.8 * 0.8 Z: von 0 bis 1.5
  return tree;
  }