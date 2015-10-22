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

void CPrintParams::PrintFunction(const char *szFuncName)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    CPrintApi::DbgPrint("\n");
    CPrintApi::DbgPrint("-----------------------------------------------------------------------------");
    if (szFuncName)
    {
        CPrintApi::DbgPrint("----函数: %s", szFuncName);
    }
}

void CPrintParams::PrintParams(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pOrder)
    {
        CPrintApi::DbgPrint("----参数：pOrder->BrokerID=%s", pOrder->BrokerID);
        CPrintApi::DbgPrint("          pOrder->InvestorID=%s", pOrder->InvestorID);
        CPrintApi::DbgPrint("          pOrder->InstrumentID=%s", pOrder->InstrumentID);
        CPrintApi::DbgPrint("          pOrder->OrderRef=%s", pOrder->OrderRef); /* 报单引用 */
        CPrintApi::DbgPrint("          pOrder->UserID=%s", pOrder->UserID);
        CPrintApi::DbgPrint("          pOrder->OrderPriceType=%c", pOrder->OrderPriceType);
        CPrintApi::DbgPrint("          pOrder->Direction=%c", pOrder->Direction);/* 报单方向 */
        CPrintApi::DbgPrint("          pOrder->CombOffsetFlag=%s", pOrder->CombOffsetFlag);/* 开平方式 */
        CPrintApi::DbgPrint("          pOrder->CombHedgeFlag=%s", pOrder->CombHedgeFlag);/* */
        CPrintApi::DbgPrint("          pOrder->LimitPrice=%8.3f", pOrder->LimitPrice);
        CPrintApi::DbgPrint("          pOrder->VolumeTotalOriginal=%d", pOrder->VolumeTotalOriginal);
        CPrintApi::DbgPrint("          pOrder->TimeCondition=%d", pOrder->TimeCondition);
        CPrintApi::DbgPrint("          pOrder->GTDDate=%s", pOrder->GTDDate);
        CPrintApi::DbgPrint("          pOrder->VolumeCondition=%c", pOrder->VolumeCondition);
        CPrintApi::DbgPrint("          pOrder->MinVolume=%d", pOrder->MinVolume);
        CPrintApi::DbgPrint("          pOrder->ContingentCondition=%c", pOrder->ContingentCondition);
        CPrintApi::DbgPrint("          pOrder->StopPrice=%8.3f", pOrder->StopPrice);
        CPrintApi::DbgPrint("          pOrder->ForceCloseReason=%c", pOrder->ForceCloseReason);
        CPrintApi::DbgPrint("          pOrder->IsAutoSuspend=%d", pOrder->IsAutoSuspend);
        CPrintApi::DbgPrint("          pOrder->BusinessUnit=%s", pOrder->BusinessUnit);
        CPrintApi::DbgPrint("          pOrder->RequestID=%d", pOrder->RequestID); /* 请求标志 */
        CPrintApi::DbgPrint("          pOrder->OrderLocalID=%s", pOrder->OrderLocalID);
        CPrintApi::DbgPrint("          pOrder->ExchangeID=%s", pOrder->ExchangeID);
        CPrintApi::DbgPrint("          pOrder->ParticipantID=%s", pOrder->ParticipantID);
        CPrintApi::DbgPrint("          pOrder->ClientID=%s", pOrder->ClientID);
        CPrintApi::DbgPrint("          pOrder->ExchangeInstID=%s", pOrder->ExchangeInstID);
        CPrintApi::DbgPrint("          pOrder->TraderID=%s", pOrder->TraderID);
        CPrintApi::DbgPrint("          pOrder->InstallID=%d", pOrder->InstallID);
        CPrintApi::DbgPrint("          pOrder->OrderSubmitStatus=%c", pOrder->OrderSubmitStatus);/* 报单提交状态 */
        CPrintApi::DbgPrint("          pOrder->NotifySequence=%d", pOrder->NotifySequence);/* */
        CPrintApi::DbgPrint("          pOrder->TradingDay=%s", pOrder->TradingDay);
        CPrintApi::DbgPrint("          pOrder->SettlementID=%d", pOrder->SettlementID);
        CPrintApi::DbgPrint("          pOrder->OrderSysID=%s", pOrder->OrderSysID);
        CPrintApi::DbgPrint("          pOrder->OrderSource=%c", pOrder->OrderSource);
        CPrintApi::DbgPrint("          pOrder->OrderStatus=%c", pOrder->OrderStatus);/* 报单状态 */
        CPrintApi::DbgPrint("          pOrder->OrderType=%c", pOrder->OrderType);
        CPrintApi::DbgPrint("          pOrder->VolumeTraded=%d", pOrder->VolumeTraded);
        CPrintApi::DbgPrint("          pOrder->VolumeTotal=%d", pOrder->VolumeTotal);
        CPrintApi::DbgPrint("          pOrder->InsertDate=%s", pOrder->InsertDate);
        CPrintApi::DbgPrint("          pOrder->InsertTime=%s", pOrder->InsertTime);
        CPrintApi::DbgPrint("          pOrder->ActiveTime=%s", pOrder->ActiveTime);
        CPrintApi::DbgPrint("          pOrder->SuspendTime=%s", pOrder->SuspendTime);
        CPrintApi::DbgPrint("          pOrder->UpdateTime=%s", pOrder->UpdateTime);
        CPrintApi::DbgPrint("          pOrder->CancelTime=%s", pOrder->CancelTime);
        CPrintApi::DbgPrint("          pOrder->ActiveTraderID=%s", pOrder->ActiveTraderID);
        CPrintApi::DbgPrint("          pOrder->ClearingPartID=%s", pOrder->ClearingPartID);
        CPrintApi::DbgPrint("          pOrder->SequenceNo=%d", pOrder->SequenceNo); /* 顺序编号 */
        CPrintApi::DbgPrint("          pOrder->FrontID=%d", pOrder->FrontID); /* 前置编号 */
        CPrintApi::DbgPrint("          pOrder->SessionID=%d", pOrder->SessionID); /* 会话编号 */
        CPrintApi::DbgPrint("          pOrder->UserProductInfo=%s", pOrder->UserProductInfo);
        CPrintApi::DbgPrint("          pOrder->StatusMsg=%s", pOrder->StatusMsg);
        CPrintApi::DbgPrint("          pOrder->UserForceClose=%d", pOrder->UserForceClose);
        CPrintApi::DbgPrint("          pOrder->ActiveUserID=%s", pOrder->ActiveUserID);
        CPrintApi::DbgPrint("          pOrder->BrokerOrderSeq=%d", pOrder->BrokerOrderSeq);
        CPrintApi::DbgPrint("          pOrder->RelativeOrderSysID=%s", pOrder->RelativeOrderSysID);
        CPrintApi::DbgPrint("          pOrder->ZCETotalTradedVolume=%d", pOrder->ZCETotalTradedVolume);
        CPrintApi::DbgPrint("          pOrder->IsSwapOrder=%d", pOrder->IsSwapOrder);
    
        /* 报单信息 */
        CPrintApi::DbgPrint("----报单信息：RequestID=%d, NotifySequence=%d, FrontID=%d, SessionID=%d, OrderRef=%s, SequenceNo=%d, BrokerOrderSeq=%d", 
            pOrder->RequestID, pOrder->NotifySequence, pOrder->FrontID, pOrder->SessionID, pOrder->OrderRef, pOrder->SequenceNo, pOrder->BrokerOrderSeq);

        /* 买卖方向 */
        switch (pOrder->Direction)
        {
        case THOST_FTDC_D_Buy:
            {
                /* 开平标志 */
                switch (pOrder->CombOffsetFlag[0])
                {
                case THOST_FTDC_OF_Open:
                    CPrintApi::DbgPrint("----开仓买入");
                    break;
                case THOST_FTDC_OF_Close:
                    CPrintApi::DbgPrint("----平仓买入");
                    break;
                case THOST_FTDC_OF_ForceClose:
                    CPrintApi::DbgPrint("----强平买入");
                    break;
                case THOST_FTDC_OF_CloseToday:
                    CPrintApi::DbgPrint("----平今买入");
                    break;
                case THOST_FTDC_OF_CloseYesterday:
                    CPrintApi::DbgPrint("----平昨买入");
                    break;
                case THOST_FTDC_OF_ForceOff:
                    CPrintApi::DbgPrint("----强减买入");
                    break;
                case THOST_FTDC_OF_LocalForceClose:
                    CPrintApi::DbgPrint("----本地强平买入");
                    break;
                default:
                    break;
                }
            }
            break;
        case THOST_FTDC_D_Sell:
            {
                /* 开平标志 */
                switch (pOrder->CombOffsetFlag[0])
                {
                case THOST_FTDC_OF_Open:
                    CPrintApi::DbgPrint("----开仓卖出");
                    break;
                case THOST_FTDC_OF_Close:
                    CPrintApi::DbgPrint("----平仓卖出");
                    break;
                case THOST_FTDC_OF_ForceClose:
                    CPrintApi::DbgPrint("----强平卖出");
                    break;
                case THOST_FTDC_OF_CloseToday:
                    CPrintApi::DbgPrint("----平今卖出");
                    break;
                case THOST_FTDC_OF_CloseYesterday:
                    CPrintApi::DbgPrint("----平昨卖出");
                    break;
                case THOST_FTDC_OF_ForceOff:
                    CPrintApi::DbgPrint("----强减卖出");
                    break;
                case THOST_FTDC_OF_LocalForceClose:
                    CPrintApi::DbgPrint("----本地强平卖出");
                    break;
                default:
                    break;
                }
            }
            break;
        default:
            break;
        }

        /* 报单提交状态 */
        switch (pOrder->OrderSubmitStatus)
        {
        case THOST_FTDC_OSS_InsertSubmitted:
            CPrintApi::DbgPrint("----报单已经提交");
            break;
        case THOST_FTDC_OSS_CancelSubmitted:
            CPrintApi::DbgPrint("----撤单已经提交");
            break;
        case THOST_FTDC_OSS_ModifySubmitted:
            CPrintApi::DbgPrint("----改单已经提交");
            break;
        case THOST_FTDC_OSS_Accepted:
            CPrintApi::DbgPrint("----委托已经接受");
            break;
        case THOST_FTDC_OSS_InsertRejected:
            CPrintApi::DbgPrint("----报单已被拒绝");
            break;
        case THOST_FTDC_OSS_CancelRejected:
            CPrintApi::DbgPrint("----撤单已被拒绝");
            break;
        case THOST_FTDC_OSS_ModifyRejected:
            CPrintApi::DbgPrint("----改单已被拒绝");
            break;
        default:
            break;
        }

        /* 报单状态 */
        switch (pOrder->OrderStatus)
        {
        case THOST_FTDC_OST_AllTraded:
            CPrintApi::DbgPrint("----全部成交");
            break;
        case THOST_FTDC_OST_PartTradedQueueing:
            CPrintApi::DbgPrint("----部分成交还在队列中");
            break;
        case THOST_FTDC_OST_PartTradedNotQueueing:
            CPrintApi::DbgPrint("----部分成交不在队列中");
            break;
        case THOST_FTDC_OST_NoTradeQueueing:
            CPrintApi::DbgPrint("----未成交还在队列中");
            break;
        case THOST_FTDC_OST_NoTradeNotQueueing:
            CPrintApi::DbgPrint("----未成交不在队列中");
            break;
        case THOST_FTDC_OST_Canceled:
            CPrintApi::DbgPrint("----撤单");
            break;
        case THOST_FTDC_OST_Unknown:
            CPrintApi::DbgPrint("----未知");
            break;
        case THOST_FTDC_OST_NotTouched:
            CPrintApi::DbgPrint("----尚未触发");
            break;
        case THOST_FTDC_OST_Touched:
            CPrintApi::DbgPrint("----已经触发");
            break;
        default:
            break;
        }
    }

    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pExecOrder)
    {
        CPrintApi::DbgPrint("----参数：pExecOrder->BrokerID=%s", pExecOrder->BrokerID);
        CPrintApi::DbgPrint("          pExecOrder->InvestorID=%s", pExecOrder->InvestorID);
        CPrintApi::DbgPrint("          pExecOrder->InstrumentID=%s", pExecOrder->InstrumentID);
        CPrintApi::DbgPrint("          pExecOrder->ExecOrderRef=%s", pExecOrder->ExecOrderRef);
        CPrintApi::DbgPrint("          pExecOrder->UserID=%s", pExecOrder->UserID);
        CPrintApi::DbgPrint("          pExecOrder->Volume=%d", pExecOrder->Volume);
        CPrintApi::DbgPrint("          pExecOrder->RequestID=%d", pExecOrder->RequestID); /* 请求标志 */
        CPrintApi::DbgPrint("          pExecOrder->BusinessUnit=%s", pExecOrder->BusinessUnit);
        CPrintApi::DbgPrint("          pExecOrder->OffsetFlag=%c", pExecOrder->OffsetFlag);
        CPrintApi::DbgPrint("          pExecOrder->HedgeFlag=%c", pExecOrder->HedgeFlag);
        CPrintApi::DbgPrint("          pExecOrder->ActionType=%c", pExecOrder->ActionType);
        CPrintApi::DbgPrint("          pExecOrder->PosiDirection=%c", pExecOrder->PosiDirection);
        CPrintApi::DbgPrint("          pExecOrder->ReservePositionFlag=%c", pExecOrder->ReservePositionFlag);
        CPrintApi::DbgPrint("          pExecOrder->CloseFlag=%c", pExecOrder->CloseFlag);
        CPrintApi::DbgPrint("          pExecOrder->ExecOrderLocalID=%s", pExecOrder->ExecOrderLocalID);
        CPrintApi::DbgPrint("          pExecOrder->ExchangeID=%s", pExecOrder->ExchangeID);
        CPrintApi::DbgPrint("          pExecOrder->ParticipantID=%s", pExecOrder->ParticipantID);
        CPrintApi::DbgPrint("          pExecOrder->ClientID=%s", pExecOrder->ClientID);
        CPrintApi::DbgPrint("          pExecOrder->ExchangeInstID=%s", pExecOrder->ExchangeInstID);
        CPrintApi::DbgPrint("          pExecOrder->TraderID=%s", pExecOrder->TraderID);
        CPrintApi::DbgPrint("          pExecOrder->InstallID=%d", pExecOrder->InstallID);
        CPrintApi::DbgPrint("          pExecOrder->OrderSubmitStatus=%c", pExecOrder->OrderSubmitStatus);
        CPrintApi::DbgPrint("          pExecOrder->NotifySequence=%d", pExecOrder->NotifySequence);
        CPrintApi::DbgPrint("          pExecOrder->TradingDay=%s", pExecOrder->TradingDay);
        CPrintApi::DbgPrint("          pExecOrder->SettlementID=%d", pExecOrder->SettlementID);
        CPrintApi::DbgPrint("          pExecOrder->ExecOrderSysID=%s", pExecOrder->ExecOrderSysID);
        CPrintApi::DbgPrint("          pExecOrder->InsertDate=%s", pExecOrder->InsertDate);
        CPrintApi::DbgPrint("          pExecOrder->InsertTime=%s", pExecOrder->InsertTime);
        CPrintApi::DbgPrint("          pExecOrder->CancelTime=%s", pExecOrder->CancelTime);
        CPrintApi::DbgPrint("          pExecOrder->ExecResult=%c", pExecOrder->ExecResult);
        CPrintApi::DbgPrint("          pExecOrder->ClearingPartID=%s", pExecOrder->ClearingPartID);
        CPrintApi::DbgPrint("          pExecOrder->SequenceNo=%d", pExecOrder->SequenceNo);
        CPrintApi::DbgPrint("          pExecOrder->FrontID=%d", pExecOrder->FrontID);
        CPrintApi::DbgPrint("          pExecOrder->SessionID=%d", pExecOrder->SessionID);
        CPrintApi::DbgPrint("          pExecOrder->UserProductInfo=%s", pExecOrder->UserProductInfo);
        CPrintApi::DbgPrint("          pExecOrder->StatusMsg=%s", pExecOrder->StatusMsg);
        CPrintApi::DbgPrint("          pExecOrder->ActiveUserID=%s", pExecOrder->ActiveUserID);
        CPrintApi::DbgPrint("          pExecOrder->BrokerExecOrderSeq=%d", pExecOrder->BrokerExecOrderSeq);

        /* 报单信息 */
        CPrintApi::DbgPrint("----报单信息：RequestID=%d, NotifySequence=%d, FrontID=%d, SessionID=%d, ExecOrderRef=%s, SequenceNo=%d, BrokerExecOrderSeq=%d", 
            pExecOrder->RequestID, pExecOrder->NotifySequence, pExecOrder->FrontID, pExecOrder->SessionID, pExecOrder->ExecOrderRef, pExecOrder->SequenceNo, pExecOrder->BrokerExecOrderSeq);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pQuote)
    {
        CPrintApi::DbgPrint("----参数：pQuote->BrokerID=%s", pQuote->BrokerID);
        CPrintApi::DbgPrint("          pQuote->InvestorID=%s", pQuote->InvestorID);
        CPrintApi::DbgPrint("          pQuote->InstrumentID=%s", pQuote->InstrumentID);
        CPrintApi::DbgPrint("          pQuote->QuoteRef=%s", pQuote->QuoteRef);
        CPrintApi::DbgPrint("          pQuote->UserID=%s", pQuote->UserID);
        CPrintApi::DbgPrint("          pQuote->AskPrice=%8.3f", pQuote->AskPrice);
        CPrintApi::DbgPrint("          pQuote->BidPrice=%8.3f", pQuote->BidPrice);
        CPrintApi::DbgPrint("          pQuote->AskVolume=%d", pQuote->AskVolume);
        CPrintApi::DbgPrint("          pQuote->BidVolume=%d", pQuote->BidVolume);
        CPrintApi::DbgPrint("          pQuote->RequestID=%d", pQuote->RequestID); /* 请求标志 */
        CPrintApi::DbgPrint("          pQuote->BusinessUnit=%s", pQuote->BusinessUnit);
        CPrintApi::DbgPrint("          pQuote->AskOffsetFlag=%c", pQuote->AskOffsetFlag);
        CPrintApi::DbgPrint("          pQuote->BidOffsetFlag=%c", pQuote->BidOffsetFlag);
        CPrintApi::DbgPrint("          pQuote->AskHedgeFlag=%c", pQuote->AskHedgeFlag);
        CPrintApi::DbgPrint("          pQuote->BidHedgeFlag=%c", pQuote->BidHedgeFlag);
        CPrintApi::DbgPrint("          pQuote->QuoteLocalID=%s", pQuote->QuoteLocalID);
        CPrintApi::DbgPrint("          pQuote->ExchangeID=%s", pQuote->ExchangeID);
        CPrintApi::DbgPrint("          pQuote->ParticipantID=%s", pQuote->ParticipantID);
        CPrintApi::DbgPrint("          pQuote->ClientID=%s", pQuote->ClientID);
        CPrintApi::DbgPrint("          pQuote->ExchangeInstID=%s", pQuote->ExchangeInstID);
        CPrintApi::DbgPrint("          pQuote->TraderID=%s", pQuote->TraderID);
        CPrintApi::DbgPrint("          pQuote->InstallID=%d", pQuote->InstallID);
        CPrintApi::DbgPrint("          pQuote->NotifySequence=%d", pQuote->NotifySequence);
        CPrintApi::DbgPrint("          pQuote->OrderSubmitStatus=%c", pQuote->OrderSubmitStatus);
        CPrintApi::DbgPrint("          pQuote->TradingDay=%s", pQuote->TradingDay);
        CPrintApi::DbgPrint("          pQuote->SettlementID=%d", pQuote->SettlementID);
        CPrintApi::DbgPrint("          pQuote->QuoteSysID=%s", pQuote->QuoteSysID);
        CPrintApi::DbgPrint("          pQuote->InsertDate=%s", pQuote->InsertDate);
        CPrintApi::DbgPrint("          pQuote->InsertTime=%s", pQuote->InsertTime);
        CPrintApi::DbgPrint("          pQuote->CancelTime=%s", pQuote->CancelTime);
        CPrintApi::DbgPrint("          pQuote->QuoteStatus=%c", pQuote->QuoteStatus);
        CPrintApi::DbgPrint("          pQuote->ClearingPartID=%s", pQuote->ClearingPartID);
        CPrintApi::DbgPrint("          pQuote->SequenceNo=%d", pQuote->SequenceNo);
        CPrintApi::DbgPrint("          pQuote->AskOrderSysID=%s", pQuote->AskOrderSysID);
        CPrintApi::DbgPrint("          pQuote->BidOrderSysID=%s", pQuote->BidOrderSysID);
        CPrintApi::DbgPrint("          pQuote->FrontID=%d", pQuote->FrontID);
        CPrintApi::DbgPrint("          pQuote->SessionID=%d", pQuote->SessionID);
        CPrintApi::DbgPrint("          pQuote->UserProductInfo=%s", pQuote->UserProductInfo);
        CPrintApi::DbgPrint("          pQuote->StatusMsg=%s", pQuote->StatusMsg);
        CPrintApi::DbgPrint("          pQuote->ActiveUserID=%s", pQuote->ActiveUserID);
        CPrintApi::DbgPrint("          pQuote->BrokerQuoteSeq=%d", pQuote->BrokerQuoteSeq);
        CPrintApi::DbgPrint("          pQuote->AskOrderRef=%s", pQuote->AskOrderRef);
        CPrintApi::DbgPrint("          pQuote->BidOrderRef=%s", pQuote->BidOrderRef);
        CPrintApi::DbgPrint("          pQuote->ForQuoteSysID=%s", pQuote->ForQuoteSysID);

        /* 报单信息 */
        CPrintApi::DbgPrint("----报单信息：RequestID=%d, NotifySequence=%d, FrontID=%d, SessionID=%d, QuoteRef=%s, SequenceNo=%d, BrokerQuoteSeq=%d", 
            pQuote->RequestID, pQuote->NotifySequence, pQuote->FrontID, pQuote->SessionID, pQuote->QuoteRef, pQuote->SequenceNo, pQuote->BrokerQuoteSeq);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcForQuoteRspField *pForQuoteRsp, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pForQuoteRsp)
    {
        CPrintApi::DbgPrint("----参数：pForQuoteRsp->TradingDay=%s", pForQuoteRsp->TradingDay);
        CPrintApi::DbgPrint("          pForQuoteRsp->InstrumentID=%s", pForQuoteRsp->InstrumentID);
        CPrintApi::DbgPrint("          pForQuoteRsp->ForQuoteSysID=%s", pForQuoteRsp->ForQuoteSysID);
        CPrintApi::DbgPrint("          pForQuoteRsp->ForQuoteTime=%s", pForQuoteRsp->ForQuoteTime);
        CPrintApi::DbgPrint("          pForQuoteRsp->ActionDay=%s", pForQuoteRsp->ActionDay);
        CPrintApi::DbgPrint("          pForQuoteRsp->ExchangeID=%s", pForQuoteRsp->ExchangeID);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pForQuote)
    {
        CPrintApi::DbgPrint("----参数：pForQuote->BrokerID=%s", pForQuote->BrokerID);
        CPrintApi::DbgPrint("          pForQuote->InvestorID=%s", pForQuote->InvestorID);
        CPrintApi::DbgPrint("          pForQuote->InstrumentID=%s", pForQuote->InstrumentID);
        CPrintApi::DbgPrint("          pForQuote->ForQuoteRef=%s", pForQuote->ForQuoteRef);
        CPrintApi::DbgPrint("          pForQuote->UserID=%s", pForQuote->UserID);
        CPrintApi::DbgPrint("          pForQuote->ForQuoteLocalID=%s", pForQuote->ForQuoteLocalID);
        CPrintApi::DbgPrint("          pForQuote->ExchangeID=%s", pForQuote->ExchangeID);
        CPrintApi::DbgPrint("          pForQuote->ParticipantID=%s", pForQuote->ParticipantID);
        CPrintApi::DbgPrint("          pForQuote->ClientID=%s", pForQuote->ClientID);
        CPrintApi::DbgPrint("          pForQuote->ExchangeInstID=%s", pForQuote->ExchangeInstID);
        CPrintApi::DbgPrint("          pForQuote->TraderID=%s", pForQuote->TraderID);
        CPrintApi::DbgPrint("          pForQuote->InstallID=%d", pForQuote->InstallID);
        CPrintApi::DbgPrint("          pForQuote->InsertDate=%s", pForQuote->InsertDate);
        CPrintApi::DbgPrint("          pForQuote->InsertTime=%s", pForQuote->InsertTime);
        CPrintApi::DbgPrint("          pForQuote->ForQuoteStatus=%c", pForQuote->ForQuoteStatus);
        CPrintApi::DbgPrint("          pForQuote->FrontID=%d", pForQuote->FrontID);
        CPrintApi::DbgPrint("          pForQuote->SessionID=%d", pForQuote->SessionID);
        CPrintApi::DbgPrint("          pForQuote->StatusMsg=%s", pForQuote->StatusMsg);
        CPrintApi::DbgPrint("          pForQuote->ActiveUserID=%s", pForQuote->ActiveUserID);
        CPrintApi::DbgPrint("          pForQuote->BrokerForQutoSeq=%d", pForQuote->BrokerForQutoSeq);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pTradingNoticeInfo)
    {
        CPrintApi::DbgPrint("----参数：pTradingNoticeInfo->BrokerID=%s", pTradingNoticeInfo->BrokerID);
        CPrintApi::DbgPrint("          pTradingNoticeInfo->InvestorID=%s", pTradingNoticeInfo->InvestorID);
        CPrintApi::DbgPrint("          pTradingNoticeInfo->SendTime=%s", pTradingNoticeInfo->SendTime);
        CPrintApi::DbgPrint("          pTradingNoticeInfo->FieldContent=%s", pTradingNoticeInfo->FieldContent);
        CPrintApi::DbgPrint("          pTradingNoticeInfo->SequenceSeries=%d", pTradingNoticeInfo->SequenceSeries);
        CPrintApi::DbgPrint("          pTradingNoticeInfo->SequenceNo=%d", pTradingNoticeInfo->SequenceNo);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pTradingNotice)
    {
        CPrintApi::DbgPrint("----参数：pTradingNotice->BrokerID=%s", pTradingNotice->BrokerID);
        CPrintApi::DbgPrint("          pTradingNotice->InvestorRange=%c", pTradingNotice->InvestorRange);
        CPrintApi::DbgPrint("          pTradingNotice->InvestorID=%s", pTradingNotice->InvestorID);
        CPrintApi::DbgPrint("          pTradingNotice->SequenceSeries=%d", pTradingNotice->SequenceSeries);
        CPrintApi::DbgPrint("          pTradingNotice->UserID=%s", pTradingNotice->UserID);
        CPrintApi::DbgPrint("          pTradingNotice->SendTime=%s", pTradingNotice->SendTime);
        CPrintApi::DbgPrint("          pTradingNotice->SequenceNo=%d", pTradingNotice->SequenceNo);
        CPrintApi::DbgPrint("          pTradingNotice->FieldContent=%s", pTradingNotice->FieldContent);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pTrade)
    {
        CPrintApi::DbgPrint("----参数：pTrade->BrokerID=%s", pTrade->BrokerID);
        CPrintApi::DbgPrint("          pTrade->InvestorID=%s", pTrade->InvestorID);
        CPrintApi::DbgPrint("          pTrade->InstrumentID=%s", pTrade->InstrumentID);
        CPrintApi::DbgPrint("          pTrade->OrderRef=%s", pTrade->OrderRef);
        CPrintApi::DbgPrint("          pTrade->UserID=%s", pTrade->UserID);
        CPrintApi::DbgPrint("          pTrade->ExchangeID=%s", pTrade->ExchangeID);
        CPrintApi::DbgPrint("          pTrade->TradeID=%s", pTrade->TradeID);
        CPrintApi::DbgPrint("          pTrade->Direction=%c", pTrade->Direction);
        CPrintApi::DbgPrint("          pTrade->OrderSysID=%s", pTrade->OrderSysID);
        CPrintApi::DbgPrint("          pTrade->ParticipantID=%s", pTrade->ParticipantID);
        CPrintApi::DbgPrint("          pTrade->ClientID=%s", pTrade->ClientID);
        CPrintApi::DbgPrint("          pTrade->TradingRole=%c", pTrade->TradingRole);
        CPrintApi::DbgPrint("          pTrade->ExchangeInstID=%s", pTrade->ExchangeInstID);
        CPrintApi::DbgPrint("          pTrade->OffsetFlag=%c", pTrade->OffsetFlag);
        CPrintApi::DbgPrint("          pTrade->HedgeFlag=%c", pTrade->HedgeFlag);
        CPrintApi::DbgPrint("          pTrade->Price=%8.3f", pTrade->Price);
        CPrintApi::DbgPrint("          pTrade->Volume=%d", pTrade->Volume);
        CPrintApi::DbgPrint("          pTrade->TradeDate=%s", pTrade->TradeDate);
        CPrintApi::DbgPrint("          pTrade->TradeTime=%s", pTrade->TradeTime);
        CPrintApi::DbgPrint("          pTrade->TradeType=%c", pTrade->TradeType);
        CPrintApi::DbgPrint("          pTrade->PriceSource=%c", pTrade->PriceSource);
        CPrintApi::DbgPrint("          pTrade->TraderID=%s", pTrade->TraderID);
        CPrintApi::DbgPrint("          pTrade->OrderLocalID=%s", pTrade->OrderLocalID);
        CPrintApi::DbgPrint("          pTrade->ClearingPartID=%s", pTrade->ClearingPartID);
        CPrintApi::DbgPrint("          pTrade->BusinessUnit=%s", pTrade->BusinessUnit);
        CPrintApi::DbgPrint("          pTrade->SequenceNo=%d", pTrade->SequenceNo);
        CPrintApi::DbgPrint("          pTrade->TradingDay=%s", pTrade->TradingDay);
        CPrintApi::DbgPrint("          pTrade->SettlementID=%d", pTrade->SettlementID);
        CPrintApi::DbgPrint("          pTrade->BrokerOrderSeq=%d", pTrade->BrokerOrderSeq);
        CPrintApi::DbgPrint("          pTrade->TradeSource=%c", pTrade->TradeSource);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pRspAuthenticateField)
    {
        CPrintApi::DbgPrint("----参数：pRspAuthenticateField->BrokerID=%s", pRspAuthenticateField->BrokerID);
        CPrintApi::DbgPrint("          pRspAuthenticateField->UserID=%s", pRspAuthenticateField->UserID);
        CPrintApi::DbgPrint("          pRspAuthenticateField->UserProductInfo=%s", pRspAuthenticateField->UserProductInfo);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pRspUserLogin)
    {
        CPrintApi::DbgPrint("----参数：pRspUserLogin->TradingDay=%s", pRspUserLogin->TradingDay);
        CPrintApi::DbgPrint("          pRspUserLogin->LoginTime=%s", pRspUserLogin->LoginTime);
        CPrintApi::DbgPrint("          pRspUserLogin->BrokerID=%s", pRspUserLogin->BrokerID);
        CPrintApi::DbgPrint("          pRspUserLogin->UserID=%s", pRspUserLogin->UserID);
        CPrintApi::DbgPrint("          pRspUserLogin->SystemName=%s", pRspUserLogin->SystemName);
        CPrintApi::DbgPrint("          pRspUserLogin->FrontID=%d", pRspUserLogin->FrontID);
        CPrintApi::DbgPrint("          pRspUserLogin->SessionID=%d", pRspUserLogin->SessionID);
        CPrintApi::DbgPrint("          pRspUserLogin->MaxOrderRef=%s", pRspUserLogin->MaxOrderRef);
        CPrintApi::DbgPrint("          pRspUserLogin->SHFETime=%s", pRspUserLogin->SHFETime);
        CPrintApi::DbgPrint("          pRspUserLogin->DCETime=%s", pRspUserLogin->DCETime);
        CPrintApi::DbgPrint("          pRspUserLogin->CZCETime=%s", pRspUserLogin->CZCETime);
        CPrintApi::DbgPrint("          pRspUserLogin->FFEXTime=%s", pRspUserLogin->FFEXTime);
        CPrintApi::DbgPrint("          pRspUserLogin->INETime=%s", pRspUserLogin->INETime);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pUserLogout)
    {
        CPrintApi::DbgPrint("----参数：pUserLogout->BrokerID=%s", pUserLogout->BrokerID);
        CPrintApi::DbgPrint("          pUserLogout->UserID=%s", pUserLogout->UserID);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pSettlementInfoConfirm)
    {
        CPrintApi::DbgPrint("----参数：pSettlementInfoConfirm->BrokerID=%s", pSettlementInfoConfirm->BrokerID);
        CPrintApi::DbgPrint("          pSettlementInfoConfirm->InvestorID=%s", pSettlementInfoConfirm->InvestorID);
        CPrintApi::DbgPrint("          pSettlementInfoConfirm->ConfirmDate=%s", pSettlementInfoConfirm->ConfirmDate);
        CPrintApi::DbgPrint("          pSettlementInfoConfirm->ConfirmTime=%s", pSettlementInfoConfirm->ConfirmTime);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pInputOrder)
    {
        CPrintApi::DbgPrint("----参数：pInputOrder->BrokerID=%s", pInputOrder->BrokerID);
        CPrintApi::DbgPrint("          pInputOrder->InvestorID=%s", pInputOrder->InvestorID);
        CPrintApi::DbgPrint("          pInputOrder->InstrumentID=%s", pInputOrder->InstrumentID);
        CPrintApi::DbgPrint("          pInputOrder->OrderRef=%s", pInputOrder->OrderRef);
        CPrintApi::DbgPrint("          pInputOrder->UserID=%s", pInputOrder->UserID);
        CPrintApi::DbgPrint("          pInputOrder->OrderPriceType=%c", pInputOrder->OrderPriceType);
        CPrintApi::DbgPrint("          pInputOrder->Direction=%c", pInputOrder->Direction);
        CPrintApi::DbgPrint("          pInputOrder->CombOffsetFlag=%s", pInputOrder->CombOffsetFlag);
        CPrintApi::DbgPrint("          pInputOrder->CombHedgeFlag=%s", pInputOrder->CombHedgeFlag);
        CPrintApi::DbgPrint("          pInputOrder->LimitPrice=%8.3f", pInputOrder->LimitPrice);
        CPrintApi::DbgPrint("          pInputOrder->VolumeTotalOriginal=%d", pInputOrder->VolumeTotalOriginal);
        CPrintApi::DbgPrint("          pInputOrder->TimeCondition=%c", pInputOrder->TimeCondition);
        CPrintApi::DbgPrint("          pInputOrder->GTDDate=%s", pInputOrder->GTDDate);
        CPrintApi::DbgPrint("          pInputOrder->VolumeCondition=%c", pInputOrder->VolumeCondition);
        CPrintApi::DbgPrint("          pInputOrder->MinVolume=%d", pInputOrder->MinVolume);
        CPrintApi::DbgPrint("          pInputOrder->ContingentCondition=%c", pInputOrder->ContingentCondition);
        CPrintApi::DbgPrint("          pInputOrder->StopPrice=%8.3f", pInputOrder->StopPrice);
        CPrintApi::DbgPrint("          pInputOrder->ForceCloseReason=%c", pInputOrder->ForceCloseReason);
        CPrintApi::DbgPrint("          pInputOrder->IsAutoSuspend=%d", pInputOrder->IsAutoSuspend);
        CPrintApi::DbgPrint("          pInputOrder->BusinessUnit=%s", pInputOrder->BusinessUnit);
        CPrintApi::DbgPrint("          pInputOrder->RequestID=%d", pInputOrder->RequestID); /* 请求标志 */
        CPrintApi::DbgPrint("          pInputOrder->UserForceClose=%d", pInputOrder->UserForceClose);
        CPrintApi::DbgPrint("          pInputOrder->IsSwapOrder=%d", pInputOrder->IsSwapOrder);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pOrderAction)
    {
        CPrintApi::DbgPrint("----参数：pOrderAction->BrokerID=%s", pOrderAction->BrokerID);
        CPrintApi::DbgPrint("          pOrderAction->InvestorID=%s", pOrderAction->InvestorID);
        CPrintApi::DbgPrint("          pOrderAction->OrderActionRef=%s", pOrderAction->OrderActionRef);
        CPrintApi::DbgPrint("          pOrderAction->OrderRef=%s", pOrderAction->OrderRef);
        CPrintApi::DbgPrint("          pOrderAction->RequestID=d", pOrderAction->RequestID); /* 请求标志 */
        CPrintApi::DbgPrint("          pOrderAction->FrontID=%d", pOrderAction->FrontID);
        CPrintApi::DbgPrint("          pOrderAction->SessionID=%d", pOrderAction->SessionID);
        CPrintApi::DbgPrint("          pOrderAction->ExchangeID=%s", pOrderAction->ExchangeID);
        CPrintApi::DbgPrint("          pOrderAction->OrderSysID=%s", pOrderAction->OrderSysID);
        CPrintApi::DbgPrint("          pOrderAction->ActionFlag=%c", pOrderAction->ActionFlag);
        CPrintApi::DbgPrint("          pOrderAction->LimitPrice=%8.3f", pOrderAction->LimitPrice);
        CPrintApi::DbgPrint("          pOrderAction->VolumeChange=%d", pOrderAction->VolumeChange);
        CPrintApi::DbgPrint("          pOrderAction->ActionDate=%s", pOrderAction->ActionDate);
        CPrintApi::DbgPrint("          pOrderAction->ActionTime=%s", pOrderAction->ActionTime);
        CPrintApi::DbgPrint("          pOrderAction->TraderID=%s", pOrderAction->TraderID);
        CPrintApi::DbgPrint("          pOrderAction->InstallID=%d", pOrderAction->InstallID);
        CPrintApi::DbgPrint("          pOrderAction->OrderLocalID=%s", pOrderAction->OrderLocalID);
        CPrintApi::DbgPrint("          pOrderAction->ActionLocalID=%s", pOrderAction->ActionLocalID);
        CPrintApi::DbgPrint("          pOrderAction->ParticipantID=%s", pOrderAction->ParticipantID);
        CPrintApi::DbgPrint("          pOrderAction->ClientID=%s", pOrderAction->ClientID);
        CPrintApi::DbgPrint("          pOrderAction->BusinessUnit=%s", pOrderAction->BusinessUnit);
        CPrintApi::DbgPrint("          pOrderAction->OrderActionStatus=%c", pOrderAction->OrderActionStatus);
        CPrintApi::DbgPrint("          pOrderAction->UserID=%s", pOrderAction->UserID);
        CPrintApi::DbgPrint("          pOrderAction->StatusMsg=%s", pOrderAction->StatusMsg);
        CPrintApi::DbgPrint("          pOrderAction->InstrumentID=%s", pOrderAction->InstrumentID);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pInputOrderAction)
    {
        CPrintApi::DbgPrint("----参数：pInputOrderAction->BrokerID=%s", pInputOrderAction->BrokerID);
        CPrintApi::DbgPrint("          pInputOrderAction->InvestorID=%s", pInputOrderAction->InvestorID);
        CPrintApi::DbgPrint("          pInputOrderAction->OrderActionRef=%s", pInputOrderAction->OrderActionRef);
        CPrintApi::DbgPrint("          pInputOrderAction->OrderRef=%s", pInputOrderAction->OrderRef);
        CPrintApi::DbgPrint("          pInputOrderAction->RequestID=d", pInputOrderAction->RequestID);
        CPrintApi::DbgPrint("          pInputOrderAction->FrontID=%d", pInputOrderAction->FrontID);
        CPrintApi::DbgPrint("          pInputOrderAction->SessionID=%d", pInputOrderAction->SessionID);
        CPrintApi::DbgPrint("          pInputOrderAction->ExchangeID=%s", pInputOrderAction->ExchangeID);
        CPrintApi::DbgPrint("          pInputOrderAction->OrderSysID=%s", pInputOrderAction->OrderSysID);
        CPrintApi::DbgPrint("          pInputOrderAction->ActionFlag=%c", pInputOrderAction->ActionFlag);
        CPrintApi::DbgPrint("          pInputOrderAction->LimitPrice=%8.3f", pInputOrderAction->LimitPrice);
        CPrintApi::DbgPrint("          pInputOrderAction->VolumeChange=%d", pInputOrderAction->VolumeChange);
        CPrintApi::DbgPrint("          pInputOrderAction->UserID=%s", pInputOrderAction->UserID);
        CPrintApi::DbgPrint("          pInputOrderAction->InstrumentID=%s", pInputOrderAction->InstrumentID);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pInputExecOrder)
    {
        CPrintApi::DbgPrint("----参数：pInputExecOrder->BrokerID=%s", pInputExecOrder->BrokerID);
        CPrintApi::DbgPrint("          pInputExecOrder->InvestorID=%s", pInputExecOrder->InvestorID);
        CPrintApi::DbgPrint("          pInputExecOrder->InstrumentID=%s", pInputExecOrder->InstrumentID);
        CPrintApi::DbgPrint("          pInputExecOrder->ExecOrderRef=%s", pInputExecOrder->ExecOrderRef);
        CPrintApi::DbgPrint("          pInputExecOrder->UserID=%s", pInputExecOrder->UserID);
        CPrintApi::DbgPrint("          pInputExecOrder->Volume=%d", pInputExecOrder->Volume);
        CPrintApi::DbgPrint("          pInputExecOrder->RequestID=%d", pInputExecOrder->RequestID); /* 请求标志 */
        CPrintApi::DbgPrint("          pInputExecOrder->BusinessUnit=%s", pInputExecOrder->BusinessUnit);
        CPrintApi::DbgPrint("          pInputExecOrder->OffsetFlag=%c", pInputExecOrder->OffsetFlag);
        CPrintApi::DbgPrint("          pInputExecOrder->HedgeFlag=%c", pInputExecOrder->HedgeFlag);
        CPrintApi::DbgPrint("          pInputExecOrder->ActionType=%c", pInputExecOrder->ActionType);
        CPrintApi::DbgPrint("          pInputExecOrder->PosiDirection=%c", pInputExecOrder->PosiDirection);
        CPrintApi::DbgPrint("          pInputExecOrder->ReservePositionFlag=%c", pInputExecOrder->ReservePositionFlag);
        CPrintApi::DbgPrint("          pInputExecOrder->CloseFlag=%c", pInputExecOrder->CloseFlag);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pExecOrderAction)
    {
        CPrintApi::DbgPrint("----参数：pExecOrderAction->BrokerID=%s", pExecOrderAction->BrokerID);
        CPrintApi::DbgPrint("          pExecOrderAction->InvestorID=%s", pExecOrderAction->InvestorID);
        CPrintApi::DbgPrint("          pExecOrderAction->ExecOrderActionRef=%s", pExecOrderAction->ExecOrderActionRef);
        CPrintApi::DbgPrint("          pExecOrderAction->ExecOrderRef=%s", pExecOrderAction->ExecOrderRef);
        CPrintApi::DbgPrint("          pExecOrderAction->RequestID=%d", pExecOrderAction->RequestID); /* 请求标志 */
        CPrintApi::DbgPrint("          pExecOrderAction->FrontID=%d", pExecOrderAction->FrontID);
        CPrintApi::DbgPrint("          pExecOrderAction->SessionID=%d", pExecOrderAction->SessionID);
        CPrintApi::DbgPrint("          pExecOrderAction->ExchangeID=%s", pExecOrderAction->ExchangeID);
        CPrintApi::DbgPrint("          pExecOrderAction->ExecOrderSysID=%s", pExecOrderAction->ExecOrderSysID);
        CPrintApi::DbgPrint("          pExecOrderAction->ActionFlag=%c", pExecOrderAction->ActionFlag);
        CPrintApi::DbgPrint("          pExecOrderAction->ActionDate=%s", pExecOrderAction->ActionDate);
        CPrintApi::DbgPrint("          pExecOrderAction->ActionTime=%s", pExecOrderAction->ActionTime);
        CPrintApi::DbgPrint("          pExecOrderAction->TraderID=%s", pExecOrderAction->TraderID);
        CPrintApi::DbgPrint("          pExecOrderAction->InstallID=%d", pExecOrderAction->InstallID);
        CPrintApi::DbgPrint("          pExecOrderAction->ExecOrderLocalID=%s", pExecOrderAction->ExecOrderLocalID);
        CPrintApi::DbgPrint("          pExecOrderAction->ActionLocalID=%s", pExecOrderAction->ActionLocalID);
        CPrintApi::DbgPrint("          pExecOrderAction->ParticipantID=%s", pExecOrderAction->ParticipantID);
        CPrintApi::DbgPrint("          pExecOrderAction->ClientID=%s", pExecOrderAction->ClientID);
        CPrintApi::DbgPrint("          pExecOrderAction->BusinessUnit=%s", pExecOrderAction->BusinessUnit);
        CPrintApi::DbgPrint("          pExecOrderAction->OrderActionStatus=%c", pExecOrderAction->OrderActionStatus);
        CPrintApi::DbgPrint("          pExecOrderAction->UserID=%s", pExecOrderAction->UserID);
        CPrintApi::DbgPrint("          pExecOrderAction->ActionType=%c", pExecOrderAction->ActionType);
        CPrintApi::DbgPrint("          pExecOrderAction->StatusMsg=%s", pExecOrderAction->StatusMsg);
        CPrintApi::DbgPrint("          pExecOrderAction->InstrumentID=%s", pExecOrderAction->InstrumentID);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pInputExecOrderAction)
    {
        CPrintApi::DbgPrint("----参数：pInputExecOrderAction->BrokerID=%s", pInputExecOrderAction->BrokerID);
        CPrintApi::DbgPrint("          pInputExecOrderAction->InvestorID=%s", pInputExecOrderAction->InvestorID);
        CPrintApi::DbgPrint("          pInputExecOrderAction->ExecOrderActionRef=%s", pInputExecOrderAction->ExecOrderActionRef);
        CPrintApi::DbgPrint("          pInputExecOrderAction->ExecOrderRef=%s", pInputExecOrderAction->ExecOrderRef);
        CPrintApi::DbgPrint("          pInputExecOrderAction->RequestID=%d", pInputExecOrderAction->RequestID);
        CPrintApi::DbgPrint("          pInputExecOrderAction->FrontID=%d", pInputExecOrderAction->FrontID);
        CPrintApi::DbgPrint("          pInputExecOrderAction->SessionID=%d", pInputExecOrderAction->SessionID);
        CPrintApi::DbgPrint("          pInputExecOrderAction->ExchangeID=%s", pInputExecOrderAction->ExchangeID);
        CPrintApi::DbgPrint("          pInputExecOrderAction->ExecOrderSysID=%s", pInputExecOrderAction->ExecOrderSysID);
        CPrintApi::DbgPrint("          pInputExecOrderAction->ActionFlag=%c", pInputExecOrderAction->ActionFlag);
        CPrintApi::DbgPrint("          pInputExecOrderAction->UserID=%s", pInputExecOrderAction->UserID);
        CPrintApi::DbgPrint("          pInputExecOrderAction->InstrumentID=%s", pInputExecOrderAction->InstrumentID);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pInputQuote)
    {
        CPrintApi::DbgPrint("----参数：pInputQuote->BrokerID=%s", pInputQuote->BrokerID);
        CPrintApi::DbgPrint("          pInputQuote->InvestorID=%s", pInputQuote->InvestorID);
        CPrintApi::DbgPrint("          pInputQuote->InstrumentID=%s", pInputQuote->InstrumentID);
        CPrintApi::DbgPrint("          pInputQuote->QuoteRef=%s", pInputQuote->QuoteRef);
        CPrintApi::DbgPrint("          pInputQuote->UserID=%s", pInputQuote->UserID);
        CPrintApi::DbgPrint("          pInputQuote->AskPrice=%8.3f", pInputQuote->AskPrice);
        CPrintApi::DbgPrint("          pInputQuote->BidPrice=%8.3f", pInputQuote->BidPrice);
        CPrintApi::DbgPrint("          pInputQuote->AskVolume=%d", pInputQuote->AskVolume);
        CPrintApi::DbgPrint("          pInputQuote->BidVolume=%d", pInputQuote->BidVolume);
        CPrintApi::DbgPrint("          pInputQuote->RequestID=%d", pInputQuote->RequestID); /* 请求标志 */
        CPrintApi::DbgPrint("          pInputQuote->BusinessUnit=%s", pInputQuote->BusinessUnit);
        CPrintApi::DbgPrint("          pInputQuote->AskOffsetFlag=%c", pInputQuote->AskOffsetFlag);
        CPrintApi::DbgPrint("          pInputQuote->BidOffsetFlag=%c", pInputQuote->BidOffsetFlag);
        CPrintApi::DbgPrint("          pInputQuote->AskHedgeFlag=%c", pInputQuote->AskHedgeFlag);
        CPrintApi::DbgPrint("          pInputQuote->BidHedgeFlag=%c", pInputQuote->BidHedgeFlag);
        CPrintApi::DbgPrint("          pInputQuote->AskOrderRef=%s", pInputQuote->AskOrderRef);
        CPrintApi::DbgPrint("          pInputQuote->BidOrderRef=%s", pInputQuote->BidOrderRef);
        CPrintApi::DbgPrint("          pInputQuote->ForQuoteSysID=%s", pInputQuote->ForQuoteSysID);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pQuoteAction)
    {
        CPrintApi::DbgPrint("----参数：pQuoteAction->BrokerID=%s", pQuoteAction->BrokerID);
        CPrintApi::DbgPrint("          pQuoteAction->InvestorID=%s", pQuoteAction->InvestorID);
        CPrintApi::DbgPrint("          pQuoteAction->QuoteActionRef=%s", pQuoteAction->QuoteActionRef);
        CPrintApi::DbgPrint("          pQuoteAction->QuoteRef=%s", pQuoteAction->QuoteRef);
        CPrintApi::DbgPrint("          pQuoteAction->RequestID=%d", pQuoteAction->RequestID); /* 请求标志 */
        CPrintApi::DbgPrint("          pQuoteAction->FrontID=%d", pQuoteAction->FrontID);
        CPrintApi::DbgPrint("          pQuoteAction->SessionID=%d", pQuoteAction->SessionID);
        CPrintApi::DbgPrint("          pQuoteAction->ExchangeID=%s", pQuoteAction->ExchangeID);
        CPrintApi::DbgPrint("          pQuoteAction->QuoteSysID=%s", pQuoteAction->QuoteSysID);
        CPrintApi::DbgPrint("          pQuoteAction->ActionFlag=%c", pQuoteAction->ActionFlag);
        CPrintApi::DbgPrint("          pQuoteAction->ActionDate=%s", pQuoteAction->ActionDate);
        CPrintApi::DbgPrint("          pQuoteAction->ActionTime=%s", pQuoteAction->ActionTime);
        CPrintApi::DbgPrint("          pQuoteAction->TraderID=%s", pQuoteAction->TraderID);
        CPrintApi::DbgPrint("          pQuoteAction->InstallID=%d", pQuoteAction->InstallID);
        CPrintApi::DbgPrint("          pQuoteAction->QuoteLocalID=%s", pQuoteAction->QuoteLocalID);
        CPrintApi::DbgPrint("          pQuoteAction->ActionLocalID=%s", pQuoteAction->ActionLocalID);
        CPrintApi::DbgPrint("          pQuoteAction->ParticipantID=%s", pQuoteAction->ParticipantID);
        CPrintApi::DbgPrint("          pQuoteAction->ClientID=%s", pQuoteAction->ClientID);
        CPrintApi::DbgPrint("          pQuoteAction->BusinessUnit=%s", pQuoteAction->BusinessUnit);
        CPrintApi::DbgPrint("          pQuoteAction->OrderActionStatus=%c", pQuoteAction->OrderActionStatus);
        CPrintApi::DbgPrint("          pQuoteAction->UserID=%s", pQuoteAction->UserID);
        CPrintApi::DbgPrint("          pQuoteAction->StatusMsg=%s", pQuoteAction->StatusMsg);
        CPrintApi::DbgPrint("          pQuoteAction->InstrumentID=%s", pQuoteAction->InstrumentID);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pInputQuoteAction)
    {
        CPrintApi::DbgPrint("----参数：pInputQuoteAction->BrokerID=%s", pInputQuoteAction->BrokerID);
        CPrintApi::DbgPrint("          pInputQuoteAction->InvestorID=%s", pInputQuoteAction->InvestorID);
        CPrintApi::DbgPrint("          pInputQuoteAction->QuoteActionRef=%s", pInputQuoteAction->QuoteActionRef);
        CPrintApi::DbgPrint("          pInputQuoteAction->QuoteRef=%s", pInputQuoteAction->QuoteRef);
        CPrintApi::DbgPrint("          pInputQuoteAction->RequestID=%d", pInputQuoteAction->RequestID);
        CPrintApi::DbgPrint("          pInputQuoteAction->FrontID=%d", pInputQuoteAction->FrontID);
        CPrintApi::DbgPrint("          pInputQuoteAction->SessionID=%d", pInputQuoteAction->SessionID);
        CPrintApi::DbgPrint("          pInputQuoteAction->ExchangeID=%s", pInputQuoteAction->ExchangeID);
        CPrintApi::DbgPrint("          pInputQuoteAction->QuoteSysID=%s", pInputQuoteAction->QuoteSysID);
        CPrintApi::DbgPrint("          pInputQuoteAction->ActionFlag=%c", pInputQuoteAction->ActionFlag);
        CPrintApi::DbgPrint("          pInputQuoteAction->UserID=%s", pInputQuoteAction->UserID);
        CPrintApi::DbgPrint("          pInputQuoteAction->InstrumentID=%s", pInputQuoteAction->InstrumentID);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pInputForQuote)
    {
        CPrintApi::DbgPrint("----参数：pInputForQuote->BrokerID=%s", pInputForQuote->BrokerID);
        CPrintApi::DbgPrint("          pInputForQuote->InvestorID=%s", pInputForQuote->InvestorID);
        CPrintApi::DbgPrint("          pInputForQuote->InstrumentID=%s", pInputForQuote->InstrumentID);
        CPrintApi::DbgPrint("          pInputForQuote->ForQuoteRef=%s", pInputForQuote->ForQuoteRef);
        CPrintApi::DbgPrint("          pInputForQuote->UserID=%s", pInputForQuote->UserID);   
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pNotice)
    {
        CPrintApi::DbgPrint("----参数：pNotice->BrokerID=%s", pNotice->BrokerID);
        CPrintApi::DbgPrint("          pNotice->Content=%s", pNotice->Content);
        CPrintApi::DbgPrint("          pNotice->SequenceLabel=%02d", pNotice->SequenceLabel);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pExchange)
    {
        CPrintApi::DbgPrint("----参数：pExchange->ExchangeID=%s", pExchange->ExchangeID);
        CPrintApi::DbgPrint("          pExchange->ExchangeName=%s", pExchange->ExchangeName);
        CPrintApi::DbgPrint("          pExchange->ExchangeProperty=%c", pExchange->ExchangeProperty);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pTradingCode)
    {
        CPrintApi::DbgPrint("----参数：pTradingCode->InvestorID=%s", pTradingCode->InvestorID);
        CPrintApi::DbgPrint("          pTradingCode->BrokerID=%s", pTradingCode->BrokerID);
        CPrintApi::DbgPrint("          pTradingCode->ExchangeID=%s", pTradingCode->ExchangeID);
        CPrintApi::DbgPrint("          pTradingCode->ClientID=%s", pTradingCode->ClientID);
        CPrintApi::DbgPrint("          pTradingCode->IsActive=%d", pTradingCode->IsActive);
        CPrintApi::DbgPrint("          pTradingCode->ClientIDType=%c", pTradingCode->ClientIDType);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pProduct)
    {
        CPrintApi::DbgPrint("----参数：pProduct->ProductID=%s", pProduct->ProductID);
        CPrintApi::DbgPrint("          pProduct->ProductName=%s", pProduct->ProductName);
        CPrintApi::DbgPrint("          pProduct->ExchangeID=%s", pProduct->ExchangeID);
        CPrintApi::DbgPrint("          pProduct->ProductClass=%c", pProduct->ProductClass);
        CPrintApi::DbgPrint("          pProduct->VolumeMultiple=%d", pProduct->VolumeMultiple);
        CPrintApi::DbgPrint("          pProduct->PriceTick=%8.3f", pProduct->PriceTick);
        CPrintApi::DbgPrint("          pProduct->MaxMarketOrderVolume=%d", pProduct->MaxMarketOrderVolume);
        CPrintApi::DbgPrint("          pProduct->MinMarketOrderVolume=%d", pProduct->MinMarketOrderVolume);
        CPrintApi::DbgPrint("          pProduct->MaxLimitOrderVolume=%d", pProduct->MaxLimitOrderVolume);
        CPrintApi::DbgPrint("          pProduct->MinLimitOrderVolume=%d", pProduct->MinLimitOrderVolume);
        CPrintApi::DbgPrint("          pProduct->PositionType=%c", pProduct->PositionType);
        CPrintApi::DbgPrint("          pProduct->PositionDateType=%c", pProduct->PositionDateType);
        CPrintApi::DbgPrint("          pProduct->CloseDealType=%c", pProduct->CloseDealType);
        CPrintApi::DbgPrint("          pProduct->TradeCurrencyID=%s", pProduct->TradeCurrencyID);
        CPrintApi::DbgPrint("          pProduct->MortgageFundUseRange=%c", pProduct->MortgageFundUseRange);
        CPrintApi::DbgPrint("          pProduct->ExchangeProductID=%s", pProduct->ExchangeProductID);
        CPrintApi::DbgPrint("          pProduct->UnderlyingMultiple=%8.3f", pProduct->UnderlyingMultiple);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pInstrument)
    {
        CPrintApi::DbgPrint("----参数：pInstrument->InstrumentID=%s", pInstrument->InstrumentID);
        CPrintApi::DbgPrint("          pInstrument->ExchangeID=%s", pInstrument->ExchangeID);
        CPrintApi::DbgPrint("          pInstrument->InstrumentName=%s", pInstrument->InstrumentName);
        CPrintApi::DbgPrint("          pInstrument->ExchangeInstID=%s", pInstrument->ExchangeInstID);
        CPrintApi::DbgPrint("          pInstrument->ProductID=%s", pInstrument->ProductID);
        CPrintApi::DbgPrint("          pInstrument->ProductClass=%c", pInstrument->ProductClass);
        CPrintApi::DbgPrint("          pInstrument->DeliveryYear=%d", pInstrument->DeliveryYear);
        CPrintApi::DbgPrint("          pInstrument->DeliveryMonth=%d", pInstrument->DeliveryMonth);
        CPrintApi::DbgPrint("          pInstrument->MaxMarketOrderVolume=%d", pInstrument->MaxMarketOrderVolume);
        CPrintApi::DbgPrint("          pInstrument->MinMarketOrderVolume=%d", pInstrument->MinMarketOrderVolume);
        CPrintApi::DbgPrint("          pInstrument->MaxLimitOrderVolume=%d", pInstrument->MaxLimitOrderVolume);
        CPrintApi::DbgPrint("          pInstrument->MinLimitOrderVolume=%d", pInstrument->MinLimitOrderVolume);
        CPrintApi::DbgPrint("          pInstrument->VolumeMultiple=%8.3f", pInstrument->VolumeMultiple);
        CPrintApi::DbgPrint("          pInstrument->PriceTick=%s", pInstrument->PriceTick);
        CPrintApi::DbgPrint("          pInstrument->CreateDate=%s", pInstrument->CreateDate);
        CPrintApi::DbgPrint("          pInstrument->OpenDate=%s", pInstrument->OpenDate);
        CPrintApi::DbgPrint("          pInstrument->ExpireDate=%s", pInstrument->ExpireDate);
        CPrintApi::DbgPrint("          pInstrument->StartDelivDate=%s", pInstrument->StartDelivDate);
        CPrintApi::DbgPrint("          pInstrument->EndDelivDate=%s", pInstrument->EndDelivDate);
        CPrintApi::DbgPrint("          pInstrument->InstLifePhase=%c", pInstrument->InstLifePhase);
        CPrintApi::DbgPrint("          pInstrument->IsTrading=%d", pInstrument->IsTrading);
        CPrintApi::DbgPrint("          pInstrument->PositionType=%c", pInstrument->PositionType);
        CPrintApi::DbgPrint("          pInstrument->PositionDateType=%c", pInstrument->PositionDateType);
        CPrintApi::DbgPrint("          pInstrument->LongMarginRatio=%8.3f", pInstrument->LongMarginRatio);
        CPrintApi::DbgPrint("          pInstrument->ShortMarginRatio=%8.3f", pInstrument->ShortMarginRatio);
        CPrintApi::DbgPrint("          pInstrument->MaxMarginSideAlgorithm=%c", pInstrument->MaxMarginSideAlgorithm);
        CPrintApi::DbgPrint("          pInstrument->UnderlyingInstrID=%s", pInstrument->UnderlyingInstrID);
        CPrintApi::DbgPrint("          pInstrument->StrikePrice=%8.3f", pInstrument->StrikePrice);
        CPrintApi::DbgPrint("          pInstrument->OptionsType=%c", pInstrument->OptionsType);
        CPrintApi::DbgPrint("          pInstrument->UnderlyingMultiple=%8.3f", pInstrument->UnderlyingMultiple);
        CPrintApi::DbgPrint("          pInstrument->CombinationType=%c", pInstrument->CombinationType);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pDepthMarketData)
    {
        CPrintApi::DbgPrint("----参数：pDepthMarketData->TradingDay=%s", pDepthMarketData->TradingDay);
        CPrintApi::DbgPrint("          pDepthMarketData->InstrumentID=%s", pDepthMarketData->InstrumentID);
        CPrintApi::DbgPrint("          pDepthMarketData->ExchangeID=%s", pDepthMarketData->ExchangeID);
        CPrintApi::DbgPrint("          pDepthMarketData->ExchangeInstID=%s", pDepthMarketData->ExchangeInstID);
        CPrintApi::DbgPrint("          pDepthMarketData->LastPrice=%8.3f", pDepthMarketData->LastPrice);
        CPrintApi::DbgPrint("          pDepthMarketData->PreSettlementPrice=%8.3f", pDepthMarketData->PreSettlementPrice);
        CPrintApi::DbgPrint("          pDepthMarketData->PreClosePrice=%8.3f", pDepthMarketData->PreClosePrice);
        CPrintApi::DbgPrint("          pDepthMarketData->PreOpenInterest=%8.3f", pDepthMarketData->PreOpenInterest);
        CPrintApi::DbgPrint("          pDepthMarketData->OpenPrice=%8.3f", pDepthMarketData->OpenPrice);
        CPrintApi::DbgPrint("          pDepthMarketData->HighestPrice=%8.3f", pDepthMarketData->HighestPrice);
        CPrintApi::DbgPrint("          pDepthMarketData->LowestPrice=%8.3f", pDepthMarketData->LowestPrice);
        CPrintApi::DbgPrint("          pDepthMarketData->Volume=%d", pDepthMarketData->Volume);
        CPrintApi::DbgPrint("          pDepthMarketData->Turnover=%8.3f", pDepthMarketData->Turnover);
        CPrintApi::DbgPrint("          pDepthMarketData->OpenInterest=%8.3f", pDepthMarketData->OpenInterest);
        CPrintApi::DbgPrint("          pDepthMarketData->ClosePrice=%8.3f", pDepthMarketData->ClosePrice);
        CPrintApi::DbgPrint("          pDepthMarketData->SettlementPrice=%8.3f", pDepthMarketData->SettlementPrice);
        CPrintApi::DbgPrint("          pDepthMarketData->UpperLimitPrice=%8.3f", pDepthMarketData->UpperLimitPrice);
        CPrintApi::DbgPrint("          pDepthMarketData->LowerLimitPrice=%8.3f", pDepthMarketData->LowerLimitPrice);
        CPrintApi::DbgPrint("          pDepthMarketData->PreDelta=%8.3f", pDepthMarketData->PreDelta);
        CPrintApi::DbgPrint("          pDepthMarketData->CurrDelta=%8.3f", pDepthMarketData->CurrDelta);
        CPrintApi::DbgPrint("          pDepthMarketData->UpdateTime=%s", pDepthMarketData->UpdateTime);
        CPrintApi::DbgPrint("          pDepthMarketData->UpdateMillisec=%u", pDepthMarketData->UpdateMillisec);
        CPrintApi::DbgPrint("          pDepthMarketData->BidPrice1=%8.3f", pDepthMarketData->BidPrice1);
        CPrintApi::DbgPrint("          pDepthMarketData->BidVolume1=%d", pDepthMarketData->BidVolume1);
        CPrintApi::DbgPrint("          pDepthMarketData->AskPrice1=%8.3f", pDepthMarketData->AskPrice1);
        CPrintApi::DbgPrint("          pDepthMarketData->AskVolume1=%d", pDepthMarketData->AskVolume1);
        CPrintApi::DbgPrint("          pDepthMarketData->BidPrice2=%8.3f", pDepthMarketData->BidPrice2);
        CPrintApi::DbgPrint("          pDepthMarketData->BidVolume2=%d", pDepthMarketData->BidVolume2);
        CPrintApi::DbgPrint("          pDepthMarketData->AskPrice2=%8.3f", pDepthMarketData->AskPrice2);
        CPrintApi::DbgPrint("          pDepthMarketData->AskVolume2=%d", pDepthMarketData->AskVolume2);
        CPrintApi::DbgPrint("          pDepthMarketData->BidPrice3=%8.3f", pDepthMarketData->BidPrice3);
        CPrintApi::DbgPrint("          pDepthMarketData->BidVolume3=%d", pDepthMarketData->BidVolume3);
        CPrintApi::DbgPrint("          pDepthMarketData->AskPrice3=%8.3f", pDepthMarketData->AskPrice3);
        CPrintApi::DbgPrint("          pDepthMarketData->AskVolume3=%d", pDepthMarketData->AskVolume3);
        CPrintApi::DbgPrint("          pDepthMarketData->BidPrice4=%8.3f", pDepthMarketData->BidPrice4);
        CPrintApi::DbgPrint("          pDepthMarketData->BidVolume4=%d", pDepthMarketData->BidVolume4);
        CPrintApi::DbgPrint("          pDepthMarketData->AskPrice4=%8.3f", pDepthMarketData->AskPrice4);
        CPrintApi::DbgPrint("          pDepthMarketData->AskVolume4=%d", pDepthMarketData->AskVolume4);
        CPrintApi::DbgPrint("          pDepthMarketData->BidPrice5=%8.3f", pDepthMarketData->BidPrice5);
        CPrintApi::DbgPrint("          pDepthMarketData->BidVolume5=%d", pDepthMarketData->BidVolume5);
        CPrintApi::DbgPrint("          pDepthMarketData->AskPrice5=%8.3f", pDepthMarketData->AskPrice5);
        CPrintApi::DbgPrint("          pDepthMarketData->AskVolume5=%d", pDepthMarketData->AskVolume5);
        CPrintApi::DbgPrint("          pDepthMarketData->AveragePrice=%8.3f", pDepthMarketData->AveragePrice);
        CPrintApi::DbgPrint("          pDepthMarketData->ActionDay=%s", pDepthMarketData->ActionDay);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pInvestorPosition)
    {
        CPrintApi::DbgPrint("----参数：pInvestorPosition->InstrumentID=%s", pInvestorPosition->InstrumentID);
        CPrintApi::DbgPrint("          pInvestorPosition->BrokerID=%s", pInvestorPosition->BrokerID);
        CPrintApi::DbgPrint("          pInvestorPosition->InvestorID=%s", pInvestorPosition->InvestorID);
        CPrintApi::DbgPrint("          pInvestorPosition->PosiDirection=%c", pInvestorPosition->PosiDirection);
        CPrintApi::DbgPrint("          pInvestorPosition->HedgeFlag=%c", pInvestorPosition->HedgeFlag);
        CPrintApi::DbgPrint("          pInvestorPosition->PositionDate=%c", pInvestorPosition->PositionDate);
        CPrintApi::DbgPrint("          pInvestorPosition->YdPosition=%d", pInvestorPosition->YdPosition);
        CPrintApi::DbgPrint("          pInvestorPosition->Position=%d", pInvestorPosition->Position);
        CPrintApi::DbgPrint("          pInvestorPosition->LongFrozen=%d", pInvestorPosition->LongFrozen);
        CPrintApi::DbgPrint("          pInvestorPosition->ShortFrozen=%d", pInvestorPosition->ShortFrozen);
        CPrintApi::DbgPrint("          pInvestorPosition->LongFrozenAmount=%8.3f", pInvestorPosition->LongFrozenAmount);
        CPrintApi::DbgPrint("          pInvestorPosition->ShortFrozenAmount=%8.3f", pInvestorPosition->ShortFrozenAmount);
        CPrintApi::DbgPrint("          pInvestorPosition->OpenVolume=%d", pInvestorPosition->OpenVolume);
        CPrintApi::DbgPrint("          pInvestorPosition->CloseVolume=%d", pInvestorPosition->CloseVolume);
        CPrintApi::DbgPrint("          pInvestorPosition->OpenAmount=%8.3f", pInvestorPosition->OpenAmount);
        CPrintApi::DbgPrint("          pInvestorPosition->CloseAmount=%8.3f", pInvestorPosition->CloseAmount);
        CPrintApi::DbgPrint("          pInvestorPosition->PositionCost=%8.3f", pInvestorPosition->PositionCost);
        CPrintApi::DbgPrint("          pInvestorPosition->PreMargin=%8.3f", pInvestorPosition->PreMargin);
        CPrintApi::DbgPrint("          pInvestorPosition->UseMargin=%8.3f", pInvestorPosition->UseMargin);
        CPrintApi::DbgPrint("          pInvestorPosition->FrozenMargin=%8.3f", pInvestorPosition->FrozenMargin);
        CPrintApi::DbgPrint("          pInvestorPosition->FrozenCash=%8.3f", pInvestorPosition->FrozenCash);
        CPrintApi::DbgPrint("          pInvestorPosition->FrozenCommission=%8.3f", pInvestorPosition->FrozenCommission);
        CPrintApi::DbgPrint("          pInvestorPosition->CashIn=%8.3f", pInvestorPosition->CashIn);
        CPrintApi::DbgPrint("          pInvestorPosition->Commission=%8.3f", pInvestorPosition->Commission);
        CPrintApi::DbgPrint("          pInvestorPosition->CloseProfit=%8.3f", pInvestorPosition->CloseProfit);
        CPrintApi::DbgPrint("          pInvestorPosition->PositionProfit=%8.3f", pInvestorPosition->PositionProfit);
        CPrintApi::DbgPrint("          pInvestorPosition->PreSettlementPrice=%8.3f", pInvestorPosition->PreSettlementPrice);
        CPrintApi::DbgPrint("          pInvestorPosition->SettlementPrice=%8.3f", pInvestorPosition->SettlementPrice);
        CPrintApi::DbgPrint("          pInvestorPosition->TradingDay=%s", pInvestorPosition->TradingDay);
        CPrintApi::DbgPrint("          pInvestorPosition->SettlementID=%d", pInvestorPosition->SettlementID);
        CPrintApi::DbgPrint("          pInvestorPosition->OpenCost=%8.3f", pInvestorPosition->OpenCost);
        CPrintApi::DbgPrint("          pInvestorPosition->ExchangeMargin=%8.3f", pInvestorPosition->ExchangeMargin);
        CPrintApi::DbgPrint("          pInvestorPosition->CombPosition=%d", pInvestorPosition->CombPosition);
        CPrintApi::DbgPrint("          pInvestorPosition->CombLongFrozen=%d", pInvestorPosition->CombLongFrozen);
        CPrintApi::DbgPrint("          pInvestorPosition->CombShortFrozen=%d", pInvestorPosition->CombShortFrozen);
        CPrintApi::DbgPrint("          pInvestorPosition->CloseProfitByDate=%8.3f", pInvestorPosition->CloseProfitByDate);
        CPrintApi::DbgPrint("          pInvestorPosition->CloseProfitByTrade=%8.3f", pInvestorPosition->CloseProfitByTrade);
        CPrintApi::DbgPrint("          pInvestorPosition->TodayPosition=%d", pInvestorPosition->TodayPosition);
        CPrintApi::DbgPrint("          pInvestorPosition->MarginRateByMoney=%8.3f", pInvestorPosition->MarginRateByMoney);
        CPrintApi::DbgPrint("          pInvestorPosition->MarginRateByVolume=%8.3f", pInvestorPosition->MarginRateByVolume);
        CPrintApi::DbgPrint("          pInvestorPosition->StrikeFrozen=%d", pInvestorPosition->StrikeFrozen);
        CPrintApi::DbgPrint("          pInvestorPosition->StrikeFrozenAmount=%8.3f", pInvestorPosition->StrikeFrozenAmount);
        CPrintApi::DbgPrint("          pInvestorPosition->AbandonFrozen=%d", pInvestorPosition->AbandonFrozen);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pTradingAccount)
    {
        CPrintApi::DbgPrint("----参数：pTradingAccount->BrokerID=%s", pTradingAccount->BrokerID);
        CPrintApi::DbgPrint("          pTradingAccount->AccountID=%s", pTradingAccount->AccountID);
        CPrintApi::DbgPrint("          pTradingAccount->PreMortgage=%8.3f", pTradingAccount->PreMortgage);
        CPrintApi::DbgPrint("          pTradingAccount->PreCredit=%8.3f", pTradingAccount->PreCredit);
        CPrintApi::DbgPrint("          pTradingAccount->PreDeposit=%8.3f", pTradingAccount->PreDeposit);
        CPrintApi::DbgPrint("          pTradingAccount->PreBalance=%8.3f", pTradingAccount->PreBalance);
        CPrintApi::DbgPrint("          pTradingAccount->PreMargin=%8.3f", pTradingAccount->PreMargin);
        CPrintApi::DbgPrint("          pTradingAccount->InterestBase=%8.3f", pTradingAccount->InterestBase);
        CPrintApi::DbgPrint("          pTradingAccount->Interest=%8.3f", pTradingAccount->Interest);
        CPrintApi::DbgPrint("          pTradingAccount->Deposit=%8.3f", pTradingAccount->Deposit);
        CPrintApi::DbgPrint("          pTradingAccount->Withdraw=%8.3f", pTradingAccount->Withdraw);
        CPrintApi::DbgPrint("          pTradingAccount->FrozenMargin=%8.3f", pTradingAccount->FrozenMargin);
        CPrintApi::DbgPrint("          pTradingAccount->FrozenCash=%8.3f", pTradingAccount->FrozenCash);
        CPrintApi::DbgPrint("          pTradingAccount->FrozenCommission=%8.3f", pTradingAccount->FrozenCommission);
        CPrintApi::DbgPrint("          pTradingAccount->CurrMargin=%8.3f", pTradingAccount->CurrMargin);
        CPrintApi::DbgPrint("          pTradingAccount->CashIn=%8.3f", pTradingAccount->CashIn);
        CPrintApi::DbgPrint("          pTradingAccount->Commission=%8.3f", pTradingAccount->Commission);
        CPrintApi::DbgPrint("          pTradingAccount->CloseProfit=%8.3f", pTradingAccount->CloseProfit);
        CPrintApi::DbgPrint("          pTradingAccount->PositionProfit=%8.3f", pTradingAccount->PositionProfit);
        CPrintApi::DbgPrint("          pTradingAccount->Balance=%8.3f", pTradingAccount->Balance);
        CPrintApi::DbgPrint("          pTradingAccount->Available=%8.3f", pTradingAccount->Available);
        CPrintApi::DbgPrint("          pTradingAccount->WithdrawQuota=%8.3f", pTradingAccount->WithdrawQuota);
        CPrintApi::DbgPrint("          pTradingAccount->Reserve=%8.3f", pTradingAccount->Reserve);
        CPrintApi::DbgPrint("          pTradingAccount->TradingDay=%s", pTradingAccount->TradingDay);
        CPrintApi::DbgPrint("          pTradingAccount->SettlementID=%08d", pTradingAccount->SettlementID);
        CPrintApi::DbgPrint("          pTradingAccount->Credit=%8.3f", pTradingAccount->Credit);
        CPrintApi::DbgPrint("          pTradingAccount->Mortgage=%8.3f", pTradingAccount->Mortgage);
        CPrintApi::DbgPrint("          pTradingAccount->ExchangeMargin=%8.3f", pTradingAccount->ExchangeMargin);
        CPrintApi::DbgPrint("          pTradingAccount->DeliveryMargin=%8.3f", pTradingAccount->DeliveryMargin);
        CPrintApi::DbgPrint("          pTradingAccount->ExchangeDeliveryMargin=%8.3f", pTradingAccount->ExchangeDeliveryMargin);
        CPrintApi::DbgPrint("          pTradingAccount->ReserveBalance=%8.3f", pTradingAccount->ReserveBalance);
        CPrintApi::DbgPrint("          pTradingAccount->CurrencyID=%s", pTradingAccount->CurrencyID);
        CPrintApi::DbgPrint("          pTradingAccount->PreFundMortgageIn=%8.3f", pTradingAccount->PreFundMortgageIn);
        CPrintApi::DbgPrint("          pTradingAccount->PreFundMortgageOut=%8.3f", pTradingAccount->PreFundMortgageOut);
        CPrintApi::DbgPrint("          pTradingAccount->FundMortgageIn=%8.3f", pTradingAccount->FundMortgageIn);
        CPrintApi::DbgPrint("          pTradingAccount->FundMortgageOut=%8.3f", pTradingAccount->FundMortgageOut);
        CPrintApi::DbgPrint("          pTradingAccount->FundMortgageAvailable=%8.3f", pTradingAccount->FundMortgageAvailable);
        CPrintApi::DbgPrint("          pTradingAccount->MortgageableFund=%8.3f", pTradingAccount->MortgageableFund);
        CPrintApi::DbgPrint("          pTradingAccount->SpecProductMargin=%8.3f", pTradingAccount->SpecProductMargin);
        CPrintApi::DbgPrint("          pTradingAccount->SpecProductFrozenMargin=%8.3f", pTradingAccount->SpecProductFrozenMargin);
        CPrintApi::DbgPrint("          pTradingAccount->SpecProductCommission=%8.3f", pTradingAccount->SpecProductCommission);
        CPrintApi::DbgPrint("          pTradingAccount->SpecProductFrozenCommission=%8.3f", pTradingAccount->SpecProductFrozenCommission);
        CPrintApi::DbgPrint("          pTradingAccount->SpecProductPositionProfit=%8.3f", pTradingAccount->SpecProductPositionProfit);
        CPrintApi::DbgPrint("          pTradingAccount->SpecProductCloseProfit=%8.3f", pTradingAccount->SpecProductCloseProfit);
        CPrintApi::DbgPrint("          pTradingAccount->SpecProductPositionProfitByAlg=%8.3f", pTradingAccount->SpecProductPositionProfitByAlg);
        CPrintApi::DbgPrint("          pTradingAccount->SpecProductExchangeMargin=%8.3f", pTradingAccount->SpecProductExchangeMargin);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pInvestor)
    {
        CPrintApi::DbgPrint("----参数：pInvestor->InvestorID=%s", pInvestor->InvestorID);
        CPrintApi::DbgPrint("          pInvestor->BrokerID=%s", pInvestor->BrokerID);
        CPrintApi::DbgPrint("          pInvestor->InvestorGroupID=%s", pInvestor->InvestorGroupID);
        CPrintApi::DbgPrint("          pInvestor->InvestorName=%s", pInvestor->InvestorName);
        CPrintApi::DbgPrint("          pInvestor->IdentifiedCardType=%c", pInvestor->IdentifiedCardType);
        CPrintApi::DbgPrint("          pInvestor->IdentifiedCardNo=%s", pInvestor->IdentifiedCardNo);
        CPrintApi::DbgPrint("          pInvestor->IsActive=%d", pInvestor->IsActive);
        CPrintApi::DbgPrint("          pInvestor->Telephone=%s", pInvestor->Telephone);
        CPrintApi::DbgPrint("          pInvestor->Address=%s", pInvestor->Address);
        CPrintApi::DbgPrint("          pInvestor->OpenDate=%s", pInvestor->OpenDate);
        CPrintApi::DbgPrint("          pInvestor->Mobile=%s", pInvestor->Mobile);
        CPrintApi::DbgPrint("          pInvestor->CommModelID=%s", pInvestor->CommModelID);
        CPrintApi::DbgPrint("          pInvestor->MarginModelID=%s", pInvestor->MarginModelID);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

void CPrintParams::PrintParams(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams *inst = CPrintParams::GetInstance();
    if (!inst->m_bPrintParams)
        return;
    if (pSpecificInstrument)
    {
        CPrintApi::DbgPrint("----参数：pSpecificInstrument->InstrumentID=%s", pSpecificInstrument->InstrumentID);
    }
    if (pRspInfo)
    {
        CPrintApi::DbgPrint("----参数: pRspInfo->ErrorID=%08d", pRspInfo->ErrorID);
        CPrintApi::DbgPrint("          pRspInfo->ErrorMsg=%s", pRspInfo->ErrorMsg);
    }
}

CPrintParams *CPrintParams::GetInstance(void)
{
    if (!m_pInstance)
    {
        m_pInstance = new CPrintParams();
        m_pInstance->m_bPrintParams = TRUE; /* 输出参数信息-默认为FALSE */
    }
    return m_pInstance;
}

CPrintParams *CPrintParams::m_pInstance = NULL;

CPrintParams::CPrintParams(void) : m_bPrintParams(FALSE)
{
}

CPrintParams::~CPrintParams(void)
{
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
        m_pInstance->m_bDbgPrint = FALSE; /* 输出调试信息-所有 */
        m_pInstance->m_bDbgCliPrint = FALSE; /* 输出调试信息-命令行 */
        m_pInstance->m_bLogPrint = TRUE; /* 输出日志信息 */
    }
    return m_pInstance;
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

    /* 创建目录 */
    char *szPrintDir = "TraderPrint";
    CreateDir(szPrintDir);

    /* 打开调试文件 */
    m_hDbgFile = fopen("TraderPrint/TraderTesterDbg.txt", "w");

    /* 打开日志文件 */
    m_hLogFile = fopen("TraderPrint/TraderTesterLog.txt", "w");

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

/* 获取时钟时间-以微秒计数 */
void GetClockTime(ClockTime *clock)
{
    /* 获取当前时间 */
    GetLocalTime(&clock->curTm);

    /* 获取当前微秒数和总秒数 */
    timeval tv;
    union {
        LONGLONG ns;
        FILETIME ft;
    } now;
    GetSystemTimeAsFileTime (&now.ft);
    tv.tv_usec = (long) ((now.ns / 10LL) % 1000000LL);
    tv.tv_sec = (long) ((now.ns - 116444736000000000LL) / 10000000LL);
    clock->curUs = tv.tv_usec - clock->curTm.wMilliseconds*1000;
    clock->allUs = ((time_t)tv.tv_sec*(time_t)1000000+tv.tv_usec);
}

/* 创建目录 */
BOOL CreateDir(const char *szDir)
{
    /* 检查参数 */
    if (!szDir || !strlen(szDir))
        return FALSE;

    /* 字符串转换 */
    TCHAR szTDir[128];
    ConvertCStrToTStr(szTDir, sizeof(szTDir), szDir);

    /* 检查目录 */
    if (FILE_ATTRIBUTE_DIRECTORY==::GetFileAttributes(szTDir))
    {
        /* 删除目录 */
        ::RemoveDirectory(szTDir);
    }

    /* 创建目录 */
    return ::CreateDirectory(szTDir, NULL);
}

/* 字符串转换函数 */
int ConvertTStrToCStr(CHAR *dst,  int dst_size, const TCHAR *src)
{
#ifdef UNICODE
    return ConvertWStrToCStr(dst, dst_size, src);
#else
    strcpy(dst, src);
    return strlen(src);
#endif /* UNICODE */
}

/* 字符串转换函数 */
int ConvertCStrToTStr(TCHAR *dst, int dst_size, const CHAR  *src)
{
#ifdef UNICODE
    return ConvertCStrToWStr(dst, dst_size, src);
#else
    strcpy(dst, src);
    return (int)strlen(src);
#endif /* UNICODE */
}

/* 字符串转换函数 */
int ConvertTStrToWStr(WCHAR *dst, int dst_size, const TCHAR *src)
{
#ifdef UNICODE
    wcscpy(dst, src);
    return (int)wcslen(src);
#else
    return ConvertCStrToWStr(dst, dst_size, src);
#endif /* UNICODE */
}

/* 字符串转换函数 */
int ConvertWStrToTStr(TCHAR *dst, int dst_size, const WCHAR *src)
{
#ifdef UNICODE
    wcscpy(dst, src);
    return (int)wcslen(src);
#else
    return ConvertWStrToCStr(dst, dst_size, src);
#endif /* UNICODE */
}

/* 字符串转换函数 */
int ConvertWStrToCStr(CHAR *dst,  int dst_size, const WCHAR *src)
{
    return WideCharToMultiByte(CP_ACP, 0, src, -1, dst, dst_size, NULL, NULL);
}

/* 字符串转换函数 */
int ConvertCStrToWStr(WCHAR *dst, int dst_size, const CHAR  *src)
{
    return MultiByteToWideChar(CP_ACP, 0, src, -1, dst, dst_size);
}

/* 检查响应结果函数 */
BOOL CheckRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
    if (!pRspInfo)
        return TRUE;
    if (pRspInfo->ErrorID)
        return FALSE;
    return TRUE;
}
