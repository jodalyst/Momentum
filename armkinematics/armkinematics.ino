#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


#define S1MIN  110 //claw
#define S1MAX  400

#define S2MIN  120
#define S2MAX  740

#define S3MIN  300
#define S3MAX  630

#define S4MIN  150
#define S4MAX  510

#define S5MIN  140
#define S5MAX  580

#define S6MIN  130
#define S6MAX  600 //base

uint8_t servonum = 5;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  #ifdef ESP8266
  Wire.pins(2, 14);   // ESP8266 can use any two pins, such as SDA to #2 and SCL to #14
  #endif

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

}

void servoMinMax(int servonum,int smin,int smax){
  Serial.println(servonum);
  for (uint16_t pulselen = smin; pulselen < smax; pulselen++) {
    pwm.setPWM(servonum, 0, pulselen);
  }

  delay(2000);
  for (uint16_t pulselen = smax; pulselen > smin; pulselen--) {
    pwm.setPWM(servonum, 0, pulselen);
  }

  delay(2000);
}

void loop() {
  servoMinMax(1,S1MIN,S1MAX);
  
}
