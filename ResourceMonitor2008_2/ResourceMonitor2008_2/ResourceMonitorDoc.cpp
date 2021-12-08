
// ResourceMonitorDoc.cpp : CResourceMonitorDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ResourceMonitor2008_2.h"
#endif



#include "ResourceMonitorView.h"
#include "ResourceMonitorDoc.h"
#include "PerfDataManager.h"
#include "Logger.h"
#include <propkey.h>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
// CResourceMonitorDoc

IMPLEMENT_DYNCREATE(CResourceMonitorDoc, CDocument)

BEGIN_MESSAGE_MAP(CResourceMonitorDoc, CDocument)

END_MESSAGE_MAP()


// CResourceMonitorDoc ����/�Ҹ�

CResourceMonitorDoc::CResourceMonitorDoc() 
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	m_perfDataManager = new CPerfDataManager(this);
	m_isExit= FALSE;
	m_logInterval= LOG_INTERVAL;
	m_cpuThreshold = LOG_CPU_THRESHOLD;
	m_memThreshold = LOG_MEM_THRESHOLD;
}

CResourceMonitorDoc::~CResourceMonitorDoc()
{
	delete m_perfDataManager;
	m_perfDataManager = NULL;
}

UINT CResourceMonitorDoc::Update(LPVOID doc)
{
	CResourceMonitorDoc* pDoc = (CResourceMonitorDoc*)doc;
	POSITION pos = pDoc->GetFirstViewPosition();
	CResourceMonitorView* pView1 = (CResourceMonitorView*)pDoc->GetNextView(pos);
	CResourceMonitorView* pView2 = (CResourceMonitorView*)pDoc->GetNextView(pos);
	CResourceMonitorView* pView3 = (CResourceMonitorView*)pDoc->GetNextView(pos);
	CResourceMonitorView* pView4 = (CResourceMonitorView*)pDoc->GetNextView(pos);
	CPerfDataManager *dataManager = pDoc->m_perfDataManager;

	while (true)
	{
		if (pDoc->m_isExit == TRUE)
		{
			break;
		}
		{
			dataManager->RefreshData();

		}


		pView1->UpdateView(dataManager);
		pView2->UpdateView(dataManager);
		pView3->UpdateView(dataManager);
		pView4->UpdateView(dataManager);

		Sleep(UPDATE_INTERVAL);
	}
	TRACE("Update Func Out!!\n");
	return EXIT_CODE;
}



UINT CResourceMonitorDoc::AddPeriodicLog(LPVOID doc)
{
	CResourceMonitorDoc * pDoc = (CResourceMonitorDoc *)doc;
	POSITION pos = pDoc->GetFirstViewPosition();
	CResourceMonitorView* pView1 = (CResourceMonitorView*)pDoc->GetNextView(pos);
	CResourceMonitorView* pView2 = (CResourceMonitorView*)pDoc->GetNextView(pos);
	CResourceMonitorView* pView3 = (CResourceMonitorView*)pDoc->GetNextView(pos);
	CResourceMonitorView* pView4 = (CResourceMonitorView*)pDoc->GetNextView(pos);
	while (true)
	{
		if (pDoc->m_isExit == TRUE)
		{
			break;
		}
		pView1->AddPeriodicLog();
		pView2->AddPeriodicLog();
		pView3->AddPeriodicLog();
		pView4->AddPeriodicLog();
		Sleep(pDoc->m_logInterval);
	}
	TRACE("AddPeriodicLog Func Out!!\n");
	return EXIT_CODE;
}

void CResourceMonitorDoc::AtExitProcess(vector<ULONGLONG>* exitedProcIDs)
{
	if (this == NULL)return;
	POSITION pos = this->GetFirstViewPosition();
	CResourceMonitorView* pView1 = (CResourceMonitorView*)this->GetNextView(pos);
	CResourceMonitorView* pView2 = (CResourceMonitorView*)this->GetNextView(pos);
	CResourceMonitorView* pView3 = (CResourceMonitorView*)this->GetNextView(pos);
	CResourceMonitorView* pView4 = (CResourceMonitorView*)this->GetNextView(pos);

	pView1->RemoveProcessFromList(exitedProcIDs);
	pView2->RemoveProcessFromList(exitedProcIDs);
	pView3->RemoveProcessFromList(exitedProcIDs);
	pView4->RemoveProcessFromList(exitedProcIDs);
}

void CResourceMonitorDoc::ExitThread()
{
	DWORD dwRetCode = WaitForSingleObject(m_updaterThread->m_hThread, INFINITE);
	if (dwRetCode == WAIT_OBJECT_0)
	{
		TRACE("m_updaterThread is terminated normally!\n");
	}
	else if (dwRetCode == WAIT_TIMEOUT)
	{
		::TerminateThread(m_updaterThread->m_hThread, 0);
		TRACE("m_updaterThread is terminated FORCELY!");
	}

	delete m_updaterThread;
	m_updaterThread = NULL;

	dwRetCode = WaitForSingleObject(m_loggerThread->m_hThread, LOG_INTERVAL);
	if (dwRetCode == WAIT_OBJECT_0)
	{
		TRACE("m_loggerThread is terminated normally!\n");
	}
	else if (dwRetCode == WAIT_TIMEOUT)
	{
		::TerminateThread(m_loggerThread->m_hThread, 0);
		TRACE("m_loggerThread is terminated FORCELY!");
	}

	delete m_loggerThread;
	m_loggerThread = NULL;
}

BOOL CResourceMonitorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	m_perfDataManager->m_pDoc = this;


	 //thread ����
	m_updaterThread = AfxBeginThread(Update, this, 0, 0, CREATE_SUSPENDED, 0);
	m_updaterThread->m_bAutoDelete = FALSE;
	m_updaterThread->ResumeThread();

	m_loggerThread = AfxBeginThread(AddPeriodicLog, this, 0, 0, CREATE_SUSPENDED, 0);
	m_loggerThread->m_bAutoDelete = FALSE;
	m_loggerThread->ResumeThread();

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CResourceMonitorDoc serialization

void CResourceMonitorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CResourceMonitorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CResourceMonitorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CResourceMonitorDoc::SetSearchContent(const CString& value)
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

// CResourceMonitorDoc ����

#ifdef _DEBUG
void CResourceMonitorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CResourceMonitorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

