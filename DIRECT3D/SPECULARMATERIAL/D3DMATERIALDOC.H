// d3dMaterialDoc.h : interface of the CD3DMaterialDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3DMATERIALDOC_H__39139C1C_9ED7_11D2_9914_000044021625__INCLUDED_)
#define AFX_D3DMATERIALDOC_H__39139C1C_9ED7_11D2_9914_000044021625__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CD3DMaterialDoc : public CDocument
{
protected: // create from serialization only
	CD3DMaterialDoc();
	DECLARE_DYNCREATE(CD3DMaterialDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CD3DMaterialDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CD3DMaterialDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CD3DMaterialDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_D3DMATERIALDOC_H__39139C1C_9ED7_11D2_9914_000044021625__INCLUDED_)
