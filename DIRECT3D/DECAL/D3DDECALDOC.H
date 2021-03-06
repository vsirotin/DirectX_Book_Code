// d3dDecalDoc.h : interface of the CD3DDecalDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3DDECALDOC_H__1E8661EC_B021_11D2_9939_000044021625__INCLUDED_)
#define AFX_D3DDECALDOC_H__1E8661EC_B021_11D2_9939_000044021625__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CD3DDecalDoc : public CDocument
{
protected: // create from serialization only
	CD3DDecalDoc();
	DECLARE_DYNCREATE(CD3DDecalDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DDecalDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CD3DDecalDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CD3DDecalDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DDECALDOC_H__1E8661EC_B021_11D2_9939_000044021625__INCLUDED_)
