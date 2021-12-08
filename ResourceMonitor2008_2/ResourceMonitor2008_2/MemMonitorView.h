#pragma once

#include "ResourceMonitorView.h"
// CMemMonitorView ���Դϴ�.

class CMemMonitorView : public CResourceMonitorView
{


public:
	DECLARE_DYNCREATE(CMemMonitorView)
	CMemMonitorView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMemMonitorView();

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


