//Alex Philpott Hovercraft Code V. 0.7

#include <Servo.h>

//receiver channels
const int ch1Pin = 9;
int ch1Value = 1480;
int ch1old = 1480;
const int ch2Pin = 10;
int ch2Value;
const int ch3Pin = 11;
int ch3Value;
const int ch4Pin = 12;
int ch4Value = 1480;
int ch4old = 1480;

//motor values
const int mainEngPin = 6;
int mainEngValue = 0;
const int forwEngPin = 5;
int forwEngValue = 0;
const int forwEngDirPin = 7;

//servo values
const int rudderServoPin = 4;
int rudderServoValue = 90; //set midpoint (0-180)
int rudderLower = 35; //lower angle bound
int rudderUpper = 170; //upper angle bound
Servo rudderServo;
const int payloadServoPin = 3;
int payloadServoValue = 90; //set midpoint
Servo payloadServo;

//averaging values for servos
int val1, val2, val3, val4, val5, val6;

const int ledpin = 8;

long int oldTime;
long int currentTime;
int light=0;

/*//switch values
const int buttonPin = 2;
int buttonValue = 1;*/

void setup() {

  //setting up receiver inputs
  pinMode(13, OUTPUT);
  pinMode(ch1Pin, INPUT); //right joystick left and right
  pinMode(ch2Pin, INPUT); //right joystick up and down
  pinMode(ch3Pin, INPUT); //left joystick up and down
  pinMode(ch4Pin, INPUT); //left joystick left and right

  //motor outputs
  pinMode(mainEngPin, OUTPUT);
  pinMode(forwEngPin, OUTPUT);
  pinMode(forwEngDirPin, OUTPUT);

  //servo outputs
  pinMode(rudderServoPin, OUTPUT);
  pinMode(payloadServoPin, OUTPUT);

  payloadServo.attach(payloadServoPin);
  payloadServo.write(payloadServoValue);
  
  rudderServo.attach(rudderServoPin);
  rudderServo.write(rudderServoValue);

  pinMode(ledpin, OUTPUT);
  
  //Serial.begin(9600);

  val1 = 1480;
  val2 = 1480;
  val3 = 1480;
  val4 = 1480;

  oldTime = millis();

}

void loop() {
  currentTime = millis();
  if (currentTime - oldTime > 500) {
    //Serial.print("triggered");
    if (light == 1) {
      digitalWrite(ledpin, LOW);
      light = 0;
      //Serial.print(" light off");
    }
    else if (light == 0){
      digitalWrite(ledpin, HIGH);
      light = 1;
      //Serial.print(" light on");
    }
    oldTime = currentTime; 
  }
  /*Serial.print(" light = ");
  Serial.print(light);
  Serial.print(" time = ");
  Serial.print(currentTime-oldTime);
  Serial.print('\n');*/
  //reading values from switch
  //buttonValue = digitalRead(buttonPin);

  if (1) {
    ch4old = payloadServoValue;
    ch1old = rudderServoValue;
    //reading in values from receiver
    ch2Value = pulseIn(ch2Pin, HIGH);
    ch3Value = pulseIn(ch3Pin, HIGH);
    /*val1 = pulseIn(ch1Pin, HIGH);
    val2 = pulseIn(ch1Pin, HIGH);
    val3 = pulseIn(ch4Pin, HIGH);
    val4 = pulseIn(ch4Pin, HIGH);*/

    //setting engine values
    mainEngValue = map(ch3Value, 1070, 1850, 0, 255);
    

    if (ch2Value < 1480) {
      digitalWrite(forwEngDirPin, LOW);
      forwEngValue = map(ch2Value, 1070, 1480, -255, 0);
      forwEngValue = -forwEngValue;
    }
    else {
      digitalWrite(forwEngDirPin, HIGH);
      forwEngValue = map(ch2Value, 1480, 1850, 0, 255);
    }

    if (mainEngValue > 255) mainEngValue = 255;
    if (mainEngValue < 15) mainEngValue = 0;
    if (forwEngValue > 255) forwEngValue = 255;
    if (forwEngValue < 20) forwEngValue = 0;

    //setting servo values
    val5 = pulseIn(ch1Pin, HIGH);
    ch1Value = (val1 + val2 + val5)/3;

    val6 = pulseIn(ch4Pin, HIGH);
    ch4Value = (val3 + val4 + val6)/3;

    val1 = val2;
    val2 = val5;
    val3 = val4;
    val4 = val6;

    rudderServoValue = map(ch1Value, 1070, 1880, rudderLower, rudderUpper);
    payloadServoValue = map(ch4Value, 1070, 1880, 0, 180);

    if (rudderServoValue < 15) rudderServoValue = 0;
    if (rudderServoValue > 180) rudderServoValue = 180;
    if (payloadServoValue < 15) payloadServoValue = 5;
    if (payloadServoValue > 75 && payloadServoValue < 105) payloadServoValue = 90;
    if (rudderServoValue > 70 && rudderServoValue < 110) rudderServoValue = 100;
    if (payloadServoValue > 180) payloadServoValue = 175;

    //writing values
    analogWrite(mainEngPin, mainEngValue);
    analogWrite(forwEngPin, forwEngValue);
    payloadServo.write(payloadServoValue);
    //if (payloadServoValue == ch4old) Serial.print("did not write");
    rudderServo.write(rudderServoValue);
    
    /*if (abs(ch4Value-ch4old) > 25) {
      payloadServo.write(payloadServoValue);
      Serial.print("wrote to servo");
    }

    if (abs(ch1Value - ch1old) > 25) {
    rudderServo.write(rudderServoValue);
    Serial.print("wrote to rudder");
    }*/

    //if (ch2Value < 1480) rudderServo.write(90);
    
  
  /*else {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
  }*/
  
  /*Serial.print("rudder servo =");
  Serial.print(rudderServoValue);
  Serial.print(" forward engine = ");
  Serial.print(forwEngValue);
  Serial.print(" lift engine = ");
  Serial.print(mainEngValue);
  Serial.print(" payload servo = ");
  Serial.print(payloadServoValue);
  Serial.print('\n');*/
  //Serial.print(" engine value = ");
  //Serial.print(forwEngValue);
  //Serial.print('\n');
  

  }
}
