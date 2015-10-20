#ifndef __MARKET_API_H__
#define __MARKET_API_H__

#include <cstdio>
#include <windows.h>

#include "ThostFtdcMdApi.h"
#include "AssistApi.h"

/* 行情数据类 */
class CMarketData
{
public:
    CMarketData();
    ~CMarketData();

public:
    /* 更新行情数据 */
    void UpdateMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
    /* 等待行情数据 */
    BOOL WaitMarketData(void);
    /* 获取更新周期 */
    int  GetTickPeriod(void);
private:
    /* 更新周期类型 */
    typedef enum
    {
        E_TICK_PERIOD_MS, /* 毫秒 */
        E_TICK_PERIOD_SEC, /* 秒 */
        E_TICK_PERIOD_MIN, /* 分 */
        E_TICK_PERIOD_HOUR, /* 时 */
        E_TICK_PERIOD_COUNT
    }E_TICK_PERIOD_TYPE;
    /* 设置更新周期 */
    void SetUpdatePeriod(E_TICK_PERIOD_TYPE type = E_TICK_PERIOD_MS);
    int m_nTickCnt; /* 更新个数 */
    int m_nTickPeriod; /* 更新周期 */
    LONGLONG m_nLastMs; /* 上次时间 */
    CEvent   m_event;

public:
    TThostFtdcInstrumentIDType   m_szInstrumentID; /* 合约代码 */
    TThostFtdcExchangeIDType     m_szExchangeID; /* 交易所代码 */
    TThostFtdcExchangeInstIDType m_szExchangeInstID; /* 交易所合约代码 */
    TThostFtdcPriceType          m_fLastPrice; /* 最新价 */
    TThostFtdcPriceType          m_fPreSettlementPrice; /* 昨结算价 */
    TThostFtdcPriceType	         m_fPreClosePrice; /* 昨收价 */
    TThostFtdcLargeVolumeType	 m_fPreOpenInterest; /* 昨持仓 */
    TThostFtdcPriceType	         m_fSettlementPrice; /* 今结算价 */
    TThostFtdcPriceType          m_fOpenPrice;  /* 今开价 */
    TThostFtdcPriceType          m_fClosePrice; /* 今收价 */
    TThostFtdcPriceType          m_fHighestPrice; /* 最高价 */
    TThostFtdcPriceType          m_fLowestPrice; /* 最低价 */
    TThostFtdcVolumeType	     m_nVolume; /* 成交量 */
    TThostFtdcMoneyType	         m_fTurnover; /* 成交额 */
    TThostFtdcLargeVolumeType	 m_fOpenInterest; /* 持仓量 */
    TThostFtdcPriceType          m_fUpperLimitPrice; /* 涨停价 */
    TThostFtdcPriceType          m_fLowerLimitPrice; /* 跌停价 */
    BOOL                         m_bUpperTrend; /* 是否上涨 */
};

/* 行情响应类 */
class CMarketSpi : public CThostFtdcMdSpi
{
public:
    CMarketSpi(void);
    ~CMarketSpi(void);

    /* 通知类 */
public:
    /* 连接通知 */
    virtual void OnFrontConnected();
    /* 断开通知 */
    virtual void OnFrontDisconnected(int nReason);
    /* 心跳通知 */
    virtual void OnHeartBeatWarning(int nTimeLapse);
    /* 行情通知 */
    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
    /* 询价通知 */
    virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

    /* 错误类 */
public:
    /* 错误响应 */
    virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    /* 响应类 */
public:
    /* 登录响应 */
    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 注销响应 */
    virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 订阅行情响应 */
    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 取消行情响应 */
    virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 订阅询价响应 */
    virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 取消询价响应 */
    virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
};

/* 行情执行类 */
class CMarketApi
{
    /* 操作类 */
public:
    /* 登录操作 */
    void Login(void);
    /* 注销操作 */
    void Logout(void);
    /* 订阅行情操作 */
    void SubMarket(void);
    /* 取消行情操作 */
    void UnSubMarket(void);
    /* 订阅询价操作 */
    void SubQuote(void);
    /* 取消询价操作 */
    void UnSubQuote(void);

public:
    typedef enum
    {
        E_OPER_DEFAULT,
        E_OPER_LOGIN,
        E_OPER_LOGOUT,
        E_OPER_SUB_MARKET,
        E_OPER_UNSUB_MARKET,
        E_OPER_SUB_QUOTE,
        E_OPER_UNSUB_QUOTE,
        E_OPER_TYPE_COUNT
    }E_OPER_TYPE;
private:
    static const char *oper_name[E_OPER_TYPE_COUNT];
    static int oper_count;

public:
    CThostFtdcMdApi  *m_api; /* 执行类实例 */
    CThostFtdcMdSpi  *m_spi; /* 响应类实例 */
    CConfigInfo       m_cfg; /* 配置信息 */
    CMarketData       m_data; /* 行情数据 */
    BOOL m_bConnect;
    BOOL m_bLogin;
    BOOL m_bHaveCli;

public:
    /* 启动 */
    void Start(void);
    /* 停止 */
    void Stop(void);
    /* 操作 */
    void Operation(void);

public:
    BOOL IsRunning(void);
private:
    BOOL  m_bRunning;

private:
    static DWORD WINAPI ThreadProc(LPVOID lpParam);
    HANDLE  m_hThread;

public:
    static CMarketApi *CreateInstance(void);
    static void ReleaseInstance(void);
    static CMarketApi *GetInstance(void);
private:
    CMarketApi(void);
    ~CMarketApi(void);
    static CMarketApi *m_pInstance;
    class CSelfRelease
    {
    public:
        CSelfRelease();
        ~CSelfRelease();
    };
    static CSelfRelease  m_self;
};

#endif /* __MARKET_API_H__ */