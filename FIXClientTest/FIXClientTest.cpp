#include "global.h"
#include "../FIXClient/FIXClient.h"
#include "quickfix/FileStore.h"
#include "quickfix/SocketInitiator.h"
#include "quickfix/SessionSettings.h"
#include "quickfix/Log.h"
#include <string>
#include <iostream>
#include <fstream>

int main(){

    std::string file = "OKCoinFIX.cfg";

    try
    {
        FIX::SessionSettings settings( file );

        FIXClient client;
        FIX::FileStoreFactory storeFactory( settings );
        FIX::ScreenLogFactory logFactory( settings );
        FIX::SocketInitiator initiator( client, storeFactory, settings);

        initiator.start();
        client.run();
        sleep(300);
        initiator.stop();

        return 0;
    }
    catch ( std::exception & e )
    {
        std::cout << e.what();
        return 1;
    }

    return 0;
}