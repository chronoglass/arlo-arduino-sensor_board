/* ArloBot arduino sensor array
 *  Version 0.3
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
const int numPing = 4;
//starting IR sensor pin (these will be labeled analog IN on the arduino, default SHOULD be A0) 
const int numIr = 0;

/*debug vars
 * enable debug info to serial
 * this will mess up ROS, so do not use in "production"
 * 0 = normal, 1 = debug mode
 */
int debug = 0;
long start, finish;
char request;

String retValFormat1 = "p,";
String retValFormat2 = ",";
String retValFormat3 = ".";
String retVal;

void setup() {
  // initialize serial communication:
  Serial.begin(57600);
  //retVal = retValFormat1;
}

void loop() {
  if(Serial.available() > 0){
    //request = '';
    request = (char)Serial.read();
  }
  if(request == 'i'){
    pollSensors(); // poll the sensors for data and print to serial
    request = 's';
  }
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
    // debug timing code
    if(debug == 1)
      start = micros();
    int pingPin = startPingPin + i;
    //pinInit(pingPin);
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    //PORTD &= ~_BV('PD'+pingPin);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    //PORTD |= _BV('PD'+pingPin);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
    //PORTD &= ~_BV('PD'+pingPin);
    if(debug == 1){
      finish = micros();
      long time1 = finish - start;
      Serial.println(time1);
    }
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  // this will cycle through each of them and print the output to serial

    pinMode(pingPin, INPUT);
    duration = pulseIn(pingPin, HIGH);

    // convert the time into a distance
    pcm = microsecondsToCentimeters(duration);
    if(debug == 1)
      start = micros();
    retVal = retValFormat1+i+retValFormat2+pcm+retValFormat3;
    Serial.print(retVal);
    if(debug == 1){
      finish = micros();
      Serial.println(" ");
      long time1 = finish - start;
      Serial.println(time1);
    }
    //if there is a matching IR sensor return it's reading as well
    if(i < numIr ){
        retVal = retValFormat1+i+retValFormat2+irSenseCm(i)+retValFormat3;
        Serial.print(retVal);
      }
  }
}

//function to return ir sensor data in cm
float reading = 0;
float readVolts;
float distanceCm;

float irSenseCm(int readPort){
  reading = analogRead('A'+readPort);  // Read the sensor
  readVolts = reading * 5.0 / 4096.0;
  distanceCm = 27.86 * pow(readVolts, -1.15);
  return distanceCm;
}

