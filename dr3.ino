#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
int pos = 60;    // variable to store the servo position 
 
#define DIR_PIN 2
#define STEP_PIN 3
#define DIR_PIN2 7
#define STEP_PIN2 5

#define SPEED .03

char val; // variable to receive data from the serial port
void setup() {
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN2, OUTPUT);
  pinMode(STEP_PIN2, OUTPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);       // start serial communication at 9600bps
}
void loop() {
  if( Serial.available() )       // if data is available to read
  {
    val = Serial.read();         // read it and store it in 'val'
    switch (val) {
    case 0x01:
        penUp();
      break;
    case 0x02:
      penDown();
      break;
    case 0x03:
      circle();
      break;
    case 0x04:
      square();
      break;
    case 0x05:
      triangle();
      break;
    case 0x06:
      heart();
      break;
    case 0x07:
      left5Degrees();
      break;
    case 0x08:
      right5Degrees();
      break;
    case 0x09:
      forward100Steps();
      break;
    case 0x0A:
      backward100Steps();
      break;
    }
  }
  delay(100);                    // wait 100ms for next reading
}

void penUp() {
  for(; pos < 60; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                 // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
                      // waits 15ms for the servo to reach the position 
  } 
  pos = 60;
  myservo.write(pos);              // tell servo to go to position in variable 'pos' 
}

void penDown() {
  for(; pos > 0; pos -= 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
                      // waits 15ms for the servo to reach the position 
  }
  pos = 0;
  myservo.write(pos);              // tell servo to go to position in variable 'pos' 
}

void circle() {
  penDown();
  step(5000, 200);
  penUp();
}

void left5Degrees() {
  step(-33, 33);
}

void right5Degrees() {
  step(33, -33);
}

void forward100Steps() {
  step(100, 100);
}

void backward100Steps() {
  step(-100, -100);
}

void heart() {
  penDown();
  step(2850, 200);
  penUp();
  step(820, -820);
  penDown();
  step(2850, 200);
  step(1500, 1000);
  penUp();
  step(-590, 590);
  penDown();
  step(1000, 1500);
  penUp();
}

void square() {
  penDown();
  step(500, 500);
  penUp();
  step(-588, 588);
  penDown();
  step(500, 500);
  penUp();
  step(-588, 588);
  penDown();
  step(500, 500);
  penUp();
  step(-588, 588);
  penDown();
  step(500, 500);
  penUp();
  step(-588, 588);
}

int triangleTurn = 780;
int triangleSide = 800;
void triangle() {
  penDown();
  step(triangleSide, triangleSide);
  penUp();
  step(-triangleTurn, triangleTurn);
  penDown();
  step(triangleSide, triangleSide);
  penUp();
  step(-triangleTurn, triangleTurn);
  penDown();
  step(triangleSide, triangleSide);
  penUp();
  step(-triangleTurn, triangleTurn);
}

// Forward
// left ticks and right ticks
// lticks = 100
// rticks = 105
// (rticks - lticks) / lticks
// let lunit = .9
// let runit = 1
// when the distance of one wheel gets a full tick behin the other wheel,
// we give it a tick to catch it up
//  ldist = N * ltick
//  rdist = N * rtick
//
//  if (ldist - rdist >= rdist) tick(right)
//  if (rdist - ldist >= ldist) tick(left)



void step(int lsteps, int rsteps) { // 2000, 1000
  int dirL = (lsteps > 0) ? LOW : HIGH;
  int dirR = (rsteps > 0) ? LOW : HIGH;
  lsteps = abs(lsteps);
  rsteps = abs(rsteps);
  if (lsteps >= rsteps) {
    float offset = 0, delta = (lsteps - rsteps) / rsteps;  // 3
    for (int i = 0; i < rsteps; i++) {
      offset += delta;
      stepOne(dirL, dirR, SPEED);
      for(;  offset >= 1; offset--) {  // 3 * 0 | 3 * 1
        stepOneLeft(dirL, SPEED);
      }
    }
  } else {
    float offset = 0, delta = (rsteps - lsteps) / lsteps;
    for (int i = 0; i < lsteps; i++) {
      offset += delta;
      stepOne(dirL, dirR, SPEED);
      for(;  offset >= 1; offset--) {  // 3 * 0 | 3 * 1
        stepOneRight(dirR, SPEED);
      }
    }
  }
}

void stepOne(int dirL, int dirR, float speed) {
  //rotate a specific number of degrees (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  digitalWrite(DIR_PIN, dirL);
  digitalWrite(DIR_PIN2, dirR);
  float usDelay = (1/speed) * 70;
  digitalWrite(STEP_PIN, HIGH); 
  digitalWrite(STEP_PIN2, HIGH); 
  delayMicroseconds(usDelay);
  digitalWrite(STEP_PIN, LOW);
  digitalWrite(STEP_PIN2, LOW);
  delayMicroseconds(usDelay);
}

void stepOneLeft(int dir, float speed) {
  //rotate a specific number of degrees (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  digitalWrite(DIR_PIN2, dir);
  float usDelay = (1/speed) * 70;
  digitalWrite(STEP_PIN2, HIGH); 
  delayMicroseconds(usDelay);
  digitalWrite(STEP_PIN2, LOW);
  delayMicroseconds(usDelay);
}

void stepOneRight(int dir, float speed) {
  //rotate a specific number of degrees (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  digitalWrite(DIR_PIN, dir);
  float usDelay = (1/speed) * 70;
  digitalWrite(STEP_PIN, HIGH); 
  delayMicroseconds(usDelay);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(usDelay);
}


