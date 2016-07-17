import tushare as ts
import DataFeed
from datetime import *
from DataFeed import *

def run(instance):
   pdf = ts.get_h_data('600000',start='2005-02-01',end='2016-02-01')
   #print pdf
   pdf = pdf.sort_index(ascending = True)
   for index, row in pdf.iterrows():
       instance.push_data(int(float(row['open'])*100),
         int(float(row['high'])*100),
         int(float(row['low'])*100),
         int(float(row['close'])*100), 
         int(float(row['close'])*100), 
         str(index), 
         Resolution.Day, 
         int(row['volume']) )

#print pdf


