import DataFeed
from Algorithm import *
from DataFeed import *
from datetime import *

sym = DataFeed.Symbol(600000)
b_bought = False

def on_data(instance, data_slice):
   global b_bought
   if not b_bought :
      #print data_slice.get_start_time()
      instance.buy(str(data_slice.get_start_time()), sym, data_slice.get_data(sym).close(), 1.0)
      b_bought = True
