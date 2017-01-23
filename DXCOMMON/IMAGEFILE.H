// ImageFile.h: interface for the CImageFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEFILE_H__9FA2EB53_E8C2_11D2_8741_00A02459434F__INCLUDED_)
#define AFX_IMAGEFILE_H__9FA2EB53_E8C2_11D2_8741_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//= IMGPAL - description of palette
typedef struct
  {
  BYTE r, g, b;
  } IMGPAL;

class CImageFile  
  {
  public:
    virtual ~CImageFile(){}

    virtual bool Init(char *fname) = 0;
    virtual bool GetLine(BYTE *line, int pos = 0) = 0;
    virtual bool GetSize(int *w, int *h) = 0;
    virtual void GetDirectDrawPalette(PALETTEENTRY *ape) = 0;
    virtual IMGPAL *GetPalette(void) = 0;
  };

#endif // !defined(AFX_IMAGEFILE_H__9FA2EB53_E8C2_11D2_8741_00A02459434F__INCLUDED_)
