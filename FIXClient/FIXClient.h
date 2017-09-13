//
// Created by yiwang on 17-5-15.
//

#ifndef ARIA_FIXCLIENT_H
#define ARIA_FIXCLIENT_H

#include <quickfix/Application.h>
#include <quickfix/MessageCracker.h>
#include <quickfix/Values.h>
#include <quickfix/Mutex.h>
#include <quickfix/fix44/MarketDataRequest.h>
#include "global.h"
#include "FIXConfig/OKCoin.hpp"

class FIXClient : public FIX::Application,
                  public FIX::MessageCracker {
public:
    FIXClient();
    void run();
    void register_price_update_call_back(std::function<void(time_point time, price_type price, double vol)> price_update) {
        _price_update_call_back = price_update;
    }
private:
    void onCreate(const FIX::SessionID &);

    void onLogon(const FIX::SessionID &sessionID);

    void onLogout(const FIX::SessionID &sessionID);

    void toAdmin(FIX::Message &, const FIX::SessionID &);

    void toApp(FIX::Message &, const FIX::SessionID &)
    throw(FIX::DoNotSend);

    void fromAdmin(const FIX::Message &, const FIX::SessionID &)
    throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon);

    void fromApp(const FIX::Message &message, const FIX::SessionID &sessionID)
    throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType);

    /*
     0	=	 Bid
     1	=	 Offer
     2	=	 Trade
     3	=	 Index Value
     4	=	 Opening Price
     5	=	 Closing Price
     6	=	 Settlement Price
     7	=	 Trading Session High Price
     8	=	 Trading Session Low Price
     9	=	 Trading Session VWAP Price
     A	=	 mbalance -- OKCoin not supported
     B	=	 Trade Volume
     C	=	 Open Interest -- OKCoin not supported
     */
    FIX::Message createOrderBookRequest();

    void onMessage(const FIX44::MarketDataSnapshotFullRefresh& message, const FIX::SessionID &sessionID);
    void onMessage(const FIX44::MarketDataIncrementalRefresh& message, const FIX::SessionID &sessionID);

    std::function<void(time_point, price_type, double)> _price_update_call_back;

    bool _haveSnapShot;
};

#endif //ARIA_FIXCLIENT_H
