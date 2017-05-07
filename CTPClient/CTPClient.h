//
// Created by yiwang on 17-5-2.
//

#ifndef CTP_CTPCLIENT_H
#define CTP_CTPCLIENT_H

#include "ThostFtdcMdApi.h"

class CTPClient : public CThostFtdcMdSpi {

public:
    CTPClient();

    CTPClient(const CTPClient& rhs);

    ~CTPClient();

    void initialize();

    virtual void OnFrontConnected();

    virtual void OnFrontDisconnected(int nReason);

    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

public:
    void register_api(CThostFtdcMdApi* api){
        m_pUserApi = api;
    }

private:
    CThostFtdcMdApi* m_pUserApi;
    int requestId;
};


#endif //CTP_CTPCLIENT_H
