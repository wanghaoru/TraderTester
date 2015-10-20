#include <cstring>
#include "AssistApi.h"

#pragma warning(disable:4996)

CConfigInfo::CConfigInfo(void)
{
    memset(&m_szTraderAddr, 0, sizeof(m_szTraderAddr));
    memset(&m_szMarketAddr, 0, sizeof(m_szMarketAddr));
    memset(&m_szBrokerID, 0, sizeof(m_szBrokerID));
    memset(&m_szInvestorID, 0, sizeof(m_szInvestorID));
    memset(&m_szUserID, 0, sizeof(m_szUserID));
    memset(&m_szUserProductInfo, 0, sizeof(m_szUserProductInfo));
    memset(&m_szPassword, 0, sizeof(m_szPassword));
    memset(&m_szAuthCode, 0, sizeof(m_szAuthCode));
    memset(&m_nFrontID, 0, sizeof(m_nFrontID));
    memset(&m_nSessionID, 0, sizeof(m_nSessionID));
    memset(&m_nRequestID, 0, sizeof(m_nRequestID));
    memset(&m_szMaxOrderRef, 0, sizeof(m_szMaxOrderRef));
    memset(&m_szOrderRef, 0, sizeof(m_szOrderRef));
    memset(&m_szInstrumentID, 0, sizeof(m_szInstrumentID));
    memset(&m_szInstrumentName, 0, sizeof(m_szInstrumentName));
    memset(&m_szExchangeID, 0, sizeof(m_szExchangeID));
    memset(&m_szExchangeInstID, 0, sizeof(m_szExchangeInstID));

    char *szFrontAddr = "tcp://180.168.146.187:10000";
    strcpy(m_szTraderAddr, szFrontAddr);
    szFrontAddr = "tcp://180.168.146.187:10010";
    strcpy(m_szMarketAddr, szFrontAddr);
    char *szBrokerID = "9999";
    strcpy(m_szBrokerID, szBrokerID);
    char *szInvestorID = "036645";
    strcpy(m_szInvestorID, szInvestorID);
    char *szUserID = "036645";
    strcpy(m_szUserID, szUserID);
    char *szUserProductInfo = "TraderTester";
    strcpy(m_szUserProductInfo, szUserProductInfo);
    char *szPassword = "20034711";
    strcpy(m_szPassword, szPassword);
    char *szAuthCode = "1234";
    strcpy(m_szAuthCode, szAuthCode);
    char *szInstrumentID = "cu1601";
    strcpy(m_szInstrumentID, szInstrumentID);
}

CConfigInfo::~CConfigInfo(void)
{
}

LONGLONG CClock::freq = 0;

CClock::CClock()
{
    counter = 0;
    if (!freq)
    {
        LARGE_INTEGER temp;
        if (TRUE!=QueryPerformanceFrequency(&temp))
        {
            return;
        }
        freq = temp.QuadPart;
    }
}

CClock::~CClock()
{

}

double CClock::GetClockTime()
{
    if (freq)
    {
        LARGE_INTEGER temp;
        if (TRUE!=QueryPerformanceCounter(&temp))
        {
            return 0;
        }
        counter = temp.QuadPart;
        return (double)(counter/freq*1000000);
    }
    return 0;
}

CLock::CLock() : m_hLock(NULL)
{
    m_hLock = ::CreateMutex(NULL, FALSE, NULL);
}

CLock::~CLock()
{
    if (m_hLock)
    {
        ::CloseHandle(m_hLock);
        m_hLock = NULL;
    }
}

BOOL CLock::Lock(void)
{
    if (!m_hLock)
    {
        return FALSE;   
    }
    ::WaitForSingleObject(m_hLock, INFINITE);
    return TRUE;
}

BOOL CLock::UnLock(void)
{
    if (!m_hLock)
    {
        return FALSE;
    }
    return ::ReleaseMutex(m_hLock);
}

CEvent::CEvent() : m_hEvent(NULL)
{
    m_hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
}

CEvent::~CEvent()
{
    if (m_hEvent)
    {
        ::CloseHandle(m_hEvent);
        m_hEvent = NULL;
    }
}

