// SaverParameters.cpp: implementation of the CSaverParameters class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SaverParameters.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSaverParameters::CSaverParameters()
  {
  CWinApp *app = AfxGetApp();

  // read all parameters from ini file
  m_iCells = app->GetProfileInt("setup", "Cells", 10);
  m_iSpeed = app->GetProfileInt("setup", "Speed", 5);
  m_iWait  = app->GetProfileInt("setup", "Wait", 10);
  m_iType  = app->GetProfileInt("setup", "TextType", 0);
  m_sText  = app->GetProfileString("setup", "Text", "DirectDraw");
  m_cBack  = RGB(app->GetProfileInt("setup", "BackR", 0),
                 app->GetProfileInt("setup", "BackG", 0),
                 app->GetProfileInt("setup", "BackB", 128));
  m_cFore  = RGB(app->GetProfileInt("setup", "ForeR", 255),
                 app->GetProfileInt("setup", "ForeG", 255),
                 app->GetProfileInt("setup", "ForeB", 0));

  memset(&(m_fFont), 0, sizeof(LOGFONT));
  m_fFont.lfHeight = app->GetProfileInt("setup", "FontHeight", 72);
  m_fFont.lfWeight = app->GetProfileInt("setup", "FontWeight", FW_BOLD);
  m_fFont.lfItalic = app->GetProfileInt("setup", "FontItalic", FALSE);
  strcpy(m_fFont.lfFaceName, app->GetProfileString("setup", "FontName", "Arial"));
  }

CSaverParameters::~CSaverParameters()
  {
  // nothing to do
  }

void CSaverParameters::Save()
  {
  CWinApp *app = AfxGetApp();

  // store parameters in ini file
  app->WriteProfileInt("setup", "Cells", m_iCells);
  app->WriteProfileInt("setup", "Speed", m_iSpeed);
  app->WriteProfileInt("setup", "Wait", m_iWait);
  app->WriteProfileInt("setup", "TextType", m_iType);
	app->WriteProfileInt("setup", "BackR", GetRValue(m_cBack));
	app->WriteProfileInt("setup", "BackG", GetGValue(m_cBack));
	app->WriteProfileInt("setup", "BackB", GetBValue(m_cBack));
	app->WriteProfileInt("setup", "ForeR", GetRValue(m_cFore));
	app->WriteProfileInt("setup", "ForeG", GetGValue(m_cFore));
	app->WriteProfileInt("setup", "ForeB", GetBValue(m_cFore));
  app->WriteProfileString("setup", "Text", (LPCTSTR)(m_sText));
  app->WriteProfileInt("setup", "FontHeight", m_fFont.lfHeight);
  app->WriteProfileInt("setup", "FontWeight", m_fFont.lfWeight);
  app->WriteProfileInt("setup", "FontItalic", m_fFont.lfItalic);
  app->WriteProfileString("setup", "FontName", m_fFont.lfFaceName);
  }

