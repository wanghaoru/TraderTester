#include "TraderApi.h"
#include "MarketApi.h"

#pragma warning(disable:4996)

CTraderData::CTraderData()
{
    memset(&m_szBrokerID, 0, sizeof(m_szBrokerID));
    memset(&m_szInvestorID, 0, sizeof(m_szInvestorID));
    memset(&m_szExchangeID, 0, sizeof(m_szExchangeID));
    memset(&m_szInstrumentID, 0, sizeof(m_szInstrumentID));
    memset(&m_szUserID, 0, sizeof(m_szUserID));
    memset(&m_szOrderRef, 0, sizeof(m_szOrderRef));
    memset(&m_szOrderActionRef, 0, sizeof(m_szOrderActionRef));
    memset(&m_nRequestID, 0, sizeof(m_nRequestID));
    memset(&m_nFrontID, 0, sizeof(m_nFrontID));
    memset(&m_nSessionID, 0, sizeof(m_nSessionID));
    memset(&m_szOrderSysID, 0, sizeof(m_szOrderSysID));
}

CTraderData::~CTraderData()
{

}

/* 更新交易数据 */
void CTraderData::UpdateTraderData(CThostFtdcInputOrderField *pInputOrder, int nTriggerStage)
{
    CheckFuncNameEx();
}

/* 更新交易数据 */
void CTraderData::UpdateTraderData(CThostFtdcInputOrderActionField *pInputAction, int nTriggerStage)
{
    CheckFuncNameEx();
}

/* 更新交易数据 */
void CTraderData::UpdateTraderData(CThostFtdcOrderActionField *pInputOrder, int nTriggerStage)
{
    CheckFuncNameEx();
}

/* 更新交易数据 */
void CTraderData::UpdateTraderData(CThostFtdcOrderField *pOrder, int nTriggerStage)
{
    CheckFuncNameEx();
}

/* 更新交易数据 */
void CTraderData::UpdateTraderData(CThostFtdcTradeField *pTrader, int nTriggerStage)
{
    CheckFuncNameEx();
}

CTraderSpi::CTraderSpi(void)
{
}

CTraderSpi::~CTraderSpi(void)
{
}

/* 连接通知 */
void CTraderSpi::OnFrontConnected()
{
    CheckFuncNameEx();
    CTraderApi *api = CTraderApi::GetInstance();
    api->m_bConnect = TRUE;
}

/* 断开通知 */
void CTraderSpi::OnFrontDisconnected(int nReason)
{
    CheckFuncNameEx();
    CPrintApi::DbgPrint("----参数：nReason=0x%08x\n", nReason);
    CTraderApi *api = CTraderApi::GetInstance();
    api->m_bConnect = FALSE;
}

/* 心跳通知 */
void CTraderSpi::OnHeartBeatWarning(int nTimeLapse)
{
    CheckFuncNameEx();
    CPrintApi::DbgPrint("----参数：nTimeLapse=%08d", nTimeLapse);
}

/* 报单通知 */
void CTraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
    CheckFuncNameEx();
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
        CPrintApi::DbgPrint("          pOrder->RequestID=%08d", pOrder->RequestID); /* 请求标志 */
        CPrintApi::DbgPrint("          pOrder->OrderLocalID=%s", pOrder->OrderLocalID);
        CPrintApi::DbgPrint("          pOrder->ExchangeID=%s", pOrder->ExchangeID);
        CPrintApi::DbgPrint("          pOrder->ParticipantID=%s", pOrder->ParticipantID);
        CPrintApi::DbgPrint("          pOrder->ClientID=%s", pOrder->ClientID);
        CPrintApi::DbgPrint("          pOrder->ExchangeInstID=%s", pOrder->ExchangeInstID);
        CPrintApi::DbgPrint("          pOrder->TraderID=%s", pOrder->TraderID);
        CPrintApi::DbgPrint("          pOrder->InstallID=%08d", pOrder->InstallID);
        CPrintApi::DbgPrint("          pOrder->OrderSubmitStatus=%c", pOrder->OrderSubmitStatus);/* 报单提交状态 */
        CPrintApi::DbgPrint("          pOrder->NotifySequence=%08d", pOrder->NotifySequence);/* */
        CPrintApi::DbgPrint("          pOrder->TradingDay=%s", pOrder->TradingDay);
        CPrintApi::DbgPrint("          pOrder->SettlementID=%08d", pOrder->SettlementID);
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
        CPrintApi::DbgPrint("          pOrder->SequenceNo=%08d", pOrder->SequenceNo); /* 顺序编号 */
        CPrintApi::DbgPrint("          pOrder->FrontID=%08d", pOrder->FrontID); /* 前置编号 */
        CPrintApi::DbgPrint("          pOrder->SessionID=%08u", pOrder->SessionID); /* 会话编号 */
        CPrintApi::DbgPrint("          pOrder->UserProductInfo=%s", pOrder->UserProductInfo);
        CPrintApi::DbgPrint("          pOrder->StatusMsg=%s", pOrder->StatusMsg);
        CPrintApi::DbgPrint("          pOrder->UserForceClose=%d", pOrder->UserForceClose);
        CPrintApi::DbgPrint("          pOrder->ActiveUserID=%s", pOrder->ActiveUserID);
        CPrintApi::DbgPrint("          pOrder->BrokerOrderSeq=%08d", pOrder->BrokerOrderSeq);
        CPrintApi::DbgPrint("          pOrder->RelativeOrderSysID=%s", pOrder->RelativeOrderSysID);
        CPrintApi::DbgPrint("          pOrder->ZCETotalTradedVolume=%d", pOrder->ZCETotalTradedVolume);
        CPrintApi::DbgPrint("          pOrder->IsSwapOrder=%d", pOrder->IsSwapOrder);

        /* 报单信息 */
        CPrintApi::DbgPrint("----报单信息：FrontID=%d, SessionID=%08u, OrderRef=%s, SequenceNo=%d", 
            pOrder->FrontID, pOrder->SessionID, pOrder->OrderRef, pOrder->SequenceNo);

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

    /* 更新数据 */
    CTraderApi *api = CTraderApi::GetInstance();
    api->m_data.UpdateTraderData(pOrder, E_TRIGGER_STAGE_RTN);
}

/* 执行通知 */
void CTraderSpi::OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder)
{
    CheckFuncNameEx();
    if (pExecOrder)
    {
        CPrintApi::DbgPrint("----参数：pExecOrder->BrokerID=%s", pExecOrder->BrokerID);
        CPrintApi::DbgPrint("          pExecOrder->InvestorID=%s", pExecOrder->InvestorID);
        CPrintApi::DbgPrint("          pExecOrder->InstrumentID=%s", pExecOrder->InstrumentID);
        CPrintApi::DbgPrint("          pExecOrder->ExecOrderRef=%s", pExecOrder->ExecOrderRef);
        CPrintApi::DbgPrint("          pExecOrder->UserID=%s", pExecOrder->UserID);
        CPrintApi::DbgPrint("          pExecOrder->Volume=%d", pExecOrder->Volume);
        CPrintApi::DbgPrint("          pExecOrder->RequestID=%08d", pExecOrder->RequestID); /* 请求标志 */
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
        CPrintApi::DbgPrint("          pExecOrder->InstallID=%08d", pExecOrder->InstallID);
        CPrintApi::DbgPrint("          pExecOrder->OrderSubmitStatus=%c", pExecOrder->OrderSubmitStatus);
        CPrintApi::DbgPrint("          pExecOrder->NotifySequence=%08d", pExecOrder->NotifySequence);
        CPrintApi::DbgPrint("          pExecOrder->TradingDay=%s", pExecOrder->TradingDay);
        CPrintApi::DbgPrint("          pExecOrder->SettlementID=%08d", pExecOrder->SettlementID);
        CPrintApi::DbgPrint("          pExecOrder->ExecOrderSysID=%s", pExecOrder->ExecOrderSysID);
        CPrintApi::DbgPrint("          pExecOrder->InsertDate=%s", pExecOrder->InsertDate);
        CPrintApi::DbgPrint("          pExecOrder->InsertTime=%s", pExecOrder->InsertTime);
        CPrintApi::DbgPrint("          pExecOrder->CancelTime=%s", pExecOrder->CancelTime);
        CPrintApi::DbgPrint("          pExecOrder->ExecResult=%c", pExecOrder->ExecResult);
        CPrintApi::DbgPrint("          pExecOrder->ClearingPartID=%s", pExecOrder->ClearingPartID);
        CPrintApi::DbgPrint("          pExecOrder->FrontID=%08d", pExecOrder->FrontID);
        CPrintApi::DbgPrint("          pExecOrder->SessionID=%08u", pExecOrder->SessionID);
        CPrintApi::DbgPrint("          pExecOrder->UserProductInfo=%s", pExecOrder->UserProductInfo);
        CPrintApi::DbgPrint("          pExecOrder->StatusMsg=%s", pExecOrder->StatusMsg);
        CPrintApi::DbgPrint("          pExecOrder->ActiveUserID=%s", pExecOrder->ActiveUserID);
        CPrintApi::DbgPrint("          pExecOrder->BrokerExecOrderSeq=%08d", pExecOrder->BrokerExecOrderSeq);
    }
}

