// DlgSetLogThreshold.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ResourceMonitor.h"
#include "DlgSetLogThreshold.h"
#include "afxdialogex.h"


// CDlgSetLogThreshold ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgSetLogThreshold, CDialogEx)

CDlgSetLogThreshold::CDlgSetLogThreshold(float * cpu, int *mem, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SET_THRESHOLD, pParent)
{
	cpuThreshold = cpu;
	memThreshold = mem;
}

CDlgSetLogThreshold::~CDlgSetLogThreshold()
{
}



void CDlgSetLogThreshold::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CPU, m_editCPUThreshold);
	DDX_Control(pDX, IDC_EDIT_MEM, m_editMemThreshold);
}


BEGIN_MESSAGE_MAP(CDlgSetLogThreshold, CDialogEx)
	ON_COMMAND(ID_LOG_SETTHRESHOLD, &CDlgSetLogThreshold::OnLogSetThreshold)
	ON_BN_CLICKED(IDOK, &CDlgSetLogThreshold::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSetLogThreshold �޽��� ó�����Դϴ�.


void CDlgSetLogThreshold::OnLogSetThreshold()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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

	CDialogEx::OnOK();
}


BOOL CDlgSetLogThreshold::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CString str;
	str.Format(_T("%.2f"), *cpuThreshold);
	m_editCPUThreshold.SetWindowTextW(str);
	str.Format(_T("%d"), (*memThreshold) / 1024);
	m_editMemThreshold.SetWindowTextW(str);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
