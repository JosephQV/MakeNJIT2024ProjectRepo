//pin number setup
const int LEFTSENSEPIN = 4;
const int RIGHTSENSEPIN = 5;
const int STOPSENSEPIN = 2;
//2 left wheels, 2 right wheels
const int LEFTDIRECTION = 12;
const int LEFTPWM = 3;
const int LEFTBRAKE = 9; 
const int RIGHTDIRECTION = 13;
const int RIGHTPWM = 11;
const int RIGHTBRAKE = 8;

//reverse sensor pins
const int LEFTSENSEPIN_R = 6;
const int RIGHTSENSEPIN_R = 7;

const int SPEED = 100;
bool DIRECTION = 0;

void setup() {
  //Set input pins for IR sensors
  //2 IR Sensors at front for steering detection
  pinMode(LEFTSENSEPIN, INPUT);
  pinMode(RIGHTSENSEPIN, INPUT);
  //2 IR sensors at back
  pinMode(LEFTSENSEPIN_R, INPUT);
  pinMode(RIGHTSENSEPIN_R, INPUT);
  //1 IR Sensor at side for stop detection
  pinMode(STOPSENSEPIN, INPUT);
  //set digital output pins for controlling the 2 left and 2 right wheels
  pinMode(LEFTDIRECTION, OUTPUT);
  pinMode(LEFTPWM, OUTPUT);
  pinMode(LEFTBRAKE, OUTPUT);
  pinMode(RIGHTDIRECTION, OUTPUT);
  pinMode(RIGHTPWM, OUTPUT);
  pinMode(RIGHTBRAKE, OUTPUT);
  
  //Serial monitor for printing for testing
  Serial.begin(9600);
}

void loop() {
  //Take input from IR sensors based on current direction
  int LEFTreading;
  int RIGHTreading;

  if(DIRECTION == 0){
    LEFTreading = digitalRead(LEFTSENSEPIN);
    RIGHTreading = digitalRead(RIGHTSENSEPIN);
  } else {
    LEFTreading = digitalRead(LEFTSENSEPIN_R);
    RIGHTreading = digitalRead(RIGHTSENSEPIN_R);
  }
  //take input from side IR sensor
  int STOPreading = digitalRead(STOPSENSEPIN);
  //TESTING - print inputs
  Serial.print("LEFT: ");
  Serial.print(LEFTreading);
  Serial.print("   RIGHT: ");
  Serial.print(RIGHTreading);
  Serial.print("   STOP: ");
  Serial.println(STOPreading);
  //check path using inputs from sensors
  if(STOPSENSEPIN == 1){
    delay(3000);
  } else {
    checkPath(LEFTreading, RIGHTreading);
  }
  //checkPath(LEFTreading, RIGHTreading);
  delay(2000);
}

void checkPath(int LEFT, int RIGHT){
  if(LEFT == 1 && RIGHT == 1){
    MOVELEFT(DIRECTION);
    MOVERIGHT(DIRECTION);
    Serial.println("MOVE FORWARD");
  }
  if(LEFT == 1 && RIGHT == 0){
    MOVELEFT(!DIRECTION);
    MOVERIGHT(DIRECTION);
    Serial.println("MOVE LEFT");
  }
  if(LEFT == 0 && RIGHT == 1){
    MOVELEFT(DIRECTION);
    MOVERIGHT(!DIRECTION);
    Serial.println("MOVE RIGHT");
  }
  if(LEFT == 0 && RIGHT == 0){
    DIRECTION = !DIRECTION;
    MOVELEFT(DIRECTION);
    MOVERIGHT(DIRECTION);
    Serial.println("MOVE BACK");
  }
}

void MOVELEFT(bool direction){
  //Left side move in opposite of current direction
  //Right side move in current direction
  digitalWrite(LEFTDIRECTION, !direction);
  digitalWrite(RIGHTDIRECTION, direction);
  //no brakes
  digitalWrite(LEFTBRAKE, LOW);
  digitalWrite(RIGHTBRAKE, LOW);  
  //work duty (speed)
  analogWrite(LEFTPWM, SPEED);
  analogWrite(RIGHTPWM, SPEED);
  //motor time
  delay(300);
}
void MOVERIGHT(bool direction){
  //Left side move in opposite of current direction
  //Right side move in current direction
  digitalWrite(LEFTDIRECTION, direction);
  digitalWrite(RIGHTDIRECTION, !direction);
  //no brakes
  digitalWrite(LEFTBRAKE, LOW);
  digitalWrite(RIGHTBRAKE, LOW);  
  //work duty (speed)
  analogWrite(LEFTPWM, SPEED);
  analogWrite(RIGHTPWM, SPEED);
  //motor time
  delay(300);
}
