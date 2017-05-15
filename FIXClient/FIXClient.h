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

class FIXClient : public FIX::Application,
                  public FIX::MessageCracker {
 public:
  void run();

 private:
  void onCreate(const FIX::SessionID& ) {}
  void onLogon(const FIX::SessionID& sessionID);
  void onLogout(const FIX::SessionID& sessionID);
};

#endif //ARIA_FIXCLIENT_H
