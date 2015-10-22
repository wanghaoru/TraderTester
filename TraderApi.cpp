#include "TraderApi.h"
#include "MarketApi.h"

#pragma warning(disable:4996)

CTraderData::CTraderData()
{
    memset(&m_szTraderDesc, 0, sizeof(m_szTraderDesc));
    memset(&m_szInstrumentID, 0, sizeof(m_szInstrumentID));
    memset(&m_nFrontID, 0, sizeof(m_nFrontID));
    memset(&m_nSessionID, 0, sizeof(m_nSessionID));
    memset(&m_tTerminalTime, 0, sizeof(m_tTerminalTime));
    memset(&m_tTHostTime, 0, sizeof(m_tTHostTime));
    memset(&m_tExchangeTime, 0, sizeof(m_tExchangeTime));
    m_nUpdateCount = 0;
}

CTraderData::~CTraderData()
{

}

/* 设置报单信息 */
void CTraderData::SetOrderInfo(const char *szTraderDesc, TThostFtdcInstrumentIDType szInstrumentID, TThostFtdcFrontIDType nFrontID, TThostFtdcSessionIDType nSessionID, TThostFtdcOrderRefType szOrderRef)
{
    strcpy(m_szTraderDesc, szTraderDesc);
    strcpy(m_szInstrumentID, szInstrumentID);
    m_nFrontID = nFrontID;
    m_nSessionID = nSessionID;
    strcpy(m_szOrderRef, szOrderRef);
    memset(&m_tTerminalTime, 0, sizeof(m_tTerminalTime));
    memset(&m_tTHostTime, 0, sizeof(m_tTHostTime));
    memset(&m_tExchangeTime, 0, sizeof(m_tExchangeTime));
    m_nUpdateCount = 0;
}

/* 更新请求时间 */
void CTraderData::UpdateReqTime(void)
{
    GetClockTime(&m_tTerminalTime);
    PrintOrderInfo();
    m_nUpdateCount++;
}

/* 更新回报时间 */
void CTraderData::UpdateRtnTime(void)
{
    if (m_nUpdateCount<=1)
    {
        GetClockTime(&m_tTHostTime);
        m_nUpdateCount = 1;
    }
    else
    {
        GetClockTime(&m_tExchangeTime);
    }
    PrintOrderInfo();
    m_nUpdateCount++;
}

/* 打印报单信息 */
void CTraderData::PrintOrderInfo(void)
{
    CPrintApi::LogPrint("\n");
    CPrintApi::LogPrint("-----------------------------------------------------------------------------");
    CPrintApi::LogPrint("----      合约编号=%s", m_szInstrumentID);
    CPrintApi::LogPrint("----      前置编号=%08u", m_nFrontID);
    CPrintApi::LogPrint("----      会话编号=%08u", m_nSessionID);
    CPrintApi::LogPrint("----  报单引用编号=%s", m_szOrderRef);
    CPrintApi::LogPrint("----      报单描述=%s", m_szTraderDesc);
    if (m_tTerminalTime.allUs)
    {
        CPrintApi::LogPrint("----  终端发送时间=%02d:%02d:%02d,%d毫秒-%lld微秒", 
            m_tTerminalTime.curTm.wHour, 
            m_tTerminalTime.curTm.wMinute, 
            m_tTerminalTime.curTm.wSecond, 
            m_tTerminalTime.curTm.wMilliseconds, 
            m_tTerminalTime.curUs);
    }
    if (m_tTHostTime.allUs)
    {
        CPrintApi::LogPrint("----  平台回报时间=%02d:%02d:%02d,%d毫秒-%lld微秒", 
            m_tTHostTime.curTm.wHour, 
            m_tTHostTime.curTm.wMinute, 
            m_tTHostTime.curTm.wSecond, 
            m_tTHostTime.curTm.wMilliseconds, 
            m_tTHostTime.curUs);
        if (m_tTerminalTime.allUs)
        {
            CPrintApi::LogPrint("----  平台回报时差=%lld微秒", (m_tTHostTime.allUs-m_tTerminalTime.allUs));
        }
    }
    if (m_tExchangeTime.allUs)
    {
        CPrintApi::LogPrint("----交易所回报时间=%02d:%02d:%02d,%d毫秒-%lld微秒", 
            m_tExchangeTime.curTm.wHour, 
            m_tExchangeTime.curTm.wMinute, 
            m_tExchangeTime.curTm.wSecond, 
            m_tExchangeTime.curTm.wMilliseconds, 
            m_tExchangeTime.curUs);
        if (m_tTerminalTime.allUs)
        {
            CPrintApi::LogPrint("----交易所回报时差=%lld微秒", (m_tExchangeTime.allUs-m_tTerminalTime.allUs));
        }
    }
    CPrintApi::LogPrint("-----------------------------------------------------------------------------");
}

CTraderDataManager::CTraderDataManager()
{

}

