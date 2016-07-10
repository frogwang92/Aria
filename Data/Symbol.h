#pragma once
#ifdef DATA_EXPORTS
#define DATA_API __declspec(dllexport)
#else
#define DATA_API __declspec(dllimport)
#endif

#include <iostream>

struct DATA_API Symbol
{
public:
   explicit Symbol( int code )
      :m_code(code)
   {
   }

   int get_code() const { return m_code; }

private:
   int m_code; 
};

DATA_API bool operator< (const Symbol& lhs, const Symbol& rhs);

using std::ostream;

inline ostream& operator<< (ostream& os, const Symbol& symbol)
{
   os << symbol.get_code();
   return os;
}