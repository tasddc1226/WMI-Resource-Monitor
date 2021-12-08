#pragma once

#include "ResourceMonitorView.h"
// CCPUMonitorView ���Դϴ�.

class CCPUMonitorView : public CResourceMonitorView
{

public:
	DECLARE_DYNCREATE(CCPUMonitorView)
	CCPUMonitorView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CCPUMonitorView();

	virtual void UpdateView(class CPerfDataManager* dataManager);
	virtual void AddPeriodicLog();

protected:
	virtual void OnInitialUpdate();     // ������ �� ó���Դϴ�.
	DECLARE_MESSAGE_MAP()

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
};