CTraderDataManager::~CTraderDataManager()
{
    /* 清空队列 */
    while (!m_UnTradeList.empty())
    {
        m_UnTradeList.pop_front();
    }

    /* 清空映射 */
    map<string, CTraderData *>::iterator iter;
    for (iter=m_OrderMap.begin(); iter!=m_OrderMap.end(); iter++)
    {
        CTraderData *data = iter->second;
        delete data;
    }
    m_OrderMap.clear();
}

/* 更新交易数据 */
void CTraderDataManager::UpdateTraderData(CThostFtdcInputOrderField *pInputOrder, E_UPDATE_STAGE_TYPE nStage)
{
    CTraderApi *api = CTraderApi::GetInstance();

    /* 设置描述 */
    char szTraderDesc[128];
    switch (pInputOrder->Direction)
    {
    case THOST_FTDC_D_Buy:
        {
            /* 开平标志 */
            switch (pInputOrder->CombOffsetFlag[0])
            {
            case THOST_FTDC_OF_Open:
                sprintf(szTraderDesc, "开仓买入");
                break;
            case THOST_FTDC_OF_Close:
                sprintf(szTraderDesc, "平仓买入");
                break;
            case THOST_FTDC_OF_ForceClose:
                sprintf(szTraderDesc, "强平买入");
                break;
            case THOST_FTDC_OF_CloseToday:
                sprintf(szTraderDesc, "平今买入");
                break;
            case THOST_FTDC_OF_CloseYesterday:
                sprintf(szTraderDesc, "平昨买入");
                break;
            case THOST_FTDC_OF_ForceOff:
                sprintf(szTraderDesc, "强减买入");
                break;
            case THOST_FTDC_OF_LocalForceClose:
                sprintf(szTraderDesc, "本地强平买入");
                break;
            default:
                break;
            }
        }
        break;
    case THOST_FTDC_D_Sell:
        {
            /* 开平标志 */
            switch (pInputOrder->CombOffsetFlag[0])
            {
            case THOST_FTDC_OF_Open:
                sprintf(szTraderDesc, "开仓卖出");
                break;
            case THOST_FTDC_OF_Close:
                sprintf(szTraderDesc, "平仓卖出");
                break;
            case THOST_FTDC_OF_ForceClose:
                sprintf(szTraderDesc, "强平卖出");
                break;
            case THOST_FTDC_OF_CloseToday:
                sprintf(szTraderDesc, "平今卖出");
                break;
            case THOST_FTDC_OF_CloseYesterday:
                sprintf(szTraderDesc, "平昨卖出");
                break;
            case THOST_FTDC_OF_ForceOff:
                sprintf(szTraderDesc, "强减卖出");
                break;
            case THOST_FTDC_OF_LocalForceClose:
                sprintf(szTraderDesc, "本地强平卖出");
                break;
            default:
                break;
            }
        }
        break;
    default:
        break;
    }

    /* 根据不同阶段进行处理 */
    switch (nStage)
    {
        /* REQ视为终端发送时间 */
    case E_UPDATE_STAGE_REQ:   /* 请求报单 */
        {
            string strMapIndex = GetMapIndex(api->m_cfg.m_nFrontID, api->m_cfg.m_nSessionID, pInputOrder->OrderRef);
            map<string, CTraderData *>::iterator iter;
            iter = m_OrderMap.find(strMapIndex);
            if (iter==m_OrderMap.end())
            {
                /* 未找到 */
                CTraderData *new_data = new CTraderData;
                new_data->SetOrderInfo(szTraderDesc, pInputOrder->InstrumentID, api->m_cfg.m_nFrontID, api->m_cfg.m_nSessionID, pInputOrder->OrderRef);
                new_data->UpdateReqTime();
                m_OrderMap[strMapIndex] = new_data;
            }
            else
            {
                /* 已找到-显示异常 */
                CPrintApi::LogPrint("----异常位置：文件=[%s], 函数=[%s], 行号=[%d]", __FILE__, __FUNCTION__, __LINE__);
            }
        }
        break;

        /* RSP和ERR视为平台回报时间  */
    case E_UPDATE_STAGE_RSP:   /* 报单响应 */
    case E_UPDATE_STAGE_ERR:   /* 报单错误 */
        {
            string strMapIndex = GetMapIndex(api->m_cfg.m_nFrontID, api->m_cfg.m_nSessionID, pInputOrder->OrderRef);
            map<string, CTraderData *>::iterator iter;
            iter = m_OrderMap.find(strMapIndex);
            if (iter==m_OrderMap.end())
            {
                /* 未找到-显示异常 */
                CPrintApi::LogPrint("----异常位置：文件=[%s], 函数=[%s], 行号=[%d]", __FILE__, __FUNCTION__, __LINE__);
            }
            else
            {
                /* 已找到 */
                CTraderData *old_data = iter->second;
                old_data->UpdateRtnTime();
            }
        }
        break;

    default:
        {
            /* 未知-显示异常 */
            CPrintApi::LogPrint("----异常位置：文件=[%s], 函数=[%s], 行号=[%d]", __FILE__, __FUNCTION__, __LINE__);
        }
        break;
    }
}

