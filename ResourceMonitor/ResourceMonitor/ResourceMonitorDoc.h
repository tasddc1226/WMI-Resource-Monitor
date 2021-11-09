
// ResourceMonitorDoc.h : CResourceMonitorDoc Ŭ������ �������̽�
//


#pragma once
#include "Logger.h"
#include "Logger_Base.h"
#include <vector>
#include <thread>

using namespace std;

class CPerfDataManager;
static CLogger m_Logger;
static CLogger_Base m_LoggerBase;
class CResourceMonitorDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CResourceMonitorDoc();
	DECLARE_DYNCREATE(CResourceMonitorDoc)

// Ư���Դϴ�.
public:
	CPerfDataManager* m_perfDataManager;
	CWinThread* m_updaterThread;
	CWinThread* m_loggerThread;
	BOOL m_isExit = FALSE;
// �۾��Դϴ�.
public:
	static UINT Update(LPVOID);
	static UINT AddPeriodicLog(LPVOID doc);
	void AtExitProcess(std::vector<ULONGLONG>* exitedProcIDs);
	void ExitThread();
// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CResourceMonitorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

void AddLog(CLogger::LogDirectory nflag, LPCTSTR lpszFormat, ...);
