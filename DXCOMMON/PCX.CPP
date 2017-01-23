// pcx.cpp: implementation of the CPCX class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pcx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static PCXHEAD pcxHead;
static IMGPAL pal[] = { 
                      {0x00, 0x00, 0x00}, 
                      {0x00, 0x00, 0xAA}, 
                      {0x00, 0xAA, 0x00}, 
                      {0x00, 0xAA, 0xAA}, 
                      {0xAA, 0x00, 0x00}, 
                      {0xAA, 0x00, 0xAA}, 
                      {0xAA, 0xAA, 0x00}, 
                      {0xAA, 0xAA, 0xAA}, 
                      {0x55, 0x55, 0x55}, 
                      {0x55, 0x55, 0xFF}, 
                      {0x55, 0xFF, 0x55}, 
                      {0x55, 0xFF, 0xFF}, 
                      {0xFF, 0x55, 0x55}, 
                      {0xFF, 0x55, 0xFF}, 
                      {0xFF, 0xFF, 0x55}, 
                      {0xFF, 0xFF, 0xFF}  
                      };

static IMGPAL *stdPal = pal;

///////////////////////////////////////////////////////////////////////////////
//
CPCX::CPCX()
  {
  m_buf = NULL;
  m_pal = NULL;
  }

///////////////////////////////////////////////////////////////////////////////
//
CPCX::~CPCX()
  {
  if (m_buf != NULL)
    {
    delete [] m_buf;
    m_buf = NULL;
    }

  if (m_pal != NULL)
    {
    free(m_pal);
    m_pal = NULL;
    }

  if (m_file.m_hFile != CFile::hFileNull)
    m_file.Close();
  }

///////////////////////////////////////////////////////////////////////////////
//
bool CPCX::Init(int type, int col, int p, int q,
                int lp, int lq, int hres, int vres,
                int blen)
  {
  BYTE bitpx = (BYTE)(type == 8 ? 8 : 1);

  if (type !=1 && type != 2 && type != 4 && type != 8 || 
      lp <= 0 || 
      lq <= 0 || 
      blen != 0 && (long)blen < ((long)lp * bitpx + 7) /8) 
    return false;

  if (hres <= 0 || vres <= 0) 
    hres = vres = 300;

  if (blen == 0) 
    blen = (int)(((long)lp * bitpx + 15) / 8) & ~1;

  m_type = (BYTE)type;
  m_col  = (BYTE)(col!=0);
  m_p    = p;
  m_q    = q;
  m_lp   = lp;
  m_lq   = lq;
  m_hres = hres;
  m_vres = vres;
  m_blen = blen;
  m_buf  = new BYTE [blen];
  return true;
  }

///////////////////////////////////////////////////////////////////////////////
//
bool CPCX::Init(char *fname)
  {
  if (m_file.m_hFile != CFile::hFileNull)
    m_file.Close();

  if (!m_file.Open(fname, CFile::modeRead))
    return false;

  //= read header of PCX file and create its descriptor
  if (m_file.Seek(0, CFile::begin) != 0          || 
      m_file.Read(&pcxHead, LHEAD) != LHEAD      || 
      pcxHead.manuf != 10                        || 
      pcxHead.ver != 5                           || 
      pcxHead.encod != 1                         || 
      pcxHead.bplin  == 0                        || 
      pcxHead.bitpx != 1 && pcxHead.bitpx != 8   || 
      pcxHead.bitpx == 8 && pcxHead.nplanes != 1 ||
      !Init(pcxHead.bitpx * pcxHead.nplanes,
            pcxHead.palinfo != 2,
            pcxHead.x1, pcxHead.y1, 
            pcxHead.x2 - pcxHead.x1 + 1,
            pcxHead.y2 - pcxHead.y1 + 1,
            pcxHead.shres, pcxHead.svres,
            pcxHead.bplin)) 
    return false;

  m_wind[0] = m_wind[1] = PCXSIZE - 3;
  m_wind[2] = 0;

  //= read palette
  switch(m_type)
    {
    case 4:
      m_pal = (IMGPAL *)memcpy(malloc(LPAL4), pcxHead.pal, LPAL4);
      break;

    case 8:
      if ((m_pal = (IMGPAL *)malloc(LPAL8)) != NULL)
        {
        m_file.Seek(-((long)LPAL8), CFile::end);
        m_file.Read(m_pal, LPAL8);
        }
      
      m_file.Seek(LHEAD, CFile::begin);
      break;
    }
  
  return true;
  }


///////////////////////////////////////////////////////////////////////////////
//
bool CPCX::GetSize(int *width, int *height)
  {
  *width = m_lp;
  *height = m_lq;

  return true;
  }

///////////////////////////////////////////////////////////////////////////////
//
IMGPAL *CPCX::GetPalette()
  {
  return m_pal;
  }

void CPCX::GetDirectDrawPalette(PALETTEENTRY *ape)
  {
  //= create palette from PCX file palette entries
  for (int i = 0; i < 256; i++)
    {
    ape[i].peRed = m_pal[i].r;
    ape[i].peGreen = m_pal[i].g;
    ape[i].peBlue = m_pal[i].b;
    ape[i].peFlags = 0;
    }
  }

///////////////////////////////////////////////////////////////////////////////
//
bool CPCX::Rewind()
  {
  m_file.Seek(LHEAD, CFile::begin);
  return true;
  }