/* 更新交易数据 */
void CTraderDataManager::UpdateTraderData(CThostFtdcInputOrderActionField *pInputAction, E_UPDATE_STAGE_TYPE nStage)
{
    /* 设置描述 */
    char szTraderDesc[128];
    switch (pInputAction->ActionFlag)
    {
    case THOST_FTDC_AF_Delete:
        sprintf(szTraderDesc, "删除操作");
        break;
    case THOST_FTDC_AF_Modify:
        sprintf(szTraderDesc, "修改操作");
        break;
    default:
        break;
    }

    /* 根据不同阶段进行处理 */
    switch (nStage)
    {
        /* REQ视为终端发送时间 */
    case E_UPDATE_STAGE_REQ:   /* 请求操作 */
        {
            string strMapIndex = GetMapIndex(pInputAction->FrontID, pInputAction->SessionID, pInputAction->OrderRef);
            map<string, CTraderData *>::iterator iter;
            iter = m_OrderMap.find(strMapIndex);
            if (iter==m_OrderMap.end())
            {
                /* 未找到-显示异常 */
                CPrintApi::LogPrint("----异常位置：文件=[%s], 函数=[%s], 行号=[%d]", __FILE__, __FUNCTION__, __LINE__);
            }
            else
            {
                /* 已找到 */
                CTraderData *old_data = iter->second;
                old_data->SetOrderInfo(szTraderDesc, pInputAction->InstrumentID, pInputAction->FrontID, pInputAction->SessionID, pInputAction->OrderRef);
                old_data->UpdateReqTime();
            }
        }
        break;

        /* RSP视为平台回报时间  */
    case E_UPDATE_STAGE_RSP:   /* 操作响应 */
        {
            string strMapIndex = GetMapIndex(pInputAction->FrontID, pInputAction->SessionID, pInputAction->OrderRef);
            map<string, CTraderData *>::iterator iter;
            iter = m_OrderMap.find(strMapIndex);
            if (iter==m_OrderMap.end())
            {
                /* 未找到-显示异常 */
                CPrintApi::LogPrint("----异常位置：文件=[%s], 函数=[%s], 行号=[%d]", __FILE__, __FUNCTION__, __LINE__);
            }
            else
            {
                /* 已找到 */
                CTraderData *old_data = iter->second;
                old_data->UpdateRtnTime();
            }
        }
        break;

    default:
        {
            /* 未知-显示异常 */
            CPrintApi::LogPrint("----异常位置：文件=[%s], 函数=[%s], 行号=[%d]", __FILE__, __FUNCTION__, __LINE__);
        }
        break;
    }
}

/* 更新交易数据 */
void CTraderDataManager::UpdateTraderData(CThostFtdcOrderActionField *pInputOrder, E_UPDATE_STAGE_TYPE nStage)
{
    /* 根据不同阶段进行处理 */
    switch (nStage)
    {
        /* ERR视为平台回报时间  */
    case E_UPDATE_STAGE_ERR:   /* 操作错误 */
        {
            string strMapIndex = GetMapIndex(pInputOrder->FrontID, pInputOrder->SessionID, pInputOrder->OrderRef);
            map<string, CTraderData *>::iterator iter;
            iter = m_OrderMap.find(strMapIndex);
            if (iter==m_OrderMap.end())
            {
                /* 未找到-显示异常 */
                CPrintApi::LogPrint("----异常位置：文件=[%s], 函数=[%s], 行号=[%d]", __FILE__, __FUNCTION__, __LINE__);
            }
            else
            {
                /* 已找到 */
                CTraderData *old_data = iter->second;
                old_data->UpdateRtnTime();
            }
        }
        break;

    default:
        {
            /* 未知-显示异常 */
            CPrintApi::LogPrint("----异常位置：文件=[%s], 函数=[%s], 行号=[%d]", __FILE__, __FUNCTION__, __LINE__);
        }
        break;
    }
}

