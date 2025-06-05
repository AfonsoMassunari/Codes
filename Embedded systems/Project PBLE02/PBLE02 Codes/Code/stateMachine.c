#include "var.h"
#include "stateMachine.h"
#include "event.h"
#include "output.h"
#include "ds1307.h"
#include "pic18f4550.h"
#include "control.h"
#include "adc.h"

void smInit(void) {
    setState(STATE_TEMPO);
    TRISB &= 0b00001111;
}

void smLoop(void) {
    unsigned char evento;
    int ad2read;
    //m�quina de estados
    evento = eventRead();//leitura do serial e do teclado
    ad2read = adcRead(2)/4;//leitura do pino anal�gico  
    controlSet(ad2read);//verifica��o de alarme
    
    switch (getState()) {//m�quina de estados
        case STATE_ALARME_1:
            //gest�o da maquina de estado
            if (evento == EV_RIGHT) {
                setState(STATE_ALARME_1_Low);
            }
            if (evento == EV_LEFT) {
                setState(STATE_TEMPO);
            }
            break;

        case STATE_ALARME_1_Low:
            //execu��o de atividade
            if (evento == EV_UP) {
                setAlarmLevel_1_Low(getAlarmLevel_1_Low() + 1);
            }
            if (evento == EV_DOWN) {
                setAlarmLevel_1_Low(getAlarmLevel_1_Low() - 1);
            }

            //gest�o da maquina de estado
            if (evento == EV_RIGHT) {
                setState(STATE_ALARME_1_High);
            }
            if (evento == EV_LEFT) {
                setState(STATE_ALARME_1);
            }
            break;


        case STATE_ALARME_1_High:
            //execu��o de atividade
            if (evento == EV_UP) {
                setAlarmLevel_1_High(getAlarmLevel_1_High() + 1);
            }
            if (evento == EV_DOWN) {
                setAlarmLevel_1_High(getAlarmLevel_1_High() - 1);
            }

            //gest�o da maquina de estado
            if (evento == EV_RIGHT) {
                setState(STATE_ALARME_2);
            }
             if (evento == EV_LEFT) {
                setState(STATE_ALARME_1_Low);
            }
            break;

        case STATE_ALARME_2:
            //gest�o da maquina de estado
            if (evento == EV_RIGHT) {
                setState(STATE_ALARME_2_Low);
            }
            if (evento == EV_LEFT) {
                setState(STATE_ALARME_1_High);
            }
            break;

        case STATE_ALARME_2_Low:
            //execu��o de atividade
            if (evento == EV_UP) {
                setAlarmLevel_2_Low(getAlarmLevel_2_Low() + 1);
            }
            if (evento == EV_DOWN) {
                setAlarmLevel_2_Low(getAlarmLevel_2_Low() - 1);
            }

            //gest�o da maquina de estado
            if (evento == EV_RIGHT) {
                setState(STATE_ALARME_2_High);
            }
            if (evento == EV_LEFT) {
                setState(STATE_ALARME_2);
            }
            break;

        case STATE_ALARME_2_High:
            //execu��o de atividade
            if (evento == EV_UP) {
                setAlarmLevel_2_High(getAlarmLevel_2_High() + 1);
            }
            if (evento == EV_DOWN) {
                setAlarmLevel_2_High(getAlarmLevel_2_High() - 1);
            }

            //gest�o da maquina de estado
            if (evento == EV_RIGHT) {
                setState(STATE_IDIOMA);
            }
              if (evento == EV_LEFT) {
                setState(STATE_ALARME_2_Low);
            }
            break;

        case STATE_IDIOMA:

            //execu��o de atividade
            if (evento == EV_UP) {
                setLanguage(getLanguage() + 1);
            }
            if (evento == EV_DOWN) {
                setLanguage(getLanguage() - 1);
            }

            //gest�o da maquina de estado
            if (evento == EV_RIGHT) {
                setState(STATE_TEMPO);
            }
            if (evento == EV_LEFT) {
                setState(STATE_ALARME_2_High);
            }
            break;


        case STATE_TEMPO:
            //execu��o de atividade
            if (evento == EV_UP) {
                setMinutes(getMinutes() + 1);
            }
            if (evento == EV_DOWN) {
                setMinutes(getMinutes() - 1);
            }

            //gest�o da maquina de estado
            if (evento == EV_RIGHT) {
                setState(STATE_ALARME_1);
            }
            if (evento == EV_LEFT) {
                setState(STATE_IDIOMA);
            }
            break;



    }
    outputPrint(getState(), getLanguage());
}
