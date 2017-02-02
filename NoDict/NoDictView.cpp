
// NoDictView.cpp : implementation of the CNoDictView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "NoDict.h"
#endif

#include "NoDictDoc.h"
#include "NoDictView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNoDictView

std::vector<Record> g_dictEn;
std::vector<Record> g_dictDe;
std::vector<Record> g_dictNo;

const CString EnDictionary("English.ddim");
const CString DeDictionary("Deutsch.ddim");
const CString NoDictionary("Norsk.ddim");


IMPLEMENT_DYNCREATE(CNoDictView, CFormView)

BEGIN_MESSAGE_MAP(CNoDictView, CFormView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CNoDictView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_EDIT_BTN, &OnEdit)
	ON_BN_CLICKED(IDC_SAVE, &OnSave)
	ON_BN_CLICKED(IDC_CANCEL, &OnCancel)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &OnChangeColorEN)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON2, &OnChangeColorDE)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON3, &OnChangeColorNO)
	ON_NOTIFY(EN_SELCHANGE, IDC_RICHEDIT22, &OnChangeSelEN)
	ON_NOTIFY(EN_SELCHANGE, IDC_RICHEDIT23, &OnChangeSelDE)
	ON_NOTIFY(EN_SELCHANGE, IDC_RICHEDIT24, &OnChangeSelNO)
	ON_EN_CHANGE(IDC_EDIT4, &OnChangeQuery)
	//ON_NOTIFY(WM_PASTE, IDC_RICHEDIT22, &OnPaste)
	ON_WM_PASTE()
END_MESSAGE_MAP()


// CNoDictView construction/destruction

CNoDictView::CNoDictView() : CFormView(CNoDictView::IDD)
{
	// TODO: add construction code here
}

CNoDictView::~CNoDictView()
{
}

BOOL CNoDictView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CFormView::PreCreateWindow(cs);
}

// CNoDictView drawing

void CNoDictView::OnDraw(CDC* pDC/*pDC*/)
{
	CNoDictDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	//pDC->Rectangle(10, 10, 100, 100);
}


// CNoDictView printing


void CNoDictView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CNoDictView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CNoDictView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CNoDictView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CNoDictView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CNoDictView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}
void CNoDictView::OnEdit() 
{
	m_edit = TRUE;
	SetEditAll(TRUE);
	CWnd* saveBtn = GetDlgItem(IDC_SAVE);
	if (saveBtn)
		saveBtn->EnableWindow(TRUE);
	CWnd* cancelBtn = GetDlgItem(IDC_CANCEL);
	if (cancelBtn)
		cancelBtn->EnableWindow(TRUE);
	CWnd* editBtn = GetDlgItem(IDC_EDIT_BTN);
	if (editBtn)
		editBtn->EnableWindow(FALSE);
}
void CNoDictView::OnSave()
{
	m_edit = FALSE;
	SetEditAll(FALSE);
	CWnd* saveBtn = GetDlgItem(IDC_SAVE);
	if (saveBtn)
		saveBtn->EnableWindow(FALSE);
	CWnd* cancelBtn = GetDlgItem(IDC_CANCEL);
	if (cancelBtn)
		cancelBtn->EnableWindow(FALSE);
	CWnd* editBtn = GetDlgItem(IDC_EDIT_BTN);
	if (editBtn)
		editBtn->EnableWindow(TRUE);
	SaveAll(); // save the contents
}
void CNoDictView::OnCancel() 
{
	m_edit = FALSE;
	SetEditAll(FALSE);
	CWnd* saveBtn = GetDlgItem(IDC_SAVE);
	if (saveBtn)
		saveBtn->EnableWindow(FALSE);
	CWnd* cancelBtn = GetDlgItem(IDC_CANCEL);
	if (cancelBtn)
		cancelBtn->EnableWindow(FALSE);
	CWnd* editBtn = GetDlgItem(IDC_EDIT_BTN);
	if (editBtn)
		editBtn->EnableWindow(TRUE);
}
void CNoDictView::OnChangeColorEN()
{
	ChangeColorAll(EDIT_EN());
}
void CNoDictView::OnChangeColorDE()
{
	ChangeColorAll(EDIT_DE());
}
void CNoDictView::OnChangeColorNO() 
{
	ChangeColorAll(EDIT_NO());
}
int CNoDictView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return CFormView::OnCreate(lpCreateStruct);
}
void CNoDictView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CRichEditCtrl* editEn = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT22);
	if (editEn) {
		editEn->SetBackgroundColor(FALSE, m_color);
		editEn->SetEventMask(editEn->GetEventMask() | ENM_SELCHANGE);
	}
	CRichEditCtrl* editEn2 = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT23);
	if (editEn2) {
		editEn2->SetBackgroundColor(FALSE, m_color);
		editEn2->SetEventMask(editEn2->GetEventMask() | ENM_SELCHANGE);
	}
	CRichEditCtrl* editEn3 = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT24);
	if (editEn3) {
		editEn3->SetBackgroundColor(FALSE, m_color);
		editEn3->SetEventMask(editEn3->GetEventMask() | ENM_SELCHANGE);
	}
	UpdateNumberOfRecords();
	return;
}
void CNoDictView::OnChangeSelEN(NMHDR* pNotifyStruct, LRESULT* result)
{
	ChangeSelPropAll(EDIT_EN(), pNotifyStruct, result);
	*result = 0;
}
void CNoDictView::OnChangeSelDE(NMHDR* pNotifyStruct, LRESULT* result) 
{
	ChangeSelPropAll(EDIT_DE(), pNotifyStruct, result);
	*result = 0;
}
void CNoDictView::OnChangeSelNO(NMHDR* pNotifyStruct, LRESULT* result)
{
	ChangeSelPropAll(EDIT_NO(), pNotifyStruct, result);
	*result = 0;
}

