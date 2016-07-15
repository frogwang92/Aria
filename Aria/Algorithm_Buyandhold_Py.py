import DataFeed
import Algorithm
from datetime import *
from DataFeed import *
from Algorithm import *

sym = DataFeed.Symbol(600000)
b_bought = False

def on_data(instance, data_slice):
   global b_bought
   if not b_bought :
      #print data_slice.get_start_time()
      instance.buy(str(data_slice.get_start_time()), sym, data_slice.get_data(sym).adj_close(), 1.0)
      b_bought = True
