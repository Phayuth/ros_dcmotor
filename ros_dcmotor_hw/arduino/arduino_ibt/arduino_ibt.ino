// Library
#define USE_USBCON
#include <ros.h>
#include <ros_dcmotor/motor.h>
#include <ros/time.h>
#include <std_msgs/Float32.h>

// Right Motor with forward positive count ( Clockwise )
#define motorR_Rpwm_pin 6
#define motorR_Lpwm_pin 7

// Motor Parameters
float pi = 3.141592653;
float a = 28.37, b = 19.15;
float PPR = 28, GR = 19.2 * 3.75;
float theta_p = 0, theta_c = 0;
float omega_d = 0, omega_d_p = 0, omega_c = 0;

//PID Parameters
float kp = (2 * 1 * 2 * pi * 6 - a) / b, ki = (2 * pi * 6 * 2 * pi * 6) / b;
float cumError = 0, error = 0;
float u = 0;
int pwm;

// Time interval for handling control loop
unsigned long time_old, time_new;
float Ts;

// Time interval for handling publish
const int interval = 30;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

// Encoder
int R_counter = 0;
uint8_t R_PinA = 8;
uint8_t R_PinB = 9;

// ROS --------------------------------------------------------------------------
ros::NodeHandle nh;
void right_cmd_pwm_cb(const std_msgs::Float32& msg);

// Init Pub and Sub
ros_dcmotor::motor right_motor_stat;
ros::Publisher rightPub("motor_stat", &right_motor_stat);
ros::Subscriber<std_msgs::Float32> right_sub("/motor_desired", &right_cmd_pwm_cb);
// ROS --------------------------------------------------------------------------

void setup() {
  pinMode(motorR_Rpwm_pin, OUTPUT);
  pinMode(motorR_Lpwm_pin, OUTPUT);
  time_old = millis();
  time_new = millis();
  pinMode(R_PinA, INPUT_PULLUP);
  pinMode(R_PinB, INPUT_PULLUP);
  attachInterrupt(R_PinA, ai8, CHANGE);
  attachInterrupt(R_PinB, ai9, CHANGE);

  // ROS Setup
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(right_sub);
  nh.advertise(rightPub);
}

void loop() {
  // Find out how time has passed
  delay(1); // put delay here to avoid 0/0 NaN, I dont know how to fix it yet.
  time_new = millis(); // handle control loop
  currentMillis = millis(); // handle publisher loop
  Ts = (time_new - time_old) * 0.001; // convert from milli second (ms) to second(s)

  // Find current theta and find omega
  theta_c = tick_2_theta(R_counter, PPR, GR);
  omega_c = (theta_c - theta_p) / Ts;

  // Calculate different error
  error = omega_d - omega_c;

  // Calculate input with PI and compensation ( PI for velocity controller using 2nd ODE standard form )
  u = (kp * error) + (ki * (cumError + error * Ts)) + ((a / b) * omega_d) + ((1 / b) * ((omega_d - omega_d_p) / Ts));

  // Write control value to motor
  pwm = pwm_cal(u, 23.5);
  write_pwm(pwm);

  //Publish stat
  if (currentMillis - previousMillis > interval)
  {
    previousMillis = currentMillis;
    right_motor_stat.header.stamp = nh.now();
    right_motor_stat.header.frame_id = "right_motor";
    right_motor_stat.speed = omega_c;
    right_motor_stat.encoder = R_counter;
    rightPub.publish( &right_motor_stat );
  }

  // Update for next time step
  time_old = time_new;
  theta_p = theta_c;
  cumError += error * Ts;
  omega_d_p = omega_d;

  nh.spinOnce();
}
