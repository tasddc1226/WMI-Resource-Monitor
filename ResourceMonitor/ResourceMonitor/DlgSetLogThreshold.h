#pragma once
#include "afxwin.h"


// CDlgSetLogThreshold ��ȭ �����Դϴ�.

class CDlgSetLogThreshold : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetLogThreshold)

public:
	CDlgSetLogThreshold(float * cpu, int *mem, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgSetLogThreshold();

	float *cpuThreshold;
	int *memThreshold;
	CEdit m_editCPUThreshold;
	CEdit m_editMemThreshold;

	afx_msg void OnLogSetThreshold();
	afx_msg void OnBnClickedOk();

	virtual BOOL OnInitDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SET_THRESHOLD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	
};
