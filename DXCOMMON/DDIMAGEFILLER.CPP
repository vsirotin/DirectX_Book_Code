// ddImageFiller.cpp: implementation of the CDDImageFiller class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ddImageFiller.h"
#include "ImageFile.h"

#include "ddSprite.h"
#include "ddMainObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CDDImageFiller, CDDSurfaceFiller);
bool CDDImageFiller::Create(LPTSTR name)
  {
  if (m_ImageFile == NULL)
    return false;

  return m_ImageFile->Init(name);
  }

bool CDDImageFiller::GetSize(int *w, int *h)
  {
  if (m_ImageFile == NULL)
    return false;

  return m_ImageFile->GetSize(w, h);
  }

void CDDImageFiller::GetDirectDrawPalette(PALETTEENTRY *ape)
  {
  if (m_ImageFile != NULL)
    m_ImageFile->GetDirectDrawPalette(ape);

  }

bool CDDImageFiller::FillSurface(CDDSprite *pSprite, int x, int y)
  {
  if (m_ImageFile == NULL)
    return false;

  LPDIRECTDRAWSURFACE3 pSurface = pSprite->GetSurface();
  return FillSurface(pSurface, x, y);
  }

bool CDDImageFiller::FillSurface(CDDMainObj *pDDObj, int x, int y)
  {
  if (m_ImageFile == NULL)
    return false;

  LPDIRECTDRAWSURFACE3 pSurface = pDDObj->GetBackSurface();
  return FillSurface(pSurface, x, y);
  }

