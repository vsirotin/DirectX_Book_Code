// d3dShadowDoc.h : interface of the CD3DShadowDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3DSHADOWDOC_H__492C432A_9DD8_11D2_8D1E_444553540000__INCLUDED_)
#define AFX_D3DSHADOWDOC_H__492C432A_9DD8_11D2_8D1E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CD3DShadowDoc : public CDocument
{
protected: // create from serialization only
	CD3DShadowDoc();
	DECLARE_DYNCREATE(CD3DShadowDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DShadowDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CD3DShadowDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CD3DShadowDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DSHADOWDOC_H__492C432A_9DD8_11D2_8D1E_444553540000__INCLUDED_)
