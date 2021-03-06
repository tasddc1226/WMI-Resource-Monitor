#pragma once

#include "ResourceMonitorView.h"
// CCPUMonitorView 뷰입니다.

class CCPUMonitorView : public CResourceMonitorView
{

public:
	DECLARE_DYNCREATE(CCPUMonitorView)
	CCPUMonitorView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CCPUMonitorView();

	virtual void UpdateView(class CPerfDataManager* dataManager);
	virtual void AddPeriodicLog();

protected:
	virtual void OnInitialUpdate();     // 생성된 후 처음입니다.
	DECLARE_MESSAGE_MAP()

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
};


