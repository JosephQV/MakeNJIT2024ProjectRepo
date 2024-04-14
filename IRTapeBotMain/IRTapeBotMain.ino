//pin number setup
//IR sensors
const int LEFTSENSEPIN = 5;
const int RIGHTSENSEPIN = 4;
const int STOPSENSEPIN = 2;
//reverse IR sensor pins (on "back")
const int LEFTSENSEPIN_R = 6;
const int RIGHTSENSEPIN_R = 7;

//left wheels, right wheels - motor shield control
//channel A
const int LEFTDIRECTION = 12;
const int LEFTPWM = 3;
const int LEFTBRAKE = 9; 
//channel B
const int RIGHTDIRECTION = 13;
const int RIGHTPWM = 11;
const int RIGHTBRAKE = 8;
//motor speed
const int SPEED = 40;
//direction state value for determining sensors to use
bool DIRECTION = 0;

//setup for on/off button functionality
const int OFFpin = 10;
int oldButtonState = 0;
int buttonState = 0;
int state = 1; //1 for ON movement, 0 for OFF no movement

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
  //set digital output pins for controlling the motor shields channels A and B
  pinMode(LEFTDIRECTION, OUTPUT);
  pinMode(LEFTPWM, OUTPUT);
  pinMode(LEFTBRAKE, OUTPUT);
  pinMode(RIGHTDIRECTION, OUTPUT);
  pinMode(RIGHTPWM, OUTPUT);
  pinMode(RIGHTBRAKE, OUTPUT);
  
  pinMode(OFFpin, INPUT_PULLUP);
  //Serial monitor for printing for testing
  Serial.begin(9600);
}

void loop() {
  //get state of button: pressed = buttonState HIGH
  buttonState = !digitalRead(OFFpin);

  if(buttonState && !oldButtonState) // same as if(button == high && oldbutton == low)
  {
    //button was pressed
    oldButtonState = 1;
    state = !state;
    Serial.println("BUTTON PRESSED");
    delay(100);
  }
  else if(!buttonState && oldButtonState)// same as if(button == low && oldbutton == high)
  {
    //button was released
    oldButtonState = 0;
    Serial.println("BUTTON RELEASED");
  }
  if(state){
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
      Serial.println("STOPPED");
      STOPMOVE(3000);
      
    } else {
      checkPath(LEFTreading, RIGHTreading);
    }
    //checkPath(LEFTreading, RIGHTreading);
    delay(300);
  } else {
    //do nothing if state is 0
    STOPMOVE(300);
    // Serial.print("BUTTON STATE   ");
    // Serial.println(buttonState);
    // Serial.print("OLD BUTTON STATE   ");
    // Serial.println(oldButtonState);
    Serial.print("STATE   ");
    Serial.println(state);
  }
}

void checkPath(int LEFT, int RIGHT){
  if(LEFT == 1 && RIGHT == 1){
    MOVELEFT(DIRECTION);
    MOVERIGHT(DIRECTION);
    Serial.println("MOVE FORWARD");
    delay(30);
  }
  if(LEFT == 1 && RIGHT == 0){
    MOVELEFT(!DIRECTION);
    MOVERIGHT(DIRECTION);
    Serial.println("MOVE LEFT");
    delay(30);
  }
  if(LEFT == 0 && RIGHT == 1){
    MOVELEFT(DIRECTION);
    MOVERIGHT(!DIRECTION);
    Serial.println("MOVE RIGHT");
    delay(30);
  }
  if(LEFT == 0 && RIGHT == 0){
    delay(1500);
    DIRECTION = !DIRECTION;
    MOVELEFT(DIRECTION);
    MOVERIGHT(DIRECTION);
    Serial.println("MOVE BACK");
    delay(30);
  }
}

void MOVELEFT(bool direction){
  //Left side move in opposite of current direction
  //Right side move in current direction
  digitalWrite(LEFTDIRECTION, !direction);
  digitalWrite(RIGHTDIRECTION, direction);
  //left brakes
  digitalWrite(LEFTBRAKE, HIGH);
  digitalWrite(RIGHTBRAKE, LOW);  
  //work duty (speed)
  analogWrite(LEFTPWM, 0);
  analogWrite(RIGHTPWM, SPEED);
  //motor time
  delay(30);
}

void MOVERIGHT(bool direction){
  //Left side move in opposite of current direction
  //Right side move in current direction
  digitalWrite(LEFTDIRECTION, direction);
  digitalWrite(RIGHTDIRECTION, !direction);
  //right brakes
  digitalWrite(LEFTBRAKE, LOW);
  digitalWrite(RIGHTBRAKE, HIGH);  
  //work duty (speed)
  analogWrite(LEFTPWM, SPEED);
  analogWrite(RIGHTPWM, 0);
  //motor time
  delay(30);
}

void STOPMOVE(int time){
  digitalWrite(LEFTDIRECTION, 0);
  digitalWrite(RIGHTDIRECTION, 0);
  //both brakes
  digitalWrite(LEFTBRAKE, HIGH);
  digitalWrite(RIGHTBRAKE, HIGH);  
  //work duty (speed)
  analogWrite(LEFTPWM, 0);
  analogWrite(RIGHTPWM, 0);
  //motor time
  delay(time);
}