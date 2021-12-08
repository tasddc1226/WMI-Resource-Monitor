// DlgSetLogThreshold.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ResourceMonitor2008_2.h"
#include "DlgSetLogThreshold.h"


// CDlgSetLogThreshold ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgSetLogThreshold, CDialog)


CDlgSetLogThreshold::CDlgSetLogThreshold(float *cpu, int *mem)
	: CDialog(CDlgSetLogThreshold::IDD, NULL)
{
	cpuThreshold = cpu;
	memThreshold = mem;
}

CDlgSetLogThreshold::CDlgSetLogThreshold(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetLogThreshold::IDD, pParent)
{

}

CDlgSetLogThreshold::~CDlgSetLogThreshold()
{
}

void CDlgSetLogThreshold::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CPU, m_editCPUThreshold);
	DDX_Control(pDX, IDC_EDIT_MEM, m_editMemThreshold);
}


BEGIN_MESSAGE_MAP(CDlgSetLogThreshold, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgSetLogThreshold::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSetLogThreshold �޽��� ó�����Դϴ�.

BOOL CDlgSetLogThreshold::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CString str;
	str.Format(_T("%.2f"), *cpuThreshold);
	m_editCPUThreshold.SetWindowTextW(str);
	str.Format(_T("%d"), (*memThreshold) / 1024);
	m_editMemThreshold.SetWindowTextW(str);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDlgSetLogThreshold::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strCPU;
	CString strMem;

	m_editCPUThreshold.GetWindowTextW(strCPU);
	m_editMemThreshold.GetWindowTextW(strMem);

	*cpuThreshold = _wtof(strCPU);
	*memThreshold = _wtoi(strMem) * 1024;
	OnOK();
}
