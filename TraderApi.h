#ifndef __TRADER_API_H__
#define __TRADER_API_H__

#include <cstdio>
#include <windows.h>

#include "ThostFtdcTraderApi.h"
#include "AssistApi.h"

/* ���������� */
class CTraderData
{
public:
    CTraderData();
    ~CTraderData();

public:
    /* ���½������� */
    void UpdateTraderData(CThostFtdcInputOrderField *pInputOrder, int nTriggerStage);
    void UpdateTraderData(CThostFtdcInputOrderActionField *pInputAction, int nTriggerStage);
    void UpdateTraderData(CThostFtdcOrderActionField *pInputOrder, int nTriggerStage);
    void UpdateTraderData(CThostFtdcOrderField *pOrder, int nTriggerStage);
    void UpdateTraderData(CThostFtdcTradeField *pTrader, int nTriggerStage);

public:
    TThostFtdcBrokerIDType         m_szBrokerID;  /* ���͹�˾���� */
    TThostFtdcInvestorIDType       m_szInvestorID; /* Ͷ���ߴ��� */
    TThostFtdcExchangeIDType	   m_szExchangeID; /* ���������� */
    TThostFtdcInstrumentIDType     m_szInstrumentID; /* ��Լ���� */
    TThostFtdcUserIDType	       m_szUserID; /* �û����� */
    TThostFtdcOrderRefType	       m_szOrderRef; /* �������� */
    TThostFtdcOrderActionRefType   m_szOrderActionRef; /* �������� */
    TThostFtdcRequestIDType	       m_nRequestID; /* ������ */
    TThostFtdcFrontIDType	       m_nFrontID; /* ǰ�ñ�� */
    TThostFtdcSessionIDType	       m_nSessionID; /* �Ự��� */
    TThostFtdcOrderSysIDType	   m_szOrderSysID; /* ������� */
};

/* ������Ӧ�� */
class CTraderSpi : public CThostFtdcTraderSpi
{
public:
    CTraderSpi(void);
    ~CTraderSpi(void);

    /* ֪ͨ�� */
public:
    /* ����֪ͨ */
    virtual void OnFrontConnected();
    /* �Ͽ�֪ͨ */
    virtual void OnFrontDisconnected(int nReason);
    /* ����֪ͨ */
    virtual void OnHeartBeatWarning(int nTimeLapse);
    /* ����֪ͨ */
    virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);
    /* ִ��֪ͨ */
    virtual void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder);
    /* ����֪ͨ */
    virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote);
    /* ѯ��֪ͨ */
    virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);
    /* ����֪ͨ */
    virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo);
    /* �ɽ�֪ͨ */
    virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

    /* ������ */
public:
    /* ����¼����� */
    virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
    /* ������������ */
    virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);
    /* ִ��¼����� */
    virtual void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo);
    /* ִ�в������� */
    virtual void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo);
    /* ����¼����� */
    virtual void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo);
    /* ���۲������� */
    virtual void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo);
    /* ѯ��¼����� */
    virtual void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo);
    /* ������Ӧ */
    virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    /* ��Ӧ�� */
public:
    /* ��֤��Ӧ */
    virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ��¼��Ӧ */
    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ע����Ӧ */
    virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ȷ�Ͻ�����Ӧ */
    virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ����¼����Ӧ */
    virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ����������Ӧ */
    virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ִ��¼����Ӧ */
    virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ִ�в�����Ӧ */
    virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ����¼����Ӧ */
    virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ���۲�����Ӧ */
    virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ѯ��¼����Ӧ */
    virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    /* ��ѯ�� */
public:
    /* ��ѯ������Ӧ */
    virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ��ѯִ����Ӧ */
    virtual void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ��ѯ������Ӧ */
    virtual void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ��ѯѯ����Ӧ */
    virtual void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ��ѯ������Ӧ */
    virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ��ѯ�ɽ���Ӧ */
    virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ��ѯ֪ͨ��Ӧ */
    virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ��ѯ��������Ӧ */
    virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ��ѯ���ױ�����Ӧ */
    virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ��ѯ��Ʒ��Ӧ */
    virtual void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ��ѯ��Լ��Ӧ */
    virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ��ѯ������Ӧ */
    virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ��ѯ�ֲ���Ӧ */
    virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ��ѯ�ʽ���Ӧ */
    virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    /* ��ѯͶ������Ӧ */
    virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
};

/* ����ִ���� */
class CTraderApi
{
    /* ������ */
public:
    /* ��֤���� */
    void Authe(void);
    /* ��¼���� */
    void Login(void);
    /* ע������ */
    void Logout(void);
    /* ȷ�Ͻ��� */
    void SettlementInfoConfirm(void);
    /* ����¼�� */
    void OrderInsert(void);
    /* �������� */
    void OrderAction(void);
    /* ִ��¼�� */
    void ExecOrderInsert(void);
    /* ִ�в��� */
    void ExecOrderAction(void);
    /* ����¼�� */
    void QuoteInsert(void);
    /* ���۲��� */
    void QuoteAction(void);
    /* ѯ��¼�� */
    void ForQuoteInsert(void);

    /* ��ѯ�� */
public:
    /* ������ѯ */
    void QryOrder(void);
    /* ִ�в�ѯ */
    void QryExecOrder(void);
    /* ���۲�ѯ */
    void QryQuote(void);
    /* ѯ�۲�ѯ */
    void QryForQuote(void);
    /* ���ײ�ѯ */
    void QryTradingNotice(void);
    /* �ɽ���ѯ */
    void QryTrade(void);
    /* ֪ͨ��ѯ */
    void QryNotice(void);
    /* ��������ѯ */
    void QryExchange(void);
    /* ���ױ����ѯ */
    void QryTradingCode(void);
    /* ���ײ�Ʒ��ѯ */
    void QryProduct(void);
    /* ��Լ��ѯ */
    void QryInstrument(void);
    /* �����ѯ */
    void QryDepthMarketData(void);
    /* �ֲֲ�ѯ */
    void QryInvestorPosition(void);
    /* �ʽ��ѯ */
    void QryTradingAccount(void);
    /* Ͷ���߲�ѯ */
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
    CThostFtdcTraderApi  *m_api; /* ִ����ʵ�� */
    CThostFtdcTraderSpi  *m_spi; /* ��Ӧ��ʵ�� */
    CConfigInfo           m_cfg; /* ������Ϣ */
    CTraderData           m_data; /* ������Ϣ */
    BOOL m_bConnect;
    BOOL m_bLogin;
    BOOL m_bHaveCli;

public:
    /* ���� */
    void Start(void);
    /* ֹͣ */
    void Stop(void);
    /* �����в��� */
    void CliOperation(void);
    /* �Զ������� */
    void AutoOperation(void);
    /* ί�� */
    void CreateOrder(void);
    /* ���� */
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