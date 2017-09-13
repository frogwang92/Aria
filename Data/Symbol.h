#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include "Common.h"

#ifdef DATA_EXPORTS
#define DATA_CLASS DLL_EXPORT_CLASS_DECL  
#define DATA_API DLL_EXPORT_DECL  
#else
#define DATA_CLASS DLL_IMPORT_CLASS_DECL
#define DATA_API DLL_IMPORT_DECL
#endif

#include <iostream>

#define BTC 0x01
#define LTC 0x02

struct DATA_CLASS Symbol {
public:
    explicit Symbol(int code)
            : m_code(code) {
    }

    int get_code() const { return m_code; }

private:
    int m_code;
};

DATA_API bool operator<(const Symbol &lhs, const Symbol &rhs);

using std::ostream;

inline ostream &operator<<(ostream &os, const Symbol &symbol) {
    os << symbol.get_code();
    return os;
}

#endif