#pragma once


// CDlgSetLogInterval ��ȭ ����

class CDlgSetLogInterval : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetLogInterval)

public:
	CDlgSetLogInterval(int *n, CWnd* pParent = nullptr);   // ǥ�� �������Դϴ�.

	virtual ~CDlgSetLogInterval();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SET_LOG_INTERVAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editInterval;
	int *interval;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