/* 报价通知 */
void CTraderSpi::OnRtnQuote(CThostFtdcQuoteField *pQuote)
{
    CheckFuncNameEx();
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
        CPrintApi::DbgPrint("          pQuote->RequestID=%08d", pQuote->RequestID); /* 请求标志 */
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
        CPrintApi::DbgPrint("          pQuote->InstallID=%08d", pQuote->InstallID);
        CPrintApi::DbgPrint("          pQuote->NotifySequence=%08d", pQuote->NotifySequence);
        CPrintApi::DbgPrint("          pQuote->OrderSubmitStatus=%c", pQuote->OrderSubmitStatus);
        CPrintApi::DbgPrint("          pQuote->TradingDay=%s", pQuote->TradingDay);
        CPrintApi::DbgPrint("          pQuote->SettlementID=%08d", pQuote->SettlementID);
        CPrintApi::DbgPrint("          pQuote->QuoteSysID=%s", pQuote->QuoteSysID);
        CPrintApi::DbgPrint("          pQuote->InsertDate=%s", pQuote->InsertDate);
        CPrintApi::DbgPrint("          pQuote->InsertTime=%s", pQuote->InsertTime);
        CPrintApi::DbgPrint("          pQuote->CancelTime=%s", pQuote->CancelTime);
        CPrintApi::DbgPrint("          pQuote->QuoteStatus=%c", pQuote->QuoteStatus);
        CPrintApi::DbgPrint("          pQuote->ClearingPartID=%s", pQuote->ClearingPartID);
        CPrintApi::DbgPrint("          pQuote->SequenceNo=%08d", pQuote->SequenceNo);
        CPrintApi::DbgPrint("          pQuote->AskOrderSysID=%s", pQuote->AskOrderSysID);
        CPrintApi::DbgPrint("          pQuote->BidOrderSysID=%s", pQuote->BidOrderSysID);
        CPrintApi::DbgPrint("          pQuote->FrontID=%08d", pQuote->FrontID);
        CPrintApi::DbgPrint("          pQuote->SessionID=%08u", pQuote->SessionID);
        CPrintApi::DbgPrint("          pQuote->UserProductInfo=%s", pQuote->UserProductInfo);
        CPrintApi::DbgPrint("          pQuote->StatusMsg=%s", pQuote->StatusMsg);
        CPrintApi::DbgPrint("          pQuote->ActiveUserID=%s", pQuote->ActiveUserID);
        CPrintApi::DbgPrint("          pQuote->BrokerQuoteSeq=%08d", pQuote->BrokerQuoteSeq);
        CPrintApi::DbgPrint("          pQuote->AskOrderRef=%s", pQuote->AskOrderRef);
        CPrintApi::DbgPrint("          pQuote->BidOrderRef=%s", pQuote->BidOrderRef);
        CPrintApi::DbgPrint("          pQuote->ForQuoteSysID=%s", pQuote->ForQuoteSysID);
    }
}

/* 询价通知 */
void CTraderSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
    CheckFuncNameEx();
    if (pForQuoteRsp)
    {
        CPrintApi::DbgPrint("----参数：pForQuoteRsp->TradingDay=%s", pForQuoteRsp->TradingDay);
        CPrintApi::DbgPrint("          pForQuoteRsp->InstrumentID=%s", pForQuoteRsp->InstrumentID);
        CPrintApi::DbgPrint("          pForQuoteRsp->ForQuoteSysID=%s", pForQuoteRsp->ForQuoteSysID);
        CPrintApi::DbgPrint("          pForQuoteRsp->ForQuoteTime=%s", pForQuoteRsp->ForQuoteTime);
        CPrintApi::DbgPrint("          pForQuoteRsp->ActionDay=%s", pForQuoteRsp->ActionDay);
        CPrintApi::DbgPrint("          pForQuoteRsp->ExchangeID=%s", pForQuoteRsp->ExchangeID);
    }
}

/* 交易通知 */
void CTraderSpi::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo)
{
    CheckFuncNameEx();
    if (pTradingNoticeInfo)
    {
        CPrintApi::DbgPrint("----参数：pTradingNoticeInfo->BrokerID=%s", pTradingNoticeInfo->BrokerID);
        CPrintApi::DbgPrint("          pTradingNoticeInfo->InvestorID=%s", pTradingNoticeInfo->InvestorID);
        CPrintApi::DbgPrint("          pTradingNoticeInfo->SendTime=%s", pTradingNoticeInfo->SendTime);
        CPrintApi::DbgPrint("          pTradingNoticeInfo->FieldContent=%s", pTradingNoticeInfo->FieldContent);
        CPrintApi::DbgPrint("          pTradingNoticeInfo->SequenceSeries=%d", pTradingNoticeInfo->SequenceSeries);
        CPrintApi::DbgPrint("          pTradingNoticeInfo->SequenceNo=%08d", pTradingNoticeInfo->SequenceNo);
    }
}

/* 成交通知 */
void CTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
    CheckFuncNameEx();
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
        CPrintApi::DbgPrint("          pTrade->SequenceNo=%08d", pTrade->SequenceNo);
        CPrintApi::DbgPrint("          pTrade->TradingDay=%s", pTrade->TradingDay);
        CPrintApi::DbgPrint("          pTrade->SettlementID=%08d", pTrade->SettlementID);
        CPrintApi::DbgPrint("          pTrade->BrokerOrderSeq=%08d", pTrade->BrokerOrderSeq);
        CPrintApi::DbgPrint("          pTrade->TradeSource=%c", pTrade->TradeSource);
    }

    /* 更新数据 */
    CTraderApi *api = CTraderApi::GetInstance();
    api->m_data.UpdateTraderData(pTrade, E_TRIGGER_STAGE_RTN);
}

/* 报单录入错误 */
void CTraderSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
    BOOL bCheck = CheckOnErrRtnInfoEx(pRspInfo);
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
        CPrintApi::DbgPrint("          pInputOrder->RequestID=%08d", pInputOrder->RequestID); /* 请求标志 */
        CPrintApi::DbgPrint("          pInputOrder->UserForceClose=%d", pInputOrder->UserForceClose);
        CPrintApi::DbgPrint("          pInputOrder->IsSwapOrder=%d", pInputOrder->IsSwapOrder);
    }

    /* 更新数据 */
    CTraderApi *api = CTraderApi::GetInstance();
    api->m_data.UpdateTraderData(pInputOrder, E_TRIGGER_STAGE_ERR);
}

/* 报单操作错误 */
void CTraderSpi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    BOOL bCheck = CheckOnErrRtnInfoEx(pRspInfo);
    if (pOrderAction)
    {
        CPrintApi::DbgPrint("----参数：pOrderAction->BrokerID=%s", pOrderAction->BrokerID);
        CPrintApi::DbgPrint("          pOrderAction->InvestorID=%s", pOrderAction->InvestorID);
        CPrintApi::DbgPrint("          pOrderAction->OrderActionRef=%s", pOrderAction->OrderActionRef);
        CPrintApi::DbgPrint("          pOrderAction->OrderRef=%s", pOrderAction->OrderRef);
        CPrintApi::DbgPrint("          pOrderAction->RequestID=%08d", pOrderAction->RequestID); /* 请求标志 */
        CPrintApi::DbgPrint("          pOrderAction->FrontID=%08d", pOrderAction->FrontID);
        CPrintApi::DbgPrint("          pOrderAction->SessionID=%08u", pOrderAction->SessionID);
        CPrintApi::DbgPrint("          pOrderAction->ExchangeID=%s", pOrderAction->ExchangeID);
        CPrintApi::DbgPrint("          pOrderAction->OrderSysID=%s", pOrderAction->OrderSysID);
        CPrintApi::DbgPrint("          pOrderAction->ActionFlag=%c", pOrderAction->ActionFlag);
        CPrintApi::DbgPrint("          pOrderAction->LimitPrice=%8.3f", pOrderAction->LimitPrice);
        CPrintApi::DbgPrint("          pOrderAction->VolumeChange=%d", pOrderAction->VolumeChange);
        CPrintApi::DbgPrint("          pOrderAction->ActionDate=%s", pOrderAction->ActionDate);
        CPrintApi::DbgPrint("          pOrderAction->ActionTime=%s", pOrderAction->ActionTime);
        CPrintApi::DbgPrint("          pOrderAction->TraderID=%s", pOrderAction->TraderID);
        CPrintApi::DbgPrint("          pOrderAction->InstallID=%08d", pOrderAction->InstallID);
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

    /* 更新数据 */
    CTraderApi *api = CTraderApi::GetInstance();
    api->m_data.UpdateTraderData(pOrderAction, E_TRIGGER_STAGE_ERR);
}

/* 执行录入错误 */
void CTraderSpi::OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo)
{
    BOOL bCheck = CheckOnErrRtnInfoEx(pRspInfo);
    if (pInputExecOrder)
    {
        CPrintApi::DbgPrint("----参数：pInputExecOrder->BrokerID=%s", pInputExecOrder->BrokerID);
        CPrintApi::DbgPrint("          pInputExecOrder->InvestorID=%s", pInputExecOrder->InvestorID);
        CPrintApi::DbgPrint("          pInputExecOrder->InstrumentID=%s", pInputExecOrder->InstrumentID);
        CPrintApi::DbgPrint("          pInputExecOrder->ExecOrderRef=%s", pInputExecOrder->ExecOrderRef);
        CPrintApi::DbgPrint("          pInputExecOrder->UserID=%s", pInputExecOrder->UserID);
        CPrintApi::DbgPrint("          pInputExecOrder->Volume=%d", pInputExecOrder->Volume);
        CPrintApi::DbgPrint("          pInputExecOrder->RequestID=%08d", pInputExecOrder->RequestID); /* 请求标志 */
        CPrintApi::DbgPrint("          pInputExecOrder->BusinessUnit=%s", pInputExecOrder->BusinessUnit);
        CPrintApi::DbgPrint("          pInputExecOrder->OffsetFlag=%c", pInputExecOrder->OffsetFlag);
        CPrintApi::DbgPrint("          pInputExecOrder->HedgeFlag=%c", pInputExecOrder->HedgeFlag);
        CPrintApi::DbgPrint("          pInputExecOrder->ActionType=%c", pInputExecOrder->ActionType);
        CPrintApi::DbgPrint("          pInputExecOrder->PosiDirection=%c", pInputExecOrder->PosiDirection);
        CPrintApi::DbgPrint("          pInputExecOrder->ReservePositionFlag=%c", pInputExecOrder->ReservePositionFlag);
        CPrintApi::DbgPrint("          pInputExecOrder->CloseFlag=%c", pInputExecOrder->CloseFlag);
    }
}

