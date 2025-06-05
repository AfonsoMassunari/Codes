#include "var.h"
#include "control.h"
#include "io.h"
#include <pic18f4520.h>

//caso a faixa dos valores definidos como alarme forem ultrapassadas,liga-se um led referente a cada faixa de alarme
void controlSet(int ad2read){
 if (ad2read < getAlarmLevel_1_Low()) {
        digitalWrite(15, 0);
    } else {
        digitalWrite(15, 1);
    }

    if (ad2read > getAlarmLevel_1_High()) {
        digitalWrite(14, 0);
    } else {
        digitalWrite(14, 1);
    }

    if (ad2read < getAlarmLevel_2_Low()) {
        digitalWrite(13, 0);
    } else {
        digitalWrite(13, 1);
    }

    if (ad2read > getAlarmLevel_2_High()) {
        digitalWrite(12, 0);
    } else {
        digitalWrite(12, 1);
    }
}
