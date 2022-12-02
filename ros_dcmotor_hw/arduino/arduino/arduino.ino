// Include library
#define USE_USBCON
#include <ros.h>
#include <ros_dcmotor/motor.h>
#include <ros/time.h>
#include <std_msgs/Float32.h>

// Handles startup and shutdown of ROS
ros::NodeHandle nh;

// Encoder and Motor Right
#define right_motor_pwm 6
#define right_motor_dir 7
int counter_right = 0;
uint8_t enc_right_A = 8;
uint8_t enc_right_B = 9;
int right_pwm;
float voltage;

void right_cmd_pwm_cb(const std_msgs::Float32& msg);

// Init Pub and Sub
ros_dcmotor::motor right_motor_stat;
ros::Publisher rightPub("motor_right", &right_motor_stat);
ros::Subscriber<std_msgs::Float32> right_sub("/right_cmd", &right_cmd_pwm_cb);

void setup() {
  // Motor
  pinMode(right_motor_pwm, OUTPUT);
  pinMode(right_motor_dir, OUTPUT);

  // Interupt encoder
  pinMode(enc_right_A, INPUT_PULLUP);
  pinMode(enc_right_B, INPUT_PULLUP);
  attachInterrupt(enc_right_A, ai8, CHANGE);
  attachInterrupt(enc_right_B, ai9, CHANGE);

  // ROS Setup
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(right_sub);
  nh.advertise(rightPub);
}

void loop() {
  nh.spinOnce();
}
