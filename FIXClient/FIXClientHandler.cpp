//
// Created by ywang on 6/3/17.
//

#include "FIXClientHandler.h"
using namespace FIX;

FIXClientHandler::FIXClientHandler(const std::string &cfg) {
    _client = std::make_unique<FIXClient>();
    _pSettings = std::make_unique<SessionSettings>(cfg);
    _pFileStoreFactory = std::make_unique<FileStoreFactory>(*_pSettings);
    _pScrLogFactory = std::make_unique<ScreenLogFactory>(*_pSettings);
    _pInitiator = std::make_unique<SocketInitiator>(*_client, *_pFileStoreFactory, *_pSettings);

    _client->register_price_update_call_back(std::bind(&FIXClientHandler::on_data, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void FIXClientHandler::run() {
    _pInitiator->start();
    _client->run();
}

void FIXClientHandler::on_data(time_point time, price_type price, double vol) {
    if(_callback) {
        _callback(time, price, vol);
    }
}

FIXClientHandler::~FIXClientHandler() {
    if(_pInitiator)
        _pInitiator->stop();
}
