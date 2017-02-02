
// NoDictDoc.cpp : implementation of the CNoDictDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "NoDict.h"
#endif

#include "NoDictDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CNoDictDoc

IMPLEMENT_DYNCREATE(CNoDictDoc, CDocument)

BEGIN_MESSAGE_MAP(CNoDictDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CNoDictDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CNoDictDoc::OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CNoDictDoc, CDocument)
END_DISPATCH_MAP()

// Note: we add support for IID_INoDict to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {BC642DE5-49CD-4FEF-96C0-EDD78DFAD1DD}
static const IID IID_INoDict =
{ 0xBC642DE5, 0x49CD, 0x4FEF, { 0x96, 0xC0, 0xED, 0xD7, 0x8D, 0xFA, 0xD1, 0xDD } };

BEGIN_INTERFACE_MAP(CNoDictDoc, CDocument)
	INTERFACE_PART(CNoDictDoc, IID_INoDict, Dispatch)
END_INTERFACE_MAP()


// CNoDictDoc construction/destruction

CNoDictDoc::CNoDictDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();

}

CNoDictDoc::~CNoDictDoc()
{
	AfxOleUnlockApp();
}

BOOL CNoDictDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CNoDictDoc serialization

void CNoDictDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CNoDictDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CNoDictDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CNoDictDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CNoDictDoc diagnostics

#ifdef _DEBUG
void CNoDictDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNoDictDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CNoDictDoc commands
