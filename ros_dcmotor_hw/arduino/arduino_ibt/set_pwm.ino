int pwm_cal (float u_in, float v_max) {
  pwm = (u_in / v_max) * 250;
  // Limit PWM
  if (pwm < -250) {
    pwm = -250;
  }
  if (pwm > 250) {
    pwm = 250;
  }
  return pwm;
}

void write_pwm(int pwm) {
  if ( pwm < 0) {
    analogWrite(motorR_Rpwm_pin, abs(pwm));
    analogWrite(motorR_Lpwm_pin, 0);
  }
  else if ( pwm > 0) {
    analogWrite(motorR_Rpwm_pin, 0);
    analogWrite(motorR_Lpwm_pin, pwm);
  }
  else {
    analogWrite(motorR_Rpwm_pin, 0);
    analogWrite(motorR_Lpwm_pin, 0);
  }
}
