// Include library
#define USE_USBCON
#include <ros.h>
#include <ros_dcmotor/motor.h>
#include <ros/time.h>
#include <std_msgs/Float32.h>

const int interval = 10;
long previousMillis = 0;
long currentMillis = 0;

// Motor Right --------------------------------------------------------
#define right_motor_Rpwm_pin 7
#define right_motor_Lpwm_pin 6
int counter_right = 0;
uint8_t enc_right_A = 8;
uint8_t enc_right_B = 9;
int PPR = 23;
float GR = 19.2*3.17;
int right_pwm;
float voltage;
float theta_now;
float theta_old;
float velRightWheel;
// Motor Right --------------------------------------------------------

void calc_vel_right_wheel(){
   
  // Previous timestamp
  static double prevTime = 0;
 
  theta_now = (2*3.1415926535*counter_right)/(PPR * GR);
  velRightWheel = (theta_now - theta_old)/((millis()/1000)-prevTime);
 
  theta_old = theta_now;
   
  prevTime = (millis()/1000);
}

// ROS --------------------------------------------------------------------------
ros::NodeHandle nh;
void right_cmd_pwm_cb(const std_msgs::Float32& msg);

// Init Pub and Sub
ros_dcmotor::motor right_motor_stat;
ros::Publisher rightPub("motor_right", &right_motor_stat);
ros::Subscriber<std_msgs::Float32> right_sub("/right_cmd", &right_cmd_pwm_cb);
// ROS --------------------------------------------------------------------------


void setup() {
  // Motor
  pinMode(right_motor_Rpwm_pin, OUTPUT);
  pinMode(right_motor_Lpwm_pin, OUTPUT);

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

  currentMillis = millis();
  if (currentMillis - previousMillis > interval)
  {
    
    previousMillis = currentMillis;
    calc_vel_right_wheel();
    
    right_motor_stat.header.stamp = nh.now();
    right_motor_stat.header.frame_id = "right_motor";
    right_motor_stat.speed = velRightWheel;
    right_motor_stat.encoder = counter_right;
    rightPub.publish( &right_motor_stat );
  }
}