/* 更新交易数据 */
void CTraderDataManager::UpdateTraderData(CThostFtdcOrderField *pOrder, E_UPDATE_STAGE_TYPE nStage)
{
    /* 设置描述 */
    char szTraderDesc[128];
    switch (pOrder->Direction)
    {
    case THOST_FTDC_D_Buy:
        {
            /* 开平标志 */
            switch (pOrder->CombOffsetFlag[0])
            {
            case THOST_FTDC_OF_Open:
                sprintf(szTraderDesc, "开仓买入");
                break;
            case THOST_FTDC_OF_Close:
                sprintf(szTraderDesc, "平仓买入");
                break;
            case THOST_FTDC_OF_ForceClose:
                sprintf(szTraderDesc, "强平买入");
                break;
            case THOST_FTDC_OF_CloseToday:
                sprintf(szTraderDesc, "平今买入");
                break;
            case THOST_FTDC_OF_CloseYesterday:
                sprintf(szTraderDesc, "平昨买入");
                break;
            case THOST_FTDC_OF_ForceOff:
                sprintf(szTraderDesc, "强减买入");
                break;
            case THOST_FTDC_OF_LocalForceClose:
                sprintf(szTraderDesc, "本地强平买入");
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
                sprintf(szTraderDesc, "开仓卖出");
                break;
            case THOST_FTDC_OF_Close:
                sprintf(szTraderDesc, "平仓卖出");
                break;
            case THOST_FTDC_OF_ForceClose:
                sprintf(szTraderDesc, "强平卖出");
                break;
            case THOST_FTDC_OF_CloseToday:
                sprintf(szTraderDesc, "平今卖出");
                break;
            case THOST_FTDC_OF_CloseYesterday:
                sprintf(szTraderDesc, "平昨卖出");
                break;
            case THOST_FTDC_OF_ForceOff:
                sprintf(szTraderDesc, "强减卖出");
                break;
            case THOST_FTDC_OF_LocalForceClose:
                sprintf(szTraderDesc, "本地强平卖出");
                break;
            default:
                break;
            }
        }
        break;
    default:
        break;
    }

    /* 根据不同阶段进行处理 */
    switch (nStage)
    {
        /* RTN视为平台回报时间和交易所回报时间  */
    case E_UPDATE_STAGE_RTN:   /* 报单回报 */
        {
            string strMapIndex = GetMapIndex(pOrder->FrontID, pOrder->SessionID, pOrder->OrderRef);
            map<string, CTraderData *>::iterator iter;
            iter = m_OrderMap.find(strMapIndex);
            if (iter==m_OrderMap.end())
            {
                /* 未找到 */
                CTraderData *new_data = new CTraderData;
                new_data->SetOrderInfo(szTraderDesc, pOrder->InstrumentID, pOrder->FrontID, pOrder->SessionID, pOrder->OrderRef);
                new_data->UpdateRtnTime();
                m_OrderMap[strMapIndex] = new_data;

                /* 如果报单处于委托状态则加入未成交报单队列 */
                switch (pOrder->OrderStatus)
                {
                case THOST_FTDC_OST_PartTradedQueueing:
                case THOST_FTDC_OST_NoTradeQueueing:
                    {
                        list<CTraderData *>::iterator iter;
                        for (iter=m_UnTradeList.begin(); iter!=m_UnTradeList.end(); iter++)
                        {
                            CTraderData *cur_data = *iter;
                            if (0 == strcmp(cur_data->m_szInstrumentID, new_data->m_szInstrumentID) &&
                                cur_data->m_nFrontID == new_data->m_nFrontID &&
                                cur_data->m_nSessionID == new_data->m_nSessionID &&
                                0 == strcmp(cur_data->m_szOrderRef, new_data->m_szOrderRef))
                            {
                                break;
                            }
                        }
                        if (iter==m_UnTradeList.end())
                        {
                            m_UnTradeList.push_back(new_data);
                        }
                    }
                    break;
                case THOST_FTDC_OST_Canceled:
                case THOST_FTDC_OST_AllTraded:
                    {
                        list<CTraderData *>::iterator iter;
                        for (iter=m_UnTradeList.begin(); iter!=m_UnTradeList.end(); iter++)
                        {
                            CTraderData *cur_data = *iter;
                            if (0 == strcmp(cur_data->m_szInstrumentID, new_data->m_szInstrumentID) &&
                                cur_data->m_nFrontID == new_data->m_nFrontID &&
                                cur_data->m_nSessionID == new_data->m_nSessionID &&
                                0 == strcmp(cur_data->m_szOrderRef, new_data->m_szOrderRef))
                            {
                                break;
                            }
                        }
                        if (iter!=m_UnTradeList.end())
                        {
                            m_UnTradeList.erase(iter);
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            else
            {
                /* 已找到 */
                CTraderData *old_data = iter->second;
                old_data->UpdateRtnTime();

                /* 如果报单处于委托状态则加入未成交报单队列 */
                switch (pOrder->OrderStatus)
                {
                case THOST_FTDC_OST_PartTradedQueueing:
                case THOST_FTDC_OST_NoTradeQueueing:
                    {
                        list<CTraderData *>::iterator iter;
                        for (iter=m_UnTradeList.begin(); iter!=m_UnTradeList.end(); iter++)
                        {
                            CTraderData *cur_data = *iter;
                            if (0 == strcmp(cur_data->m_szInstrumentID, old_data->m_szInstrumentID) &&
                                cur_data->m_nFrontID == old_data->m_nFrontID &&
                                cur_data->m_nSessionID == old_data->m_nSessionID &&
                                0 == strcmp(cur_data->m_szOrderRef, old_data->m_szOrderRef))
                            {
                                break;
                            }
                        }
                        if (iter==m_UnTradeList.end())
                        {
                            m_UnTradeList.push_back(old_data);
                        }
                    }
                    break;
                case THOST_FTDC_OST_Canceled:
                case THOST_FTDC_OST_AllTraded:
                    {
                        list<CTraderData *>::iterator iter;
                        for (iter=m_UnTradeList.begin(); iter!=m_UnTradeList.end(); iter++)
                        {
                            CTraderData *cur_data = *iter;
                            if (0 == strcmp(cur_data->m_szInstrumentID, old_data->m_szInstrumentID) &&
                                cur_data->m_nFrontID == old_data->m_nFrontID &&
                                cur_data->m_nSessionID == old_data->m_nSessionID &&
                                0 == strcmp(cur_data->m_szOrderRef, old_data->m_szOrderRef))
                            {
                                break;
                            }
                        }
                        if (iter!=m_UnTradeList.end())
                        {
                            m_UnTradeList.erase(iter);
                        }
                    }
                    break;
                default:
                    break;
                }
            }
        }
        break;

    default:
        {
            /* 未知-显示异常 */
            CPrintApi::LogPrint("----异常位置：文件=[%s], 函数=[%s], 行号=[%d]", __FILE__, __FUNCTION__, __LINE__);
        }
        break;
    }
}

/* 更新交易数据 */
void CTraderDataManager::UpdateTraderData(CThostFtdcTradeField *pTrader, E_UPDATE_STAGE_TYPE nStage)
{ 
}

/* 计算索引标识 */
string CTraderDataManager::GetMapIndex(int nFrontID, int nSessionID, char *szOrderRef)
{
    char szIndex[128];
    sprintf(szIndex, "%u%u%s", nFrontID, nSessionID, szOrderRef);
    string strIndex = szIndex;
    return strIndex;
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
    CPrintParams::PrintFunctionEx();

    /* 设置连接状态 */
    CTraderApi *api = CTraderApi::GetInstance();
    api->m_bConnect = TRUE;
}

/* 断开通知 */
void CTraderSpi::OnFrontDisconnected(int nReason)
{
    CPrintParams::PrintFunctionEx();
    CPrintApi::DbgPrint("----参数：nReason=0x%08x\n", nReason);

    /* 设置连接状态 */
    CTraderApi *api = CTraderApi::GetInstance();
    api->m_bConnect = FALSE;
}

/* 心跳通知 */
void CTraderSpi::OnHeartBeatWarning(int nTimeLapse)
{
    CPrintParams::PrintFunctionEx();
    CPrintApi::DbgPrint("----参数：nTimeLapse=%08d", nTimeLapse);
}

/* 报单通知 */
void CTraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pOrder);

    /* 更新数据 */
    CTraderApi *api = CTraderApi::GetInstance();
    api->m_mgr.UpdateTraderData(pOrder, E_UPDATE_STAGE_RTN);
}

/* 执行通知 */
void CTraderSpi::OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pExecOrder);
}

