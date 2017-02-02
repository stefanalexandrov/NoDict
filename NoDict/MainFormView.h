#pragma once

class CMainFormView : public CFormView
{
	DECLARE_DYNCREATE(CMainFormView)

protected:
	CMainFormView();           // protected constructor used by dynamic creation
	virtual ~CMainFormView();

public:
	enum { IDD = IDD_DIALOG_MAIN };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
