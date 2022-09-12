#include <Servo.h>

int defaultpos = 1500;
String comdata;
int integerdata = defaultpos;

Servo myservo1; // declare servo
 
void setup ()
{
  Serial.begin(9600);
  myservo1.attach(5);

  myservo1.write(defaultpos);
}

void loop ()
{
  SerialChecker();
  myservo1.write(integerdata);
  Serial.println(analogRead(A0));
  delay(50);

}

void SerialChecker()
{
  //read string from serial monitor
  if (Serial.available() > 0) // if we get a valid byte, read analog ins:
  {
    comdata = ""; //reset the old values
    while (Serial.available() > 0)
    {
      comdata += char(Serial.read()); //Add the character value to comdata
      delay(2);//so that whole message is sent before the arduino reads it
      integerdata = comdata.toInt(); //converts our character data into a number
    }
    Serial.println(comdata);//prints out what you are typing
  }
}
