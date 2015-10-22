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
    TThostFtdcOrderRefType	    m_szOrderRef; /* 期货报单引用 */
    TThostFtdcOrderRefType      m_szExecOrderRef; /* 期权报单引用 */
    TThostFtdcOrderRefType      m_szQuoteRef; /* ??? */

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

/* 参数打印类 */
class CPrintParams
{
public:
    static void PrintFunction(const char *szFuncName);
#define PrintFunctionEx()         PrintFunction((const char *)__FUNCTION__)
    static void PrintParams(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcForQuoteRspField *pForQuoteRsp, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcRspInfoField *pRspInfo);
    static void PrintParams(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo);
    static void PrintParams(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo);
    static void PrintParams(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo);
    static void PrintParams(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo);
    static void PrintParams(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
    static void PrintParams(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);
    static void PrintParams(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo);
    static void PrintParams(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo);
    static void PrintParams(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo);
    static void PrintParams(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo);
    static void PrintParams(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo);
    static void PrintParams(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo);
    static void PrintParams(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo);
    static void PrintParams(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo);
    static void PrintParams(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo = NULL);
    static void PrintParams(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo = NULL);
private:
    static CPrintParams *GetInstance(void);
    CPrintParams(void);
    ~CPrintParams(void);
    static CPrintParams *m_pInstance;
    BOOL   m_bPrintParams;
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

/* 时钟类型 */
typedef struct  
{
    SYSTEMTIME  curTm;  /* 当前时间 */
    time_t      curUs;  /* 当前微秒数 */
    time_t      allUs;  /* 当前总秒数 */
}ClockTime;

/* 获取时钟时间-以微秒计数 */
void GetClockTime(ClockTime *clock);

/* 创建目录 */
BOOL CreateDir(const char *szDir);

/* 字符串转换函数 */
int ConvertTStrToCStr(CHAR *dst,  int dst_size, const TCHAR *src);
int ConvertCStrToTStr(TCHAR *dst, int dst_size, const CHAR  *src);
int ConvertTStrToWStr(WCHAR *dst, int dst_size, const TCHAR *src);
int ConvertWStrToTStr(TCHAR *dst, int dst_size, const WCHAR *src);
int ConvertWStrToCStr(CHAR *dst,  int dst_size, const WCHAR *src);
int ConvertCStrToWStr(WCHAR *dst, int dst_size, const CHAR  *src);

/* 检查响应结果函数 */
BOOL CheckRspInfo(CThostFtdcRspInfoField *pRspInfo);

#endif /* __ASSIST_API_H__ */