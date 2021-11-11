
// ResourceMonitorDoc.h : CResourceMonitorDoc 클래스의 인터페이스
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
protected: // serialization에서만 만들어집니다.
	CResourceMonitorDoc();
	DECLARE_DYNCREATE(CResourceMonitorDoc)

// 특성입니다.
public:
	CPerfDataManager* m_perfDataManager;
	// Thread 관련 변수 선언
	CWinThread* m_updaterThread;
	CWinThread* m_loggerThread;
	// Thread 종료 시 TRUE로 변경
	BOOL m_isExit = FALSE;
	int m_logInterval = LOG_INTERVAL;
	float m_cpuThreshold = LOG_CPU_THRESHOLD;
	int m_memThreshold = LOG_MEM_THRESHOLD;
// 작업입니다.
public:
	// Thread 함수
	static UINT Update(LPVOID);
	static UINT AddPeriodicLog(LPVOID doc);

	void AtExitProcess(std::vector<ULONGLONG>* exitedProcIDs);

	// Thread 종료 함수
	void ExitThread();
// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CResourceMonitorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:

};

void AddLog(CLogger::LogDirectory nflag, LPCTSTR lpszFormat, ...);
