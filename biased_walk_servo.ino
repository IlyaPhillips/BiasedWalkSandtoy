#include <Servo.h>
float posX, posY, randX, randY, velX, velY, midX, midY;
int maxDist,minDist;
bool midReturn = false;
Servo servoX;
Servo servoY;

void setup() {
  posX = 91;
  posY = 91;
  maxDist = 180;
  minDist = 0;
  randX = 0;
  randY = 0;
  velX = 0;
  velY = 0;
  midX = 90;
  midY = 90;
  servoX.attach(9);
  servoY.attach(7);
  servoX.write(midX);
  servoY.write(midY);
  Serial.begin(9600);
}

void loop() {
  
  if(posX>maxDist || posY>maxDist || posX<minDist || posY<minDist){
    midReturn = true;
    }
    
  if(posX-midX<1 && posY-midY<1){
      midReturn = false;
    }
    
  if(!midReturn){
  biasedWalk();
  }
  
  if(midReturn){
      midVel();
      posX+=velX;
      posY+=velY;
    }
    Serial.println(posX);
    Serial.println(midReturn);
    
    
    
  servoX.write((int)posX);
  servoY.write((int)posY);
  delay(60);
}
void biasedWalk(){
  randX = random(-1,2);
  randY = random(-1,2);
  setVel();
  posX += velX+randX;
  posY += velY+randY;
}

void midVel(){
    velX = midX-posX;
    velY = midY-posY;
    float unit = sqrt(sq(velX) + sq(velY));
    velX = velX/unit;
    velY = velY/unit;
  }

void setVel(){
    velX = posX-midX;
    velY = posY-midY;
    float unit = sqrt(sq(velX) + sq(velY));
    velX = velX/unit;
    velY = velY/unit;
  }
