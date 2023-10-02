#include <RN.h>
RN sf(16, 17); // front sensor with trig 16 and echo 17
RN sl(14, 15); // left sensor with trig 14 and echo 15
RN sr(18, 19); // right sensor with trig 18 and echo 19
RN motor(8, 9, 10); // connect dcmotor pins
RN servo(2); // connect servo
int x=20;
void setup() {
  Serial.begin(9600);
  servo.Servobegin();
}

void loop() {
  //Get the distances using the sensor and assign it to a variable
  int df = sf.getDistance();
  int dl = sl.getDistance();
  int dr = sr.getDistance();
  motor.setMotorSpeed(255); // Speed out of 255
  if(df<x){
    motor.setMotorDirection(-1); // rotate the motor in the other direction
    if(dr>dl){
      servo.setServoPosition(30);  // Turn left
    }
    else if(dl>dr){
      servo.setServoPosition(150);  // Turn right
    }
    delay(500);
  }
  else if(abs(dl-dr)<40){
    servo.setServoPosition(90);  // Stay Centered
    motor.setMotorDirection(1); // Go forward
    if(df<20){
      servo.setServoPosition(150);  // Turn right
    }
    x=0;
  }
  else if(dl>dr){
    servo.setServoPosition(30);  // Turn left
    motor.setMotorDirection(1); // Go forward
    x=0;
  }
  else{
    servo.setServoPosition(150);  // Turn right
    motor.setMotorDirection(1); // Go forward
    x=0;
  }
  delay(100);
}

