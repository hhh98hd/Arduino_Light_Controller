# Arduino_Light_Controller
By Hoang Huy Hoang, UET-VNU, Vietnam
- Main features:
  + Control of 1 220V-AC electric device (Here is a light bulb)
  + Display current time (hour, minute, day, month, year) and set times (**Vietnamese**)
  + Set time for the RTC in case it runs fast or slow via buttons and LCD
  + Set times for turning the device on / off (6 times) via buttons and LCD
  + Manual control of the device via the touch sensor
  
  
  
- System overview:

![alt text](/image/72751413_1179619482242045_8107323517973823488_n.jpg)

- Components used:
  + Arduino Uno R3
  + 20x4 LCD Screen
  + I2C Converter for 20x4 LCD Screen
  + RTC DS1302
  + Pad of 4 buttons
  + TP223 Touch Sensor
  + 5V Relay
  
  ![alt text](/image/72321272_2384129848571660_1293922433371209728_n.jpg)
  
  - Some images:
    + 2 modes (Set RTC and set on/off times). **Notice the curson is at Chinh dong ho (Set RTC)**
    
    ![alt text](/image/72232460_2282617761864821_3378212397889093632_n.jpg)
    
    + Setting time for the RTC. **Notice the cursor is at hour**
    
    ![alt text](/image/72705294_1021482451516088_3364614376811134976_n.jpg)
    
    + Display list of all times when mode **Hen gio ON/OFF (Set on/off times)** is selected.
      **////////** indicates that the slot is empty
      **Notice the slot with cursor is the currently selected slot**
      
    ![alt text](/image/72294810_2484676048470748_8924680477579673600_n.jpg)
    
    + Setting time for the selected slot. At 0:00 the device will be turned off
      The cursor is at HUY (cancel). Actually it has 2 options: OK and HUY
      
     ![alt text](/image/72477935_718343875307413_3976153870777712640_n.jpg)