void CNoDictView::OnChangeQuery()
{
	UpdateNumberOfRecords();
	CEdit* editEnKeyWord = (CEdit*)GetDlgItem(IDC_EDIT_EN);
	CEdit* editDeKeyWord = (CEdit*)GetDlgItem(IDC_EDIT_DE);
	CEdit* editNoKeyWord = (CEdit*)GetDlgItem(IDC_EDIT_NO);
	CRichEditCtrl* editEn = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT22);
	CRichEditCtrl* editDe = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT23);
	CRichEditCtrl* editNo = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT24);

	CEdit* query = (CEdit*)GetDlgItem(IDC_EDIT4);
	TCHAR tmpBuff[KEYWORD_LIMIT];
	memset(tmpBuff, 0, KEYWORD_LIMIT);
	//query->GetLine(0, tmpBuff, KEYWORD_LIMIT);
	query->GetWindowTextW(tmpBuff, KEYWORD_LIMIT);
	CString queryKeyWord(tmpBuff, KEYWORD_LIMIT);
	EDITSTREAM es;
	es.pfnCallback = StreamInCallback;

	// search English dictionary
	auto itEn = std::find_if(g_dictEn.begin(), g_dictEn.end(),
		[queryKeyWord](Record& rc) {if (!queryKeyWord.CompareNoCase(rc.m_keyword)) return true;
		else return false; });
	
	if (itEn != g_dictEn.end()) {// found
		// display English record
		editEnKeyWord->SetWindowTextW((LPCTSTR)itEn->m_keyword);
		es.dwCookie = (DWORD)&(itEn->m_data);
		editEn->StreamIn(SF_RTF, es);
		// display German record
		editDeKeyWord->SetWindowTextW((LPCTSTR)g_dictDe.at(itEn->m_indexDe).m_keyword);
		es.dwCookie = (DWORD)&(g_dictDe.at(itEn->m_indexDe).m_data);
		editDe->StreamIn(SF_RTF, es);
		// display Norwegian record
		editNoKeyWord->SetWindowTextW((LPCTSTR)g_dictNo.at(itEn->m_indexNo).m_keyword);
		es.dwCookie = (DWORD)&(g_dictNo.at(itEn->m_indexNo).m_data);
		editNo->StreamIn(SF_RTF, es);
		return; // no need to search further
	}
	// search German dictionary
	auto itDe = std::find_if(g_dictDe.begin(), g_dictDe.end(),
			[queryKeyWord](Record& rc) {if (!queryKeyWord.CompareNoCase(rc.m_keyword)) return true;
			else return false; });

	if (itDe != g_dictDe.end()) {// found
		// display German record
		editDeKeyWord->SetWindowTextW((LPCTSTR)itDe->m_keyword);
		es.dwCookie = (DWORD)&(itDe->m_data);
		editDe->StreamIn(SF_RTF, es);
		// display English record
		editEnKeyWord->SetWindowTextW((LPCTSTR)g_dictEn.at(itDe->m_indexEn).m_keyword);
		es.dwCookie = (DWORD)&(g_dictEn.at(itDe->m_indexEn).m_data);
		editEn->StreamIn(SF_RTF, es);
		// display Norwegian record
		editNoKeyWord->SetWindowTextW((LPCTSTR)g_dictNo.at(itDe->m_indexNo).m_keyword);
		es.dwCookie = (DWORD)&(g_dictNo.at(itDe->m_indexNo).m_data);
		editNo->StreamIn(SF_RTF, es);
		return;
	}
	// search Norwegian dictionary
	auto itNo = std::find_if(g_dictNo.begin(), g_dictNo.end(),
		[queryKeyWord](Record& rc) {if (!queryKeyWord.CompareNoCase(rc.m_keyword)) return true;
		else return false; });

	if (itNo != g_dictNo.end()) {// found
		// display Norwegian record
		editNoKeyWord->SetWindowTextW((LPCTSTR)itNo->m_keyword);
		es.dwCookie = (DWORD)&(itNo->m_data);
		editNo->StreamIn(SF_RTF, es);
		// display English record
		editEnKeyWord->SetWindowTextW((LPCTSTR)g_dictEn.at(itNo->m_indexEn).m_keyword);
		es.dwCookie = (DWORD)&(g_dictEn.at(itNo->m_indexEn).m_data);
		editEn->StreamIn(SF_RTF, es);
		// display German record
		editDeKeyWord->SetWindowTextW((LPCTSTR)g_dictDe.at(itNo->m_indexDe).m_keyword);
		es.dwCookie = (DWORD)&(g_dictDe.at(itNo->m_indexDe).m_data);
		editDe->StreamIn(SF_RTF, es);
		return;
	}
	
}

