// DlgSetLogInterval.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ResourceMonitor2008_2.h"
#include "DlgSetLogInterval.h"


// CDlgSetLogInterval ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgSetLogInterval, CDialog)

CDlgSetLogInterval::CDlgSetLogInterval(int *n)
	: CDialog(CDlgSetLogInterval::IDD, NULL)
{
	interval = n;
}

CDlgSetLogInterval::CDlgSetLogInterval(CWnd* pParent)
	: CDialog(CDlgSetLogInterval::IDD, pParent)
{
}
CDlgSetLogInterval::~CDlgSetLogInterval()
{
}

void CDlgSetLogInterval::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editInterval);
}


BEGIN_MESSAGE_MAP(CDlgSetLogInterval, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgSetLogInterval::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSetLogInterval �޽��� ó�����Դϴ�.

void CDlgSetLogInterval::OnBnClickedOk()
{
	CString str;
	m_editInterval.GetWindowTextW(str);
	*interval = _wtoi(str);
	OnOK();
}

BOOL CDlgSetLogInterval::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CString str;
	str.Format(_T("%d"), *interval);
	m_editInterval.SetWindowTextW(str);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