BOOL CEvent::Wait(void)
{
    if (!m_hEvent)
    {
        return FALSE;   
    }
    ::WaitForSingleObject(m_hEvent, INFINITE);
    return TRUE;
}

BOOL CEvent::Wake(void)
{
    if (!m_hEvent)
    {
        return FALSE;   
    }
    ::SetEvent(m_hEvent);
    return TRUE;
}

CPrintApi *CPrintApi::m_pInstance = NULL;

CPrintApi::CPrintApi(void) : m_hDbgFile(NULL), m_bDbgPrint(FALSE), m_bDbgCliPrint(FALSE), m_hLogFile(NULL), m_bLogPrint(FALSE)
{
    m_lock.Lock();

    /* 打开控制台 */
    if(AllocConsole())
    {
        freopen("CONOUT$", "w", stdout);
    }

    /* 打开调试文件 */
    m_hDbgFile = fopen("TraderTesterDbg.txt", "w");

    /* 打开日志文件 */
    m_hLogFile = fopen("TraderTesterLog.txt", "w");

    m_lock.UnLock();
}

CPrintApi::~CPrintApi(void)
{   
    m_lock.Lock();

    /* 关闭日志文件 */
    if (m_hLogFile)
    {
        fclose(m_hLogFile);
        m_hLogFile = NULL;
    }

    /* 关闭调试文件 */
    if (m_hDbgFile)
    {
        fclose(m_hDbgFile);
        m_hDbgFile = NULL;
    }

    /* 关闭控制台 */
    FreeConsole();

    m_lock.UnLock();
}

void CPrintApi::AppPrint(const char *format, ...)
{
    CPrintApi *api = CPrintApi::GetInstance();
    if (api->m_lock.Lock())
    {
        va_list arg_list;
        char szBuf[BUFSIZ];
        va_start(arg_list, format);
        vsnprintf(szBuf, BUFSIZ, format, arg_list);
        va_end(arg_list);
        if (stdout)
        {
            fprintf(stdout, "%s", szBuf);
            fflush(stdout);
        }
        api->m_lock.UnLock();
    }
}

void CPrintApi::DbgPrint(const char *format, ...)
{
    CPrintApi *api = CPrintApi::GetInstance();
    if (!api->m_bDbgPrint)
        return;
    if (api->m_lock.Lock())
    {
        va_list arg_list;
        char szBuf[BUFSIZ];
        va_start(arg_list, format);
        vsnprintf(szBuf, BUFSIZ, format, arg_list);
        va_end(arg_list);
        if (api->m_bDbgCliPrint)
        {
            if (stdout)
            {
                fprintf(stdout, "%s\n", szBuf);
                fflush(stdout);
            }
        }
        if (api->m_hDbgFile)
        {
            fprintf(api->m_hDbgFile, "%s\n", szBuf);
            fflush(api->m_hDbgFile);
        }
        api->m_lock.UnLock();
    }
}

void CPrintApi::LogPrint(const char *format, ...)
{
    CPrintApi *api = CPrintApi::GetInstance();
    if (!api->m_bLogPrint)
        return;
    if (api->m_lock.Lock())
    {
        va_list arg_list;
        char szBuf[BUFSIZ];
        va_start(arg_list, format);
        vsnprintf(szBuf, BUFSIZ, format, arg_list);
        va_end(arg_list);
        if (stdout)
        {
            fprintf(stdout, "%s\n", szBuf);
            fflush(stdout);
        }
        if (api->m_hLogFile)
        {
            fprintf(api->m_hLogFile, "%s\n", szBuf);
            fflush(api->m_hLogFile);
        }
        api->m_lock.UnLock();
    }
}

CPrintApi *CPrintApi::GetInstance(void)
{
    if (!m_pInstance)
    {
        m_pInstance = new CPrintApi();
        m_pInstance->m_bDbgPrint = TRUE;
        m_pInstance->m_bDbgCliPrint = FALSE;
        m_pInstance->m_bLogPrint = TRUE;
    }
    return m_pInstance;
}

