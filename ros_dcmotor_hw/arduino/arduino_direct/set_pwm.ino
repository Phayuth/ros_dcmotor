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
    analogWrite(motorR_pwm_pin, abs(pwm));
    digitalWrite(motorR_dir_pin, 1);
  }
  else if ( pwm > 0) {
    analogWrite(motorR_pwm_pin, pwm);
    digitalWrite(motorR_dir_pin, 0);
  }
  else {
    analogWrite(motorR_pwm_pin, 0);
    digitalWrite(motorR_dir_pin, 0);
  }
}