void CNoDictView::OnPaste()
{
	return;
}

void CNoDictView::SetEditAll(BOOL edit)
{
	CRichEditCtrl* editEn = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT22);
	CEdit* editEnKey = (CEdit*)GetDlgItem(IDC_EDIT_EN);
	if (editEn && editEnKey) {
		editEn->SetReadOnly(!edit);
		editEnKey->SetReadOnly(!edit);
	}
	CRichEditCtrl* editDe = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT23);
	CEdit* editDeKey = (CEdit*)GetDlgItem(IDC_EDIT_DE);
	if (editDe && editDeKey) {
		editDe->SetReadOnly(!edit);
		editDeKey->SetReadOnly(!edit);
	}
	CRichEditCtrl* editNo = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT24);
	CEdit* editNoKey = (CEdit*)GetDlgItem(IDC_EDIT_NO);
	if (editNo && editNoKey) {
		editNo->SetReadOnly(!edit);
		editNoKey->SetReadOnly(!edit);
	}
}
void CNoDictView::ChangeSelPropAll(EDIT controls, NMHDR* pNotifyStruct, LRESULT* result) 
{
	if (!m_edit)
		return;
	CRichEditCtrl* editEn = (CRichEditCtrl*)GetDlgItem(controls.m_editCtrl);
	CMFCColorButton* colorPick = (CMFCColorButton*)GetDlgItem(controls.m_colorSel);
	SELCHANGE* ch = (SELCHANGE*)pNotifyStruct;
	if (editEn && colorPick && (ch->chrg.cpMax != ch->chrg.cpMin)) {
		CHARFORMAT2 format;
		editEn->GetSelectionCharFormat(format);
		format.cbSize = sizeof(CHARFORMAT2);
		colorPick->EnableWindow(TRUE);
		colorPick->SetColor(format.crTextColor);
	}
	else if (editEn && colorPick && (ch->chrg.cpMax == ch->chrg.cpMin)) {
		colorPick->EnableWindow(FALSE);
	}
}
void CNoDictView::ChangeColorAll(EDIT controls) 
{
	CMFCColorButton* colorPick = (CMFCColorButton*)GetDlgItem(controls.m_colorSel);
	CRichEditCtrl* editEn = (CRichEditCtrl*)GetDlgItem(controls.m_editCtrl);
	if (!editEn)
		return;
	CHARRANGE cr;
	editEn->GetSel(cr);
	if (cr.cpMax == cr.cpMin) {// empty selection: set default color for the following text entry
							   /*
							   CHARFORMAT2 format;
							   editEn->GetDefaultCharFormat(format);
							   format.cbSize = sizeof(CHARFORMAT2);
							   format.dwMask |= CFM_COLOR;
							   format.dwEffects &= !CFE_AUTOCOLOR;
							   format.crTextColor = colorPick->GetColor();
							   format.crBackColor = m_color;
							   editEn->SetDefaultCharFormat(format);
							   */
	}
	else {
		CHARFORMAT2 format;
		editEn->GetSelectionCharFormat(format);
		format.cbSize = sizeof(CHARFORMAT2);
		format.dwMask |= CFM_COLOR;
		format.dwEffects &= !CFE_AUTOCOLOR;
		format.crTextColor = colorPick->GetColor();
		format.crBackColor = m_color;
		editEn->SetSelectionCharFormat(format);
	}
}

