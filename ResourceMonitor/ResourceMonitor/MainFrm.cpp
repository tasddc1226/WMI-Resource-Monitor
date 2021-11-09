
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "ResourceMonitor.h"
#include "ResourceMonitorView.h"
#include "CPUMonitorView.h"
#include "MemMonitorView.h"
#include "DiskMonitorView.h"
#include "NetMonitorView.h"
#include "MainFrm.h"
#include "ResourceMonitorDoc.h"
#include "PerfDataManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CMainFrame::~CMainFrame()
{

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	m_wndSplitter.CreateStatic(this, 2, 2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CCPUMonitorView), CSize(500, 500), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CMemMonitorView), CSize(300, 300), pContext);
	m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CDiskMonitorView), CSize(500, 500), pContext);
	m_wndSplitter.CreateView(1, 1, RUNTIME_CLASS(CNetMonitorView), CSize(300, 300), pContext);

	//SetActiveView((CView *)m_wndSplitter.GetPane(0, 0));
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	if (cs.hMenu != NULL)
	{
		::DestroyMenu(cs.hMenu);
		cs.hMenu = NULL;
	}


	return TRUE;
}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame �޽��� ó����



void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nID == SC_CLOSE)
	{
		if (MessageBox(L"Program Exit?", L"Resource Monitor EXIT", MB_YESNO) == IDYES)
		{
			// exit evnet
			CResourceMonitorDoc* d = (CResourceMonitorDoc*)GetActiveDocument();
			
			// thread loop Ż�� ���� ����
			d->m_isExit = TRUE; 

			// m_table claer �� erase
			d->m_perfDataManager->m_win32PerfFormatProc->m_table->clear();
			d->m_perfDataManager->m_win32PerfFormatProc->m_table->erase(d->m_perfDataManager->m_win32PerfFormatProc->m_table->begin(), d->m_perfDataManager->m_win32PerfFormatProc->m_table->end());

			d->m_perfDataManager->m_win32OperatingSystem->m_table->clear();
			d->m_perfDataManager->m_win32OperatingSystem->m_table->erase(d->m_perfDataManager->m_win32OperatingSystem->m_table->begin(), d->m_perfDataManager->m_win32OperatingSystem->m_table->end());

			// thread ����
			d->ExitThread();


			// PerfDataManager �Ҹ��� ȣ��
			d->m_perfDataManager->~CPerfDataManager();

			// CResourceMonitorDoc �Ҹ��� ȣ��
			d->~CResourceMonitorDoc();
			

		}
		else {
			// cancle event
			// do something
		}
		

		CDocument* doc =  GetActiveDocument();

	}
	CFrameWnd::OnSysCommand(nID, lParam);

}
