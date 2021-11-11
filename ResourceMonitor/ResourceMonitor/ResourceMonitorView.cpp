
// ResourceMonitorView.cpp : CResourceMonitorView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ResourceMonitor.h"
#endif
#include "ResourceMonitorDoc.h"
#include "ResourceMonitorView.h"
#include "PerfData.h"
#include <vector>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CResourceMonitorView

//IMPLEMENT_DYNCREATE(CResourceMonitorView, CScrollView)

BEGIN_MESSAGE_MAP(CResourceMonitorView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_SIZE()
	// 3.
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CResourceMonitorView::OnHdnItemclickList1)
END_MESSAGE_MAP()



void CResourceMonitorView::InitTable()
{
	CRect rect;
	GetClientRect(&rect);
	m_processList.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT, CRect(0, FRAME_WIDTH, rect.Width(), rect.Height()), this, 100);
	m_processList.SetColumnWidth(m_tableCaptions.size(), LVSCW_AUTOSIZE_USEHEADER);
	m_processList.SetExtendedStyle(LVS_EX_DOUBLEBUFFER);

	for (auto iter = m_tableCaptions.begin() ; iter != m_tableCaptions.end(); iter++)
	{
		m_processList.InsertColumn(0, *iter, LVCFMT_LEFT, 150, 0);
	}

}
void CResourceMonitorView::InitFrame()
{
	CRect rect;
	GetClientRect(&rect);
	m_farmeList.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT, CRect(0, 0, rect.Width(), FRAME_WIDTH), this, 100);

	m_farmeList.SetExtendedStyle(LVS_EX_DOUBLEBUFFER | LVSICF_NOSCROLL);
	m_farmeList.ShowScrollBar(SB_BOTH, FALSE);

	m_farmeList.InsertColumn(0, m_title, LVCFMT_LEFT, 200, 0);
	int i = 1;
	for (auto iter = m_frameCaptions.begin(); iter != m_frameCaptions.end(); i++, iter++)
	{
		m_farmeList.InsertColumn(i, *iter, LVCFMT_LEFT, 200, 0);
		//m_farmeList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
	m_bInit = true;
}

void CResourceMonitorView::RemoveProcessFromList(vector<ULONGLONG>* exitedProcIDs)
{
	for (auto iter = exitedProcIDs->begin(); iter != exitedProcIDs->end(); iter++)
	{
		LVFINDINFO info;
		int nIndex;
		info.flags = LVFI_STRING;
		CString str;
		str.Format(_T("%llu"), *iter);
		info.psz = str;

		if ((nIndex = m_processList.FindItem(&info)) != -1)
		{
			m_processList.DeleteItem(nIndex);
		}
		str.Empty();
	}


}

// ����Ʈ��Ʈ�� �÷� Ŭ���� ������ ����
void CResourceMonitorView::OnHdnItemclickList1(NMHDR * pNMHDR, LRESULT * pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// Ŭ���� �÷��� �ε���
	int nColumn = pNMLV->iItem;

	// �� ����Ʈ ��Ʈ�ѿ� �ִ� ������ �� �ڷ� ������ŭ ����
	for (int i = 0; i < (m_processList.GetItemCount()); i++)
	{
		m_processList.SetItemData(i, i);
	}

	// ���� ��� ����
	m_bAscending = !m_bAscending;

	// ���� ���� ����ü ���� ���� �� ������ �ʱ�ȭ
	SORTPARAM sortparams;
	sortparams.pList = &m_processList;
	sortparams.iSortColumn = nColumn;
	sortparams.bSortDirect = m_bAscending;
	
	// | 0	|  1   |     2		 |
	// | PID| NAME | USAGE(rate) |

	// PID ����
	if (nColumn == 0)
		sortparams.flag = 0;

	// NAME�� ���ĺ� ����
	if (nColumn == 1)
		sortparams.flag = 1;

	// Usage(rate) ����
	if (nColumn == 2 || nColumn == 3)
		sortparams.flag = 2;

	// ���� �Լ� ȣ��
	m_processList.SortItems(&CompareItem, (LPARAM)&sortparams);
	*pResult = 0;
}

int CResourceMonitorView::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl *pList = ((SORTPARAM*)lParamSort)->pList;
	int iSortColumn = ((SORTPARAM*)lParamSort)->iSortColumn;
	bool bSortDirect = ((SORTPARAM*)lParamSort)->bSortDirect;
	int flag = ((SORTPARAM*)lParamSort)->flag;

	LVFINDINFO info1, info2;
	info1.flags = LVFI_PARAM;
	info1.lParam = lParam1;

	info2.flags = LVFI_PARAM;
	info2.lParam = lParam2;

	int irow1 = pList->FindItem(&info1, -1);
	int irow2 = pList->FindItem(&info2, -1);

	CString strItem1 = pList->GetItemText(irow1, iSortColumn);
	CString strItem2 = pList->GetItemText(irow2, iSortColumn);

	// PID ����
	if (flag == 0)
	{
		int iItem1 = _tstoi(strItem1);
		int iItem2 = _tstoi(strItem2);

		if (bSortDirect)
		{
			return iItem1 == iItem2 ? 0 : iItem1 > iItem2;
		}
		else
		{
			return iItem1 == iItem2 ? 0 : iItem1 < iItem2;
		}
	}
	// NAME ����
	else if (flag == 1)
	{
		return	bSortDirect ? strcmp(LPSTR(LPCTSTR(strItem1)), LPSTR(LPCTSTR(strItem2))) : -strcmp(LPSTR(LPCTSTR(strItem1)), LPSTR(LPCTSTR(strItem2)));
	}
	// RATE ����
	else
	{
		double dItem1 = _wtof(strItem1);
		double dItem2 = _wtof(strItem2);

		if (bSortDirect)
		{
			return dItem1 == dItem2 ? 0 : dItem1 > dItem2;
		}
		else
		{
			return dItem1 == dItem2 ? 0 : dItem1 < dItem2;
		}
	}

	
}




CResourceMonitorView::CResourceMonitorView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

CResourceMonitorView::~CResourceMonitorView()
{
}

BOOL CResourceMonitorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}



// CResourceMonitorView �׸���


void CResourceMonitorView::OnDraw(CDC* pDC)
{
	CResourceMonitorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

}

void CResourceMonitorView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �� ���� ��ü ũ�⸦ ����մϴ�.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);



}


// CResourceMonitorView �μ�

BOOL CResourceMonitorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CResourceMonitorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CResourceMonitorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CResourceMonitorView ����

#ifdef _DEBUG
void CResourceMonitorView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CResourceMonitorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#include "CPUMonitorView.h"
CResourceMonitorDoc* CResourceMonitorView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{

	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CResourceMonitorDoc)));
	return (CResourceMonitorDoc*)m_pDocument;
}
#endif //_DEBUG


// CResourceMonitorView �޽��� ó����


void CResourceMonitorView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);
	if (!m_bInit)
		return;
	m_processList.MoveWindow(0, FRAME_WIDTH, cx, cy-FRAME_WIDTH,TRUE);
	m_farmeList.MoveWindow(0, 0, cx, FRAME_WIDTH, TRUE);
	m_farmeList.ShowScrollBar(SB_BOTH, FALSE);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

}

