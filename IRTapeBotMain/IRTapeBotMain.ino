const int LEFTSENSEPIN = 45;
const int RIGHTSENSEPIN = 41;
const int STOPSENSEPIN = 37;

const int STOPMOTORPIN = 33;
const int LEFT1PIN = 2;
const int LEFT2PIN = 3;
const int RIGHT1PIN = 4;
const int RIGHT2PIN = 5;

bool DIRECTION = 0;

void setup() {
  //Set input pins for IR sensors
  //2 IR Sensors at front for steering detection
  pinMode(LEFTSENSEPIN, INPUT);
  pinMode(RIGHTSENSEPIN, INPUT);
  //1 IR Sensor at side for stop detection
  pinMode(STOPSENSEPIN, INPUT);
  //set output pin for start/stopping back wheel motors
  pinMode(STOPMOTORPIN, OUTPUT);
  //set digital output pins for controlling the 2 left and 2 right wheels
  pinMode(LEFT1PIN, OUTPUT);
  pinMode(LEFT2PIN, OUTPUT);
  pinMode(RIGHT1PIN, OUTPUT);
  pinMode(RIGHT2PIN, OUTPUT);
  
  //Serial monitor for printing for testing
  Serial.begin(9600);

  void Left(const level){
    digitalwrite(STEERINGLEFTPIN, level)
  }

  void RIGHT(const level){
    digitalwrite(STEERINGRIGHTPIN, level)
  }

}

void loop() {
  //Take input from front IR sensors
  int LEFTreading = digitalRead(LEFTSENSEPIN);
  int RIGHTreading = digitalRead(RIGHTSENSEPIN);
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
  // if(STOPSENSEPIN){
  //   delay(3000);
  // } else {
      checkPath(LEFTreading, RIGHTreading);
  // }
  delay(300);
  //If statement aka Conditionals
  // Going Straight when both are 0
  if ((digitalRead(LEFTSENSEPIN)=LOW) && (digitalRead(RIGHTSENSEPIN)=LOW)){
    Left(HIGH);
    Right(HIGH);
  }
  // Turning Left when L is 0 and R is 1
  if ((digitalRead(LEFTSENSEPIN)=LOW) && (digitalRead(RIGHTSENSEPIN)=HIGH)){
    Left(LOW);
    Right(HIGH);
  }
  // Turning Right when L is 1 and R is 0
  if ((digitalRead(LEFTSENSEPIN)=HIGH) && (digitalRead(RIGHTSENSEPIN)=LOW)){
    Left(HIGH);
    Right(LOW);
  }
  // Stopping when both are 1
  if ((digitalRead(LEFTSENSEPIN)=HIGH) && (digitalRead(RIGHTSENSEPIN)=HIGH)){
    Left(LOW);
    Right(LOW);
  }
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
  digitalWrite(LEFT1PIN, direction);
  digitalWrite(LEFT2PIN, direction);
}
void MOVERIGHT(bool direction){
  digitalWrite(RIGHT1PIN, direction);
  digitalWrite(RIGHT2PIN, direction);
}
