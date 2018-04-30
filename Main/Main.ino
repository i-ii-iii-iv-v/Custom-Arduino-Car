#define E1 10 //Enabler
#define I1 8 // Control pin 1 
#define I2 9 // Control pin 2 

#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial btSerial(4,6); // read & write
Servo servo;

byte LEDpin = 7; //debugging purpose
byte servoPin = 3;

// put your setup code here, to run once:
void setup() 
{
  servoPos = 180/2; // cener the servo position

  //blueTooth connection 9600 bard 
  //default password: 1234
  Serial.begin(9600); 
  Serial.println("SetupComplete");
  btSerial.begin(9600);

  servo.attach(servoPin);
  servo.write(servoPos);

  pinMode(E1, OUTPUT);
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);  
  pinMode(LEDpin, OUTPUT);

}

// put your main code here, to run repeatedly:
void loop()
{

  //template
  if(btSerial.available()> 0)
  {
    char data = (char)btSerial.read();
    switch(data)
    {
     case '1': // turn right
     Serial.println("ON");
     servoPos+=5;
     servo.write(servoPos);
     digitalWrite(LEDpin, HIGH);
     break;

     case '2': //turn left
     Serial.println("OFF");
     servoPos-=5;
     servo.write(servoPos);
     break;

     case '3': //forward
        digitalWrite(E1, HIGH);
        digitalWrite(I1, HIGH);
        digitalWrite(I2, LOW);
        break;
        
     case '4': //backward
        digitalWrite(E1, HIGH);
        digitalWrite(I1, LOW);
        digitalWrite(I2, HIGH);
        break;

     case '5': //stop
        digitalWrite(E1, LOW);
        break;
        
     default:
     break;
    }
  }


}
