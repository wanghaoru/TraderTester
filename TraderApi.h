#ifndef __TRADER_API_H__
#define __TRADER_API_H__

#include <cstdio>
#include <windows.h>

#include "ThostFtdcTraderApi.h"
#include "AssistApi.h"

/* 交易数据类 */
class CTraderData
{
public:
    CTraderData();
    ~CTraderData();

public:
    /* 更新交易数据 */
    void UpdateTraderData(CThostFtdcInputOrderField *pInputOrder, int nTriggerStage);
    void UpdateTraderData(CThostFtdcInputOrderActionField *pInputAction, int nTriggerStage);
    void UpdateTraderData(CThostFtdcOrderActionField *pInputOrder, int nTriggerStage);
    void UpdateTraderData(CThostFtdcOrderField *pOrder, int nTriggerStage);
    void UpdateTraderData(CThostFtdcTradeField *pTrader, int nTriggerStage);

public:
    TThostFtdcBrokerIDType         m_szBrokerID;  /* 经纪公司代码 */
    TThostFtdcInvestorIDType       m_szInvestorID; /* 投资者代码 */
    TThostFtdcExchangeIDType	   m_szExchangeID; /* 交易所代码 */
    TThostFtdcInstrumentIDType     m_szInstrumentID; /* 合约代码 */
    TThostFtdcUserIDType	       m_szUserID; /* 用户代码 */
    TThostFtdcOrderRefType	       m_szOrderRef; /* 报单引用 */
    TThostFtdcOrderActionRefType   m_szOrderActionRef; /* 操作引用 */
    TThostFtdcRequestIDType	       m_nRequestID; /* 请求编号 */
    TThostFtdcFrontIDType	       m_nFrontID; /* 前置编号 */
    TThostFtdcSessionIDType	       m_nSessionID; /* 会话编号 */
    TThostFtdcOrderSysIDType	   m_szOrderSysID; /* 报单编号 */
};

/* 交易响应类 */
class CTraderSpi : public CThostFtdcTraderSpi
{
public:
    CTraderSpi(void);
    ~CTraderSpi(void);

    /* 通知类 */
public:
    /* 连接通知 */
    virtual void OnFrontConnected();
    /* 断开通知 */
    virtual void OnFrontDisconnected(int nReason);
    /* 心跳通知 */
    virtual void OnHeartBeatWarning(int nTimeLapse);
    /* 报单通知 */
    virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);
    /* 执行通知 */
    virtual void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder);
    /* 报价通知 */
    virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote);
    /* 询价通知 */
    virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);
    /* 交易通知 */
    virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo);
    /* 成交通知 */
    virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

    /* 错误类 */
public:
    /* 报单录入错误 */
    virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
    /* 报单操作错误 */
    virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);
    /* 执行录入错误 */
    virtual void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo);
    /* 执行操作错误 */
    virtual void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo);
    /* 报价录入错误 */
    virtual void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo);
    /* 报价操作错误 */
    virtual void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo);
    /* 询价录入错误 */
    virtual void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo);
    /* 错误响应 */
    virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    /* 响应类 */
public:
    /* 认证响应 */
    virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 登录响应 */
    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 注销响应 */
    virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 确认结算响应 */
    virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 报单录入响应 */
    virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 报单操作响应 */
    virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 执行录入响应 */
    virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 执行操作响应 */
    virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 报价录入响应 */
    virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 报价操作响应 */
    virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 询价录入响应 */
    virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    /* 查询类 */
public:
    /* 查询报单响应 */
    virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 查询执行响应 */
    virtual void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 查询报价响应 */
    virtual void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 查询询价响应 */
    virtual void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 查询交易响应 */
    virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 查询成交响应 */
    virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 查询通知响应 */
    virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 查询交易所响应 */
    virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 查询交易编码响应 */
    virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 查询产品响应 */
    virtual void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 查询合约响应 */
    virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 查询行情响应 */
    virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 查询持仓响应 */
    virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 查询资金响应 */
    virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* 查询投资者响应 */
    virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
};