/* 报价通知 */
void CTraderSpi::OnRtnQuote(CThostFtdcQuoteField *pQuote)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pQuote);
}

/* 询价通知 */
void CTraderSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pForQuoteRsp);
}

/* 交易通知 */
void CTraderSpi::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pTradingNoticeInfo);
}

/* 成交通知 */
void CTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pTrade);

    /* 更新数据 */
    CTraderApi *api = CTraderApi::GetInstance();
    api->m_mgr.UpdateTraderData(pTrade, E_UPDATE_STAGE_RTN);
}

/* 报单录入错误 */
void CTraderSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pInputOrder, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);

        /* 更新数据 */
        CTraderApi *api = CTraderApi::GetInstance();
        api->m_mgr.UpdateTraderData(pInputOrder, E_UPDATE_STAGE_ERR);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 报单操作错误 */
void CTraderSpi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pOrderAction, pRspInfo);
    
    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);

        /* 更新数据 */
        CTraderApi *api = CTraderApi::GetInstance();
        api->m_mgr.UpdateTraderData(pOrderAction, E_UPDATE_STAGE_ERR);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 执行录入错误 */
void CTraderSpi::OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pInputExecOrder, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 执行操作错误 */
void CTraderSpi::OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pExecOrderAction, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 报价录入错误 */
void CTraderSpi::OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pInputQuote, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 报价操作错误 */
void CTraderSpi::OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pQuoteAction, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 询价录入错误 */
void CTraderSpi::OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pInputForQuote, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 错误响应 */
void CTraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 认证响应 */
void CTraderSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pRspAuthenticateField, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 登录响应 */
void CTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pRspUserLogin, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);

        /* 登录 */
        CTraderApi *api = CTraderApi::GetInstance();
        api->m_cfg.m_nFrontID = pRspUserLogin->FrontID;
        api->m_cfg.m_nSessionID = pRspUserLogin->SessionID;
        memcpy(&api->m_cfg.m_szMaxOrderRef, &pRspUserLogin->MaxOrderRef, sizeof(pRspUserLogin->MaxOrderRef));
        sprintf(api->m_cfg.m_szOrderRef, "%d", 1+atoi(api->m_cfg.m_szMaxOrderRef));
        sprintf(api->m_cfg.m_szExecOrderRef, "%d", 1+atoi(api->m_cfg.m_szMaxOrderRef));
        sprintf(api->m_cfg.m_szQuoteRef, "%d", 1+atoi(api->m_cfg.m_szMaxOrderRef));
        api->m_bLogin = TRUE;

        /* 首次登录必须确认结算 */
        api->SettlementInfoConfirm();
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 注销响应 */
void CTraderSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pUserLogout, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);

        /* 注销 */
        CTraderApi *api = CTraderApi::GetInstance();
        api->m_bLogin = FALSE;
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 确认结算响应 */
void CTraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pSettlementInfoConfirm, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 报单录入响应 */
void CTraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pInputOrder, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);

        /* 更新数据 */
        CTraderApi *api = CTraderApi::GetInstance();
        api->m_mgr.UpdateTraderData(pInputOrder, E_UPDATE_STAGE_RSP);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 报单操作响应 */
void CTraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pInputOrderAction, pRspInfo);  

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);

        /* 更新数据 */
        CTraderApi *api = CTraderApi::GetInstance();
        api->m_mgr.UpdateTraderData(pInputOrderAction, E_UPDATE_STAGE_RSP);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 执行录入响应 */
void CTraderSpi::OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pInputExecOrder, pRspInfo);  

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 执行操作响应 */
void CTraderSpi::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pInputExecOrderAction, pRspInfo);  

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 报价录入响应 */
void CTraderSpi::OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pInputQuote, pRspInfo);  

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 报价操作响应 */
void CTraderSpi::OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pInputQuoteAction, pRspInfo);  

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 询价录入响应 */
void CTraderSpi::OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pInputForQuote, pRspInfo);  

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 查询报单响应 */
void CTraderSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pOrder, pRspInfo);  

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 查询执行响应 */
void CTraderSpi::OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pExecOrder, pRspInfo);  

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 查询报价响应 */
void CTraderSpi::OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pQuote, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 查询询价响应 */
void CTraderSpi::OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pForQuote, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 查询交易响应 */
void CTraderSpi::OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pTradingNotice, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 查询成交响应 */
void CTraderSpi::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pTrade, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 查询通知响应 */
void CTraderSpi::OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pNotice, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 查询交易所响应 */
void CTraderSpi::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pExchange, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 查询交易编码响应 */
void CTraderSpi::OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pTradingCode, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 查询产品响应 */
void CTraderSpi::OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pProduct, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 查询合约响应 */
void CTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pInstrument, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 查询行情响应 */
void CTraderSpi::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pDepthMarketData, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 查询持仓响应 */
void CTraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pInvestorPosition, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 查询资金响应 */
void CTraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pTradingAccount, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 查询投资者响应 */
void CTraderSpi::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CPrintParams::PrintFunctionEx();
    CPrintParams::PrintParams(pInvestor, pRspInfo);

    /* 检查响应结果 */
    BOOL bCheck = CheckRspInfo(pRspInfo);
    if (bCheck)
    {
        CPrintApi::DbgPrint("----%s响应成功", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----%s响应失败", __FUNCTION__);
    }
}

/* 认证操作 */
void CTraderApi::Authe(void)
{
    CPrintParams::PrintFunctionEx();
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
    CPrintParams::PrintFunctionEx();
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
    CPrintParams::PrintFunctionEx();
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
    CPrintParams::PrintFunctionEx();
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
    CPrintParams::PrintFunctionEx();

    CMarketApi *api = CMarketApi::GetInstance();
    if (!api)
        return;

    /* 填充数据 */
    CPrintApi::LogPrint("\n");
    CPrintApi::LogPrint("-----------------------------------------------------------------------------");
#if 0
    /* 开仓跌停价买入 */
    CThostFtdcInputOrderField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID));
    memcpy(&req.OrderRef, &m_cfg.m_szOrderRef, sizeof(m_cfg.m_szOrderRef));
    sprintf(m_cfg.m_szOrderRef, "%d", 1+atoi(req.OrderRef));
    memcpy(&req.UserID, &m_cfg.m_szUserID, sizeof(m_cfg.m_szUserID));
    req.OrderPriceType = THOST_FTDC_OPT_LimitPrice; /* 经测试，THOST_FTDC_OPT_AnyPrice不被支持 */
    req.Direction = THOST_FTDC_D_Buy;
    req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    req.LimitPrice = api->m_data.m_fLowerLimitPrice;
    req.VolumeTotalOriginal = 1;
    req.TimeCondition = THOST_FTDC_TC_GFD;
    req.VolumeCondition = THOST_FTDC_VC_AV;
    req.MinVolume = 1;
    req.ContingentCondition = THOST_FTDC_CC_Immediately;
    req.StopPrice = 0;
    req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    req.RequestID = m_cfg.m_nRequestID;
    req.IsAutoSuspend = 0;
    req.IsSwapOrder = 0;
    CPrintApi::LogPrint("----跌停价开仓买入期货合约（%s），报单引用编号（%s）", req.InstrumentID, req.OrderRef);
