//
// Created by ywang on 6/3/17.
//

#ifndef ARIA_FIXCLIENTHANDLER_H
#define ARIA_FIXCLIENTHANDLER_H

#include "global.h"
#include "FIXClient.h"
#include "quickfix/FileStore.h"
#include "quickfix/SocketInitiator.h"
#include "quickfix/SessionSettings.h"
#include "quickfix/Log.h"
#include <string>
#include <functional>

class FIXClientHandler {
public:
    FIXClientHandler(const std::string& cfg);
    FIXClientHandler(const FIXClientHandler& rhs) = delete;
    FIXClientHandler& operator=(const FIXClientHandler& rhs) = delete;

    ~FIXClientHandler();

public:
    void run();

public:
    void register_callback(std::function<void(time_point, price_type, double)> callback) {
        _callback = callback;
    }

private:
    unique_ptr<FIXClient> _client;
    unique_ptr<FIX::SessionSettings> _pSettings;
    unique_ptr<FIX::FileStoreFactory> _pFileStoreFactory;
    unique_ptr<FIX::ScreenLogFactory> _pScrLogFactory;
    unique_ptr<FIX::SocketInitiator> _pInitiator;

private:
    std::function<void(time_point, price_type, double)> _callback;

    void on_data(time_point, price_type, double);
};


#endif //ARIA_FIXCLIENTHANDLER_H
