
// ResourceMonitor.h : ResourceMonitor ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CResourceMonitorApp:
// �� Ŭ������ ������ ���ؼ��� ResourceMonitor.cpp�� �����Ͻʽÿ�.
//

class CResourceMonitorApp : public CWinApp
{
public:
	CResourceMonitorApp();

	CSingleDocTemplate* pDocTemplate;

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CResourceMonitorApp theApp;
