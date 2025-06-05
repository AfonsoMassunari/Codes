#include "serial.h"
#include <pic18f4520.h>
#include "io.h"
#include "bits.h"

void serialSend(unsigned char c) {
    while (!bitTst(PIR1, 4)); //aguarda o registro ficar disponível
    TXREG = c; //coloca o valor para ser enviado
}

unsigned char serialRead(void) {
    char resp = 0;

    if (bitTst(RCSTA, 1)) //Verifica se há erro de overrun e reseta a serial
    {
        bitClr(RCSTA, 4);
        bitSet(RCSTA, 4);
    }

    if (bitTst(PIR1, 5)) //Verifica se existe algum valor disponivel
    {
        resp = RCREG; //retorna o valor
    }
    return resp; //retorna zero


}

void serialInit(void) {
    TXSTA = 0b00101100; //configura a transmissão de dados da serial
    RCSTA = 0b10010000; //configura a recepção de dados da serial
    BAUDCON = 0b00001000; //configura sistema de velocidade da serial
    SPBRGH = 0; //configura para 56k
    SPBRG = 34; //configura para 56k
    bitSet(TRISC, 6); //pino de recepção de dados
    bitSet(TRISC, 7); //pino de envio de dados
}

void serialInt(int val) {//envia um inteiro por serial
    if (val < 0) {
        val = val * (-1);
        serialSend('-');
    }
    serialSend((val / 10000) % 10 + 48);
    serialSend((val / 1000) % 10 + 48);
    serialSend((val / 100) % 10 + 48);
    serialSend((val / 10) % 10 + 48);
    serialSend((val / 1) % 10 + 48);

}

void serial_string(const char *str) {//envia uma string por serial
    while(*str) {
        serialSend(*str++);
    }
}

void serial_string2(char msg[]){//envia uma string por serial
    int i = 0 ;
    while(msg[i] != 0 ){
        serialSend(msg[i]);
    }
    i++;
}