CTrigger::CTrigger(int nRequestID, char *szFuncName, double fTriggerTime, int nTriggerStage)
{
    m_nRequestID = nRequestID;
    m_szFuncName = szFuncName;
    m_fTriggerTime = fTriggerTime;
    m_nTriggerStage = nTriggerStage;
}

CTrigger::CTrigger(CTrigger *trigger)
{
    m_nRequestID = trigger->m_nRequestID;
    m_szFuncName = trigger->m_szFuncName;
    m_fTriggerTime = trigger->m_fTriggerTime;
    m_nTriggerStage = trigger->m_nTriggerStage;
}

CTrigger::~CTrigger(void)
{

}

CTriggerList::CTriggerList() : m_nRequestID(0), m_bIsComplete(FALSE)
{
}

CTriggerList::~CTriggerList()
{
    CTrigger *trigger = NULL;

    /* 清空内存 */
    if (m_vector.size())
    {
        vector<CTrigger *>::iterator iter;
        for (iter=m_vector.begin(); iter!=m_vector.end(); iter++)
        {
            trigger = *iter;
            delete trigger;
        }
        m_vector.clear();
    }
}

void CTriggerList::AddTrigger(CTrigger *trigger)
{
    m_nRequestID = trigger->m_nRequestID;
    CTrigger *new_trigger = new CTrigger(trigger);
    m_vector.push_back(new_trigger);
    //if (new_trigger->m_nTriggerStage == 2)
        m_bIsComplete = TRUE;
}

BOOL CTriggerList::IsComplete(void)
{
    return m_bIsComplete;
}

void CTriggerList::PrintLog(void)
{
    CTrigger *trigger;
    vector<CTrigger *>::iterator iter;
    CPrintApi::LogPrint("m_nRequestID=%u, ", m_nRequestID);
    for (iter=m_vector.begin(); iter!=m_vector.end(); iter++)
    {
        trigger = *iter;
        CPrintApi::LogPrint("m_szFuncName=%s, m_fTriggerTime=%f, m_nTriggerStage=%u", trigger->m_szFuncName, trigger->m_fTriggerTime, trigger->m_nTriggerStage);
    }
}

/* 启动 */
void CTriggerLogApi::Start(void)
{
    if (!m_bRunning)
    {
        m_hThread = ::CreateThread(NULL, 0, ThreadProc, this, 0, NULL);
        if (m_hThread)
        {
            m_bRunning = TRUE;
        }
    }
}

/* 停止 */
void CTriggerLogApi::Stop(void)
{
    if (m_bRunning)
    {
        m_bRunning = FALSE;
        m_event.Wake();
        ::WaitForSingleObject(m_hThread, INFINITE);
        ::CloseHandle(m_hThread);
        m_hThread = NULL;
    }
}

/* 触发 */
void CTriggerLogApi::Trigger(int nReqeustID, char *szFuncName, int nStage)
{
    CTriggerLogApi *api = CTriggerLogApi::GetInstance();
    if (api->m_bRunning)
    {
        CClock clock;
        CTrigger *trigger = new CTrigger(nReqeustID, szFuncName, clock.GetClockTime(), nStage);
        api->m_triggerQueue.push(trigger);
        api->m_event.Wake();
    }
}

/* 处理 */
void CTriggerLogApi::Process(void)
{
    if (!m_event.Wait())
        return;
    CTrigger     *trigger = NULL;
    CTriggerList *triggerList = NULL;
    while (!m_triggerQueue.empty())
    {
        trigger = m_triggerQueue.front();
        map<int, CTriggerList *>::iterator iter;
        iter = m_trigerListMap.find(trigger->m_nRequestID);
        if (iter==m_trigerListMap.end())
        {
            triggerList = new CTriggerList;
            triggerList->AddTrigger(trigger);
            m_trigerListMap[trigger->m_nRequestID] = triggerList;
            iter = m_trigerListMap.find(trigger->m_nRequestID);
        }
        else
        {
            triggerList = iter->second;
            triggerList->AddTrigger(trigger);
        }
        if (triggerList->IsComplete())
        {
            triggerList->PrintLog();
            m_trigerListMap.erase(iter);
            delete triggerList;
        }
        m_triggerQueue.pop();
        delete trigger;
    }
}

