#pragma once


// CDlgSetLogInterval ��ȭ ����

class CDlgSetLogInterval : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetLogInterval)

public:
	CDlgSetLogInterval(int *n, CWnd* pParent = nullptr);   // ǥ�� �������Դϴ�.

	CEdit m_editInterval;
	int *interval;

	virtual BOOL OnInitDialog();
	virtual ~CDlgSetLogInterval();
	afx_msg void OnBnClickedOk();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SET_LOG_INTERVAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	
};