void CNoDictView::SaveAll()
{
	/*
	CFile cFileEn(TEXT("English.ddim"), CFile::modeCreate | CFile::modeWrite);
	CFile cFileDe(TEXT("Deutsch.ddim"), CFile::modeCreate | CFile::modeWrite);
	CFile cFileNo(TEXT("Norsk.ddim"), CFile::modeCreate | CFile::modeWrite);
	*/
	EDITSTREAM es;
	es.pfnCallback = StreamOutCallback;
	CRichEditCtrl* editEn = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT22);
	CRichEditCtrl* editDe = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT23);
	CRichEditCtrl* editNo = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT24);
	CEdit* editEnKeyWord = (CEdit*)GetDlgItem(IDC_EDIT_EN);
	CEdit* editDeKeyWord = (CEdit*)GetDlgItem(IDC_EDIT_DE);
	CEdit* editNoKeyWord = (CEdit*)GetDlgItem(IDC_EDIT_NO);

	if (!editEn || !editDe || !editNo || !editEnKeyWord || !editDeKeyWord || !editNoKeyWord)
		return;

	//es.dwCookie = (DWORD)&cFileEn;
	TCHAR tmpKeyWordBuff[KEYWORD_LIMIT];
	memset(tmpKeyWordBuff, 0, KEYWORD_LIMIT);
	//editEnKeyWord->GetLine(0, tmpKeyWordBuff, KEYWORD_LIMIT);
	editEnKeyWord->GetWindowTextW(tmpKeyWordBuff, KEYWORD_LIMIT);
	CString tmpEnKeyWord(tmpKeyWordBuff, KEYWORD_LIMIT);
	memset(tmpKeyWordBuff, 0, KEYWORD_LIMIT);
	//editDeKeyWord->GetLine(0, tmpKeyWordBuff, KEYWORD_LIMIT);
	editDeKeyWord->GetWindowTextW(tmpKeyWordBuff, KEYWORD_LIMIT);
	CString tmpDeKeyWord(tmpKeyWordBuff, KEYWORD_LIMIT);
	memset(tmpKeyWordBuff, 0, KEYWORD_LIMIT);
	//editNoKeyWord->GetLine(0, tmpKeyWordBuff, KEYWORD_LIMIT);
	editNoKeyWord->GetWindowTextW(tmpKeyWordBuff, KEYWORD_LIMIT);
	CString tmpNoKeyWord(tmpKeyWordBuff, KEYWORD_LIMIT);

	auto it = std::find_if(g_dictEn.begin(), g_dictEn.end(),
							[tmpEnKeyWord](Record& rc) {if (tmpEnKeyWord == rc.m_keyword) return true;
													 else return false; });
	if (it != g_dictEn.end()) {
		// updating existing records, indexex not need be updated
		// update English record
		it->m_data.clear();
		es.dwCookie = (DWORD)&(it->m_data);
		editEn->StreamOut(SF_RTF, es);

		// update German record
		g_dictDe.at(it->m_indexDe).m_data.clear();
		g_dictDe.at(it->m_indexDe).m_keyword = tmpDeKeyWord;
		es.dwCookie = (DWORD)&(g_dictDe.at(it->m_indexDe).m_data);
		editDe->StreamOut(SF_RTF, es);

		// update Norwegian record
		g_dictNo.at(it->m_indexNo).m_data.clear();
		g_dictNo.at(it->m_indexNo).m_keyword = tmpNoKeyWord;
		es.dwCookie = (DWORD)&(g_dictNo.at(it->m_indexNo).m_data);
		editNo->StreamOut(SF_RTF, es);
		
	}
	else { // new record 
		// English
		size_t sizeEn = g_dictEn.size();
		size_t sizeDe = g_dictDe.size();
		size_t sizeNo = g_dictNo.size();
		Record enRec(tmpEnKeyWord, EN_RECORD);
		enRec.m_keyword = tmpEnKeyWord;
		enRec.m_indexEn = sizeEn;
		enRec.m_indexDe = sizeDe;
		enRec.m_indexNo = sizeNo;
		g_dictEn.push_back(enRec);
		es.dwCookie = (DWORD)&(g_dictEn.back().m_data);
		editEn->StreamOut(SF_RTF, es);
		// German
		Record deRec(tmpDeKeyWord, DE_RECORD);
		deRec.m_keyword = tmpDeKeyWord;
		deRec.m_indexEn = sizeEn;
		deRec.m_indexDe = sizeDe;
		deRec.m_indexNo = sizeNo;
		g_dictDe.push_back(deRec);
		es.dwCookie = (DWORD)&(g_dictDe.back().m_data);
		editDe->StreamOut(SF_RTF, es);
		// Norwegian
		Record noRec(tmpNoKeyWord, NO_RECORD);
		noRec.m_keyword = tmpNoKeyWord;
		noRec.m_indexEn = sizeEn;
		noRec.m_indexDe = sizeDe;
		noRec.m_indexNo = sizeNo;
		g_dictNo.push_back(noRec);
		es.dwCookie = (DWORD)&(g_dictNo.back().m_data);
		editNo->StreamOut(SF_RTF, es);
	}
	/*
	if (editDe) {
		//es.dwCookie = (DWORD)&cFileDe;
		es.dwCookie = (DWORD)&g_dictDe;
		editDe->StreamOut(SF_TEXTIZED, es);
	}
	
	if (editNo) {
		//es.dwCookie = (DWORD)&cFileNo;
		es.dwCookie = (DWORD)&g_dictNo;
		editNo->StreamOut(SF_TEXTIZED, es);
	}
	*/
	CommitToDisk();
	UpdateNumberOfRecords();
}

