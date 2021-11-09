// DiskMonitorView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ResourceMonitor.h"
#include "DiskMonitorView.h"
#include "ResourceMonitorDoc.h"
#include "PerfDataManager.h"

// CDiskMonitorView

IMPLEMENT_DYNCREATE(CDiskMonitorView, CResourceMonitorView)

CDiskMonitorView::CDiskMonitorView()
{
	m_title = _T("Disk");
	m_frameCaptions.push_back(_T("Partition: "));
	m_frameCaptions.push_back(_T("Total(MB): "));
	m_frameCaptions.push_back(_T("Using(MB): "));


	m_tableCaptions.push_back(_T("Write(B/s)"));
	m_tableCaptions.push_back(_T("Read(B/s)"));
	m_tableCaptions.push_back(_T("Name"));
	m_tableCaptions.push_back(_T("PID"));
	colCount = 3;
}

CDiskMonitorView::~CDiskMonitorView()
{
}


BEGIN_MESSAGE_MAP(CDiskMonitorView, CResourceMonitorView)
END_MESSAGE_MAP()


// CDiskMonitorView �׸����Դϴ�.

void CDiskMonitorView::OnInitialUpdate()
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

void CDiskMonitorView::UpdateView(CPerfDataManager * dataManager)
{
	CPerfDataPerProcess *perfData = dataManager->m_win32PerfFormatProc;

	map<ULONGLONG, PerProcessDataObj>	*table =perfData->m_table;
	for (auto iter = table->begin(); iter != table->end(); iter++)
	{
		CString id;
		id.Format(_T("%lu"), iter->first);
		CString name;
		name = iter->second.name;
		CString ioRead;
		ioRead = iter->second.ioRead;
		CString ioWrite;
		ioWrite = iter->second.ioWrite;
		LVFINDINFO info;
		int nIndex;
		info.flags = LVFI_STRING;
		info.psz = id;

		if ((nIndex = m_processList.FindItem(&info)) == -1)
		{
			m_processList.InsertItem(0, id);

			m_processList.SetItemText(0, 1, name);
			m_processList.SetItemText(0, 2, ioRead);
			m_processList.SetItemText(0, 3, ioWrite);
		}
		else
		{
			m_processList.SetItemText(nIndex, 1, name);
			m_processList.SetItemText(nIndex, 2, ioRead);
			m_processList.SetItemText(nIndex, 3, ioWrite);
		}
		id.Empty();
		name.Empty();
		ioRead.Empty();
		ioWrite.Empty();
	}


}

void CDiskMonitorView::AddPeriodicLog()
{
}

//void CDiskMonitorView::OnDraw(CDC* pDC)
//{
//	CResourceMonitorDoc* pDoc = GetDocument();
//	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
//
//}


// CDiskMonitorView �����Դϴ�.

#ifdef _DEBUG
void CDiskMonitorView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CDiskMonitorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}


#endif
#endif //_DEBUG


// CDiskMonitorView �޽��� ó�����Դϴ�.
