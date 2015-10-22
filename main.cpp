#include "TraderApi.h"
#include "MarketApi.h"
#include "AssistApi.h"

int main(int argc, char *argv[])
{
#if 1
    /* 交易接口测试 */
    CTraderApi *trader_api = CTraderApi::GetInstance();
    if (!trader_api)
    {
        trader_api = CTraderApi::CreateInstance();
    }
    trader_api->Start();
#endif
#if 1
    /* 行情接口测试 */
    CMarketApi *market_api = CMarketApi::GetInstance();
    if (!market_api)
    {
        market_api = CMarketApi::CreateInstance();
    }
    market_api->Start();
#endif
#if 1
    /* 主线程等待 */
    while (1)
    {
        Sleep(300000);
    }
#endif
    return 0;
}