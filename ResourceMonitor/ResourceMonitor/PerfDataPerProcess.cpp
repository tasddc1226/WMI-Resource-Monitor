#include "stdafx.h"
#include "PerfDataPerProcess.h"
#include "PerfDataManager.h"
#include "ResourceMonitorDoc.h"

CPerfDataPerProcess::CPerfDataPerProcess()
{
	nCores = GetNumberOfCores();

}


CPerfDataPerProcess::~CPerfDataPerProcess()
{
}

void CPerfDataPerProcess::Init(const PerfDataInfo & info, CResourceMonitorDoc * doc)
{
	m_table = new map<ULONGLONG, PerProcessDataObj>;
	CPerfData::Init(info, doc);
}

void CPerfDataPerProcess::GetData()
{
	PerProcessDataObj obj;
	obj.flag = true;
	ULONGLONG ID;
	VARIANT propertyVal;

	CPerfData::Refresh();

	for (unsigned int i = 0; i < dwNumReturned; i++)
	{
		for (size_t j = 0; j < m_nProps; ++j)
		{

			if (FAILED(hr = apEnumAccess[i]->Get(propertyNames[j], 0, &propertyVal,0, 0)))
			{
				Cleanup();
				break;
			}
			switch (j)
			{
			case PROCESS_ID_INDEX:
				ID = propertyVal.ullVal;
				break;
			case PROCESS_NAME_INDEX:
				obj.name = propertyVal.bstrVal ;
				break;
			case PROCESS_WORKINGSET_INDEX:
				obj.workingSet = propertyVal.bstrVal;
				break;
			case PROCESS_USEAGERATE_INDEX:
				obj.usageRate = propertyVal.bstrVal;
				break;
			case PROCESS_IOREAD_INDEX:
				obj.ioRead = propertyVal.bstrVal;
				break;
			case PROCESS_IOWRITE_INDEX:
				obj.ioWrite = propertyVal.bstrVal;
				break;
			default:
				break;
			}
			VariantClear(&propertyVal);

		}
		//(*table)[propertyVal[m_idIndex].bstrVal] = obj;
		//(table->empty()) && 
		usingPercent = _wtoi64(obj.usageRate);
		if ((obj.name.Compare(_T("Idle")) == 0))
		{
			idlePercent = _wtoi64(obj.usageRate);
		}
		if (obj.name.Compare(_T("_Total")) == 0)
		{
			usingPercent = abs(_wtoi64(obj.usageRate) - idlePercent);
		}
		usingPercent = (usingPercent / nCores);
		//SysFreeString(obj.usageRate);
		obj.usageRate.Format(_T("%.02f"), usingPercent) ;

		(*m_table)[ID] = obj;


		//clear obj & apEnumAccess
		obj.Clear();
		apEnumAccess[i]->Release();
		apEnumAccess[i] = nullptr;
	}

	//false�� ã��
	for (auto iter = m_table->begin(); iter != m_table->end(); iter++)
	{
		if (iter->second.flag == false)
		{
			exitedProcIDs.push_back(iter->first);
		}
	}
	//false�ξ� �����ְ� 
	for (auto iter = exitedProcIDs.begin(); iter != exitedProcIDs.end(); iter++)
	{
		m_table->erase(*iter);
	}
	if (exitedProcIDs.size() > 0)
	{
		m_pDoc->AtExitProcess(&exitedProcIDs);
	}

	//table�� �� false�� �ٲ�
	for (auto iter = m_table->begin(); iter != m_table->end(); iter++)
	{		
		iter->second.flag = false;
	}

	if (nullptr != apEnumAccess)
	{
		delete[] apEnumAccess;
		apEnumAccess = nullptr;
	}

	// clear exitedProcIDs
	vector<ULONGLONG>().swap(exitedProcIDs);
	exitedProcIDs.clear();

}
int CPerfDataPerProcess::GetNumberOfCores()
{
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION pProcessorInformations = NULL;
	DWORD length = 0;

	BOOL result = GetLogicalProcessorInformation(pProcessorInformations, &length);
	if (!result)
	{
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)

		{
			pProcessorInformations = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)new BYTE[length];
		}
	}
	result = GetLogicalProcessorInformation(pProcessorInformations, &length);
	if (!result)
	{		// er
		return -1;

	}
	int numOfCores = 0;
	for (int i = 0; i < length / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); i++)

	{
		if (pProcessorInformations[i].Relationship == RelationProcessorCore)

			numOfCores++;
	}
	delete[] pProcessorInformations;
	pProcessorInformations = nullptr;

	return numOfCores;
}

