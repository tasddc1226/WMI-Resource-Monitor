
// ResourceMonitorView.h : CResourceMonitorView Ŭ������ �������̽�
//

#pragma once
#include <vector>
#include <map>

using namespace std;

class CLogger;
class CPerfData;
class CResourceMonitorDoc;
class CPerfDataManager;


class CResourceMonitorView :public CScrollView
{
public:
	CResourceMonitorView();
	virtual ~CResourceMonitorView();

	struct SORTPARAM
	{
		int iSortColumn;
		bool bSortDirect;
		CListCtrl *pList;
		int flag = -1;
	};

	BOOL m_bInit = false;
	BOOL m_bAscending; // ����, �������� ���� flag

	CString m_title;
	CListCtrl m_processList;
	CListCtrl m_farmeList;
	vector<CString> m_frameProps;		//frame�� ����� WMI�� �Ӽ� �̸�
	vector<CString> m_tableProps;		//table�� ����� WMI�� �Ӽ� �̸�
	vector<CString> m_frameCaptions;    //ȭ�鿡 ǥ�õ� frame �Ӽ� �̸�
	vector<CString> m_tableCaptions;    //ȭ�鿡 ǥ�õ� table �Ӽ� �̸�


	CResourceMonitorDoc* GetDocument() const;

	void InitTable();
	void InitFrame();
	void RemoveProcessFromList(std::vector<ULONGLONG>* exitedProcIDs);
	
	virtual void UpdateView(CPerfDataManager* dataManager) abstract;
	virtual void AddPeriodicLog() abstract;
	virtual void OnDraw(CDC* pDC);  
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	static int CALLBACK CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort); // ���� ���� �Լ�


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnInitialUpdate(); 
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ResourceMonitorView.cpp�� ����� ����
inline CResourceMonitorDoc* CResourceMonitorView::GetDocument() const
   { return reinterpret_cast<CResourceMonitorDoc*>(m_pDocument); }
#endif

