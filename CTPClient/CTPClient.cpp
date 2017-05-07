//
// Created by yiwang on 17-5-2.
//

#include "CTPClient.h"
#include "ThostFtdcMdApi.h"
#include <iostream>
#include <cstring>

using namespace std;

CTPClient::CTPClient() : requestId(0) {

}

CTPClient::CTPClient(const CTPClient &rhs) {

}

CTPClient::~CTPClient() {

}

void CTPClient::OnFrontConnected() {
    CThostFtdcMdSpi::OnFrontConnected();
    cout << __LINE__ << "OnFrontConnected";

    CThostFtdcReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, "9999");
    strcpy(req.UserID, "090938");
    strcpy(req.Password, "nana1017");
    int ret = m_pUserApi->ReqUserLogin(&req, ++requestId);
}

void CTPClient::OnFrontDisconnected(int nReason) {
    CThostFtdcMdSpi::OnFrontDisconnected(nReason);
    cout << __LINE__ << "OnFrontDisconnected, reason: " << nReason;
}

void CTPClient::initialize() {


}

void
CTPClient::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                          bool bIsLast) {
    CThostFtdcMdSpi::OnRspUserLogin(pRspUserLogin, pRspInfo, nRequestID, bIsLast);

    if(pRspInfo->ErrorID == 0) {

        char* ppInstrument[] = {"rb1705"};
        m_pUserApi->SubscribeMarketData(ppInstrument, 1);
    } // no error

}

void
CTPClient::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo,
                              int nRequestID, bool bIsLast) {
    CThostFtdcMdSpi::OnRspSubMarketData(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
}

void CTPClient::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
    CThostFtdcMdSpi::OnRtnDepthMarketData(pDepthMarketData);
}