#endif
#if 1
    /* 开仓涨停价卖出 */
    CThostFtdcInputOrderField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID));
    memcpy(&req.OrderRef, &m_cfg.m_szOrderRef, sizeof(m_cfg.m_szOrderRef));
    sprintf(m_cfg.m_szOrderRef, "%d", 1+atoi(req.OrderRef));
    memcpy(&req.UserID, &m_cfg.m_szUserID, sizeof(m_cfg.m_szUserID));
    req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;  /* 经测试，THOST_FTDC_OPT_AnyPrice不被支持 */
    req.Direction = THOST_FTDC_D_Sell;
    req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    req.LimitPrice = api->m_data.m_fUpperLimitPrice;
    req.VolumeTotalOriginal = 1;
    req.TimeCondition = THOST_FTDC_TC_GFD;
    req.VolumeCondition = THOST_FTDC_VC_AV;
    req.MinVolume = 1;
    req.ContingentCondition = THOST_FTDC_CC_Immediately;
    req.StopPrice = 0;
    req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    req.RequestID = m_cfg.m_nRequestID;
    req.IsAutoSuspend = 0;
    req.IsSwapOrder = 0;
    CPrintApi::LogPrint("----涨停价开仓卖出期货合约（%s），报单引用编号（%s）", req.InstrumentID, req.OrderRef);
#endif
    CPrintApi::LogPrint("-----------------------------------------------------------------------------");

    /* 发起请求 */
    m_mgr.UpdateTraderData(&req, E_UPDATE_STAGE_REQ);
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
    CPrintParams::PrintFunctionEx();
    CThostFtdcInputOrderActionField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID));
    memcpy(&req.UserID, &m_cfg.m_szUserID, sizeof(m_cfg.m_szUserID));
    req.RequestID = m_cfg.m_nRequestID;
    strcpy(req.OrderRef, "2"); /* 注意修改 */
    req.FrontID = 1; /* 注意修改 */
    req.SessionID = 1350645504; /* 注意修改 */
    req.ActionFlag = THOST_FTDC_AF_Delete;
    req.LimitPrice = 0;
    req.VolumeChange = 0;
    m_mgr.UpdateTraderData(&req, E_UPDATE_STAGE_REQ);
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
    CPrintParams::PrintFunctionEx();
#if 0
    CThostFtdcInputExecOrderField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID));
    memcpy(&req.ExecOrderRef, &m_cfg.m_szExecOrderRef, sizeof(m_cfg.m_szExecOrderRef));
    sprintf(m_cfg.m_szExecOrderRef, "%d", 1+atoi(req.ExecOrderRef));
    memcpy(&req.UserID, &m_cfg.m_szUserID, sizeof(m_cfg.m_szUserID));
    int result = m_api->ReqExecOrderInsert(&req, m_cfg.m_nRequestID++);
    if (result)
    {
        CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
    }
    else
    {
        CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
    }
#endif
}

/* 执行操作 */
void CTraderApi::ExecOrderAction(void)
{
    CPrintParams::PrintFunctionEx();
#if 0
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
#endif
}

/* 报价录入 */
void CTraderApi::QuoteInsert(void)
{
    CPrintParams::PrintFunctionEx();
#if 0
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
#endif
}

/* 报价操作 */
void CTraderApi::QuoteAction(void)
{
    CPrintParams::PrintFunctionEx();
#if 0
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
#endif
}

/* 询价录入 */
void CTraderApi::ForQuoteInsert(void)
{
    CPrintParams::PrintFunctionEx();
#if 0
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
#endif
}

