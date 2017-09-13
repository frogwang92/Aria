//
// Created by ywang on 6/3/17.
//

#ifndef ARIA_REALTIMEENGINE_H
#define ARIA_REALTIMEENGINE_H

#include "../Data/RealTimeDataFeed.h"

class RealTimeEngine {
public:
    RealTimeEngine();

public:
    void run();

private:
    void init();

private:
    unique_ptr<RealTimeDataFeed> _pDataFeed;
    unsigned long _duration;
};


#endif //ARIA_REALTIMEENGINE_H
