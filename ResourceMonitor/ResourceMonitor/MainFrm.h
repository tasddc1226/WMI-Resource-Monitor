
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once


class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
	virtual ~CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnSetLogInterval();
	afx_msg void OnLogSetthreshold();

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CSplitterWnd	  m_wndSplitter;
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

	// ������ �޽��� �� �Լ�	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	
};


