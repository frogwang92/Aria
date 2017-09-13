//
// Created by yiwang on 17-5-15.
//

#include <iostream>
#include "FIXClient.h"

#include "quickfix/Session.h"
#include "quickfix/fix44/MarketDataSnapshotFullRefresh.h"
#include "quickfix/fix44/MarketDataIncrementalRefresh.h"

using namespace std;

FIXClient::FIXClient()
        : _haveSnapShot(false) {
}

void FIXClient::run() {

}

void FIXClient::onCreate(const FIX::SessionID &sessionID) {
    cout << "Application created - session: " << sessionID.toString() << endl;
}

void FIXClient::onLogon(const FIX::SessionID &sessionID) {
    cout << "Successful Logon to session." << endl;

    // orderbook data request
    FIX::Message message = createOrderBookRequest();
    FIX::Session::sendToTarget(message, sessionID);
}

void FIXClient::onLogout(const FIX::SessionID &sessionID) {
    cout << "Client logout or falied to login." << endl;
}

void FIXClient::toAdmin(FIX::Message &message, const FIX::SessionID &sessionID) {
    message.setField(FIX::Username(OKCoin::fix_usr));
    message.setField(FIX::Password(OKCoin::fix_pwd));
    cout << "Sent the Admin following message: " << message.toString() << endl;
}

void FIXClient::toApp(FIX::Message &message, const FIX::SessionID &sessionID)
throw(FIX::DoNotSend) {
    cout << "Sent the following message:" << message.toString() << endl;
}

void FIXClient::fromApp(const FIX::Message &message, const FIX::SessionID &sessionID)
throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType) {
    crack(message, sessionID);
    std::cout << std::endl << "IN: " << message << std::endl;
}

void FIXClient::fromAdmin(const FIX::Message &message, const FIX::SessionID &sessionID)
throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon) {
    crack(message, sessionID);
    cout << "Received the Admin following message:" << message.toString() << endl;
}

FIX::Message FIXClient::createOrderBookRequest() {
    FIX44::MarketDataRequest request;
    FIX44::MarketDataRequest::NoRelatedSym sym;
    sym.setField(FIX::Symbol("LTC/CNY"));
    request.addGroup(sym);
    request.setField(FIX::MDReqID("123"));
    // 1 = Snapshot + Subscribe
    // 2 Unsubscribe
    request.setField(FIX::SubscriptionRequestType('1'));
    request.setField(FIX::MDUpdateType(1));   // 0 = full refresh, 1: incremental refresh
    request.setField(FIX::MarketDepth(0));    // 0 = full book,

    FIX44::MarketDataRequest::NoMDEntryTypes group1;
    group1.setField(FIX::MDEntryType('2')); // Trade
    request.addGroup(group1);

//    FIX44::MarketDataRequest::NoMDEntryTypes group2;
//    group2.setField(FIX::MDEntryType('1'));  // asks
//    request.addGroup(group2);

    return request;
}

void FIXClient::onMessage(const FIX44::MarketDataSnapshotFullRefresh &message, const FIX::SessionID &sessionID) {
    FIX::NoMDEntries noofentries;
    FIX::MDEntryPx mdentrypx;
    FIX::Side side;
    FIX44::MarketDataSnapshotFullRefresh::NoMDEntries group;
    message.get(noofentries);
    if(!_haveSnapShot){
        _haveSnapShot = true;
        return;
    }
    for (int i = 0; i < noofentries.getValue(); ++i) {
        message.getGroup(i + 1, group);
        group.get(mdentrypx);
        group.getField(side);
        std::cout << "mdentrypx: " << mdentrypx << ",Side" << side << std::endl;
        _price_update_call_back(boost::posix_time::second_clock::local_time(), mdentrypx, 0);
    }
}

void FIXClient::onMessage(const FIX44::MarketDataIncrementalRefresh &message, const FIX::SessionID &sessionID) {
    //FIX44::MessageCracker::onMessage(message, sessionID);

}
