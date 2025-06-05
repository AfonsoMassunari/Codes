/* 
 * File:   stateMachine.h
 * Author: Avell
 *
 * Created on 18 de Junho de 2017, 22:17
 */

#ifndef STATEMACHINE_H
#define	STATEMACHINE_H



enum {
    STATE_TEMPO,
    STATE_ALARME_1,
    STATE_ALARME_1_Low,
    STATE_ALARME_1_High,
    STATE_ALARME_2,
    STATE_ALARME_2_Low,
    STATE_ALARME_2_High,
    STATE_IDIOMA,
    STATE_FIM,
};


void smInit(void);
void smLoop(void);


#endif	/* STATEMACHINE_H */

