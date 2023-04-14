# Python code transmits a byte to Arduino /Microcontroller

#https://www.instructables.com/Python-Serial-Port-Communication-Between-PC-and-Ar/

import serial
import getch

SerialObj = serial.Serial('COM5') # COMxx  format on Windows
SerialObj.baudrate = 115200 # set Baud rate to 9600
SerialObj.bytesize = 8      # Number of data bits = 8
SerialObj.parity   ='N'      # No parity
SerialObj.stopbits = 1   # Number of Stop bits = 1

while True:
  ch = getch.getch()
  SerialObj.write(ch) 

SerialObj.close()      # Close the port

### end ###