BOOL CTriggerLogApi::IsRunning(void)
{
    return m_bRunning;
}

DWORD CTriggerLogApi::ThreadProc(LPVOID lpParam)
{
    CTriggerLogApi *api = (CTriggerLogApi *)lpParam;
    if (!api)
        return -1;

    /* 处理队列 */
    while (api->IsRunning())
    {
        api->Process();
    }

    return 0;
}

CTriggerLogApi *CTriggerLogApi::m_pInstance = NULL;

CTriggerLogApi *CTriggerLogApi::GetInstance(void)
{
    if (!m_pInstance)
    {
        m_pInstance = new CTriggerLogApi();
    }
    return m_pInstance;
}

CTriggerLogApi::CTriggerLogApi(void) : m_hThread(NULL), m_bRunning(FALSE)
{
}

CTriggerLogApi::~CTriggerLogApi(void)
{
    CTrigger      *trigger = NULL;
    CTriggerList  *triggerList = NULL;

    /* 停止监视 */
    Stop();

    /* 清空队列 */
    while (!m_triggerQueue.empty())
    {
        trigger = m_triggerQueue.front();
        m_triggerQueue.pop();
        delete trigger;
    }

    /* 清空映射 */
    map<int, CTriggerList *>::iterator iter;
    for (iter=m_trigerListMap.begin(); iter!=m_trigerListMap.end(); iter++)
    {
        triggerList = iter->second;
        delete triggerList;
    }
    m_trigerListMap.clear();
}

CTriggerLogApi::CSelfRelease CTriggerLogApi::m_self;

CTriggerLogApi::CSelfRelease::CSelfRelease()
{

}
CTriggerLogApi::CSelfRelease::~CSelfRelease()
{
    if(CTriggerLogApi::m_pInstance)
        delete CTriggerLogApi::m_pInstance;
    CTriggerLogApi::m_pInstance = NULL;
}

#ifdef _DEBUG

/* 检查函数名称 */
void CheckFuncName(const char *szFuncName)
{
    CPrintApi::DbgPrint("\n");
    CPrintApi::DbgPrint("-----------------------------------------------------------------------------");
    if (szFuncName)
    {
        CPrintApi::DbgPrint("----函数: %s", szFuncName);
    }
}

/* 检查错误信息 */
BOOL CheckOnErrRtnInfo(const char *szFuncName, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintApi::DbgPrint("\n");
    CPrintApi::DbgPrint("-----------------------------------------------------------------------------");
    if (szFuncName)
    {
        CPrintApi::DbgPrint("----函数: %s", szFuncName);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
    if (!pRspInfo || pRspInfo->ErrorID)
        return FALSE;
    return TRUE;
}

/* 检查响应信息 */
BOOL CheckOnRspInfo(const char *szFuncName, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintApi::DbgPrint("\n");
    CPrintApi::DbgPrint("-----------------------------------------------------------------------------");
    if (szFuncName)
    {
        CPrintApi::DbgPrint("----函数: %s", szFuncName);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
    CPrintApi::DbgPrint("----参数: nRequestID=%08d", nRequestID);
    CPrintApi::DbgPrint("----参数: bIsLast=%08d", bIsLast);
    if (!pRspInfo || pRspInfo->ErrorID)
        return FALSE;
    return TRUE;
}

#else

/* 检查函数名称 */
void CheckFuncName(void)
{

}

/* 检查错误信息 */
BOOL CheckOnErrRtnInfo(CThostFtdcRspInfoField *pRspInfo)
{
    if (!pRspInfo || pRspInfo->ErrorID)
        return FALSE;
    return TRUE;
}

/* 检查响应信息 */
BOOL CheckOnRspInfo(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (!pRspInfo || pRspInfo->ErrorID)
        return FALSE;
    return TRUE;
}

#endif