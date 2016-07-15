import os
import os.path
import shutil
import glob

data_src_file = "Aria/data*.log"
data_dest_file = "amstockchart/data/table.csv"
portfolio_src_file = "Aria/portfolio*.log"
portfolio_dest_file = "amstockchart/data/portfolio.csv"
event_src_file = "Aria/trade*.log"
event_dest_file = "amstockchart/data/event.csv"
dest_bak_dir = "amstockchart/data_bak"

def copy_data(src_file, dest_file, bak_dir = dest_bak_dir):
    
    result = []
    for filename in glob.iglob(src_file):
        result.append(filename)
    if len(result) == 0:
        print "no log file in src folder, skipping..."
        return
    assert(len(result) == 1)
    if os.path.isfile(dest_file):
        os.remove(dest_file)
    print "from: " + str(result)
    print "to: " + dest_file
    print "bakup: " + bak_dir
    shutil.copy(result[0], dest_file)
    shutil.move(result[0], bak_dir)

copy_data(data_src_file, data_dest_file)
copy_data(portfolio_src_file, portfolio_dest_file)
copy_data(event_src_file, event_dest_file)