import DataFeed
import csv
from datetime import *
from DataFeed import *

def run(instance):
   #print "start reading..."
   reader = csv.DictReader(file('table.csv','rb'))
   for row in reader:
      #print row
      instance.push_data(int(float(row['Open'])*100),
         int(float(row['High'])*100),
         int(float(row['Low'])*100),
         int(float(row['Close'])*100), 
         int(float(row['Adj Close'])*100), 
         row['Date'], 
         Resolution.Day, 
         int(row['Volume']) )