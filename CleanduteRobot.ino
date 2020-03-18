#include <LiquidCrystal_I2C.h>
#include <Wire.h>


#define motorRPM 98
#define motorRPS motorRPM/60

// #define wheelDiameterInMeters 0.1
#define wheelRayInMeters 0.05
#define wheelCircumference wheelRayInMeters*2*PI

#define maxVelocity 254
#define maxBrushVelocity 254

#define rPWM_R 3
#define rPWM_L 5
#define lPWM_R 6
#define lPWM_L 9

#define bPWM_L 10
#define bPWM_R 11

#define potentiometerPin A0

#define joystickXaxy A6
#define joystickYaxy A7

uint64_t timer = 0;

int pwm = 0;

double displacementInMeters = 0;

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
  timer = millis();
}

void loop() {
  drive();
  brush();
  showInfos();
  debug();
}

void setupPins() {
  pinMode(rPWM_R, OUTPUT);
  pinMode(rPWM_L, OUTPUT);
  pinMode(lPWM_R, OUTPUT);
  pinMode(lPWM_L, OUTPUT);
  pinMode(bPWM_L, OUTPUT);
  pinMode(bPWM_R, OUTPUT);
  pinMode(potentiometerPin, INPUT);
  pinMode(joystickXaxy, INPUT);
  pinMode(joystickYaxy, INPUT);
}
void brush() {
  getVelocity();
  analogWrite(bPWM_L, velocity);
  analogWrite(bPWM_R, 0);
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
  lcd.print("Displacement: ");
  lcd.print(displacementInMeters);
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
  Serial.print("\tDisplacement: ");
  Serial.print(displacementInMeters);
  Serial.println();
}