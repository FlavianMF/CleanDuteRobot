enum statesMotors { FRENTE, PARA, TRAS, ESQUERDA, DIREITA };
uint8_t stateMotor = PARA;

void Frente() {
    if (stateMotor != FRENTE) {
        Serial.println("FRENTE");
        stateMotor = FRENTE;
        RodaDireitaFrente();
        RodaEsquerdaFrente();
    }
}

void Tras() {
    if (stateMotor != TRAS) {
        Serial.println("TRAS");
        stateMotor = TRAS;
        RodaDireitaTras();
        RodaEsquerdaTras();
    }
}

void Para() {
    if (stateMotor != PARA) {
        Serial.println("PARA");
        stateMotor = PARA;
        RodaDireitaPara();
        RodaEsquerdaPara();
    }
}

void Esquerda() {
    if (stateMotor != ESQUERDA) {
        stateMotor = ESQUERDA;
        Serial.println("ESQUERDA");
        RodaDireitaFrente();
        RodaEsquerdaTras();
    }
}

void Direita() {
    if (stateMotor != DIREITA) {
        stateMotor = DIREITA;
        Serial.println("DIREITA");
        RodaDireitaTras();
        RodaEsquerdaFrente();
    }
}
// SetUp Rodas
void RodaDireitaFrente(int PWM) {
    analogWrite(rPWM_R, 0);
    analogWrite(rPWM_L, PWM);
}
void RodaDireitaTras(int PWM) {
    analogWrite(rPWM_R, PWM);
    analogWrite(rPWM_L, 0);
}
void RodaDireitaPara() {
    analogWrite(rPWM_R, 0);
    analogWrite(rPWM_L, 0);
}
void RodaEsquerdaFrente(int PWM) {
    analogWrite(lPWM_R, 0);
    analogWrite(lPWM_L, PWM);
}
void RodaEsquerdaTras(int PWM) {
    analogWrite(lPWM_R, PWM);
    analogWrite(lPWM_L, 0);
}
void RodaEsquerdaPara() {
    analogWrite(lPWM_R, 0);
    analogWrite(lPWM_L, 0);
}