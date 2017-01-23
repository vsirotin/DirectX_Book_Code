// SaverParameters.h: interface for the CSaverParameters class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAVERPARAMETERS_H__ADE2CD71_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
#define AFX_SAVERPARAMETERS_H__ADE2CD71_94E1_11D2_A3CF_00A02459434F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSaverParameters
  {
  public:
    CSaverParameters(void);   
    virtual ~CSaverParameters(void);
    void Save(void);          

  public:
    int      m_iCells;  //= Anzahl der Zellen
    int      m_iSpeed;  //= Geschwindigkeit
    int      m_iWait;   //= Schlafeninterwall 
    int      m_iType;   //= Type vom Text(0 - Festgelegter Text, 1 - Zeit)
    COLORREF m_cBack;   //= Hintergrundfarbe
    COLORREF m_cFore;   //= Vordergrungfarbe
    LOGFONT  m_fFont;   //= Schriftart
    CString	 m_sText;   //= Texttext
  };

#endif // !defined(AFX_SAVERPARAMETERS_H__ADE2CD71_94E1_11D2_A3CF_00A02459434F__INCLUDED_)
