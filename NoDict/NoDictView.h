
// NoDictView.h : interface of the CNoDictView class
//

#pragma once
#include <vector>
#include <algorithm>

#define  UNDEF_RECORD  -1
#define  EN_RECORD  1
#define  DE_RECORD  2
#define  NO_RECORD  3

#define KEYWORD_LIMIT 100

struct Record {
	Record() : m_stringSize(0), m_dataSize(0), m_type(UNDEF_RECORD), m_indexEn(0), m_indexDe(0), m_indexNo(0), m_keyword(CString(_T(""))) {};
	Record(CString str, UINT type) :  m_keyword(str), m_type(type)
	{ /*
		if (m_type == EN_RECORD)
			m_indexEn++;
		else if (m_type == DE_RECORD)
			m_indexDe++;
		else if (m_type == NO_RECORD)
			m_indexNo++;*/
	};
	const static size_t m_sizeStatic = sizeof(size_t)*2 + sizeof(UINT)*4;	// size of not dynamic members
	size_t m_stringSize;		// size of the m_keyword (actual character bytes plus trailing zero)
	size_t m_dataSize;			// size of m_data
	UINT m_indexEn;				// unique indentifier
	UINT m_indexDe;				// unique indentifier (for example, points to corresponding German record if m_type id EN_RECORD or NO_RECORD)
	UINT m_indexNo;				// unique indentifier (see above)
	UINT m_type;				// either English record (EN_RECORD) or German (DE_RECORD) or Norwegian (NO_RECORD) or undefined UNDEF_RECORD
	CString m_keyword;			// 
	std::vector<BYTE> m_data;	// the explanation of the word
};


extern std::vector<Record> g_dictEn;
extern std::vector<Record> g_dictDe;
extern std::vector<Record> g_dictNo;

class CNoDictView : public CFormView
{
protected: // create from serialization only
	CNoDictView();
	DECLARE_DYNCREATE(CNoDictView)

	struct EDIT {
		EDIT(UINT editCtrl, UINT colorSel, UINT editKeyWord) :
					m_editCtrl(editCtrl), m_colorSel(colorSel), m_editKeyWord(editKeyWord) {}
		UINT m_editCtrl;
		UINT m_colorSel;
		UINT m_editKeyWord;
	};
	struct EDIT_EN : EDIT {
		EDIT_EN() : EDIT(IDC_RICHEDIT22, IDC_MFCCOLORBUTTON1, IDC_EDIT_EN) {}
	};
	struct EDIT_DE : EDIT {
		EDIT_DE() : EDIT(IDC_RICHEDIT23, IDC_MFCCOLORBUTTON2, IDC_EDIT_DE) {}
	};
	struct EDIT_NO : EDIT {
		EDIT_NO() : EDIT(IDC_RICHEDIT24, IDC_MFCCOLORBUTTON3, IDC_EDIT_NO) {}
	};

// Attributes
public:
	CNoDictDoc* GetDocument() const;
	enum { IDD = IDD_DIALOG_MAIN };

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void SetEditAll(BOOL edit);
	virtual void ChangeSelPropAll(EDIT controls, NMHDR* pNotifyStruct, LRESULT* result);
	virtual void ChangeColorAll(EDIT controls);
	virtual void SaveAll();
	virtual void CommitToDisk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void UpdateNumberOfRecords();
	


	COLORREF m_color = RGB(250, 245, 227);
	BOOL m_edit = false;
	
	
	//CEdit pEdit;
	//CMainFormView m_MainDlg;
	//HWND m_MainGlgHandle = NULL;
// Implementation
public:
	virtual ~CNoDictView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEdit();
	afx_msg void OnSave();
	afx_msg void OnCancel();
	afx_msg void OnChangeColorEN();
	afx_msg void OnChangeColorDE();
	afx_msg void OnChangeColorNO();
	afx_msg void OnChangeSelEN(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnChangeSelDE(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnChangeSelNO(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnChangeQuery();
	afx_msg void OnPaste();

	DECLARE_MESSAGE_MAP()
};

static DWORD CALLBACK StreamOutCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
static DWORD CALLBACK StreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
void LoadFromDisk();

#ifndef _DEBUG  // debug version in NoDictView.cpp
inline CNoDictDoc* CNoDictView::GetDocument() const
   { return reinterpret_cast<CNoDictDoc*>(m_pDocument); }
#endif

