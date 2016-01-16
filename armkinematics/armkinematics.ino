#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

/*Adafruit_PWMServoDriver pwm6 = Adafruit_PWMServoDriver();
Adafruit_PWMServoDriver pwm5 = Adafruit_PWMServoDriver();
Adafruit_PWMServoDriver pwm4 = Adafruit_PWMServoDriver();
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver();
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver();*/
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

float L1 = 14.5;
float L2 = 18.75;
float L3 = 7.3;

//int servos[] = {} 
int s1 = 100; //initial angles
int s2 = 105;
int s3 = 135;
int s4 = 130;
int s5 = 90;
int s6 = 105;

float L4;
float t1; //thetas
float t2a;
float t2b;
float t3;
float r;
float z;

int sNum = 6;


int emg1 = 0; //analog pins
int emg2 = 1;
int emg3 = 2;

int tstate = 0; //toggle state

uint8_t servo1 = 1;
uint8_t servo2 = 2;
uint8_t servo3 = 3;
uint8_t servo4 = 4;
uint8_t servo5 = 5;
uint8_t servo6 = 6;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  #ifdef ESP8266
  Wire.pins(2, 14);   // ESP8266 can use any two pins, such as SDA to #2 and SCL to #14
  #endif

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  
  t1 = s6; //initial values
  t3 = (60)*PI/180.0;
  L4 = sqrt(L1*L1 + L2*L2 -2*L1*L2*cos(t3));
  t2a = acos((L2*L2+L1*L1-L4*L4)/(2*L1*L4));
  t2b = (s5-7)*PI/180.0 - t2a;
  z = L4*sin(t2b);
  r = L4*cos(t2b);
  Serial.println(t2a*180/PI);// + ", " + t2a + ", " + t2b + ", " + t3 + ", " + L4 + ", " + z + ", " + r);
  Serial.println(t2b*180/PI);
  Serial.println(t3*180/PI);
  Serial.println(L4);
  Serial.println(z);
  Serial.println(r);
  
  s1 = map(s1,0,254,S1MIN,S1MAX); //inverted
  s2 = map(s2,0,180,S2MIN,S2MAX);
  s3 = map(s3,0,135,S3MIN,S3MAX);
  s4 = map(s4,0,175,S4MIN,S4MAX);//fold down = greater
  s5 = map(s5,0,190,S5MIN,S5MAX);
  s6 = map(s6,0,210,S6MIN,S6MAX);
  
  pwm.setPWM(servo1, 0, s1);
  pwm.setPWM(servo2, 0, s2);
  pwm.setPWM(servo3, 0, s3);
  pwm.setPWM(servo4, 0, s4);
  pwm.setPWM(servo5, 0, s5);
  pwm.setPWM(servo6, 0, s6);
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

void toggle(int tog){
   tog++;
   if (tog > 2){
     tog = 0;
   }
}


void extend(int tog){
  switch (tog) {
  case 0: //z
    break;
  case 1: //r
    break;
  case 2: //theta
    break;
  default:
    Serial.println("error in extend function");
    break;
  }
}

void emgUpdate (){
  //code
}

void cUpdate (){
  
}

void loop() {
  
}
