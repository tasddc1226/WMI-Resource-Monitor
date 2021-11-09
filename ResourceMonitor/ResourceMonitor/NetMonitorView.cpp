// NetMonitorView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ResourceMonitor.h"
#include "NetMonitorView.h"
#include "ResourceMonitorDoc.h"
#include "PerfDataManager.h"
// CNetMonitorView

IMPLEMENT_DYNCREATE(CNetMonitorView, CResourceMonitorView)

CNetMonitorView::CNetMonitorView()
{
	m_title = _T("Network");
	m_frameCaptions.push_back( _T("Total I/O(KB/s):"));

	m_tableCaptions.push_back(_T("Recv(B/s)"));
	m_tableCaptions.push_back(_T("Send(B/s)"));
	m_tableCaptions.push_back(_T("Name"));
	m_tableCaptions.push_back(_T("PID"));

	colCount = 4;
}

CNetMonitorView::~CNetMonitorView()
{
}


BEGIN_MESSAGE_MAP(CNetMonitorView, CResourceMonitorView)
END_MESSAGE_MAP()


// CNetMonitorView �׸����Դϴ�.

void CNetMonitorView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �� ���� ��ü ũ�⸦ ����մϴ�.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	CResourceMonitorDoc* pDoc = GetDocument();

	InitTable();
	InitFrame();
}
void CNetMonitorView::UpdateView(CPerfDataManager * dataManager)
{
	CPerfDataPerProcess *perfData = dataManager->m_win32PerfFormatProc;

	map<ULONGLONG, PerProcessDataObj>	*table = perfData->m_table;
	for (auto iter = table->begin(); iter != table->end(); iter++)
	{
		CString id;
		id.Format(_T("%lu"), iter->first);
		CString name;
		name = iter->second.name;
		LVFINDINFO info;
		int nIndex;
		info.flags = LVFI_STRING;
		info.psz = id;
		if ((nIndex = m_processList.FindItem(&info)) == -1)
		{
			m_processList.InsertItem(0, id);

			m_processList.SetItemText(0, 1, name);

		}
		else
		{
			m_processList.SetItemText(nIndex, 1, name);
		}
		id.Empty();
		name.Empty();
	}

}
void CNetMonitorView::AddPeriodicLog()
{
}
//void CNetMonitorView::OnDraw(CDC* pDC)
//{
//	CResourceMonitorDoc* pDoc = GetDocument();
//	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
//}


// CNetMonitorView �����Դϴ�.

#ifdef _DEBUG

void CNetMonitorView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CNetMonitorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

#endif
#endif //_DEBUG


// CNetMonitorView �޽��� ó�����Դϴ�.