/* 报单查询 */
void CTraderApi::QryOrder(void)
{
    CPrintParams::PrintFunctionEx();
    CThostFtdcQryOrderField req;
    memset(&req, 0, sizeof(req)); /* 为空则查询今日所有报单 */
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID));
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
    CPrintParams::PrintFunctionEx();
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
    CPrintParams::PrintFunctionEx();
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
    CPrintParams::PrintFunctionEx();
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
    CPrintParams::PrintFunctionEx();
    CThostFtdcQryTradingNoticeField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
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
    CPrintParams::PrintFunctionEx();
    CThostFtdcQryTradeField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID));
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
    CPrintParams::PrintFunctionEx();
    CThostFtdcQryNoticeField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
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
    CPrintParams::PrintFunctionEx();
    CThostFtdcQryExchangeField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.ExchangeID, &m_cfg.m_szExchangeID, sizeof(m_cfg.m_szExchangeID)); /* 不指定则查询所有交易所 */
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
    CPrintParams::PrintFunctionEx();
    CThostFtdcQryTradingCodeField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    memcpy(&req.ExchangeID, &m_cfg.m_szExchangeID, sizeof(m_cfg.m_szExchangeID));
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
    CPrintParams::PrintFunctionEx();
    CThostFtdcQryProductField req;
    memset(&req, 0, sizeof(req));
    int result = m_api->ReqQryProduct(&req, m_cfg.m_nRequestID++); /* 不指定则查询所有产品 */
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
    CPrintParams::PrintFunctionEx();
    CThostFtdcQryInstrumentField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID)); /* 不指定则查询所有合约 */
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
    CPrintParams::PrintFunctionEx();
    CThostFtdcQryDepthMarketDataField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID)); /* 不指定则查询所有合约 */
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
    CPrintParams::PrintFunctionEx();
    CThostFtdcQryInvestorPositionField req;
    memset(&req, 0, sizeof(req));
    memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
    memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
    memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID)); /* 不指定则查询所有合约 */
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
    CPrintParams::PrintFunctionEx();
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
    CPrintParams::PrintFunctionEx();
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
                }
            }
        }
        else
        {
            /* 登录 */
            Login();
            Sleep(5000);
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
    CPrintParams::PrintFunctionEx();

    CMarketApi *api = CMarketApi::GetInstance();
    if (!api)
        return;

    CPrintApi::LogPrint("\n");
    CPrintApi::LogPrint("-----------------------------------------------------------------------------");
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
        CPrintApi::LogPrint("----跌停价开仓买入期货合约（%s），报单引用编号（%s）", req.InstrumentID, req.OrderRef);
    }
    else
    {
        /* 下跌趋势，以涨停价卖出 */
        req.Direction = THOST_FTDC_D_Sell;
        req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
        req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
        req.LimitPrice = api->m_data.m_fUpperLimitPrice;
        CPrintApi::LogPrint("----涨停价开仓卖出期货合约（%s），报单引用编号（%s）", req.InstrumentID, req.OrderRef);
    }
    req.VolumeTotalOriginal = 1;
    req.TimeCondition = THOST_FTDC_TC_GFD;
    req.VolumeCondition = THOST_FTDC_VC_AV;
    req.MinVolume = 1;
    req.ContingentCondition = THOST_FTDC_CC_Immediately; /* 非立即成交的预埋单 */
    req.StopPrice = 0;
    req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    req.RequestID = m_cfg.m_nRequestID;
    req.IsAutoSuspend = 0;
    req.IsSwapOrder = 0;
    CPrintApi::LogPrint("-----------------------------------------------------------------------------");

    /* 发起请求 */
    m_mgr.UpdateTraderData(&req, E_UPDATE_STAGE_REQ);
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
    CPrintParams::PrintFunctionEx();

    /* 遍历队列 */
    while (!m_mgr.m_UnTradeList.empty())
    {
        CTraderData *data = m_mgr.m_UnTradeList.front();

        /* 撤销报单 */
        CPrintApi::LogPrint("\n");
        CPrintApi::LogPrint("-----------------------------------------------------------------------------");
        CThostFtdcInputOrderActionField req;
        memset(&req, 0, sizeof(req));
        memcpy(&req.BrokerID, &m_cfg.m_szBrokerID, sizeof(m_cfg.m_szBrokerID));
        memcpy(&req.InvestorID, &m_cfg.m_szInvestorID, sizeof(m_cfg.m_szInvestorID));
        memcpy(&req.InstrumentID, &m_cfg.m_szInstrumentID, sizeof(m_cfg.m_szInstrumentID));
        memcpy(&req.UserID, &m_cfg.m_szUserID, sizeof(m_cfg.m_szUserID));
        req.RequestID = m_cfg.m_nRequestID;
        memcpy(&req.OrderRef, &data->m_szOrderRef, sizeof(data->m_szOrderRef));
        req.FrontID = data->m_nFrontID;
        req.SessionID = data->m_nSessionID;
        req.ActionFlag = THOST_FTDC_AF_Delete;
        req.LimitPrice = 0;
        req.VolumeChange = 0;
        CPrintApi::LogPrint("----撤销委托期货合约（%s），报单引用编号（%s）", req.InstrumentID, req.OrderRef);
        CPrintApi::LogPrint("----FrontID=%08u，SessionID=%08u", req.FrontID, req.SessionID);
        CPrintApi::LogPrint("-----------------------------------------------------------------------------");

        /* 发起请求 */
        m_mgr.UpdateTraderData(&req, E_UPDATE_STAGE_REQ);
        int result = m_api->ReqOrderAction(&req, m_cfg.m_nRequestID++);
        if (result)
        {
            CPrintApi::DbgPrint("----执行%s失败", __FUNCTION__);
        }
        else
        {
            CPrintApi::DbgPrint("----执行%s成功", __FUNCTION__);
        }

        m_mgr.m_UnTradeList.pop_front();
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
        m_pInstance->m_bHaveCli = FALSE;
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
    char *szFlowDir = "./TraderFlow/";
    CreateDir(szFlowDir);
    m_api = CThostFtdcTraderApi::CreateFtdcTraderApi(szFlowDir);
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
