#pragma once


#include "ResourceMonitorView.h"
#include "AdvComboBox.h"
#include "AdvListCtrl.h"

// CDiskMonitorView ���Դϴ�.

class CDiskMonitorView : public CResourceMonitorView
{
public:
	DECLARE_DYNCREATE(CDiskMonitorView)
	CDiskMonitorView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CDiskMonitorView();

	virtual void UpdateView(class CPerfDataManager* dataManager);
	virtual void AddPeriodicLog();


protected:
	virtual void OnInitialUpdate();     // ������ �� ó���Դϴ�.
	virtual void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
};


