// ddPCXFiller.h: interface for the CDDPCXFiller class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDPCXFILLER_H__7DF6D344_989B_11D2_A3D6_00A02459434F__INCLUDED_)
#define AFX_DDPCXFILLER_H__7DF6D344_989B_11D2_A3D6_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ddImageFiller.h"
#include "pcx.h"

class CDDPCXFiller : public CDDImageFiller
  {
  public:
    CDDPCXFiller(){m_ImageFile = new CPCX;}
    virtual ~CDDPCXFiller(){delete m_ImageFile;}
    
  };

#endif // !defined(AFX_DDPCXFILLER_H__7DF6D344_989B_11D2_A3D6_00A02459434F__INCLUDED_)