bool CDDImageFiller::FillSurface(LPDIRECTDRAWSURFACE3 pSurface, int x, int y)
  {
  DDSURFACEDESC   ddsd;
  BYTE           *b;

  int iWidth, iHeight;

  m_ImageFile->GetSize(&iWidth, &iHeight);
  ZeroMemory(&ddsd, sizeof(ddsd));
  ddsd.dwSize = sizeof(ddsd);
  DDTRY(pSurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL));

  BYTE *bb;
  b = (BYTE *)ddsd.lpSurface + y * ddsd.lPitch + x * (ddsd.ddpfPixelFormat.dwRGBBitCount / 8);
  int j, k;
  if ((ddsd.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED8) != 0)
    {
    for (j = 0; j < iHeight; j++, b += ddsd.lPitch)
      if (!m_ImageFile->GetLine(b))
        break;

    }
  else if ((ddsd.ddpfPixelFormat.dwFlags & DDPF_RGB) != 0)
    {
    IMGPAL *pal = m_ImageFile->GetPalette();
    BYTE *buff = new BYTE [iWidth];

    if (ddsd.ddpfPixelFormat.dwRGBBitCount == 16)
      {
      int nR, nG, nB, nr, ng, nb;
      WORD W;

      W = (WORD)(ddsd.ddpfPixelFormat.dwRBitMask);
      for (nR = 0; (W & 0x0001) == 0; nR++) W >>= 1;
      for (nr = 0; (W & 0x0001) != 0; nr++) W >>= 1;

      W = (WORD)(ddsd.ddpfPixelFormat.dwGBitMask);
      for (nG = 0; (W & 0x0001) == 0; nG++) W >>= 1;
      for (ng = 0; (W & 0x0001) != 0; ng++) W >>= 1;

      W = (WORD)(ddsd.ddpfPixelFormat.dwBBitMask);
      for (nB = 0; (W & 0x0001) == 0; nB++) W >>= 1;
      for (nb = 0; (W & 0x0001) != 0; nb++) W >>= 1;

      for (j = 0; j < iHeight; j++, b += ddsd.lPitch)
        {
        if (!m_ImageFile->GetLine(buff))
          {
          ASSERT(FALSE);
          break;
          }

        bb = b;
        for (k = 0; k < iWidth; k++)
          {
          W = 0;
          W |= ((((WORD)(pal[buff[k]].r) & 0x00FF) >> (8 - nr)) << nR) & ddsd.ddpfPixelFormat.dwRBitMask;
          W |= ((((WORD)(pal[buff[k]].g) & 0x00FF) >> (8 - ng)) << nG) & ddsd.ddpfPixelFormat.dwGBitMask;
          W |= ((((WORD)(pal[buff[k]].b) & 0x00FF) >> (8 - nb)) << nB) & ddsd.ddpfPixelFormat.dwBBitMask;

          *bb++ = *(((BYTE *)&W) + 0);
          *bb++ = *(((BYTE *)&W) + 1);
          }
        for (; k < (int)ddsd.dwWidth; k++)
          {
          *bb++ = 0;
          *bb++ = 0;
          }
        }
      for (; j < (int)ddsd.dwHeight; j++, b += ddsd.lPitch)
        {
        bb = b;
        for (k = 0; k < (int)ddsd.dwWidth; k++)
          {
          *bb++ = 0;
          *bb++ = 0;
          }
        }
      }
    else if (ddsd.ddpfPixelFormat.dwRGBBitCount == 24)
      {
      int nR, nG, nB;
      DWORD DW;

      DW = ddsd.ddpfPixelFormat.dwRBitMask;
      for (nR = 0; (DW & 0x00000001) == 0; nR++)
        DW >>= 1;

      DW = ddsd.ddpfPixelFormat.dwGBitMask;
      for (nG = 0; (DW & 0x00000001) == 0; nG++)
        DW >>= 1;

      DW = ddsd.ddpfPixelFormat.dwBBitMask;
      for (nB = 0; (DW & 0x00000001) == 0; nB++)
        DW >>= 1;

      for (j = 0; j < iHeight; j++, b += ddsd.lPitch)
        {
        if (!m_ImageFile->GetLine(buff))
          {
          ASSERT(FALSE);
          break;
          }

        bb = b;
        for (k = 0; k < iWidth; k++)
          {
          DW = 0;
          DW |= (((DWORD)(pal[buff[k]].r) & 0x000000FF) << nR) & ddsd.ddpfPixelFormat.dwRBitMask;
          DW |= (((DWORD)(pal[buff[k]].g) & 0x000000FF) << nG) & ddsd.ddpfPixelFormat.dwGBitMask;
          DW |= (((DWORD)(pal[buff[k]].b) & 0x000000FF) << nB) & ddsd.ddpfPixelFormat.dwBBitMask;

          *bb++ = *(((BYTE *)&DW) + 0);
          *bb++ = *(((BYTE *)&DW) + 1);
          *bb++ = *(((BYTE *)&DW) + 2);
          }
        for (; k < (int)ddsd.dwWidth; k++)
          {
          *bb++ = 0;
          *bb++ = 0;
          *bb++ = 0;
          }
        }
      for (; j < (int)ddsd.dwHeight; j++, b += ddsd.lPitch)
        {
        bb = b;
        for (k = 0; k < (int)ddsd.dwWidth; k++)
          {
          *bb++ = 0;
          *bb++ = 0;
          *bb++ = 0;
          }
        }
      }
    else if (ddsd.ddpfPixelFormat.dwRGBBitCount == 32)
      {
      int nR, nG, nB;
      DWORD DW;

      DW = ddsd.ddpfPixelFormat.dwRBitMask;
      for (nR = 0; (DW & 0x00000001) == 0; nR++)
        DW >>= 1;

      DW = ddsd.ddpfPixelFormat.dwGBitMask;
      for (nG = 0; (DW & 0x00000001) == 0; nG++)
        DW >>= 1;

      DW = ddsd.ddpfPixelFormat.dwBBitMask;
      for (nB = 0; (DW & 0x00000001) == 0; nB++)
        DW >>= 1;

      for (j = 0; j < iHeight; j++, b += ddsd.lPitch)
        {
        if (!m_ImageFile->GetLine(buff))
          {
          ASSERT(FALSE);
          break;
          }

        bb = b;
        for (k = 0; k < iWidth; k++)
          {
          DW = 0;
          DW |= (((DWORD)(pal[buff[k]].r) & 0x000000FF) << nR) & ddsd.ddpfPixelFormat.dwRBitMask;
          DW |= (((DWORD)(pal[buff[k]].g) & 0x000000FF) << nG) & ddsd.ddpfPixelFormat.dwGBitMask;
          DW |= (((DWORD)(pal[buff[k]].b) & 0x000000FF) << nB) & ddsd.ddpfPixelFormat.dwBBitMask;

          BYTE bbb = *(((BYTE *)&DW) + 0);
          *bb++ = bbb;
          bbb = *(((BYTE *)&DW) + 1);
          *bb++ = bbb;
          bbb = *(((BYTE *)&DW) + 2);
          *bb++ = bbb;
          *bb++ = 0;
          }
        for (; k < (int)ddsd.dwWidth; k++)
          {
          *bb++ = 0;
          *bb++ = 0;
          *bb++ = 0;
          *bb++ = 0;
          }
        }
      for (; j < (int)ddsd.dwHeight; j++, b += ddsd.lPitch)
        {
        bb = b;
        for (k = 0; k < (int)ddsd.dwWidth; k++)
          {
          *bb++ = 0;
          *bb++ = 0;
          *bb++ = 0;
          *bb++ = 0;
          }
        }
      }

    delete buff;
    }

  return DDCHECK(pSurface->Unlock(NULL));
  }
