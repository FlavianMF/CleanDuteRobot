#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define maxVelocity 254
#define maxBrushVelocity 254

#define rPWM_R 5
#define rPWM_L 6
#define lPWM_R 9
#define lPWM_L 10

#define brushPin 3

#define potentiometerPin A0

#define joystickXaxy A6
#define joystickYaxy A7

int pwm = 0;

int rawPotentiometer = 0;
int velocity = 0;

int xAxy = 0;
int yAxy = 0;
int deadZone = 10;

int xValue = 0;
int yValue = 0;

int rOutput = 0;
int lOutput = 0;

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
    showInfos();
    debug();
    delay(10);
}

void setupPins() {
    pinMode(rPWM_R, OUTPUT);
    pinMode(rPWM_L, OUTPUT);
    pinMode(lPWM_R, OUTPUT);
    pinMode(lPWM_L, OUTPUT);
}
void brush() {
    getVelocity();
    analogWrite(5, 0);
    analogWrite(brushPin, velocity);
}

void getVelocity() {
    rawPotentiometer = readPotentiometer();
    if (rawPotentiometer > 900 || rawPotentiometer < 0) rawPotentiometer = 0;
    velocity = normallizerPotentiometer(rawPotentiometer);
}

uint16_t readPotentiometer() { return analogRead(potentiometerPin); }

uint8_t normallizerPotentiometer(uint16_t potentiometerValue) {
    return map(potentiometerValue, 0, 900, 0, maxBrushVelocity);
}

void showInfos() {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Brush Vel: ");
    lcd.print(velocity);
    lcd.setCursor(1, 1);
    lcd.print("Robot Vel: ");
    lcd.print(pwm);
}

void debug() {
    Serial.print("Raw Pot: ");
    Serial.print(rawPotentiometer);
    Serial.print("\tBrush Vel: ");
    Serial.print(velocity);
    Serial.print("\tRobot Vel: ");
    Serial.print(pwm);
    Serial.print("\tJoyX: ");
    Serial.print(xAxy);
    Serial.print("\tJoyY: ");
    Serial.print(yAxy);
    Serial.print("\tlOutput: ");
    Serial.print(lOutput);
    Serial.print("\trOutput: ");
    Serial.print(rOutput);
    Serial.println();
}