void CNoDictView::CommitToDisk()
{
	CFile cFileEn((LPCTSTR)EnDictionary, CFile::modeCreate | CFile::modeWrite);
	CFile cFileDe((LPCTSTR)DeDictionary, CFile::modeCreate | CFile::modeWrite);
	CFile cFileNo((LPCTSTR)NoDictionary, CFile::modeCreate | CFile::modeWrite);

	for (auto it = g_dictEn.begin(); it != g_dictEn.end(); it++) {
		it->m_stringSize = it->m_keyword.GetLength() + 1;
		it->m_dataSize = it->m_data.size();
		cFileEn.Write((BYTE*)&(*it), it->m_sizeStatic); // write static part
		cFileEn.Write((LPCTSTR)it->m_keyword, it->m_stringSize); // write CString content
		for (size_t i = 0; i < it->m_dataSize; i++)
			cFileEn.Write(&(it->m_data[i]), 1); // write vector content
	}
	for (auto it = g_dictDe.begin(); it != g_dictDe.end(); it++) {
		it->m_stringSize = it->m_keyword.GetLength() + 1;
		it->m_dataSize = it->m_data.size();
		cFileDe.Write((BYTE*)&(*it), it->m_sizeStatic); // write static part
		cFileDe.Write((LPCTSTR)it->m_keyword, it->m_stringSize); // write CString content
		for (size_t i = 0; i < it->m_dataSize; i++)
			cFileDe.Write(&(it->m_data[i]), 1); // write vector content
	}
	for (auto it = g_dictNo.begin(); it != g_dictNo.end(); it++) {
		it->m_stringSize = it->m_keyword.GetLength() + 1;
		it->m_dataSize = it->m_data.size();
		cFileNo.Write((BYTE*)&(*it), it->m_sizeStatic); // write static part
		cFileNo.Write((LPCTSTR)it->m_keyword, it->m_stringSize); // write CString content
		for (size_t i = 0; i < it->m_dataSize; i++)
			cFileNo.Write(&(it->m_data[i]), 1); // write vector content
	}
	cFileEn.Flush();
	cFileDe.Flush();
	cFileNo.Flush();

}

