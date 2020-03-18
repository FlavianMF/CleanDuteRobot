void drive() {
  readControll();
  normallizer();
  mix();
  motorControll();
  hodometer();
}

void readControll() {
  xAxy = analogRead(joystickXaxy);
  yAxy = analogRead(joystickYaxy);

  if (xAxy - 900 > -deadZone && xAxy - 900 < deadZone) {
    xAxy = 441;
  }
  if (yAxy - 900 > -deadZone && yAxy - 900 < deadZone) {
    yAxy = 441;
  }
}

void normallizer() {
  xValue = map(xAxy, minXRangeJoystick, maxXRangeJoystick, -maxVelocity, maxVelocity);
  yValue = map(yAxy, minYRangeJoystick, maxYRangeJoystick, maxVelocity, -maxVelocity);
}

void mix() {
  lOutput = yValue + xValue;
  lOutput = constrain(lOutput, -maxVelocity, maxVelocity);

  rOutput = yValue - xValue;
  rOutput = constrain(rOutput, -maxVelocity, maxVelocity);
}

void motorControll() {
  if (lOutput > 0) {
    RodaEsquerdaFrente(lOutput);
  } else if (lOutput < 0) {
    lOutput *= -1;
    RodaEsquerdaTras(lOutput);
    lOutput *= -1;
  } else {
    RodaEsquerdaPara();
  }

  if (rOutput > 0) {
    RodaDireitaFrente(rOutput);
  } else if (rOutput < 0) {
    rOutput *= -1;
    RodaDireitaTras(rOutput);
    rOutput *= -1;
  } else {
    RodaDireitaPara();
  }
}

void hodometer() {
  if (lOutput > 0 && rOutput > 0) {
    if (millis() > timer + 1000) {
      timer = millis();
      displacementInMeters += wheelCircumference;
    }
  }
}
