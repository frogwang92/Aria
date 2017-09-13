#include "Symbol.h"

bool operator< (const Symbol& lhs, const Symbol& rhs) 
{
   return lhs.get_code() < rhs.get_code(); 
}