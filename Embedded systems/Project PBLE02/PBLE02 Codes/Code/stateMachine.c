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
    //máquina de estados
    evento = eventRead();//leitura do serial e do teclado
    ad2read = adcRead(2)/4;//leitura do pino analógico  
    controlSet(ad2read);//verificação de alarme
    
    switch (getState()) {//máquina de estados
        case STATE_ALARME_1:
            //gestão da maquina de estado
            if (evento == EV_RIGHT) {
                setState(STATE_ALARME_1_Low);
            }
            if (evento == EV_LEFT) {
                setState(STATE_TEMPO);
            }
            break;

        case STATE_ALARME_1_Low:
            //execução de atividade
            if (evento == EV_UP) {
                setAlarmLevel_1_Low(getAlarmLevel_1_Low() + 1);
            }
            if (evento == EV_DOWN) {
                setAlarmLevel_1_Low(getAlarmLevel_1_Low() - 1);
            }

            //gestão da maquina de estado
            if (evento == EV_RIGHT) {
                setState(STATE_ALARME_1_High);
            }
            if (evento == EV_LEFT) {
                setState(STATE_ALARME_1);
            }
            break;


        case STATE_ALARME_1_High:
            //execução de atividade
            if (evento == EV_UP) {
                setAlarmLevel_1_High(getAlarmLevel_1_High() + 1);
            }
            if (evento == EV_DOWN) {
                setAlarmLevel_1_High(getAlarmLevel_1_High() - 1);
            }

            //gestão da maquina de estado
            if (evento == EV_RIGHT) {
                setState(STATE_ALARME_2);
            }
             if (evento == EV_LEFT) {
                setState(STATE_ALARME_1_Low);
            }
            break;

        case STATE_ALARME_2:
            //gestão da maquina de estado
            if (evento == EV_RIGHT) {
                setState(STATE_ALARME_2_Low);
            }
            if (evento == EV_LEFT) {
                setState(STATE_ALARME_1_High);
            }
            break;

        case STATE_ALARME_2_Low:
            //execução de atividade
            if (evento == EV_UP) {
                setAlarmLevel_2_Low(getAlarmLevel_2_Low() + 1);
            }
            if (evento == EV_DOWN) {
                setAlarmLevel_2_Low(getAlarmLevel_2_Low() - 1);
            }

            //gestão da maquina de estado
            if (evento == EV_RIGHT) {
                setState(STATE_ALARME_2_High);
            }
            if (evento == EV_LEFT) {
                setState(STATE_ALARME_2);
            }
            break;

        case STATE_ALARME_2_High:
            //execução de atividade
            if (evento == EV_UP) {
                setAlarmLevel_2_High(getAlarmLevel_2_High() + 1);
            }
            if (evento == EV_DOWN) {
                setAlarmLevel_2_High(getAlarmLevel_2_High() - 1);
            }

            //gestão da maquina de estado
            if (evento == EV_RIGHT) {
                setState(STATE_IDIOMA);
            }
              if (evento == EV_LEFT) {
                setState(STATE_ALARME_2_Low);
            }
            break;

        case STATE_IDIOMA:

            //execução de atividade
            if (evento == EV_UP) {
                setLanguage(getLanguage() + 1);
            }
            if (evento == EV_DOWN) {
                setLanguage(getLanguage() - 1);
            }

            //gestão da maquina de estado
            if (evento == EV_RIGHT) {
                setState(STATE_TEMPO);
            }
            if (evento == EV_LEFT) {
                setState(STATE_ALARME_2_High);
            }
            break;


        case STATE_TEMPO:
            //execução de atividade
            if (evento == EV_UP) {
                setMinutes(getMinutes() + 1);
            }
            if (evento == EV_DOWN) {
                setMinutes(getMinutes() - 1);
            }

            //gestão da maquina de estado
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