/* 执行操作错误 */
void CTraderSpi::OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    BOOL bCheck = CheckOnErrRtnInfoEx(pRspInfo);
    if (pExecOrderAction)
    {
        CPrintApi::DbgPrint("----参数：pExecOrderAction->BrokerID=%s", pExecOrderAction->BrokerID);
        CPrintApi::DbgPrint("          pExecOrderAction->InvestorID=%s", pExecOrderAction->InvestorID);
        CPrintApi::DbgPrint("          pExecOrderAction->ExecOrderActionRef=%s", pExecOrderAction->ExecOrderActionRef);
        CPrintApi::DbgPrint("          pExecOrderAction->ExecOrderRef=%s", pExecOrderAction->ExecOrderRef);
        CPrintApi::DbgPrint("          pExecOrderAction->RequestID=%08d", pExecOrderAction->RequestID); /* 请求标志 */
        CPrintApi::DbgPrint("          pExecOrderAction->FrontID=%08d", pExecOrderAction->FrontID);
        CPrintApi::DbgPrint("          pExecOrderAction->SessionID=%08u", pExecOrderAction->SessionID);
        CPrintApi::DbgPrint("          pExecOrderAction->ExchangeID=%s", pExecOrderAction->ExchangeID);
        CPrintApi::DbgPrint("          pExecOrderAction->ExecOrderSysID=%s", pExecOrderAction->ExecOrderSysID);
        CPrintApi::DbgPrint("          pExecOrderAction->ActionFlag=%c", pExecOrderAction->ActionFlag);
        CPrintApi::DbgPrint("          pExecOrderAction->ActionDate=%s", pExecOrderAction->ActionDate);
        CPrintApi::DbgPrint("          pExecOrderAction->ActionTime=%s", pExecOrderAction->ActionTime);
        CPrintApi::DbgPrint("          pExecOrderAction->TraderID=%s", pExecOrderAction->TraderID);
        CPrintApi::DbgPrint("          pExecOrderAction->InstallID=%08d", pExecOrderAction->InstallID);
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
}

/* 报价录入错误 */
void CTraderSpi::OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo)
{
    BOOL bCheck = CheckOnErrRtnInfoEx(pRspInfo);
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
        CPrintApi::DbgPrint("          pInputQuote->RequestID=%08d", pInputQuote->RequestID); /* 请求标志 */
        CPrintApi::DbgPrint("          pInputQuote->BusinessUnit=%s", pInputQuote->BusinessUnit);
        CPrintApi::DbgPrint("          pInputQuote->AskOffsetFlag=%c", pInputQuote->AskOffsetFlag);
        CPrintApi::DbgPrint("          pInputQuote->BidOffsetFlag=%c", pInputQuote->BidOffsetFlag);
        CPrintApi::DbgPrint("          pInputQuote->AskHedgeFlag=%c", pInputQuote->AskHedgeFlag);
        CPrintApi::DbgPrint("          pInputQuote->BidHedgeFlag=%c", pInputQuote->BidHedgeFlag);
        CPrintApi::DbgPrint("          pInputQuote->AskOrderRef=%s", pInputQuote->AskOrderRef);
        CPrintApi::DbgPrint("          pInputQuote->BidOrderRef=%s", pInputQuote->BidOrderRef);
        CPrintApi::DbgPrint("          pInputQuote->ForQuoteSysID=%s", pInputQuote->ForQuoteSysID);
    }
}

/* 报价操作错误 */
void CTraderSpi::OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo)
{
    BOOL bCheck = CheckOnErrRtnInfoEx(pRspInfo);
    if (pQuoteAction)
    {
        CPrintApi::DbgPrint("----参数：pQuoteAction->BrokerID=%s", pQuoteAction->BrokerID);
        CPrintApi::DbgPrint("          pQuoteAction->InvestorID=%s", pQuoteAction->InvestorID);
        CPrintApi::DbgPrint("          pQuoteAction->QuoteActionRef=%s", pQuoteAction->QuoteActionRef);
        CPrintApi::DbgPrint("          pQuoteAction->QuoteRef=%s", pQuoteAction->QuoteRef);
        CPrintApi::DbgPrint("          pQuoteAction->RequestID=%08d", pQuoteAction->RequestID); /* 请求标志 */
        CPrintApi::DbgPrint("          pQuoteAction->FrontID=%08d", pQuoteAction->FrontID);
        CPrintApi::DbgPrint("          pQuoteAction->SessionID=%08u", pQuoteAction->SessionID);
        CPrintApi::DbgPrint("          pQuoteAction->ExchangeID=%s", pQuoteAction->ExchangeID);
        CPrintApi::DbgPrint("          pQuoteAction->QuoteSysID=%s", pQuoteAction->QuoteSysID);
        CPrintApi::DbgPrint("          pQuoteAction->ActionFlag=%c", pQuoteAction->ActionFlag);
        CPrintApi::DbgPrint("          pQuoteAction->ActionDate=%s", pQuoteAction->ActionDate);
        CPrintApi::DbgPrint("          pQuoteAction->ActionTime=%s", pQuoteAction->ActionTime);
        CPrintApi::DbgPrint("          pQuoteAction->TraderID=%s", pQuoteAction->TraderID);
        CPrintApi::DbgPrint("          pQuoteAction->InstallID=%08d", pQuoteAction->InstallID);
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
}

/* 询价录入错误 */
void CTraderSpi::OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo)
{
    BOOL bCheck = CheckOnErrRtnInfoEx(pRspInfo);
    if (pInputForQuote)
    {
        CPrintApi::DbgPrint("----参数：pInputForQuote->BrokerID=%s", pInputForQuote->BrokerID);
        CPrintApi::DbgPrint("          pInputForQuote->InvestorID=%s", pInputForQuote->InvestorID);
        CPrintApi::DbgPrint("          pInputForQuote->InstrumentID=%s", pInputForQuote->InstrumentID);
        CPrintApi::DbgPrint("          pInputForQuote->ForQuoteRef=%s", pInputForQuote->ForQuoteRef);
        CPrintApi::DbgPrint("          pInputForQuote->UserID=%s", pInputForQuote->UserID);   
    }
}

/* 错误响应 */
void CTraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
}

/* 认证响应 */
void CTraderSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
    if (pRspAuthenticateField)
    {
        CPrintApi::DbgPrint("----参数：pRspAuthenticateField->BrokerID=%s", pRspAuthenticateField->BrokerID);
        CPrintApi::DbgPrint("          pRspAuthenticateField->UserID=%s", pRspAuthenticateField->UserID);
        CPrintApi::DbgPrint("          pRspAuthenticateField->UserProductInfo=%s", pRspAuthenticateField->UserProductInfo);
    }
}

/* 登录响应 */
void CTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
    if (pRspUserLogin)
    {
        CPrintApi::DbgPrint("----参数：pRspUserLogin->TradingDay=%s", pRspUserLogin->TradingDay);
        CPrintApi::DbgPrint("          pRspUserLogin->LoginTime=%s", pRspUserLogin->LoginTime);
        CPrintApi::DbgPrint("          pRspUserLogin->BrokerID=%s", pRspUserLogin->BrokerID);
        CPrintApi::DbgPrint("          pRspUserLogin->UserID=%s", pRspUserLogin->UserID);
        CPrintApi::DbgPrint("          pRspUserLogin->SystemName=%s", pRspUserLogin->SystemName);
        CPrintApi::DbgPrint("          pRspUserLogin->FrontID=%08d", pRspUserLogin->FrontID);
        CPrintApi::DbgPrint("          pRspUserLogin->SessionID=%08u", pRspUserLogin->SessionID);
        CPrintApi::DbgPrint("          pRspUserLogin->MaxOrderRef=%s", pRspUserLogin->MaxOrderRef);
        CPrintApi::DbgPrint("          pRspUserLogin->SHFETime=%s", pRspUserLogin->SHFETime);
        CPrintApi::DbgPrint("          pRspUserLogin->DCETime=%s", pRspUserLogin->DCETime);
        CPrintApi::DbgPrint("          pRspUserLogin->CZCETime=%s", pRspUserLogin->CZCETime);
        CPrintApi::DbgPrint("          pRspUserLogin->FFEXTime=%s", pRspUserLogin->FFEXTime);
        CPrintApi::DbgPrint("          pRspUserLogin->INETime=%s", pRspUserLogin->INETime);
    }
    if (bCheck)
    {
        /* 保存会话信息 */
        CTraderApi *api = CTraderApi::GetInstance();
        api->m_cfg.m_nFrontID = pRspUserLogin->FrontID;
        api->m_cfg.m_nSessionID = pRspUserLogin->SessionID;
        memcpy(&api->m_cfg.m_szMaxOrderRef, &pRspUserLogin->MaxOrderRef, sizeof(pRspUserLogin->MaxOrderRef));
        sprintf(api->m_cfg.m_szOrderRef, "%d", 1+atoi(api->m_cfg.m_szMaxOrderRef));
        api->m_bLogin = TRUE;
    }
}

/* 注销响应 */
void CTraderSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
    if (pUserLogout)
    {
        CPrintApi::DbgPrint("----参数：pUserLogout->BrokerID=%s", pUserLogout->BrokerID);
        CPrintApi::DbgPrint("          pUserLogout->UserID=%s", pUserLogout->UserID);
    }
    CTraderApi *api = CTraderApi::GetInstance();
    api->m_bLogin = FALSE;
}

/* 确认结算响应 */
void CTraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
    if (pSettlementInfoConfirm)
    {
        CPrintApi::DbgPrint("----参数：pSettlementInfoConfirm->BrokerID=%s", pSettlementInfoConfirm->BrokerID);
        CPrintApi::DbgPrint("          pSettlementInfoConfirm->InvestorID=%s", pSettlementInfoConfirm->InvestorID);
        CPrintApi::DbgPrint("          pSettlementInfoConfirm->ConfirmDate=%s", pSettlementInfoConfirm->ConfirmDate);
        CPrintApi::DbgPrint("          pSettlementInfoConfirm->ConfirmTime=%s", pSettlementInfoConfirm->ConfirmTime);
    }
}

