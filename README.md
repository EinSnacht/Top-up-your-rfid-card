I'm a newbie coder studying Cpre in Bachelor degree year 1 so don't blame me if my code look 
newbie but you can suggest me you improve it I'm ready to listen to all opinions that come in.
make sure you install esp32 and MFRC522 library for this code 
and change ssid and pwd off your wifi router
ESP32 -> RC522
            • 3V3 -> 3V3
            • GND -> GND
            • D27 -> RST
            • D5 -> SDA
            • D23 -> MOSI
            • D19 -> MISO
            • D18 -> SCK
ESP32 -> Sensor and Buzzer
            • 3V3 -> VCC
            • GND -> GND
            • D32 -> Coin sensor 1
            • D35 -> Coin sersor 2
            • D34 -> Coin sensor 3
            • D33 -> Buzzer
you can change pin on esp32 depends on you
and make sure that you create a folder in C:\AppServ\www and move all my php file in your folder 

Instruction:
1.download and install appServ
2.log in to 127.0.0.1 with username root and your password that you use to install appServ
3.create your new database  and table in phpmyadmin (remember your database name and table cause you need to use your name in your code) for my code i have picture only for my table name. 
4.edit your code with your database and table name in connect.php
to open display make sure that you use same LAN as your computer and go to http://127.0.0.1/"your folder name on C:\AppServ\www"/display1
you can use my project anywhere don't care about license(Probably no one cares anyway).
