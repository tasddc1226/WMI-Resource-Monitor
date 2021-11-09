#pragma once

#include "ResourceMonitorView.h"

// CCPUMonitorView ���Դϴ�.

class CCPUMonitorView : public CResourceMonitorView
{
	DECLARE_DYNCREATE(CCPUMonitorView)

protected:
	CCPUMonitorView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CCPUMonitorView();

public:
	//CResourceMonitorDoc* GetDocument() const;
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