/* 报单录入响应 */
void CTraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
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
        CPrintApi::DbgPrint("          pInputOrder->RequestID=%08d", pInputOrder->RequestID);
        CPrintApi::DbgPrint("          pInputOrder->UserForceClose=%d", pInputOrder->UserForceClose);
        CPrintApi::DbgPrint("          pInputOrder->IsSwapOrder=%d", pInputOrder->IsSwapOrder);
    }

    /* 更新数据 */
    CTraderApi *api = CTraderApi::GetInstance();
    api->m_data.UpdateTraderData(pInputOrder, E_TRIGGER_STAGE_RSP);
}

/* 报单操作响应 */
void CTraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
    if (pInputOrderAction)
    {
        CPrintApi::DbgPrint("----参数：pInputOrderAction->BrokerID=%s", pInputOrderAction->BrokerID);
        CPrintApi::DbgPrint("          pInputOrderAction->InvestorID=%s", pInputOrderAction->InvestorID);
        CPrintApi::DbgPrint("          pInputOrderAction->OrderActionRef=%s", pInputOrderAction->OrderActionRef);
        CPrintApi::DbgPrint("          pInputOrderAction->OrderRef=%s", pInputOrderAction->OrderRef);
        CPrintApi::DbgPrint("          pInputOrderAction->RequestID=%08d", pInputOrderAction->RequestID);
        CPrintApi::DbgPrint("          pInputOrderAction->FrontID=%08d", pInputOrderAction->FrontID);
        CPrintApi::DbgPrint("          pInputOrderAction->SessionID=%08u", pInputOrderAction->SessionID);
        CPrintApi::DbgPrint("          pInputOrderAction->ExchangeID=%s", pInputOrderAction->ExchangeID);
        CPrintApi::DbgPrint("          pInputOrderAction->OrderSysID=%s", pInputOrderAction->OrderSysID);
        CPrintApi::DbgPrint("          pInputOrderAction->ActionFlag=%c", pInputOrderAction->ActionFlag);
        CPrintApi::DbgPrint("          pInputOrderAction->LimitPrice=%8.3f", pInputOrderAction->LimitPrice);
        CPrintApi::DbgPrint("          pInputOrderAction->VolumeChange=%d", pInputOrderAction->VolumeChange);
        CPrintApi::DbgPrint("          pInputOrderAction->UserID=%s", pInputOrderAction->UserID);
        CPrintApi::DbgPrint("          pInputOrderAction->InstrumentID=%s", pInputOrderAction->InstrumentID);
    }

    /* 更新数据 */
    CTraderApi *api = CTraderApi::GetInstance();
    api->m_data.UpdateTraderData(pInputOrderAction, E_TRIGGER_STAGE_RSP);
}

/* 执行录入响应 */
void CTraderSpi::OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
    if (pInputExecOrder)
    {
        CPrintApi::DbgPrint("----参数：pInputExecOrder->BrokerID=%s", pInputExecOrder->BrokerID);
        CPrintApi::DbgPrint("          pInputExecOrder->InvestorID=%s", pInputExecOrder->InvestorID);
        CPrintApi::DbgPrint("          pInputExecOrder->InstrumentID=%s", pInputExecOrder->InstrumentID);
        CPrintApi::DbgPrint("          pInputExecOrder->ExecOrderRef=%s", pInputExecOrder->ExecOrderRef);
        CPrintApi::DbgPrint("          pInputExecOrder->UserID=%s", pInputExecOrder->UserID);
        CPrintApi::DbgPrint("          pInputExecOrder->Volume=%d", pInputExecOrder->Volume);
        CPrintApi::DbgPrint("          pInputExecOrder->RequestID=%08d", pInputExecOrder->RequestID);
        CPrintApi::DbgPrint("          pInputExecOrder->BusinessUnit=%s", pInputExecOrder->BusinessUnit);
        CPrintApi::DbgPrint("          pInputExecOrder->OffsetFlag=%c", pInputExecOrder->OffsetFlag);
        CPrintApi::DbgPrint("          pInputExecOrder->HedgeFlag=%c", pInputExecOrder->HedgeFlag);
        CPrintApi::DbgPrint("          pInputExecOrder->ActionType=%c", pInputExecOrder->ActionType);
        CPrintApi::DbgPrint("          pInputExecOrder->PosiDirection=%c", pInputExecOrder->PosiDirection);
        CPrintApi::DbgPrint("          pInputExecOrder->ReservePositionFlag=%c", pInputExecOrder->ReservePositionFlag);
        CPrintApi::DbgPrint("          pInputExecOrder->CloseFlag=%c", pInputExecOrder->CloseFlag);
    }
}

/* 执行操作响应 */
void CTraderSpi::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
    if (pInputExecOrderAction)
    {
        CPrintApi::DbgPrint("----参数：pInputExecOrderAction->BrokerID=%s", pInputExecOrderAction->BrokerID);
        CPrintApi::DbgPrint("          pInputExecOrderAction->InvestorID=%s", pInputExecOrderAction->InvestorID);
        CPrintApi::DbgPrint("          pInputExecOrderAction->ExecOrderActionRef=%s", pInputExecOrderAction->ExecOrderActionRef);
        CPrintApi::DbgPrint("          pInputExecOrderAction->ExecOrderRef=%s", pInputExecOrderAction->ExecOrderRef);
        CPrintApi::DbgPrint("          pInputExecOrderAction->RequestID=%08d", pInputExecOrderAction->RequestID);
        CPrintApi::DbgPrint("          pInputExecOrderAction->FrontID=%08d", pInputExecOrderAction->FrontID);
        CPrintApi::DbgPrint("          pInputExecOrderAction->SessionID=%08u", pInputExecOrderAction->SessionID);
        CPrintApi::DbgPrint("          pInputExecOrderAction->ExchangeID=%s", pInputExecOrderAction->ExchangeID);
        CPrintApi::DbgPrint("          pInputExecOrderAction->ExecOrderSysID=%s", pInputExecOrderAction->ExecOrderSysID);
        CPrintApi::DbgPrint("          pInputExecOrderAction->ActionFlag=%c", pInputExecOrderAction->ActionFlag);
        CPrintApi::DbgPrint("          pInputExecOrderAction->UserID=%s", pInputExecOrderAction->UserID);
        CPrintApi::DbgPrint("          pInputExecOrderAction->InstrumentID=%s", pInputExecOrderAction->InstrumentID);
    }
}

/* 报价录入响应 */
void CTraderSpi::OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
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
        CPrintApi::DbgPrint("          pInputQuote->RequestID=%08d", pInputQuote->RequestID);
        CPrintApi::DbgPrint("          pInputQuote->BusinessUnit=%s", pInputQuote->BusinessUnit);
        CPrintApi::DbgPrint("          pInputQuote->AskOffsetFlag=%c", pInputQuote->AskOffsetFlag);
        CPrintApi::DbgPrint("          pInputQuote->BidOffsetFlag=%c", pInputQuote->BidOffsetFlag);
        CPrintApi::DbgPrint("          pInputQuote->AskHedgeFlag=%c", pInputQuote->AskHedgeFlag);
        CPrintApi::DbgPrint("          pInputQuote->BidHedgeFlag=%c", pInputQuote->BidHedgeFlag);
        CPrintApi::DbgPrint("          pInputQuote->AskOrderRef=%s", pInputQuote->AskOrderRef);
        CPrintApi::DbgPrint("          pInputQuote->BidOrderRef=%s", pInputQuote->BidOrderRef);
        CPrintApi::DbgPrint("          pInputQuote->ForQuoteSysID=%s", pInputQuote->ForQuoteSysID);
    }
}

/* 报价操作响应 */
void CTraderSpi::OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
    if (pInputQuoteAction)
    {
        CPrintApi::DbgPrint("----参数：pInputQuoteAction->BrokerID=%s", pInputQuoteAction->BrokerID);
        CPrintApi::DbgPrint("          pInputQuoteAction->InvestorID=%s", pInputQuoteAction->InvestorID);
        CPrintApi::DbgPrint("          pInputQuoteAction->QuoteActionRef=%s", pInputQuoteAction->QuoteActionRef);
        CPrintApi::DbgPrint("          pInputQuoteAction->QuoteRef=%s", pInputQuoteAction->QuoteRef);
        CPrintApi::DbgPrint("          pInputQuoteAction->RequestID=%08d", pInputQuoteAction->RequestID);
        CPrintApi::DbgPrint("          pInputQuoteAction->FrontID=%08d", pInputQuoteAction->FrontID);
        CPrintApi::DbgPrint("          pInputQuoteAction->SessionID=%08u", pInputQuoteAction->SessionID);
        CPrintApi::DbgPrint("          pInputQuoteAction->ExchangeID=%s", pInputQuoteAction->ExchangeID);
        CPrintApi::DbgPrint("          pInputQuoteAction->QuoteSysID=%s", pInputQuoteAction->QuoteSysID);
        CPrintApi::DbgPrint("          pInputQuoteAction->ActionFlag=%c", pInputQuoteAction->ActionFlag);
        CPrintApi::DbgPrint("          pInputQuoteAction->UserID=%s", pInputQuoteAction->UserID);
        CPrintApi::DbgPrint("          pInputQuoteAction->InstrumentID=%s", pInputQuoteAction->InstrumentID);
    }
}

/* 询价录入响应 */
void CTraderSpi::OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
    if (pInputForQuote)
    {
        CPrintApi::DbgPrint("----参数：pInputForQuote->BrokerID=%s", pInputForQuote->BrokerID);
        CPrintApi::DbgPrint("          pInputForQuote->InvestorID=%s", pInputForQuote->InvestorID);
        CPrintApi::DbgPrint("          pInputForQuote->InstrumentID=%s", pInputForQuote->InstrumentID);
        CPrintApi::DbgPrint("          pInputForQuote->ForQuoteRef=%s", pInputForQuote->ForQuoteRef);
        CPrintApi::DbgPrint("          pInputForQuote->UserID=%s", pInputForQuote->UserID);
    }
}

