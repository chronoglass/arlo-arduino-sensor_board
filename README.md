# arlo-arduino-sensor_board

Arduino sketch trying to replicate 
2nd board code from:

https://github.com/chrisl8/ArloBot/tree/master/Propeller%20C%20Code%20for%20ArloBot

Serial connections: (changed to use softwareserial library)
(if you havn't changed the transmission settings from per_robot file in .arlobot)
arduino 11 (rx) -> Parallax activity board P6
arduino 12 (tx) -> parallax activity board P5
arduino Gnd -> parallax activity board Gnd

I have a 105 capaciter on gnd and a 1k resistor on the tx line as well
