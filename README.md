# arlo-arduino-sensor_board

Arduino sketch trying to replicate 
2nd board code from:

https://github.com/chrisl8/ArloBot/tree/master/Propeller%20C%20Code%20for%20ArloBot

Serial communication apears to be working

Serial connections:
(if you havn't changed the transmission settings from per_robot file in .arlobot)
arduino 0 (rx) -> Parallax activity board P6
arduino 1 (tx) -> parallax activity board P5
arduino Dng -> parallax activity board Gnd

if you have more than 3 sensors, you should use the 5 volt line off of the robot for power.
Otherwise you may experience overheating on the arduino.
