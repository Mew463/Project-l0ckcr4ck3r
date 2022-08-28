#include <AccelStepper.h>
#include "AS5600.h"
// #include <SPI.h>
#include "Wire.h"
#include "Servo.h"
#include "FastLED.h"
#include <U8x8lib.h>
#include "Button2.h"; //  https://github.com/LennartHennigs/Button2
#include "ESPRotary.h";

U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);

#define offset 788 // Offset value gotten from readAngle()
#define stepsperRev 1600

#define servoNeutral 1900 // Point when shcakle is fully pushed INTO THE LOCK
#define servoOpen 1500
#define servoFeedbackOpen 346

bool checkTwice = false;
bool cracked = false;

enum DIR{CC, CW, CLOSE};

AccelStepper stepper(1,3,4); // STEP, DIR 
int enablePin = 2;
AS5600 as5600;  //  use default Wire

double gateBounds[2];

Servo servo;
const int servofeedback = A0;

unsigned long lockTime;

// Related to each lock!! for testing!!
int gateHeight = 1798;
int firstNum = 0;
int firstNumRem;
int thirdNum[] = {-1, -1, -1, -1}; 
int secondNums[4][8];
//

void dial(float num, DIR _dir = CLOSE, int extraRot = 0);
float readLockNum(int num = -1);
void crackLock();

void setup()
{  
  Serial.begin(9600);

  u8x8.begin();

  stepper.setMaxSpeed(10000);
  stepper.setAcceleration(100000);

  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW); //Enable motor driver

  servo.attach(5);
  servo.writeMicroseconds(servoNeutral);
  pinMode(servofeedback, INPUT);

  Wire.begin();
  as5600.begin(4);  //  set direction pin.
  as5600.setDirection(AS5600_COUNTERCLOCK_WISE);  // default, just be explicit.

  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,0,"Project");
  u8x8.drawString(0,1,"l0ckcr4ck3r");
  u8x8.drawString(0,4,"By Mu");
  delay(1000);
  u8x8.clearDisplay();

  crackLock();

  dial(0);
  delay(5000);
  servo.writeMicroseconds(servoNeutral);
  
}

void loop()
{  

}