BOOL CNoDictView::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN) // allows "system" keys like: ctrl, alt, tab...
	{
		if (pMsg->wParam == 'C' || pMsg->wParam == 'V')
		{
			if (GetKeyState(VK_CONTROL) < 0)
			{
				CRichEditCtrl* editEn = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT22);
				CRichEditCtrl* editDe = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT23);
				CRichEditCtrl* editNo = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT24);
				CEdit* editEnKeyWord = (CEdit*)GetDlgItem(IDC_EDIT_EN);
				CEdit* editDeKeyWord = (CEdit*)GetDlgItem(IDC_EDIT_DE);
				CEdit* editNoKeyWord = (CEdit*)GetDlgItem(IDC_EDIT_NO);
				CEdit* wnd;
				if ((wnd = (CEdit*)GetFocus()) != NULL && pMsg->wParam == 'V')
					wnd->Paste();
				if ((wnd = (CEdit*)GetFocus()) != NULL && pMsg->wParam == 'C')
					wnd->Copy();
				return TRUE;

			}
		}
	}
	return CFormView::PreTranslateMessage(pMsg);
}

void CNoDictView::UpdateNumberOfRecords()
{
	CWnd* numRecods = GetDlgItem(IDC_STATIC_NREC);
	TCHAR tmp[KEYWORD_LIMIT];
	_itow_s(g_dictEn.size(), tmp, KEYWORD_LIMIT, 10);
	numRecods->SetWindowTextW(tmp);
}

