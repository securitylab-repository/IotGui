
Pour installer QT:

- libqt5x11extras5 
- xcb
g++ multiple.c -o multiple -lmosquitto

apt-get install :

libmosquittopp-dev - MQTT version 3.1 client C++ library, development files



serveur mosquitto

apt-get install :

mosquitto - MQTT version 3.1/3.1.1 compatible message broker
mosquitto-clients - Mosquitto command line MQTT clients


mosquitto_pub -h 127.0.0.1 -t my/topic -m "{ \"Temp\":44.0 , \"Hum\": 30.0}" 
mosquitto_pub -h 127.0.0.1 -t iot/8/gps -m "{ \"la\":48.811208 , \"lo\": 2.613182}"
https://mosquitto.org/man/libmosquitto-3.html
