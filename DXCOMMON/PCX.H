// pcx.h: interface for the CPCX class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCX_H__7DF6D343_989B_11D2_A3D6_00A02459434F__INCLUDED_)
#define AFX_PCX_H__7DF6D343_989B_11D2_A3D6_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageFile.h"

//=-------------------------------------------------------//
#define PCXSIZE 128
#define LHEAD   sizeof(PCXHEAD)
#define LPAL4   (16 * sizeof(IMGPAL))
#define LPAL8   (256 * sizeof(IMGPAL))


//= PCXHEAD - pcx descriptor
typedef struct 
  {
  BYTE  manuf;        // magic number: 10
  BYTE  ver;          // version: 5
  BYTE  encod;        // group coding: 1
  BYTE  bitpx;        // bits per pixel in one plane
  short x1,y1;        // upper left corner
  short x2,y2;        // bottom right
  short hres,vres;    // resolution
  IMGPAL  pal[16];    // palette
  BYTE  vmode;        // ignored
  BYTE  nplanes;      // number of planes
  short bplin;        // bytes per line
  short palinfo;      // palette type: 1 - color, 2 - grey
  short shres,svres;  // scanner resolution
  BYTE  xtra[54];     // extra empty place
  } PCXHEAD;

class CPCX : public CImageFile
  {
  public:
    CPCX(void);
    ~CPCX(void);

  private:
    BYTE    m_type;       // number of bits per pixel
                          // 1, 2, 4, 8 -- 2, 4, 16, 256 colors
    BYTE    m_col;        // palette type
    int     m_p, m_q;     // upper left corner
    int     m_lp, m_lq;   // picture size
    int     m_hres, m_vres; // resolution
    int     m_blen;       // buffer lenght
    BYTE   *m_buf;        // buffer
    IMGPAL *m_pal;        // palette 
    BYTE    m_wind[PCXSIZE];  // working window
    CFile   m_file;       // file

  public:
    bool Init(char *fname);
    bool Init(int type, int col, int p, int q,
              int lp, int lq, int hres = 300, int vres = 300, int blen = 0);

    bool Rewind(void);
    bool GetLine(BYTE *line, int pos = 0);
    bool SkipLines(int count);
    bool Write(char *fname, IMGPAL *pal = NULL);
    bool PutLine(BYTE *line);
    bool WritePal(IMGPAL *pal);
    bool GetSize(int *w, int *h);
    IMGPAL *GetPalette(void);
    void GetDirectDrawPalette(PALETTEENTRY *ape);


  private:
    int locRead(void);
    int locWrite(void);
  };


#endif // !defined(AFX_PCX_H__7DF6D343_989B_11D2_A3D6_00A02459434F__INCLUDED_)