void LoadFromDisk()
{
	//CFile cFileEn((LPCTSTR)EnDictionary, CFile::modeRead);
	//CFile cFileDe((LPCTSTR)DeDictionary, CFile::modeRead);
	//CFile cFileNo((LPCTSTR)NoDictionary, CFile::modeRead);
	CFile cFileEn;
	CFile cFileDe;
	CFile cFileNo;

	UINT bytesRead = 1;
	if (cFileEn.Open((LPCTSTR)EnDictionary, CFile::modeRead))
	while (bytesRead > 0) {
		
		Record tmpRc(CString(_T("")), EN_RECORD);
		bytesRead = cFileEn.Read((BYTE*)&tmpRc, Record::m_sizeStatic); // read static part

		TCHAR tmpKeyWordBuff[KEYWORD_LIMIT * sizeof(TCHAR)];
		memset(tmpKeyWordBuff, 0, KEYWORD_LIMIT * sizeof(TCHAR));
		bytesRead = cFileEn.Read(tmpKeyWordBuff, tmpRc.m_stringSize); // read CString content
		CString tmpKeyWord(tmpKeyWordBuff, KEYWORD_LIMIT * sizeof(TCHAR));
		tmpRc.m_keyword = tmpKeyWord;
		for (LONG i = 0; i < tmpRc.m_dataSize; i++) {
			BYTE b = 0;
			bytesRead = cFileEn.Read(&b, 1); // read vector content
			tmpRc.m_data.push_back(b);
		}
		if (bytesRead <= 0)
			break;
		g_dictEn.push_back(tmpRc);
	}
	bytesRead = 1;
	if (cFileDe.Open((LPCTSTR)DeDictionary, CFile::modeRead))
		while (bytesRead > 0) {

			Record tmpRc(CString(_T("")), EN_RECORD);
			bytesRead = cFileDe.Read((BYTE*)&tmpRc, Record::m_sizeStatic); // read static part

			TCHAR tmpKeyWordBuff[KEYWORD_LIMIT * sizeof(TCHAR)];
			memset(tmpKeyWordBuff, 0, KEYWORD_LIMIT * sizeof(TCHAR));
			bytesRead = cFileDe.Read(tmpKeyWordBuff, tmpRc.m_stringSize); // read CString content
			CString tmpKeyWord(tmpKeyWordBuff, KEYWORD_LIMIT * sizeof(TCHAR));
			tmpRc.m_keyword = tmpKeyWord;
			for (LONG i = 0; i < tmpRc.m_dataSize; i++) {
				BYTE b = 0;
				bytesRead = cFileDe.Read(&b, 1); // read vector content
				tmpRc.m_data.push_back(b);
			}
			if (bytesRead <= 0)
				break;
			g_dictDe.push_back(tmpRc);
		}
	bytesRead = 1;
	if (cFileNo.Open((LPCTSTR)NoDictionary, CFile::modeRead))
		while (bytesRead > 0) {

			Record tmpRc(CString(_T("")), EN_RECORD);
			bytesRead = cFileNo.Read((BYTE*)&tmpRc, Record::m_sizeStatic); // read static part

			TCHAR tmpKeyWordBuff[KEYWORD_LIMIT * sizeof(TCHAR)];
			memset(tmpKeyWordBuff, 0, KEYWORD_LIMIT * sizeof(TCHAR));
			bytesRead = cFileNo.Read(tmpKeyWordBuff, tmpRc.m_stringSize); // read CString content
			CString tmpKeyWord(tmpKeyWordBuff, KEYWORD_LIMIT * sizeof(TCHAR));
			tmpRc.m_keyword = tmpKeyWord;
			for (LONG i = 0; i < tmpRc.m_dataSize; i++) {
				BYTE b = 0;
				bytesRead = cFileNo.Read(&b, 1); // read vector content
				tmpRc.m_data.push_back(b);
			}
			if (bytesRead <= 0)
				break;
			g_dictNo.push_back(tmpRc);
		}
	return;
}

// CNoDictView diagnostics

#ifdef _DEBUG
void CNoDictView::AssertValid() const
{
	CFormView::AssertValid();
}

void CNoDictView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CNoDictDoc* CNoDictView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNoDictDoc)));
	return (CNoDictDoc*)m_pDocument;
}
#endif //_DEBUG

static DWORD CALLBACK StreamOutCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb)
{
	/*
	CFile* pFile = (CFile*)dwCookie;
	pFile->Write(pbBuff, cb);
	*pcb = cb;
	*/
	std::vector<BYTE>* buff = (std::vector<BYTE>*)dwCookie;
	for (LONG i = 0; i < cb; i++)
		buff->push_back(pbBuff[i]);
	*pcb = cb;
	return 0;
}
static DWORD CALLBACK StreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb)
{
	//CFile* pFile = (CFile*)dwCookie;
	//*pcb = pFile->Read(pbBuff, cb);
	std::vector<BYTE>* buff = (std::vector<BYTE>*)dwCookie;
	LONG size = cb > buff->size() ? buff->size() : cb;
	for (LONG i = 0; i < size; i++)
		pbBuff[i] = buff->at(i);
	*pcb = cb;
	return 0;
}
