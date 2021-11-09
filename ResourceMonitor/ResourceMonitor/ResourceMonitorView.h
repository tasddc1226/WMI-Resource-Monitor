
// ResourceMonitorView.h : CResourceMonitorView Ŭ������ �������̽�
//

#pragma once
#include <vector>
#include <map>
#include <mutex>

class CLogger;
class CPerfData;
class CResourceMonitorDoc;
class CPerfDataManager;
class CResourceMonitorView :public CScrollView
{
	//DECLARE_DYNCREATE(CResourceMonitorView)
protected:

	// serialization������ ��������ϴ�.
	CResourceMonitorView();
	virtual ~CResourceMonitorView();

	// Ư���Դϴ�.
public:
	bool m_bInit = false;

	CString m_title;
	std::vector<CString> m_frameProps; //frame�� ����� WMI�� �Ӽ� �̸�
	std::vector<CString> m_tableProps; //table�� ����� WMI�� �Ӽ� �̸�
	std::vector<CString> m_frameCaptions;  //ȭ�鿡 ǥ�õ� frame �Ӽ� �̸�
	std::vector<CString> m_tableCaptions;  //ȭ�鿡 ǥ�õ� table �Ӽ� �̸�
	int colCount;
	CListCtrl m_processList;
	CListCtrl m_farmeList;
	std::mutex m;

	// 1.
	BOOL m_bAscending;
	struct SORTPARAM
	{
		int iSortColumn;
		bool bSortDirect;
		CListCtrl *pList;
		int flag = -1;
	};

// �۾��Դϴ�.
public:
	CResourceMonitorDoc* GetDocument() const;

	virtual void UpdateView(CPerfDataManager* dataManager) abstract;
	virtual void AddPeriodicLog()abstract;
	void InitTable();
	void InitFrame();
	void RemoveProcessFromList(std::vector<ULONGLONG>* exitedProcIDs);
	
	// 2.
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	static int CALLBACK CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);


// �������Դϴ�.
public:

	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	

// �����Դϴ�.
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // ResourceMonitorView.cpp�� ����� ����
inline CResourceMonitorDoc* CResourceMonitorView::GetDocument() const
   { return reinterpret_cast<CResourceMonitorDoc*>(m_pDocument); }
#endif

