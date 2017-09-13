#ifndef _TRADE_JOB_NODE_H_
#define _TRADE_JOB_NODE_H_

#include "../Data/Symbol.h"
#include <iostream>
#include <boost/date_time.hpp>

class TradeJobNode {
public:
    enum JobType {
        Buy, Sell, BuyResult, SellResult
    };

public:
    TradeJobNode(const boost::posix_time::ptime &trade_time, JobType type, Symbol symbol, double shares, double price,
                 double cash);

    ~TradeJobNode(void);

public:
    JobType get_type() const { return m_type; }

    Symbol get_symbol() const { return m_symbol; }

    double get_shares() const { return m_shares; }

    double get_price() const { return m_price; }

    double get_cash() const { return m_cash; }

    const boost::posix_time::ptime &get_trade_time() const { return m_trade_time; }

private:
    JobType m_type;
    Symbol m_symbol;
    double m_shares;
    double m_price;
    double m_cash;
    boost::posix_time::ptime m_trade_time;
};

using std::ostream;

inline ostream &operator<<(ostream &os, const TradeJobNode &tradenode) {
    return os << tradenode.get_type() << ","
              << tradenode.get_symbol() << ","
              << tradenode.get_shares() << ","
              << tradenode.get_price() << ","
              << tradenode.get_cash();
}

#endif