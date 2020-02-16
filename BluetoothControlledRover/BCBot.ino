/*
   Gamepad module provides three different mode namely Digital, JoyStick and Accerleometer.

   You can reduce the size of library compiled by enabling only those modules that you want to
   use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/game-pad-module/
*/
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>
#include <L298N.h>
#include <Servo.h>



Servo myservo;  
#define ENA 9
#define IN1 8
#define IN2 7

#define ENB A3
#define IN3 A4
#define IN4 A5 // backward



//create a motor1 instance
L298N motor1(ENA, IN1, IN2);
L298N motor2(ENB, IN3, IN4);
int servoPos = 0;

void setup() 
{
  // put your setup code here, to run once:
  myservo.attach(6);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600,3,2);  //(baudrate, RX pin, TX pin)
  

  motor1.setSpeed(255); // an integer between 0 and 255
  motor2.setSpeed(255);
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    motor1.forward();
    motor2.backward();
      delay(200);

  //stop running
  motor1.stop();
  motor2.stop();
  }

  if (GamePad.isDownPressed())
  {

    motor2.forward();
    motor1.backward();
      delay(200);

  //stop running
  motor1.stop();
  motor2.stop();
  }

  if (GamePad.isLeftPressed())
  {
    motor2.backward();
    delay(200);
    motor2.stop(); 
  }

  if (GamePad.isRightPressed())
  {
    motor1.forward();
    delay(200);
    motor1.stop();
  }

  if (GamePad.isSquarePressed())
  {
    motor1.backward();
    motor2.backward();
    delay(200);
    motor1.stop();
    motor2.stop();
  }

  if (GamePad.isCirclePressed())
  {
    motor1.forward();
    motor2.forward();
    delay(200);
    motor1.stop();
    motor2.stop();
  }

  if (GamePad.isCrossPressed())
  {
    servoPos -= 30;
    if(servoPos < 0)
      servoPos = 0;    
    myservo.write(servoPos);   
  }

  if (GamePad.isTrianglePressed())
  {
    servoPos += 30;
    if(servoPos > 180)
      servoPos = 180;
    myservo.write(servoPos);
  }

  if (GamePad.isStartPressed())
  {
    myservo.write(0); 
    delay(500);
    myservo.write(180); 
    delay(500);
    myservo.write(90); 
  }

  if (GamePad.isSelectPressed())
  {
    Serial.print("Select");
  }
  Serial.print('\t');

  int a = GamePad.getAngle();
  Serial.print("Angle: ");
  Serial.print(a);
  Serial.print('\t');
  int b = GamePad.getRadius();
  Serial.print("Radius: ");
  Serial.print(b);
  Serial.print('\t');
  float c = GamePad.getXaxisData();
  Serial.print("x_axis: ");
  Serial.print(c);
  Serial.print('\t');
  float d = GamePad.getYaxisData();
  Serial.print("y_axis: ");
  Serial.println(d);
  Serial.println();
}
