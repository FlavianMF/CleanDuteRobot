void drive() {
    readControll();
    normallizer();
    mix();
    motorControll();
}

void readControll() {
    xAxy = analogRead(joystickXaxy);
    yAxy = analogRead(joystickYaxy);

    if (xAxy - 1023 > -deadZone && xAxy - 1023 < deadZone) {
        xAxy = 511;
    }
    if (yAxy - 1023 > -deadZone && yAxy - 1023 < deadZone) {
        yAxy = 511;
    }
}

void normallizer() {
    xValue = map(xAxy, 0, 1023, -maxVelocity, maxVelocity);
    yValue = map(yAxy, 0, 1023, -maxVelocity, maxVelocity);
}

void mix() {
    lOutput = yValue + xValue;
    lOutput = constrain(lOutput, -maxVelocity, maxVelocity);

    rOutput = yValue - xValue;
    rOutput = constrain(rOutput, -maxVelocity, maxVelocity);
}

void motorControll() {
    if (lOutput > 0) {
        analogWrite(lPWM_R, 0);
        analogWrite(lPWM_L, lOutput);
    } else if (lOutput < 0) {
        lOutput *= -1;
        analogWrite(lPWM_R, lOutput);
        analogWrite(lPWM_L, 0);
    } else {
        analogWrite(lPWM_R, 0);
        analogWrite(lPWM_L, 0);
    }

    if (rOutput > 0) {
        analogWrite(rPWM_R, 0);
        analogWrite(rPWM_L, rOutput);
    } else if (rOutput < 0) {
        rOutput *= -1;
        analogWrite(rPWM_R, rOutput);
        analogWrite(rPWM_L, 0);
    } else {
        analogWrite(rPWM_R, 0);
        analogWrite(rPWM_L, 0);
    }
}