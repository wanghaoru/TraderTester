#ifndef __ASSIST_API_H__
#define __ASSIST_API_H__

#include <cstdio>
#include <windows.h>
#include <vector>
#include <queue>
#include <map>
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"

using namespace std;

/* 配置信息类 */
class CConfigInfo
{
public:
    CConfigInfo(void);
    ~CConfigInfo(void);

    /* 网络信息 */
public:
    char                        m_szTraderAddr[256]; /* 交易前置地址 */
    char                        m_szMarketAddr[256]; /* 行情前置地址 */

    /* 认证信息 */
public:
    TThostFtdcBrokerIDType      m_szBrokerID; /* 经纪公司代码 */
    TThostFtdcInvestorIDType    m_szInvestorID; /* 投资者代码 */
    TThostFtdcUserIDType        m_szUserID; /* 用户代码 */
    TThostFtdcPasswordType      m_szPassword; /* 用户密码 */
    TThostFtdcProductInfoType   m_szUserProductInfo; /* 用户产品信息 */
    TThostFtdcAuthCodeType      m_szAuthCode; /* 认证码 */

    /* 会话信息 */
public:
    TThostFtdcFrontIDType       m_nFrontID; /* 前置编号 */
    TThostFtdcSessionIDType     m_nSessionID; /* 会话编号 */
    int                         m_nRequestID; /* 请求编号 */

    /* 报单信息 */
public:
    TThostFtdcOrderRefType      m_szMaxOrderRef;/* 最大报单引用 */
    TThostFtdcOrderRefType	    m_szOrderRef; /* 报单引用 */

    /* 合约信息 */
public:
    TThostFtdcInstrumentIDType   m_szInstrumentID; /* 合约代码 */
    TThostFtdcInstrumentNameType m_szInstrumentName; /* 合约名称 */
    TThostFtdcExchangeIDType     m_szExchangeID; /* 交易所代码 */
    TThostFtdcExchangeInstIDType m_szExchangeInstID; /* 交易所合约代码 */
};

/* 时钟类 */
class CClock
{
public:
    CClock();
    ~CClock();

public:
    double GetClockTime();

private:
    LONGLONG         counter;
    static LONGLONG  freq;
};

/* 互斥类 */
class CLock
{
public:
    CLock();
    ~CLock();

public:
    BOOL Lock(void);
    BOOL UnLock(void);

private:
    HANDLE m_hLock;
};

/* 事件类 */
class CEvent
{
public:
    CEvent();
    ~CEvent();

public:
    BOOL Wait(void);
    BOOL Wake(void);

private:
    HANDLE m_hEvent;
};

/* 打印类 */
class CPrintApi
{
public:
    static void AppPrint(const char *format, ...);
    static void DbgPrint(const char *format, ...);
    static void LogPrint(const char *format, ...);

private:
    static CPrintApi *GetInstance(void);
    CPrintApi(void);
    ~CPrintApi(void);
    static CPrintApi *m_pInstance;

private:
    FILE   *m_hDbgFile;
    BOOL    m_bDbgPrint;
    BOOL    m_bDbgCliPrint;
    FILE   *m_hLogFile;
    BOOL    m_bLogPrint;
    CLock   m_lock;
};

/* 触发阶段 */
typedef enum
{
    E_TRIGGER_STAGE_REQ,
    E_TRIGGER_STAGE_RSP,
    E_TRIGGER_STAGE_ERR,
    E_TRIGGER_STAGE_RTN,
    E_TRIGGER_STAGE_COUNT
}E_TRIGGER_STAGE_TYPE;

/* 触发类 */
class CTrigger
{
public:
    CTrigger(int nRequestID, char *szFuncName, double fTriggerTime, int nTriggerStage);
    CTrigger(CTrigger *trigger);
    ~CTrigger(void);

private:
    friend class CTriggerLogApi;
    friend class CTriggerList;
    int     m_nRequestID;
    char   *m_szFuncName;
    double  m_fTriggerTime;
    int     m_nTriggerStage;
};

/* 触发链表 */
class CTriggerList
{
public:
    CTriggerList();
    ~CTriggerList();

public:
    void AddTrigger(CTrigger *trigger);
    BOOL IsComplete(void);
    void PrintLog(void);
private:
    vector<CTrigger *> m_vector;
    int   m_nRequestID;
    BOOL  m_bIsComplete;
};

/* 触发日志 */
class CTriggerLogApi
{
public:
    /* 启动 */
    void Start(void);
    /* 停止 */
    void Stop(void);
    /* 触发 */
    static void Trigger(int nReqeustID, char *szFuncName, int nTriggerStage);
#define TriggerEx(nRequestID, nTriggerStage)       Trigger(nRequestID, __FUNCTION__, nTriggerStage)
    /* 处理 */
    void Process(void);

private:
    queue<CTrigger *>         m_triggerQueue;
    map<int, CTriggerList *>  m_trigerListMap;
    CEvent  m_event;

public:
    BOOL IsRunning(void);
private:
    BOOL  m_bRunning;

private:
    static DWORD WINAPI ThreadProc(LPVOID lpParam);
    HANDLE  m_hThread;

public:
    static CTriggerLogApi *GetInstance(void);
private:
    CTriggerLogApi(void);
    ~CTriggerLogApi(void);
    static CTriggerLogApi *m_pInstance;
    class CSelfRelease
    {
    public:
        CSelfRelease();
        ~CSelfRelease();
    };
    static CSelfRelease  m_self;
};

#ifdef _DEBUG
/* 检查函数名称 */
extern void CheckFuncName(const char *szFuncName);
/* 检查错误信息 */
extern BOOL CheckOnErrRtnInfo(const char *szFuncName, CThostFtdcRspInfoField *pRspInfo);
/* 检查响应信息 */
extern BOOL CheckOnRspInfo(const char *szFuncName, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
#define CheckFuncNameEx()                CheckFuncName((const char *)__FUNCTION__)
#define CheckOnErrRtnInfoEx(x1)          CheckOnErrRtnInfo((const char *)__FUNCTION__, x1)
#define CheckOnRspInfoEx(x1, x2, x3)     CheckOnRspInfo((const char *)__FUNCTION__, x1, x2, x3)
#else
/* 检查函数名称 */
extern void CheckFuncName(void);
/* 检查错误信息 */
extern BOOL CheckOnErrRtnInfo(CThostFtdcRspInfoField *pRspInfo);
/* 检查响应信息 */
extern BOOL CheckOnRspInfo(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
#define CheckFuncNameEx()                CheckFuncName()
#define CheckOnErrRtnInfoEx(x1)          CheckOnErrRtnInfo(x1)
#define CheckOnRspInfoEx(x1, x2, x3)     CheckOnRspInfo(x1, x2, x3)
#endif /* _DEBUG */

#endif /* __ASSIST_API_H__ */