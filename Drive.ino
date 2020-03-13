void drive() {
    readControll();
    normallizer();
    mix();
    motorControll();
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
    xValue = map(xAxy, 0, 900, -maxVelocity, maxVelocity);
    yValue = map(yAxy, 0, 900, maxVelocity, -maxVelocity);
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
        lOutput *= -1;
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
        rOutput *= -1;
    } else {
        analogWrite(rPWM_R, 0);
        analogWrite(rPWM_L, 0);
    }
}