/* 查询报单响应 */
void CTraderSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
    if (pOrder)
    {
        CPrintApi::DbgPrint("----参数：pOrder->BrokerID=%s", pOrder->BrokerID);
        CPrintApi::DbgPrint("          pOrder->InvestorID=%s", pOrder->InvestorID);
        CPrintApi::DbgPrint("          pOrder->InstrumentID=%s", pOrder->InstrumentID);
        CPrintApi::DbgPrint("          pOrder->OrderRef=%s", pOrder->OrderRef);
        CPrintApi::DbgPrint("          pOrder->UserID=%s", pOrder->UserID);
        CPrintApi::DbgPrint("          pOrder->OrderPriceType=%c", pOrder->OrderPriceType);
        CPrintApi::DbgPrint("          pOrder->Direction=%c", pOrder->Direction);
        CPrintApi::DbgPrint("          pOrder->CombOffsetFlag=%s", pOrder->CombOffsetFlag);
        CPrintApi::DbgPrint("          pOrder->CombHedgeFlag=%s", pOrder->CombHedgeFlag);
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
        CPrintApi::DbgPrint("          pOrder->RequestID=%08d", pOrder->RequestID);
        CPrintApi::DbgPrint("          pOrder->OrderLocalID=%s", pOrder->OrderLocalID);
        CPrintApi::DbgPrint("          pOrder->ExchangeID=%s", pOrder->ExchangeID);
        CPrintApi::DbgPrint("          pOrder->ParticipantID=%s", pOrder->ParticipantID);
        CPrintApi::DbgPrint("          pOrder->ClientID=%s", pOrder->ClientID);
        CPrintApi::DbgPrint("          pOrder->ExchangeInstID=%s", pOrder->ExchangeInstID);
        CPrintApi::DbgPrint("          pOrder->TraderID=%s", pOrder->TraderID);
        CPrintApi::DbgPrint("          pOrder->InstallID=%08d", pOrder->InstallID);
        CPrintApi::DbgPrint("          pOrder->OrderSubmitStatus=%c", pOrder->OrderSubmitStatus);
        CPrintApi::DbgPrint("          pOrder->NotifySequence=%08d", pOrder->NotifySequence);
        CPrintApi::DbgPrint("          pOrder->TradingDay=%s", pOrder->TradingDay);
        CPrintApi::DbgPrint("          pOrder->SettlementID=%08d", pOrder->SettlementID);
        CPrintApi::DbgPrint("          pOrder->OrderSysID=%s", pOrder->OrderSysID);
        CPrintApi::DbgPrint("          pOrder->OrderSource=%c", pOrder->OrderSource);
        CPrintApi::DbgPrint("          pOrder->OrderStatus=%c", pOrder->OrderStatus);
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
        CPrintApi::DbgPrint("          pOrder->SequenceNo=%08d", pOrder->SequenceNo);
        CPrintApi::DbgPrint("          pOrder->FrontID=%08d", pOrder->FrontID);
        CPrintApi::DbgPrint("          pOrder->SessionID=%08u", pOrder->SessionID);
        CPrintApi::DbgPrint("          pOrder->UserProductInfo=%s", pOrder->UserProductInfo);
        CPrintApi::DbgPrint("          pOrder->StatusMsg=%s", pOrder->StatusMsg);
        CPrintApi::DbgPrint("          pOrder->UserForceClose=%d", pOrder->UserForceClose);
        CPrintApi::DbgPrint("          pOrder->ActiveUserID=%s", pOrder->ActiveUserID);
        CPrintApi::DbgPrint("          pOrder->BrokerOrderSeq=%08d", pOrder->BrokerOrderSeq);
        CPrintApi::DbgPrint("          pOrder->RelativeOrderSysID=%s", pOrder->RelativeOrderSysID);
        CPrintApi::DbgPrint("          pOrder->ZCETotalTradedVolume=%d", pOrder->ZCETotalTradedVolume);
        CPrintApi::DbgPrint("          pOrder->IsSwapOrder=%d", pOrder->IsSwapOrder);

        /* 请求标志 */
        CTriggerLogApi::TriggerEx(nRequestID, E_TRIGGER_STAGE_RSP); // 记录请求时间
    }
}

/* 查询执行响应 */
void CTraderSpi::OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
    if (pExecOrder)
    {
        CPrintApi::DbgPrint("----参数：pExecOrder->BrokerID=%s", pExecOrder->BrokerID);
        CPrintApi::DbgPrint("          pExecOrder->InvestorID=%s", pExecOrder->InvestorID);
        CPrintApi::DbgPrint("          pExecOrder->InstrumentID=%s", pExecOrder->InstrumentID);
        CPrintApi::DbgPrint("          pExecOrder->ExecOrderRef=%s", pExecOrder->ExecOrderRef);
        CPrintApi::DbgPrint("          pExecOrder->UserID=%s", pExecOrder->UserID);
        CPrintApi::DbgPrint("          pExecOrder->Volume=%d", pExecOrder->Volume);
        CPrintApi::DbgPrint("          pExecOrder->RequestID=%08d", pExecOrder->RequestID);
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
        CPrintApi::DbgPrint("          pExecOrder->InstallID=%08d", pExecOrder->InstallID);
        CPrintApi::DbgPrint("          pExecOrder->OrderSubmitStatus=%c", pExecOrder->OrderSubmitStatus);
        CPrintApi::DbgPrint("          pExecOrder->NotifySequence=%08d", pExecOrder->NotifySequence);
        CPrintApi::DbgPrint("          pExecOrder->TradingDay=%s", pExecOrder->TradingDay);
        CPrintApi::DbgPrint("          pExecOrder->SettlementID=%08d", pExecOrder->SettlementID);
        CPrintApi::DbgPrint("          pExecOrder->ExecOrderSysID=%s", pExecOrder->ExecOrderSysID);
        CPrintApi::DbgPrint("          pExecOrder->InsertDate=%s", pExecOrder->InsertDate);
        CPrintApi::DbgPrint("          pExecOrder->InsertTime=%s", pExecOrder->InsertTime);
        CPrintApi::DbgPrint("          pExecOrder->CancelTime=%s", pExecOrder->CancelTime);
        CPrintApi::DbgPrint("          pExecOrder->ExecResult=%c", pExecOrder->ExecResult);
        CPrintApi::DbgPrint("          pExecOrder->ClearingPartID=%s", pExecOrder->ClearingPartID);
        CPrintApi::DbgPrint("          pExecOrder->FrontID=%08d", pExecOrder->FrontID);
        CPrintApi::DbgPrint("          pExecOrder->SessionID=%08u", pExecOrder->SessionID);
        CPrintApi::DbgPrint("          pExecOrder->UserProductInfo=%s", pExecOrder->UserProductInfo);
        CPrintApi::DbgPrint("          pExecOrder->StatusMsg=%s", pExecOrder->StatusMsg);
        CPrintApi::DbgPrint("          pExecOrder->ActiveUserID=%s", pExecOrder->ActiveUserID);
        CPrintApi::DbgPrint("          pExecOrder->BrokerExecOrderSeq=%08d", pExecOrder->BrokerExecOrderSeq);
    }
}

/* 查询报价响应 */
void CTraderSpi::OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
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
        CPrintApi::DbgPrint("          pQuote->RequestID=%08d", pQuote->RequestID);
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
        CPrintApi::DbgPrint("          pQuote->InstallID=%08d", pQuote->InstallID);
        CPrintApi::DbgPrint("          pQuote->NotifySequence=%08d", pQuote->NotifySequence);
        CPrintApi::DbgPrint("          pQuote->OrderSubmitStatus=%c", pQuote->OrderSubmitStatus);
        CPrintApi::DbgPrint("          pQuote->TradingDay=%s", pQuote->TradingDay);
        CPrintApi::DbgPrint("          pQuote->SettlementID=%08d", pQuote->SettlementID);
        CPrintApi::DbgPrint("          pQuote->QuoteSysID=%s", pQuote->QuoteSysID);
        CPrintApi::DbgPrint("          pQuote->InsertDate=%s", pQuote->InsertDate);
        CPrintApi::DbgPrint("          pQuote->InsertTime=%s", pQuote->InsertTime);
        CPrintApi::DbgPrint("          pQuote->CancelTime=%s", pQuote->CancelTime);
        CPrintApi::DbgPrint("          pQuote->QuoteStatus=%c", pQuote->QuoteStatus);
        CPrintApi::DbgPrint("          pQuote->ClearingPartID=%s", pQuote->ClearingPartID);
        CPrintApi::DbgPrint("          pQuote->SequenceNo=%08d", pQuote->SequenceNo);
        CPrintApi::DbgPrint("          pQuote->AskOrderSysID=%s", pQuote->AskOrderSysID);
        CPrintApi::DbgPrint("          pQuote->BidOrderSysID=%s", pQuote->BidOrderSysID);
        CPrintApi::DbgPrint("          pQuote->FrontID=%08d", pQuote->FrontID);
        CPrintApi::DbgPrint("          pQuote->SessionID=%08u", pQuote->SessionID);
        CPrintApi::DbgPrint("          pQuote->UserProductInfo=%s", pQuote->UserProductInfo);
        CPrintApi::DbgPrint("          pQuote->StatusMsg=%s", pQuote->StatusMsg);
        CPrintApi::DbgPrint("          pQuote->ActiveUserID=%s", pQuote->ActiveUserID);
        CPrintApi::DbgPrint("          pQuote->BrokerQuoteSeq=%08d", pQuote->BrokerQuoteSeq);
        CPrintApi::DbgPrint("          pQuote->AskOrderRef=%s", pQuote->AskOrderRef);
        CPrintApi::DbgPrint("          pQuote->BidOrderRef=%s", pQuote->BidOrderRef);
        CPrintApi::DbgPrint("          pQuote->ForQuoteSysID=%s", pQuote->ForQuoteSysID);
    }
}

