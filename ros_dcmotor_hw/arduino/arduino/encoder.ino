void ai8() {
  if (digitalRead(enc_right_A) == HIGH) {
    if (digitalRead(enc_right_B) == LOW) {
      counter_right++;
    }
    else {
      counter_right--;
    }
  }
  else {
    if (digitalRead(enc_right_B) == LOW) {
      counter_right--;
    }
    else {
      counter_right++;
    }
  }
}

void ai9() {
  if (digitalRead(enc_right_B) == HIGH) {
    if (digitalRead(enc_right_A) == LOW) {
      counter_right--;
    }
    else {
      counter_right++;
    }
  }
  else {
    if (digitalRead(enc_right_A) == LOW) {
      counter_right++;
    }
    else {
      counter_right--;
    }
  }
}
