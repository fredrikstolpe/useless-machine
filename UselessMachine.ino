#include <Servo.h>
#include "CBButton.h"
#include "CBLed.h"
#include "CBServo.h"

CBButton openSwitch = CBButton(6, &openSwitchCallback);
CBLed statusLed = CBLed(13);
CBServo openServo = CBServo(5);
CBServo pushServo = CBServo(3);
int pinServoPower = 2;

void setup() 
{
  openServo.init(170);
  pushServo.init(170);
  pinMode(pinServoPower, OUTPUT);
  digitalWrite(pinServoPower, HIGH);
  randomSeed(analogRead(0));
}

void loop()
{
  openSwitch.doWork();
  pushServo.doWork();
  openServo.doWork();
}

void openSwitchCallback(CBButton* button)
{
  if (button->pressed){
    statusLed.on();
    openLid();
  }
  else{
    statusLed.off();
    unpushButton();
  }
}

void openLid(){
  delay(random(1, 500));
  openServo.animateTo(140, random(1, 8), &pushButton);
}

void pushButton(){
  delay(random(1, 500));
  pushServo.animateTo(70, random(2, 20));
}

void unpushButton(){
  pushServo.animateTo(170, random(3, 20), &closeLid);
}

void closeLid(){
  delay(random(1, 500));
  openServo.animateTo(170, random(1, 20));
}