/* 查询询价响应 */
void CTraderSpi::OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
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
        CPrintApi::DbgPrint("          pForQuote->InstallID=%08d", pForQuote->InstallID);
        CPrintApi::DbgPrint("          pForQuote->InsertDate=%s", pForQuote->InsertDate);
        CPrintApi::DbgPrint("          pForQuote->InsertTime=%s", pForQuote->InsertTime);
        CPrintApi::DbgPrint("          pForQuote->ForQuoteStatus=%c", pForQuote->ForQuoteStatus);
        CPrintApi::DbgPrint("          pForQuote->FrontID=%08d", pForQuote->FrontID);
        CPrintApi::DbgPrint("          pForQuote->SessionID=%08u", pForQuote->SessionID);
        CPrintApi::DbgPrint("          pForQuote->StatusMsg=%s", pForQuote->StatusMsg);
        CPrintApi::DbgPrint("          pForQuote->ActiveUserID=%s", pForQuote->ActiveUserID);
        CPrintApi::DbgPrint("          pForQuote->BrokerForQutoSeq=%08d", pForQuote->BrokerForQutoSeq);
    }
}

/* 查询交易响应 */
void CTraderSpi::OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
    if (pTradingNotice)
    {
        CPrintApi::DbgPrint("----参数：pTradingNotice->BrokerID=%s", pTradingNotice->BrokerID);
        CPrintApi::DbgPrint("          pTradingNotice->InvestorRange=%c", pTradingNotice->InvestorRange);
        CPrintApi::DbgPrint("          pTradingNotice->InvestorID=%s", pTradingNotice->InvestorID);
        CPrintApi::DbgPrint("          pTradingNotice->SequenceSeries=%d", pTradingNotice->SequenceSeries);
        CPrintApi::DbgPrint("          pTradingNotice->UserID=%s", pTradingNotice->UserID);
        CPrintApi::DbgPrint("          pTradingNotice->SendTime=%s", pTradingNotice->SendTime);
        CPrintApi::DbgPrint("          pTradingNotice->SequenceNo=%08d", pTradingNotice->SequenceNo);
        CPrintApi::DbgPrint("          pTradingNotice->FieldContent=%s", pTradingNotice->FieldContent);
    }
}

/* 查询成交响应 */
void CTraderSpi::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
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
        CPrintApi::DbgPrint("          pTrade->SequenceNo=%08d", pTrade->SequenceNo);
        CPrintApi::DbgPrint("          pTrade->TradingDay=%s", pTrade->TradingDay);
        CPrintApi::DbgPrint("          pTrade->SettlementID=%08d", pTrade->SettlementID);
        CPrintApi::DbgPrint("          pTrade->BrokerOrderSeq=%08d", pTrade->BrokerOrderSeq);
        CPrintApi::DbgPrint("          pTrade->TradeSource=%c", pTrade->TradeSource);
    }
}

/* 查询通知响应 */
void CTraderSpi::OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
    if (pNotice)
    {
        CPrintApi::DbgPrint("----参数：pNotice->BrokerID=%s", pNotice->BrokerID);
        CPrintApi::DbgPrint("          pNotice->Content=%s", pNotice->Content);
        CPrintApi::DbgPrint("          pNotice->SequenceLabel=%02d", pNotice->SequenceLabel);
    }
}

/* 查询交易所响应 */
void CTraderSpi::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
    if (pExchange)
    {
        CPrintApi::DbgPrint("----参数：pExchange->ExchangeID=%s", pExchange->ExchangeID);
        CPrintApi::DbgPrint("          pExchange->ExchangeName=%s", pExchange->ExchangeName);
        CPrintApi::DbgPrint("          pExchange->ExchangeProperty=%c", pExchange->ExchangeProperty);
    }
}

/* 查询交易编码响应 */
void CTraderSpi::OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
    if (pTradingCode)
    {
        CPrintApi::DbgPrint("----参数：pTradingCode->InvestorID=%s", pTradingCode->InvestorID);
        CPrintApi::DbgPrint("          pTradingCode->BrokerID=%s", pTradingCode->BrokerID);
        CPrintApi::DbgPrint("          pTradingCode->ExchangeID=%s", pTradingCode->ExchangeID);
        CPrintApi::DbgPrint("          pTradingCode->ClientID=%s", pTradingCode->ClientID);
        CPrintApi::DbgPrint("          pTradingCode->IsActive=%d", pTradingCode->IsActive);
        CPrintApi::DbgPrint("          pTradingCode->ClientIDType=%c", pTradingCode->ClientIDType);
    }
}

/* 查询产品响应 */
void CTraderSpi::OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
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
}

/* 查询合约响应 */
void CTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
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
}

/* 查询行情响应 */
void CTraderSpi::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
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
}

/* 查询持仓响应 */
void CTraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
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
        CPrintApi::DbgPrint("          pInvestorPosition->SettlementID=%08d", pInvestorPosition->SettlementID);
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
}

/* 查询资金响应 */
void CTraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
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
}

/* 查询投资者响应 */
void CTraderSpi::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    BOOL bCheck = CheckOnRspInfoEx(pRspInfo, nRequestID, bIsLast);
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
}

/* 认证操作 */
void CTraderApi::Authe(void)
{
    CheckFuncNameEx();
    CThostFtdcReqAuthenticateField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.UserID, &m_cfg.m_szUserID, sizeof(m_cfg.m_szUserID));
    memcpy(&req.UserProductInfo, &m_cfg.m_szUserProductInfo, sizeof(m_cfg.m_szUserProductInfo));
    memcpy(&req.AuthCode, &m_cfg.m_szAuthCode, sizeof(m_cfg.m_szAuthCode));
    int result = m_api->ReqAuthenticate(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 登录操作 */
void CTraderApi::Login(void)
{
    CheckFuncNameEx();
    CThostFtdcReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.UserID, &m_cfg.m_szUserID, sizeof(m_cfg.m_szUserID));
    memcpy(&req.Password, &m_cfg.m_szPassword, sizeof(m_cfg.m_szPassword));
    int result = m_api->ReqUserLogin(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 注销操作 */
void CTraderApi::Logout(void)
{
    CheckFuncNameEx();
    CThostFtdcUserLogoutField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.UserID, &m_cfg.m_szUserID, sizeof(m_cfg.m_szUserID));
    int result = m_api->ReqUserLogout(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 确认结算 */
void CTraderApi::SettlementInfoConfirm(void)
{
    CheckFuncNameEx();
    CThostFtdcSettlementInfoConfirmField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    int result = m_api->ReqSettlementInfoConfirm(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 报单录入 */
void CTraderApi::OrderInsert(void)
{
    CheckFuncNameEx();
#if 0
    /* 开仓买入 */
    CThostFtdcInputOrderField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID));
    memcpy(&req.OrderRef, &m_cfg.m_szOrderRef, sizeof(m_cfg.m_szOrderRef));
    sprintf(m_cfg.m_szOrderRef, "%d", 1+atoi(req.OrderRef));
    memcpy(&req.UserID, &m_cfg.m_szUserID, sizeof(m_cfg.m_szUserID));
    req.OrderPriceType = THOST_FTDC_OPT_AnyPrice;
    req.Direction = THOST_FTDC_D_Buy;
    req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    req.LimitPrice = 39100;
    req.VolumeTotalOriginal = 1;
    req.TimeCondition = THOST_FTDC_TC_GFD;
    req.VolumeCondition = THOST_FTDC_VC_AV;
    req.MinVolume = 1;
    req.ContingentCondition = THOST_FTDC_CC_Immediately;
    req.StopPrice = 0;
    req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    req.IsAutoSuspend = 0;
    req.IsSwapOrder = 0;
#endif
#if 1
    /* 平仓卖出 */
    CThostFtdcInputOrderField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID));
    memcpy(&req.OrderRef, &m_cfg.m_szOrderRef, sizeof(m_cfg.m_szOrderRef));
    sprintf(m_cfg.m_szOrderRef, "%d", 1+atoi(req.OrderRef));
    memcpy(&req.UserID, &m_cfg.m_szUserID, sizeof(m_cfg.m_szUserID));
    req.OrderPriceType = THOST_FTDC_OPT_AnyPrice;
    req.Direction = THOST_FTDC_D_Sell;
    req.CombOffsetFlag[0] = THOST_FTDC_OF_Close;
    req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    req.LimitPrice = 39000;
    req.VolumeTotalOriginal = 1;
    req.TimeCondition = THOST_FTDC_TC_GFD;
    req.VolumeCondition = THOST_FTDC_VC_AV;
    req.MinVolume = 1;
    req.ContingentCondition = THOST_FTDC_CC_Immediately;
    req.StopPrice = 0;
    req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    req.IsAutoSuspend = 0;
    req.IsSwapOrder = 0;
#endif
#if 0
    /* 开仓卖出 */
    CThostFtdcInputOrderField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID));
    memcpy(&req.OrderRef, &m_cfg.m_szOrderRef, sizeof(m_cfg.m_szOrderRef));
    sprintf(m_cfg.m_szOrderRef, "%d", 1+atoi(req.OrderRef));
    memcpy(&req.UserID, &m_cfg.m_szUserID, sizeof(m_cfg.m_szUserID));
    req.OrderPriceType = THOST_FTDC_OPT_AnyPrice;
    req.Direction = THOST_FTDC_D_Sell;
    req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    req.LimitPrice = 39100;
    req.VolumeTotalOriginal = 1;
    req.TimeCondition = THOST_FTDC_TC_GFD;
    req.VolumeCondition = THOST_FTDC_VC_AV;
    req.MinVolume = 1;
    req.ContingentCondition = THOST_FTDC_CC_Immediately;
    req.StopPrice = 0;
    req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    req.IsAutoSuspend = 0;
    req.IsSwapOrder = 0;
