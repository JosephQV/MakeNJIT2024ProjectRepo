const int LEFTSENSEPIN = 45;
const int RIGHTSENSEPIN = 41;
const int STOPSENSEPIN = 37;

const int STOPMOTORPIN = 33;
const int STEERINGLEFTPIN = 2;
const int STEERINGRIGHTPIN = 3;

void setup() {
  //Set input pins for IR sensors
  //2 IR Sensors at front for steering detection
  pinMode(LEFTSENSEPIN, INPUT);
  pinMode(RIGHTSENSEPIN, INPUT);
  //1 IR Sensor at side for stop detection
  pinMode(STOPSENSEPIN, INPUT);
  //set output pin for start/stopping back wheel motors
  pinMode(STOPMOTORPIN, OUTPUT);
  //set digital output pins for controlling left and right steering
  pinMode(STEERINGLEFTPIN, OUTPUT);
  pinMode(STEERINGRIGHTPIN, OUTPUT);
  
  //Serial monitor for printing for testing
  Serial.begin(9600);
}

void loop() {
  //Take input from front IR sensors
  int LEFTreading = digitalRead(LEFTSENSEPIN);
  int RIGHTreading = digitalRead(RIGHTSENSEPIN);
  //take input from side IR sensor
  int STOPreading = digitalRead(STOPSENSEPIN);
  //TESTING - print inputs
  Serial.println(LEFTreading);
  Serial.println(RIGHTreading);
  Serial.println(STOPreading);
  delay(300);
}
