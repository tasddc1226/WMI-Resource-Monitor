#pragma once
#include "afxwin.h"


// CDlgSetLogThreshold ��ȭ �����Դϴ�.

class CDlgSetLogThreshold : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetLogThreshold)

public:
	CDlgSetLogThreshold(float *cpu, int *mem);   // ǥ�� �������Դϴ�.
	CDlgSetLogThreshold(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgSetLogThreshold();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SET_THRESHOLD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editCPUThreshold;
	CEdit m_editMemThreshold;
	float *cpuThreshold;
	int *memThreshold;
	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