#endif
#if 0
    /* 平仓买入 */
    CThostFtdcInputOrderField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID));
    memcpy(&req.OrderRef, &m_cfg.m_szOrderRef, sizeof(m_cfg.m_szOrderRef));
    sprintf(m_cfg.m_szOrderRef, "%d", 1+atoi(req.OrderRef));
    memcpy(&req.UserID, &m_cfg.m_szUserID, sizeof(m_cfg.m_szUserID));
    req.OrderPriceType = THOST_FTDC_OPT_AnyPrice;
    req.Direction = THOST_FTDC_D_Buy;
    req.CombOffsetFlag[0] = THOST_FTDC_OF_Close;
    req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    req.LimitPrice = 39100;
    req.VolumeTotalOriginal = 1;
    req.TimeCondition = THOST_FTDC_TC_GFD;
    req.VolumeCondition = THOST_FTDC_VC_AV;
    req.MinVolume = 1;
    req.ContingentCondition = THOST_FTDC_CC_Immediately;
    req.StopPrice = 0;
    req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    req.IsAutoSuspend = 0;
    req.IsSwapOrder = 0;
#endif
    CTriggerLogApi::TriggerEx(m_cfg.m_nRequestID, E_TRIGGER_STAGE_REQ); // 记录请求时间
    int result = m_api->ReqOrderInsert(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 报单操作 */
void CTraderApi::OrderAction(void)
{
    CheckFuncNameEx();
    CThostFtdcInputOrderActionField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    //memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID));
    //memcpy(&req.OrderActionRef, &m_cfg.m_szOrderActionRef, sizeof(m_cfg.m_szOrderActionRef));
    //memcpy(&req.OrderRef, &m_cfg.m_szOrderRef, sizeof(m_cfg.m_szOrderRef));
    //memcpy(&req.UserID, &m_cfg.m_szUserID, sizeof(m_cfg.m_szUserID));
    //req.RequestID = m_cfg.m_nRequestID;
    //req.FrontID = m_cfg.m_nFrontID;
    //req.SessionID = m_cfg.m_nSessionID;
    //memcpy(&req.ExchangeID, &m_cfg.m_szExchangeID, sizeof(m_cfg.m_szExchangeID));
    //memcpy(&req.OrderSysID, &m_cfg.m_szOrderSysID, sizeof(m_cfg.m_szOrderSysID));
    req.ActionFlag = THOST_FTDC_AF_Delete;
    req.LimitPrice = 0;
    req.VolumeChange = 0;
    CTriggerLogApi::TriggerEx(m_cfg.m_nRequestID, E_TRIGGER_STAGE_REQ); // 记录请求时间
    int result = m_api->ReqOrderAction(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 执行录入 */
void CTraderApi::ExecOrderInsert(void)
{
    CheckFuncNameEx();
    CThostFtdcInputExecOrderField req;
    memset(&req, 0, sizeof(req));
    int result = m_api->ReqExecOrderInsert(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 执行操作 */
void CTraderApi::ExecOrderAction(void)
{
    CheckFuncNameEx();
    CThostFtdcInputExecOrderActionField req;
    memset(&req, 0, sizeof(req));
    int result = m_api->ReqExecOrderAction(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 报价录入 */
void CTraderApi::QuoteInsert(void)
{
    CheckFuncNameEx();
    CThostFtdcInputQuoteField req;
    memset(&req, 0, sizeof(req));
    int result = m_api->ReqQuoteInsert(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 报价操作 */
void CTraderApi::QuoteAction(void)
{
    CheckFuncNameEx();
    CThostFtdcInputQuoteActionField req;
    memset(&req, 0, sizeof(req));
    int result = m_api->ReqQuoteAction(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 询价录入 */
void CTraderApi::ForQuoteInsert(void)
{
    CheckFuncNameEx();
    CThostFtdcInputForQuoteField req;
    memset(&req, 0, sizeof(req));
    int result = m_api->ReqForQuoteInsert(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 报单查询 */
void CTraderApi::QryOrder(void)
{
    CheckFuncNameEx();
    CThostFtdcQryOrderField req;
    memset(&req, 0, sizeof(req));
    int result = m_api->ReqQryOrder(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 执行查询 */
void CTraderApi::QryExecOrder(void)
{
    CheckFuncNameEx();
    CThostFtdcQryExecOrderField req;
    memset(&req, 0, sizeof(req));
    int result = m_api->ReqQryExecOrder(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 报价查询 */
void CTraderApi::QryQuote(void)
{
    CheckFuncNameEx();
    CThostFtdcQryQuoteField req;
    memset(&req, 0, sizeof(req));
    int result = m_api->ReqQryQuote(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 询价查询 */
void CTraderApi::QryForQuote(void)
{
    CheckFuncNameEx();
    CThostFtdcQryForQuoteField req;
    memset(&req, 0, sizeof(req));
    int result = m_api->ReqQryForQuote(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 交易查询 */
void CTraderApi::QryTradingNotice(void)
{
    CheckFuncNameEx();
    CThostFtdcQryTradingNoticeField req;
    memset(&req, 0, sizeof(req));
    int result = m_api->ReqQryTradingNotice(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 成交查询 */
void CTraderApi::QryTrade(void)
{
    CheckFuncNameEx();
    CThostFtdcQryTradeField req;
    memset(&req, 0, sizeof(req));
    int result = m_api->ReqQryTrade(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 通知查询 */
void CTraderApi::QryNotice(void)
{
    CheckFuncNameEx();
    CThostFtdcQryNoticeField req;
    memset(&req, 0, sizeof(req));
    int result = m_api->ReqQryNotice(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 交易所查询 */
void CTraderApi::QryExchange(void)
{
    CheckFuncNameEx();
    CThostFtdcQryExchangeField req;
    memset(&req, 0, sizeof(req));
    int result = m_api->ReqQryExchange(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 交易编码查询 */
void CTraderApi::QryTradingCode(void)
{
    CheckFuncNameEx();
    CThostFtdcQryTradingCodeField req;
    memset(&req, 0, sizeof(req));
    int result = m_api->ReqQryTradingCode(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 交易产品查询 */
void CTraderApi::QryProduct(void)
{
    CheckFuncNameEx();
    CThostFtdcQryProductField req;
    memset(&req, 0, sizeof(req));
    int result = m_api->ReqQryProduct(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 合约查询 */
void CTraderApi::QryInstrument(void)
{
    CheckFuncNameEx();
    CThostFtdcQryInstrumentField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID));
    int result = m_api->ReqQryInstrument(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 行情查询 */
void CTraderApi::QryDepthMarketData(void)
{
    CheckFuncNameEx();
    CThostFtdcQryDepthMarketDataField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID));
    int result = m_api->ReqQryDepthMarketData(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 持仓查询 */
void CTraderApi::QryInvestorPosition(void)
{
    CheckFuncNameEx();
    CThostFtdcQryInvestorPositionField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID));
    int result = m_api->ReqQryInvestorPosition(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 资金查询 */
void CTraderApi::QryTradingAccount(void)
{
    CheckFuncNameEx();
    CThostFtdcQryTradingAccountField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    int result = m_api->ReqQryTradingAccount(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 投资者查询 */
void CTraderApi::QryInvestor(void)
{
    CheckFuncNameEx();
    CThostFtdcQryInvestorField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    int result = m_api->ReqQryInvestor(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

const char *CTraderApi::oper_name[E_OPER_TYPE_COUNT]= {
    "default",
    "Authe()",
    "Login()",
    "Logout()",
    "SettlementInfoConfirm()",
    "OrderInsert()",
    "OrderAction()",
    "ExecOrderInsert()",
    "ExecOrderAction()",
    "QuoteInsert()",
    "QuoteAction()",
    "ForQuoteInsert()",
    "QryOrder()",
    "QryExecOrder()",
    "QryQuote()",
    "QryForQuote()",
    "QryTradingNotice()",
    "QryTrade()",
    "QryNotice()",
    "QryExchange()",
    "QryTradingCode()",
    "QryProduct()",
    "QryInstrument()",
    "QryDepthMarketData()",
    "QryInvestorPosition()",
    "QryTradingAccount()",
    "QryInvestor()"
};

int CTraderApi::oper_count = 0;

/* 启动 */
void CTraderApi::Start(void)
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
void CTraderApi::Stop(void)
{
    if (m_bRunning)
    {
        m_bRunning = FALSE;
        if (m_hThread)
        {
            ::WaitForSingleObject(m_hThread, INFINITE);
            ::CloseHandle(m_hThread);
            m_hThread = NULL;
        }
    }
}

/* 命令行操作 */
void CTraderApi::CliOperation(void)
{
    /* 延迟以让反馈消息 */
    Sleep(3000);

    if (m_bConnect)
    {
        int oper_type = 0;
        CPrintApi::AppPrint("\n\n");
        CPrintApi::AppPrint("-----------------------------------------------------------------------------\n");
        CPrintApi::AppPrint("----操作提示：\n");
        if (m_bLogin)
        {
            for (oper_type=0; oper_type<E_OPER_TYPE_COUNT; oper_type++)
            {
                if (E_OPER_LOGIN!=oper_type)
                {
                    CPrintApi::AppPrint("    %2d. %s;\n", oper_type, oper_name[oper_type]);
                }
            }
            CPrintApi::AppPrint("----请选择序号：");

            oper_type = 0;
            scanf("%d", &oper_type);
            if (E_OPER_DEFAULT<=oper_type && E_OPER_TYPE_COUNT>oper_type && E_OPER_LOGIN!=oper_type)
            {
                CPrintApi::DbgPrint("\n");
                CPrintApi::DbgPrint("-----------------------------------------------------------------------------");
                CPrintApi::DbgPrint("----函数: %s", __FUNCTION__);
                CPrintApi::DbgPrint("----第%d次操作：%2d. %s.", ++oper_count, oper_type, oper_name[oper_type]);
            }
            else
            {
                CPrintApi::DbgPrint("\n");
                CPrintApi::DbgPrint("-----------------------------------------------------------------------------");
                CPrintApi::DbgPrint("----函数: %s", __FUNCTION__);
                CPrintApi::DbgPrint("----输入序号错误");
            }
            switch (oper_type)
            {
            case E_OPER_AUTHE:
                Authe();
                break;

            case E_OPER_LOGIN:
                break;

            case E_OPER_LOGOUT:
                Logout();
                break;

            case E_OPER_SETTLEMENT_INFO_CONFIRM:
                SettlementInfoConfirm();
                break;

            case E_OPER_ORDER_INSERT:
                OrderInsert();
                break;

            case E_OPER_ORDER_ACTION:
                OrderAction();
                break;

            case E_OPER_EXEC_ORDER_INSERT:
                ExecOrderInsert();
                break;

            case E_OPER_EXEC_ORDER_ACTION:
                ExecOrderAction();
                break;

            case E_OPER_QUOTE_INSERT:
                QuoteInsert();
                break;

            case E_OPER_QUOTE_ACTION:
                QuoteAction();
                break;

            case E_OPER_FOR_QUETE_INSERT:
                ForQuoteInsert();
                break;

            case E_OPER_QRY_ORDER:
                QryOrder();
                break;

            case E_OPER_QRY_EXEC_ORDER:
                QryExecOrder();
                break;

            case E_OPER_QRY_QUOTE:
                QryQuote();
                break;

            case E_OPER_QRY_FOR_QUOTE:
                QryForQuote();
                break;

            case E_OPER_QRY_TRADING_NOTICE:
                QryTradingNotice();
                break;

            case E_OPER_QRY_TRADE:
                QryTrade();
                break;

            case E_OPER_QRY_NOTICE:
                QryNotice();
                break;

            case E_OPER_QRY_EXCHANGE:
                QryExchange();
                break;

            case E_OPER_QRY_TRADING_CODE:
                QryTradingCode();
                break;

            case E_OPER_QRY_PRODUCT:
                QryProduct();
                break;

            case E_OPER_QRY_INSTRUMENT:
                QryInstrument();
                break;

            case E_OPER_QRY_DEPTH_MARKET_DATE:
                QryDepthMarketData();
                break;

            case E_OPER_QRY_INVESTOR_POSITION:
                QryInvestorPosition();
                break;

            case E_OPER_QRY_TRADING_ACCOUNT:
                QryTradingAccount();
                break;

            case E_OPER_QRY_INVESTOR:
                QryInvestor();
                break;

            default:
                break;
            }
        }
        else
        {
            for (oper_type=0; oper_type<E_OPER_TYPE_COUNT; oper_type++)
            {
                switch (oper_type)
                {
                case E_OPER_LOGIN:
                    CPrintApi::AppPrint("    %2d. Login();\n", oper_type);
                    break;

                default:
                    break;
                }
            }
            CPrintApi::AppPrint("----请选择序号：");

            oper_type = 0;
            scanf("%d", &oper_type);
            if (E_OPER_LOGIN == oper_type)
            {
                CPrintApi::DbgPrint("\n");
                CPrintApi::DbgPrint("-----------------------------------------------------------------------------");
                CPrintApi::DbgPrint("----函数: %s", __FUNCTION__);
                CPrintApi::DbgPrint("----第%d次操作：%2d. %s.", ++oper_count, oper_type, oper_name[oper_type]);
                Login();
            }
            else
            {
                CPrintApi::DbgPrint("\n");
                CPrintApi::DbgPrint("-----------------------------------------------------------------------------");
                CPrintApi::DbgPrint("----函数: %s", __FUNCTION__);
                CPrintApi::DbgPrint("----输入序号错误");
            }
        }
    }
}

/* 自动化操作 */
void CTraderApi::AutoOperation(void)
{
    if (m_bConnect)
    {
        if (m_bLogin)
        {
            CMarketApi *api = CMarketApi::GetInstance();
            if (api)
            {
                /* 等待行情数据 */
                if (api->m_data.WaitMarketData())
                {
                    /* 委托 */
                    CreateOrder(); /* 每隔20个Tick执行一次委托 */

                    /* 等待 */
                    int nTickPeriod = api->m_data.GetTickPeriod();
                    int nTickTime = 2*nTickPeriod;
                    Sleep(nTickTime);

                    /* 撤销 */
                    RevokeOrder(); /* 每隔2个Tick执行一次撤销 */

                    m_bRunning = FALSE;
                }
            }
        }
        else
        {
            /* 登录 */
            Login();
        }
    }
    else
    {
        /* 等待 */
        Sleep(5000);
    }
}

/* 委托 */
void CTraderApi::CreateOrder(void)
{
    CheckFuncNameEx();

    CMarketApi *api = CMarketApi::GetInstance();
    if (!api)
        return;

    CThostFtdcInputOrderField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID));
    memcpy(&req.OrderRef, &m_cfg.m_szOrderRef, sizeof(m_cfg.m_szOrderRef));
    sprintf(m_cfg.m_szOrderRef, "%d", 1+atoi(req.OrderRef));
    memcpy(&req.UserID, &m_cfg.m_szUserID, sizeof(m_cfg.m_szUserID));
    req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
    if (api->m_data.m_bUpperTrend)
    {
        /* 上涨趋势，以跌停价买入 */
        req.Direction = THOST_FTDC_D_Buy;
        req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
        req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
        req.LimitPrice = api->m_data.m_fLowerLimitPrice;
    }
    else
    {
        /* 下跌趋势，以涨停价卖出 */
        req.Direction = THOST_FTDC_D_Sell;
        req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
        req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
        req.LimitPrice = api->m_data.m_fUpperLimitPrice;
    }
    req.VolumeTotalOriginal = 1;
    req.TimeCondition = THOST_FTDC_TC_GFD;
    req.VolumeCondition = THOST_FTDC_VC_AV;
    req.MinVolume = 1;
    req.ContingentCondition = THOST_FTDC_CC_ParkedOrder; /* 非立即成交的预埋单 */
    req.StopPrice = 0;
    req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    req.IsAutoSuspend = 0;
    req.IsSwapOrder = 0;

    /* 发起请求 */
    m_data.UpdateTraderData(&req, E_TRIGGER_STAGE_REQ);
    int result = m_api->ReqOrderInsert(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

/* 撤销 */
void CTraderApi::RevokeOrder(void)
{
    CheckFuncNameEx();
    CThostFtdcInputOrderActionField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_data.m_szBrokerID, sizeof(m_data.m_szBrokerID));
    memcpy(&req.InvestorID, &m_data.m_szInvestorID, sizeof(m_data.m_szInvestorID));
    memcpy(&req.ExchangeID, &m_cfg.m_szExchangeID, sizeof(m_cfg.m_szExchangeID));
    memcpy(&req.InstrumentID, &m_data.m_szInstrumentID, sizeof(m_data.m_szInstrumentID));
    memcpy(&req.OrderActionRef, &m_data.m_szOrderActionRef, sizeof(m_data.m_szOrderActionRef));
    memcpy(&req.OrderRef, &m_data.m_szOrderRef, sizeof(m_data.m_szOrderRef));
    memcpy(&req.UserID, &m_data.m_szUserID, sizeof(m_data.m_szUserID));
    req.RequestID = m_cfg.m_nRequestID;
    req.FrontID = m_cfg.m_nFrontID;
    req.SessionID = m_cfg.m_nSessionID;
    memcpy(&req.OrderSysID, &m_data.m_szOrderSysID, sizeof(m_data.m_szOrderSysID));
    req.ActionFlag = THOST_FTDC_AF_Delete;
    req.LimitPrice = 0;
    req.VolumeChange = 0;

    /* 发起请求 */
    m_data.UpdateTraderData(&req, E_TRIGGER_STAGE_REQ);
    int result = m_api->ReqOrderAction(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
}

BOOL CTraderApi::IsRunning(void)
{
    return m_bRunning;
}

DWORD CTraderApi::ThreadProc(LPVOID lpParam)
{
    CTraderApi *api = (CTraderApi *)lpParam;
    if (!api)
        return -1;

    /* 交易业务 */
    while (api->IsRunning())
    {
        if (api->m_bHaveCli)
        {
            api->CliOperation();
        }
        else
        {
            api->AutoOperation();
        }
    }

    return 0;
}

CTraderApi *CTraderApi::m_pInstance = NULL;

CTraderApi *CTraderApi::CreateInstance(void)
{
    if (!m_pInstance)
    {
        m_pInstance = new CTraderApi();
        //m_pInstance->m_bHaveCli = TRUE;
    }
    return m_pInstance;
}

void CTraderApi::ReleaseInstance(void)
{
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

CTraderApi *CTraderApi::GetInstance(void)
{
    return m_pInstance;
}

CTraderApi::CTraderApi(void)
{
    m_bRunning = FALSE;
    m_bConnect = FALSE;
    m_bLogin = FALSE;
    m_bHaveCli = FALSE;
    m_hThread = NULL;
    m_api = CThostFtdcTraderApi::CreateFtdcTraderApi();
    m_spi = new CTraderSpi;
    m_api->RegisterSpi(m_spi);
    m_api->SubscribePublicTopic(THOST_TERT_RESTART);
    m_api->SubscribePrivateTopic(THOST_TERT_RESTART);
    m_api->RegisterFront(m_cfg.m_szTraderAddr);
    m_api->Init();
}

CTraderApi::~CTraderApi(void)
{
    /* 停止运行 */
    Stop();

    /* 释放内存 */
    if (m_api)
    {
        m_api->Release();
        m_api = NULL;
    }
    if (m_spi)
    {
        delete m_spi;
        m_spi = NULL;
    }
}

CTraderApi::CSelfRelease CTraderApi::m_self;

CTraderApi::CSelfRelease::CSelfRelease()
{
}
CTraderApi::CSelfRelease::~CSelfRelease()
{
    if(CTraderApi::m_pInstance)
        delete CTraderApi::m_pInstance;
    CTraderApi::m_pInstance = NULL;
}
