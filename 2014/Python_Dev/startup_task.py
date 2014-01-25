import datetime
import os
from time import sleep

#sleep(90)

f = open('startup_log.txt','a')
now = datetime.datetime.now()
print now.strftime("%Y-%m-%d %H:%M:%S")
f.write('I ran on ')
f.write(now.strftime("%Y-%m-%d"))
f.write(' at ')
f.write(now.strftime("%H:%M:%S"))
f.write(' \n')
f.write('Starting T7...\n')
#os.system("python serial_com.py&")
f.write('T7 Started!\n')
f.write('Starting ImageProcessing...\n')
#os.system("python pyth_img_proc.py&")
f.write('WE CAN SEE!\n')


