#pragma once
#include "afxwin.h"


// CDlgSetLogInterval ��ȭ �����Դϴ�.

class CDlgSetLogInterval : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetLogInterval)

public:
	CDlgSetLogInterval(int *n);
	CDlgSetLogInterval(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgSetLogInterval();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SET_LOG_INTERVAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CEdit m_editInterval;
	int *interval;
};
