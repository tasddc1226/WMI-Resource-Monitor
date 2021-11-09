#pragma once


#include "ResourceMonitorView.h"
// CDiskMonitorView ���Դϴ�.

class CDiskMonitorView : public CResourceMonitorView
{
	DECLARE_DYNCREATE(CDiskMonitorView)

protected:
	CDiskMonitorView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CDiskMonitorView();

public:
	virtual void UpdateView(class CPerfDataManager* dataManager);
	virtual void AddPeriodicLog();
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	//virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual void OnInitialUpdate();     // ������ �� ó���Դϴ�.

	DECLARE_MESSAGE_MAP()
};


