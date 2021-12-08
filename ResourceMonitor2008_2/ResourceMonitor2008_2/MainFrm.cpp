
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "ResourceMonitor2008_2.h"
#include "ResourceMonitorView.h"
#include "CPUMonitorView.h"
#include "MemMonitorView.h"
#include "DiskMonitorView.h"
#include "NetMonitorView.h"
#include "MainFrm.h"
#include "ResourceMonitorDoc.h"
#include "PerfDataManager.h"
#include "DlgSetLogInterval.h"
#include "DlgSetLogThreshold.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()

	ON_COMMAND(ID_LOG_SETINTERVAL, &CMainFrame::OnLogSetinterval)
	ON_COMMAND(ID_LOG_SETTHRESHOLD, &CMainFrame::OnLogSetthreshold)
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

	//CMenu menuMain;
	//menuMain.CreateMenu();
	//CMenu menuPopup;
	//menuPopup.CreatePopupMenu();

	//CMenu menuSubPopup;
	//menuSubPopup.CreatePopupMenu();

	//// Item �˾��޴��� �����޴� �Դϴ�.
	//menuSubPopup.AppendMenu(MF_STRING, 1001, _T("SubItem2-1"));

	//// Test �ֻ��� �޴��� �˾��޴� �Դϴ�.
	//	// ���� �޴��� ���� �� MF_POPUP�� ���ڷ� �Ѱ��ּž� �մϴ�.
	//menuPopup.AppendMenu(MF_STRING, 1101, _T("Item1"));
	//menuPopup.AppendMenu(MF_POPUP, (UINT)menuSubPopup.Detach(), _T("Item2"));
	//menuPopup.AppendMenu(MF_STRING, 1102, _T("Item3"));

	//// �ֻ��� �޴� �Դϴ�.
	//menuMain.AppendMenu(MF_POPUP, (UINT)menuPopup.Detach(), _T("Test"));

	//// �����쿡 �޴��� �߰��մϴ�.
	//SetMenu(&menuMain);
	//// �޴� ��ü�� �޴��� �и��մϴ�.
	//menuMain.Detach();

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	CRect rect;
	GetClientRect(&rect);

	m_wndSplitter.CreateStatic(this, 2, 2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CCPUMonitorView), CSize(rect.Width()/2, rect.Height()/2), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CMemMonitorView), CSize(rect.Width()/2, rect.Height()/2), pContext);
	m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CDiskMonitorView), CSize(rect.Width()/2, rect.Height()/2), pContext);
	m_wndSplitter.CreateView(1, 1, RUNTIME_CLASS(CNetMonitorView), CSize(rect.Width()/2, rect.Height()/2), pContext);

	//SetActiveView((CView *)m_wndSplitter.GetPane(0, 0));
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	//if (cs.hMenu != NULL)
	//{
	//	::DestroyMenu(cs.hMenu);
	//	cs.hMenu = NULL;

	//}
	//CMenu* pMenu = GetMenu();

	//pMenu->DeleteMenu(1, MF_BYPOSITION);

	//DrawMenuBar();
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
			CPerfDataManager* dm = d->m_perfDataManager;

			// m_table claer �� erase
			dm->m_win32PerfFormatProc->CleanUpOnce();
			dm->m_win32PerfFormatProc->Cleanup();
			dm->m_win32PerfFormatProc->m_table->clear();
			dm->m_win32PerfFormatProc->m_table->erase(dm->m_win32PerfFormatProc->m_table->begin(), dm->m_win32PerfFormatProc->m_table->end());
			delete dm->m_win32PerfFormatProc->m_table;
			delete dm->m_win32PerfFormatProc->dataObj;

			dm->m_win32OperatingSystem->Cleanup();
			dm->m_win32OperatingSystem->m_table->clear();
			dm->m_win32OperatingSystem->m_table->erase(dm->m_win32OperatingSystem->m_table->begin(), dm->m_win32OperatingSystem->m_table->end());
			delete dm->m_win32OperatingSystem->m_table;
			delete dm->m_win32OperatingSystem->dataObj;
	

			// thread ����
			d->ExitThread();


			// PerfDataManager �Ҹ��� ȣ��
			d->m_perfDataManager->~CPerfDataManager();

			// CResourceMonitorDoc �Ҹ��� ȣ��
			d->~CResourceMonitorDoc();
			CFrameWnd::OnSysCommand(nID, lParam);
		}
	}
	else {
		CFrameWnd::OnSysCommand(nID, lParam);
	}


}


//void CMainFrame::OnSetLogInterval()
//{
//	//CDlgSetLogInterval *pDlg = new CDlgSetLogInterval;
//	//pDlg->Create(IDD_SET_LOG_INTERVAL);
//	//pDlg->ShowWindow(SW_SHOW);
//	CResourceMonitorDoc* doc = (CResourceMonitorDoc*)GetActiveDocument();
//	CDlgSetLogInterval dlg(&(doc->m_logInterval));
//	dlg.DoModal();
//
//	return ;
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//}
//
//
//void CMainFrame::OnLogSetthreshold()
//{
//	CResourceMonitorDoc* doc = (CResourceMonitorDoc*)GetActiveDocument();
//	CDlgSetLogThreshold dlg(&(doc->m_cpuThreshold), &(doc->m_memThreshold));
//	dlg.DoModal();
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//}

void CMainFrame::OnLogSetinterval()
{
	CResourceMonitorDoc* doc = (CResourceMonitorDoc*)GetActiveDocument();
	CDlgSetLogInterval dlg(&(doc->m_logInterval));
	dlg.DoModal();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CMainFrame::OnLogSetthreshold()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CResourceMonitorDoc* doc = (CResourceMonitorDoc*)GetActiveDocument();
	CDlgSetLogThreshold dlg(&(doc->m_cpuThreshold), &(doc->m_memThreshold));
	dlg.DoModal();
}
