void ai8() {
  if (digitalRead(R_PinA) == HIGH) {
    if (digitalRead(R_PinB) == LOW) {
      R_counter++;
    }
    else {
      R_counter--;
    }
  }
  else {
    if (digitalRead(R_PinB) == LOW) {
      R_counter--;
    }
    else {
      R_counter++;
    }
  }
}

void ai9() {
  if (digitalRead(R_PinB) == HIGH) {
    if (digitalRead(R_PinA) == LOW) {
      R_counter--;
    }
    else {
      R_counter++;
    }
  }
  else {
    if (digitalRead(R_PinA) == LOW) {
      R_counter++;
    }
    else {
      R_counter--;
    }
  }
}
