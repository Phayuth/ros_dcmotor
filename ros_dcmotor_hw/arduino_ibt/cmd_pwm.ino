// callback function for subcribe to right wheel
void right_cmd_pwm_cb(const std_msgs::Float32& msg)
{
  voltage = msg.data;
  right_pwm = (voltage/23.5)*255;

  // write pwm to pin
  if (right_pwm < 0) {
    analogWrite(right_motor_Rpwm_pin, 0);
    analogWrite(right_motor_Lpwm_pin, right_pwm * -1);
  }
  else if (right_pwm > 0) {
    analogWrite(right_motor_Rpwm_pin, right_pwm);
    analogWrite(right_motor_Lpwm_pin, 0);
  }
  else {
    analogWrite(right_motor_Rpwm_pin, 0);
    analogWrite(right_motor_Lpwm_pin, 0);
  }
}
