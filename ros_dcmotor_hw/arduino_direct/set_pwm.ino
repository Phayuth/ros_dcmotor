int pwm_cal (float u_in, float v_max) {
  int pwm = (u_in / v_max) * 255;
  // Limit PWM
  if (pwm < -255) {
    pwm = -255;
  }
  if (pwm > 255) {
    pwm = 255;
  }
  return pwm;
}

void write_pwm(int pwm) {
  if ( pwm < 0) {
    analogWrite(motorR_Rpwm_pin, 0);
    analogWrite(motorR_Lpwm_pin, pwm * -1);
  }
  else if ( pwm > 0) {
    analogWrite(motorR_Rpwm_pin, pwm);
    analogWrite(motorR_Lpwm_pin, 0);
  }
  else {
    analogWrite(motorR_Rpwm_pin, 0);
    analogWrite(motorR_Lpwm_pin, 0);
  }
}
