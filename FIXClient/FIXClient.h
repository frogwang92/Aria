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

#include "FIXConfig/OKCoin.hpp"

class FIXClient : public FIX::Application,
                  public FIX::MessageCracker {
public:
    void run();

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

    FIX::Message createOrderBookRequest();

    void onMessage(const FIX44::MarketDataSnapshotFullRefresh& message, const FIX::SessionID &sessionID);
    void onMessage(const FIX44::MarketDataIncrementalRefresh& message, const FIX::SessionID &sessionID);

};

#endif //ARIA_FIXCLIENT_H