///////////////////////////////////////////////////////////////////////////////
//
bool CPCX::GetLine(BYTE *line, int pos)
  {
  int len  = m_lp - pos;
  BYTE type = m_type;

  if (pos < 0 || len < 0) 
    return false;

  if (type == 8) 
    {
    if (!locRead()) 
      return false;

    memcpy(line, m_buf + pos, len);
    }

  else 
    {
    BYTE  *b;
    int i;
    register BYTE c, mask, plane;

    memset(line, 0, len);
    for (plane = 1; type; type--, plane <<= 1) 
      {
      if(!locRead()) 
        return false;

      b = m_buf + pos / 8;
      c = *b++;
      mask = (BYTE)(0x80 >> (pos % 8));
      for (i = 0; i < len; i++, mask >>= 1) 
        {
        if (!mask) 
          mask = 0x80, c = *b++;

        if (c & mask) 
          line[i] |= plane;
        }
      }
    }

  return true;
  }

///////////////////////////////////////////////////////////////////////////////
//
bool CPCX::SkipLines(int count)
  {
  long num = (long)count * (m_type == 8 ? 1 : m_type);

  for (; num > 0; num--) 
    if(!locRead()) 
      return false;

  return true;
  }

///////////////////////////////////////////////////////////////////////////////
//
bool CPCX::Write(char *fname, IMGPAL *pal)
  {
  pcxHead.manuf = 10;
  pcxHead.ver   = 5;
  pcxHead.encod = 1;
  pcxHead.bitpx = (BYTE)(m_type == 8 ? 8 : 1);
  pcxHead.x1    = m_p;
  pcxHead.y1    = m_q;
  pcxHead.x2    = pcxHead.x1 + m_lp - 1;
  pcxHead.y2    = pcxHead.y1 + m_lq - 1;
  pcxHead.hres  = 300;
  pcxHead.vres  = 300;
  memcpy(pcxHead.pal, pal == NULL ? stdPal : pal, LPAL4);
  pcxHead.nplanes = (BYTE)(m_type == 8 ? 1 : m_type);
  pcxHead.bplin   = m_blen;
  pcxHead.palinfo = m_col ? 1 : 2;
  pcxHead.shres   = m_hres;
  pcxHead.svres   = m_vres;

  if (m_file.m_hFile != CFile::hFileNull)
    m_file.Close();

  if (!m_file.Open(fname, CFile::modeCreate | CFile::modeWrite))
    return false;

  m_file.Write((void *)&pcxHead, LHEAD);
  return true;
  }

///////////////////////////////////////////////////////////////////////////////
//
bool CPCX::WritePal(IMGPAL *pal)
  {
  BYTE code = 12;

  m_file.Write(&code, 1);
  m_file.Write(pal, LPAL8);
  return true;
  }

///////////////////////////////////////////////////////////////////////////////
//
bool CPCX::PutLine(BYTE *line)
  {
  int len  = m_lp;
  BYTE  type = m_type;

  if (type == 8) 
    {
    memcpy(m_buf, line, len);
    if (!locWrite()) 
      return false;
    }

  else 
    {
    BYTE  *b;
    int i;
    register BYTE c, mask, plane;

    for (plane = 1; type; type--, plane <<= 1) 
      {
      for (i = 0, b = m_buf, c = 0, mask = 0x80; 
           i < len; i++, mask >>= 1) 
        {
        if (!mask) 
          *b++ = c, c = 0, mask = 0x80;

        if (line[i] & plane) 
          c |= mask;
        }

      *b = c;
      if (!locWrite()) 
        return false;
      }
    }

  return true;
  }

///////////////////////////////////////////////////////////////////////////////
//
int CPCX::locRead(void)
  {
  BYTE  len  = m_wind[0];
  BYTE  pos  = m_wind[1];
  BYTE  *b   = m_buf;
  BYTE  *w   = m_wind + 3 + pos;
  int l      = m_blen;
  BYTE  n    = m_wind[2];
  BYTE  data = (BYTE)(n ? w[-1] : 0);

  for(; l > 0; l--, b++)
    if (n) 
      n--, *b = data;
    else 
      {
      if (pos == len) 
        {
        w = m_wind + 3; 
        pos = 0;
        if (!(len = (BYTE)m_file.Read(w, len))) 
          return 0;
        }

      data = *w++; 
      pos++;
      
      if ((data & 0xC0) != 0xC0) 
        *b = data;
      else 
        {
        n = (BYTE)((data & 0x3F) - 1);
        if (pos == len) 
          {
          w = m_wind + 3; 
          pos = 0;
          if (!(len = (BYTE)m_file.Read(w, len))) 
            return 0;
        }
      *b = data = *w++; 
      pos++;
      }
    }

  m_wind[0] = len;
  m_wind[1] = pos;
  m_wind[2] = n;
  return 1;
  }

///////////////////////////////////////////////////////////////////////////////
//
int CPCX::locWrite(void)
  {
  BYTE  len = PCXSIZE - 1;
  BYTE  pos = 0;
  BYTE  *b  = m_buf;
  BYTE  *w  = m_wind;
  int l     = m_blen;
  BYTE  n   = 0;
  BYTE  d   = *b;
  BYTE  data, i;

  for (i = 0; i != 2; i++, data = (BYTE)~d, b = &data, l = 1) 
    for(; l > 0; l--) 
      {
      data = *b++;
      if (data == d && n != 0x3F) 
        { 
        n++; 
        continue; 
        }

      if (pos >= len) 
        {
        w = m_wind; 
        m_file.Write(w, pos); 

        pos = 0;
        }

      if (n != 1 || (d & 0xC0) == 0xC0) 
        pos++, *w++ = (BYTE)(n | 0xC0);

      pos++; 
      *w++ = d; 
      d = data; 
      n = 1;
      }

  m_file.Write(&(m_wind[0]), pos);
  return 1;
  }

