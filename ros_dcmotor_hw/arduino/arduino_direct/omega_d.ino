void right_cmd_pwm_cb(const std_msgs::Float32& msg)
{
  omega_d = msg.data;
}

float tick_2_theta(int tick, float PPR, float GR) {
  float theta = (2 * pi * tick) / (PPR * GR);
  return theta;
}
