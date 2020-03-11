#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define maxVelocity 254
#define maxBrushVelocity 254

#define rPWM_R 5
#define rPWM_L 6
#define lPWM_R 9
#define lPWM_L 10

#define brushPin 4

#define potentiometerPin A0

#define joystickXaxy A1
#define joystickYaxy A2

uint8_t pwm = 0;

uint16_t rawPotentiometer = 0;
uint8_t velocity = 0;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void RodaDireitaFrente(int PWM = pwm);
void RodaDireitaTras(int PWM = pwm);
void RodaEsquerdaFrente(int PWM = pwm);
void RodaEsquerdaTras(int PWM = pwm);

void setup() {
    Serial.begin(9600);

    setupPins();

    lcd.begin(16, 2);
    lcd.setBacklight(HIGH);
}

void loop() {
    drive();
    brush();
}

void setupPins() {
    pinMode(rPWM_R, OUTPUT);
    pinMode(rPWM_L, OUTPUT);
    pinMode(lPWM_R, OUTPUT);
    pinMode(lPWM_L, OUTPUT);
}
void brush() {
    analogWrite(brushPin, velocity);
}

uint8_t getVelocity() {
    rawPotentiometer = readPotentiometer();
    if (rawPotentiometer > 1023 || rawPotentiometer < 0) rawPotentiometer = 0;
    velocity = normallizerPotentiometer(rawPotentiometer);
}

uint16_t readPotentiometer() { return analogRead(potentiometerPin); }

uint8_t normallizerPotentiometer(uint16_t potentiometerValue) {
    return map(potentiometerValue, 0, 1023, 0, maxBrushVelocity);
}
