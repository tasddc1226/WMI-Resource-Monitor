
// ResourceMonitorDoc.h : CResourceMonitorDoc Ŭ������ �������̽�
//
#pragma once
#include "Logger.h"
#include <vector>
#include <thread>

using namespace std;

class CPerfDataManager;
static CLogger sLogger;

class CResourceMonitorDoc : public CDocument
{
public:
	CResourceMonitorDoc();
	virtual ~CResourceMonitorDoc();

	BOOL m_isExit = FALSE;
	CWinThread* m_updaterThread;
	CWinThread* m_loggerThread;
	CPerfDataManager* m_perfDataManager;
	int m_logInterval = LOG_INTERVAL;
	float m_cpuThreshold = LOG_CPU_THRESHOLD;
	int m_memThreshold = LOG_MEM_THRESHOLD;

	// Thread �Լ�
	static UINT Update(LPVOID);
	static UINT AddPeriodicLog(LPVOID doc);

	// Thread ���� �Լ�
	void ExitThread(); 
	void AtExitProcess(std::vector<ULONGLONG>* exitedProcIDs);

	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

protected: // serialization������ ��������ϴ�.
	DECLARE_DYNCREATE(CResourceMonitorDoc)
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

};
