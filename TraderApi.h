#ifndef __TRADER_API_H__
#define __TRADER_API_H__

#include <cstdio>
#include <windows.h>

#include "ThostFtdcTraderApi.h"
#include "AssistApi.h"

#include <string>
#include <list>
#include <map>

using namespace std;

/* 更新阶段 */
typedef enum
{
    E_UPDATE_STAGE_REQ,  /* 请求阶段更新 */
    E_UPDATE_STAGE_RSP,  /* 响应阶段更新 */
    E_UPDATE_STAGE_ERR,  /* 错误阶段更新 */
    E_UPDATE_STAGE_RTN,  /* 回报阶段更新 */
    E_UPDATE_STAGE_COUNT
}E_UPDATE_STAGE_TYPE;

/* 交易数据类 */
class CTraderData
{
public:
    CTraderData();
    ~CTraderData();

public:
    /* 设置报单信息 */
    void SetOrderInfo(const char *szTraderDesc, TThostFtdcInstrumentIDType szInstrumentID, TThostFtdcFrontIDType nFrontID, TThostFtdcSessionIDType nSessionID, TThostFtdcOrderRefType szOrderRef);
    /* 更新请求时间 */
    void UpdateReqTime(void);
    /* 更新回报时间 */
    void UpdateRtnTime(void);

public:
    char                             m_szTraderDesc[128]; /* 报单描述 */
    TThostFtdcInstrumentIDType	     m_szInstrumentID; /* 合约标识 */
    TThostFtdcFrontIDType            m_nFrontID;  /* 前置编号 */
    TThostFtdcSessionIDType          m_nSessionID;  /* 会话编号 */
    TThostFtdcOrderRefType           m_szOrderRef; /* 报单引用 */

private:
    /* 打印报单信息 */
    void PrintOrderInfo(void);
    ClockTime                        m_tTerminalTime; /* 终端发送时间 */
    ClockTime                        m_tTHostTime;    /* 平台回报时间 */
    ClockTime                        m_tExchangeTime; /* 交易所回报时间 */
    int                              m_nUpdateCount;   /* 更新次数 */
};

/* 交易数据管理类 */
class CTraderDataManager
{
public:
    CTraderDataManager();
    ~CTraderDataManager();

public:
    /* 更新交易数据 */
    void UpdateTraderData(CThostFtdcInputOrderField *pInputOrder, E_UPDATE_STAGE_TYPE nStage); /* 请求报单/报单响应/报单错误 */
    void UpdateTraderData(CThostFtdcOrderActionField *pInputOrder, E_UPDATE_STAGE_TYPE nStage); /* 操作错误 */
    void UpdateTraderData(CThostFtdcInputOrderActionField *pInputAction, E_UPDATE_STAGE_TYPE nStage); /* 请求操作/操作响应 */
    void UpdateTraderData(CThostFtdcOrderField *pOrder, E_UPDATE_STAGE_TYPE nStage); /* 报单回报 */
    void UpdateTraderData(CThostFtdcTradeField *pTrader, E_UPDATE_STAGE_TYPE nStage); /* 成交回报 */

public:
    /* 计算索引标识 */
    string GetMapIndex(int nFrontID, int nSessionID, char *szOrderRef);
    list<CTraderData *>           m_UnTradeList;  /* 未成交报单队列 */
    map<string, CTraderData *>    m_OrderMap;     /* 报单映射 */
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
    /* 报单录入-指的是委托期货报单 */
    void OrderInsert(void);
    /* 报单操作-指的是修改或撤销期货报单 */
    void OrderAction(void);
    /* 备注：功能不明，后续再做 */
    void ExecOrderInsert(void);
    /* 备注：功能不明，后续再做 */
    void ExecOrderAction(void);
    /* 备注：功能不明，后续再做 */
    void QuoteInsert(void);
    /* 备注：功能不明，后续再做 */
    void QuoteAction(void);
    /* 备注：功能不明，后续再做 */
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
    CTraderDataManager    m_mgr; /* 交易数据管理 */
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