/* 交易执行类 */
class CTraderApi
{
    /* 操作类 */
public:
    /* 认证操作 */
    void Authe(void);
    /* 登录操作 */
    void Login(void);
    /* 注销操作 */
    void Logout(void);
    /* 确认结算 */
    void SettlementInfoConfirm(void);
    /* 报单录入 */
    void OrderInsert(void);
    /* 报单操作 */
    void OrderAction(void);
    /* 执行录入 */
    void ExecOrderInsert(void);
    /* 执行操作 */
    void ExecOrderAction(void);
    /* 报价录入 */
    void QuoteInsert(void);
    /* 报价操作 */
    void QuoteAction(void);
    /* 询价录入 */
    void ForQuoteInsert(void);

    /* 查询类 */
public:
    /* 报单查询 */
    void QryOrder(void);
    /* 执行查询 */
    void QryExecOrder(void);
    /* 报价查询 */
    void QryQuote(void);
    /* 询价查询 */
    void QryForQuote(void);
    /* 交易查询 */
    void QryTradingNotice(void);
    /* 成交查询 */
    void QryTrade(void);
    /* 通知查询 */
    void QryNotice(void);
    /* 交易所查询 */
    void QryExchange(void);
    /* 交易编码查询 */
    void QryTradingCode(void);
    /* 交易产品查询 */
    void QryProduct(void);
    /* 合约查询 */
    void QryInstrument(void);
    /* 行情查询 */
    void QryDepthMarketData(void);
    /* 持仓查询 */
    void QryInvestorPosition(void);
    /* 资金查询 */
    void QryTradingAccount(void);
    /* 投资者查询 */
    void QryInvestor(void);

public:
    typedef enum
    {
        E_OPER_DEFAULT,
        E_OPER_AUTHE,
        E_OPER_LOGIN,
        E_OPER_LOGOUT,
        E_OPER_SETTLEMENT_INFO_CONFIRM,
        E_OPER_ORDER_INSERT,
        E_OPER_ORDER_ACTION,
        E_OPER_EXEC_ORDER_INSERT,
        E_OPER_EXEC_ORDER_ACTION,
        E_OPER_QUOTE_INSERT,
        E_OPER_QUOTE_ACTION,
        E_OPER_FOR_QUETE_INSERT,
        E_OPER_QRY_ORDER,
        E_OPER_QRY_EXEC_ORDER,
        E_OPER_QRY_QUOTE,
        E_OPER_QRY_FOR_QUOTE,
        E_OPER_QRY_TRADING_NOTICE,
        E_OPER_QRY_TRADE,
        E_OPER_QRY_NOTICE,
        E_OPER_QRY_EXCHANGE,
        E_OPER_QRY_TRADING_CODE,
        E_OPER_QRY_PRODUCT,
        E_OPER_QRY_INSTRUMENT,
        E_OPER_QRY_DEPTH_MARKET_DATE,
        E_OPER_QRY_INVESTOR_POSITION,
        E_OPER_QRY_TRADING_ACCOUNT,
        E_OPER_QRY_INVESTOR,
        E_OPER_TYPE_COUNT
    }E_OPER_TYPE;
private:
    static const char *oper_name[E_OPER_TYPE_COUNT];
    static int oper_count;

public:
    CThostFtdcTraderApi  *m_api; /* 执行类实例 */
    CThostFtdcTraderSpi  *m_spi; /* 响应类实例 */
    CConfigInfo           m_cfg; /* 配置信息 */
    CTraderData           m_data; /* 交易信息 */
    BOOL m_bConnect;
    BOOL m_bLogin;
    BOOL m_bHaveCli;

public:
    /* 启动 */
    void Start(void);
    /* 停止 */
    void Stop(void);
    /* 命令行操作 */
    void CliOperation(void);
    /* 自动化操作 */
    void AutoOperation(void);
    /* 委托 */
    void CreateOrder(void);
    /* 撤销 */
    void RevokeOrder(void);

public:
    BOOL IsRunning(void);
private:
    BOOL  m_bRunning;

private:
    static DWORD WINAPI ThreadProc(LPVOID lpParam);
    HANDLE  m_hThread;

public:
    static CTraderApi *CreateInstance(void);
    static void ReleaseInstance(void);
    static CTraderApi *GetInstance(void);
private:
    CTraderApi(void);
    ~CTraderApi(void);
    static CTraderApi *m_pInstance;
    class CSelfRelease
    {
    public:
        CSelfRelease();
        ~CSelfRelease();
    };
    static CSelfRelease  m_self;
};

#endif /* __TRADER_API_H__ */