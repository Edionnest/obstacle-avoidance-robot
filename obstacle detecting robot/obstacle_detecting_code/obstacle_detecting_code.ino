#include <Arduino_RouterBridge.h>
#include <Servo.h>

Servo my_servo;
const int in1 = 2;
const int in2 = 3;
const int in3 = 4;
const int in4 = 5;
const int in5 = 6;
const int in6 = 7;
const int in7 = 8;
const int in8 = 9;
const int echo_pin = 11;
const int trig_pin = 12;
const int servo_pin = 10;

float duration;
float distance_cm;
float left_side; // when the servo is at 180 degrees
float right_side;// when the servo is at 0 degrees
int delay_time = 1000;



void setup() {
  Monitor.begin(); // if using a normal arduino, change monitor.begin() to Serial.begin(any baudrate you prefer)
  delay(5000);
  my_servo.attach(servo_pin);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  // Bridge.provide("get_distance_cm", get_distance_cm());
 
 

}

void loop() {
  my_servo.write(90);
  distance_cm = get_distance_cm();
  while (distance_cm > 15){  // continue driving as long as there is no obstacles detetected
    robot_forward();
    distance_cm = get_distance_cm();
    Monitor.println("driving distance = " + String(distance_cm));
  }
  robot_stop();
  my_servo.write(0);
  delay(1000);
  right_side = get_distance_cm(); // scan right
  delay(500);
  my_servo.write(180);
  delay(1000);
  left_side = get_distance_cm();// scan left
  delay(500);
  robot_reverse();
  delay(500);
  if (left_side > right_side){ // compare which path has the farthest obstacle
    robot_left();
  }
  else{
    robot_right();
  }
  delay(1500);
  Monitor.println("current distance = " + String(distance_cm));
  Monitor.println("left side distance = " + String(left_side));
  Monitor.println("right side distance = " + String(right_side));

}
    

float get_distance_cm(){
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  duration = pulseIn(echo_pin, HIGH, 1000); // time out parameter was added due to the ultrasonic sensor freezing up when distance detected is less than 2

  return (0.0343* duration)/2;
}

float averaage_distance(){ // to get accurate distance measurement
  int loops = 0;
  float distance;
  while (loops < 10){
    distance += get_distance_cm();
    loops++;
    
  }
  if (distance/10 < 3){
    return 3;
  }
  else{
      return distance/10; 
  }

}
void robot_reverse() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
    
  
}

void robot_forward() {
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in6, HIGH);
  digitalWrite(in5, LOW);
  digitalWrite(in8, LOW);
  digitalWrite(in7, HIGH);
    
  
}

void robot_right () {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
    
  
}

void robot_left () {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
    
  
}

void robot_stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
  
}