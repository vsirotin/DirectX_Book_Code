// d3dDynaChromeDoc.h : interface of the CD3DDynaChromeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3DDYNACHROMEDOC_H__E0833C6A_BE94_11D2_8D1E_444553540000__INCLUDED_)
#define AFX_D3DDYNACHROMEDOC_H__E0833C6A_BE94_11D2_8D1E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CD3DDynaChromeDoc : public CDocument
{
protected: // create from serialization only
	CD3DDynaChromeDoc();
	DECLARE_DYNCREATE(CD3DDynaChromeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DDynaChromeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CD3DDynaChromeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CD3DDynaChromeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DDYNACHROMEDOC_H__E0833C6A_BE94_11D2_8D1E_444553540000__INCLUDED_)
