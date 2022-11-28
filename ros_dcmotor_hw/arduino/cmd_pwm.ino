// callback function for subcribe to right wheel
void right_cmd_pwm_cb(const std_msgs::Float32& msg)
{
  voltage = msg.data;
  right_pwm = (voltage/23.5)*255;

  // write pwm to pin
  if (right_pwm < 0) {
    analogWrite(right_motor_pwm, abs(right_pwm));
    digitalWrite(right_motor_dir, 1);
  }
  else if (right_pwm > 0) {
    analogWrite(right_motor_pwm, right_pwm);
    digitalWrite(right_motor_dir, 0);
  }
  else {
    analogWrite(right_motor_pwm, 0);
    digitalWrite(right_motor_dir, 0);
  }
  right_motor_stat.header.stamp = nh.now();
  right_motor_stat.header.frame_id = "right_motor";
  right_motor_stat.encoder = counter_right;
  rightPub.publish( &right_motor_stat );
}
