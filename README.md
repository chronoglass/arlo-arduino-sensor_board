# arlo-arduino-sensor_board

Arduino sketch trying to replicate 
2nd board code from:

https://github.com/chrisl8/ArloBot/tree/master/Propeller%20C%20Code%20for%20ArloBot

Serial communication apears to be working after adding the softwareserial library

Serial connections: (changed to use softwareserial library)
(if you havn't changed the transmission settings from per_robot file in .arlobot)
arduino 11 (rx) -> Parallax activity board P6
arduino 12 (tx) -> parallax activity board P5
arduino Gnd -> parallax activity board Gnd

it's possible that the duino can't keep up with the parallax' requests.
though i am not looking for rate limit (yet)
