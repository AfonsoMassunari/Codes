#include "keypad.h"
#include "event.h"
#include "pic18f4520.h"
#include "serial.h"
#include "var.h"


static unsigned int key_ant;
char buffer[30];

void eventInit(void) {
    kpInit();
    key_ant = 0;
}

unsigned int eventRead(void) {
    int key;
    int ev = EV_NOEVENT;
    unsigned char serialTest;
    serialInit();
    key = kpRead();
   //sincroniza cada valor do bot�o com um evento
    if (key != key_ant) {
        if (key == 1) {
            ev = EV_RIGHT;
        }

        if (key == 2) {
            ev = EV_LEFT;
        }
        if (key == 3) {
            ev = EV_UP;
        }

        if (key == 4) {
            ev = EV_DOWN;
        }

        if (key == 5) {
            ev = EV_ENTER;
        }
    }

//protocolo para alterar os valores de alarme por meio de comunica��o serial
    serialTest = serialRead();
    if (serialTest != 0) {
        if ((serialTest == 'C') || (getPos() > 29)) {//caso enviado C come�a o protocolo
            setPos(0);
        }
        if((serialTest == '1')||(serialTest == '2')||(serialTest == 'L')||(serialTest == 'H')||(serialTest == '3')||(serialTest == '4')||(serialTest == '5')||(serialTest == '6')||(serialTest == '7')||(serialTest == '8')||(serialTest == '9')||(serialTest == '0')||(serialTest == 'F')){
        buffer[getPos()] = serialTest;//salva letras e n�meros enviados em um vetor
        setPos(getPos() + 1);
        }

        if ((serialTest == 'F') && (getPos() > 1)) {//recebeu F acabou o protocolo
            setPos(0);
            int level;
            level = (((buffer[3] - 48)*100) + ((buffer[4] - 48)*10) + ((buffer[5] - 48)*1));//convers�o ascii para int
            if ((buffer[7] == 'F')) {//configurando o alarme requisitado
                if ((buffer[0] == 'C')&&(buffer[1] == '1')&&(buffer[2] == 'L')) {
                    setAlarmLevel_1_Low(level);
                }
                if ((buffer[0] == 'C')&&(buffer[1] == '1')&&(buffer[2] == 'H')) {
                    setAlarmLevel_1_High(level);
                }
                if ((buffer[0] == 'C')&&(buffer[1] == '2')&&(buffer[2] == 'L')) {
                    setAlarmLevel_2_Low(level);
                }
                if ((buffer[0] == 'C')&&(buffer[1] == '2')&&(buffer[2] == 'H')) {
                    setAlarmLevel_2_High(level);
                }
            }
        }
    }

    //serial com a mesma fun��o dos bot�es
    if (serialTest == 'D' || serialTest == 'd') {
        ev = EV_RIGHT;
    }
    if (serialTest == 'A' || serialTest == 'a') {
        ev = EV_LEFT;
    }
    if (serialTest == 'W' || serialTest == 'w') {
        ev = EV_UP;
    }

    if (serialTest == 'S' || serialTest == 's') {
        ev = EV_DOWN;
    }
    if (serialTest == 'E' || serialTest == 'e') {
        ev = EV_ENTER;
    }

    key_ant = key;
    return ev;//envia o evento
}
