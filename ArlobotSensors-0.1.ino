/* ArloBot arduino PING))) sensor array
 * 
 *  Code to read an array of sensors and return serial data to main Arlobot board
 *  running Chrisl8's arlobot ROS code
 *  https://github.com/chrisl8/ArloBot
 *  
 *  Created 4 October 2015
 *  by Chronoglass
 *  Based on:
 *  http://www.arduino.cc/en/Tutorial/Ping
 *
 *  created 3 Nov 2008
 *  by David A. Mellis
 *  modified 30 Aug 2011
 *  by Tom Igoe

 * This example code is in the public domain.

 */

//first numbered pin a ping data line is plugged into
//these need to be consecutive
//pins 0 and 1 should be reserved for serial communication, do not use for sensors
const int startPingPin = 2;
//number of ping sensors
const int numPing = 1;
//starting IR sensor pin (these will be labeled analog IN on the arduino, default SHOULD be A0) 
const int numIr = 1;

char request;

void setup() {
  // initialize serial communication:
  Serial.begin(115200);
  // reserve a byte for the input:
  //inputString.reserve(1);
}

void loop() {
  if(Serial.available() > 0){
    //request = "";
    request = (char)Serial.read();
  }
  if(request == 'i'){
    pollSensors(); // poll the sensors for data and print to serial
  }
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void pollSensors(){
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, pcm, ircm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  // init each of the pings in order
  
  for(int i=0; i < numPing; i++){
    int pingPin = startPingPin + i;
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
  
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  // this will cycle through each of them and print the output to serial
  
    pinMode(pingPin, INPUT);
    duration = pulseIn(pingPin, HIGH);

    // convert the time into a distance
    pcm = microsecondsToCentimeters(duration);

    Serial.print("p,");
    Serial.print(i);
    Serial.print(",");
    Serial.print(pcm);
    Serial.println(".");
    //if there is a matching IR sensor return it's reading as well
    if(i < numIr ){
        Serial.print("i,");
        Serial.print(i);
        Serial.print(",");
        Serial.print(irSenseCm(i));
        Serial.println(".");
      }
    delay(100);
    
  }
}

//function to return ir sensor data in cm
float reading = 0;
float readVolts;
float distanceCm;

float irSenseCm(int readPort){
  reading = analogRead(retAnalogPort(readPort));  // Read the sensor
  readVolts = reading * 5.0 / 4096.0;
  distanceCm = 27.86 * pow(readVolts, -1.15);
  return distanceCm;
}

//there has to be a better way to cycle over all of the analog ports
//this is currently only tested with the uno which has 5 analog ports
//if you have more, add more case statements

int retAnalogPort(int input){
  switch(input){
    case 0:
      return A0;
    case 1:
      return A1;
    case 2:
      return A2;
    case 3:
      return A3;
    case 4:
      return A4;
    case 5:
      return A5;
    default:
    break;
  }
}

